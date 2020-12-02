#include <cstring>
#include <mosquitto.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static bool alive = true;
static bool connected = false;

void handle_signal(int s)
{
  alive = false;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
  printf("Connected to MQTT broker\n");
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
        char buffer[32];
        int random = (rand() % 3) + 1;
        sprintf(buffer, "%d", random);

        rc = mosquitto_publish(
          mosq, NULL, "sensor/people_count", sizeof(buffer), buffer, 0, true
        );

        if (!rc) {
          printf("Published: %s\n", buffer);
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