#include <iostream>
#include <mosquitto.h>
#include <signal.h>
#include <sstream>
#include <unistd.h>

static bool alive = true;
static bool connected = false;

void handle_signal(int s)
{
  alive = false;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
  std::cout << "Connected to MQTT broker" << std::endl;
  connected = true;
}

int main(int argc, char *argv[])
{
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);

  mosquitto_lib_init();

  struct mosquitto *mosq = mosquitto_new("people_count_publisher", true, NULL);

  if (mosq)
  {
    mosquitto_connect_callback_set(mosq, connect_callback);

    int rc = mosquitto_connect(mosq, "localhost", 1883, 60);

    while (alive)
    {
      if (alive && rc) {
        connected = false;
        mosquitto_reconnect(mosq);
      }

      if (connected)
      {
        std::stringstream ss;

        int random = (rand() % 3) + 1;
        ss << random;

        auto message = ss.str();

        rc = mosquitto_publish(
          mosq, NULL, "sensor/people_count", message.size(), message.c_str(), 0, true
        );

        if (!rc) {
          std::cout << "Published: " << message << std::endl;
          sleep(5);
        }
      }

      rc = mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);
  }

  mosquitto_lib_cleanup();

  return 0;
}