#include <cstring>
#include <iostream>
#include <mosquitto.h>
#include <signal.h>
#include <stdlib.h>

static bool alive = true;

void handle_signal(int s)
{
  alive = false;
}

void connect_callback(struct mosquitto *mosq, void *obj, int result)
{
  printf("Connected to MQTT broker\n");
}

void message_callback(struct mosquitto *mosq, void *obj,
    const struct mosquitto_message *message)
{
  if (!strcmp(message->topic, "sensor/temperature")) {
    std::cout << "Temperature: " << (char *)message->payload << std::endl;
  }

  if (!strcmp(message->topic, "sensor/people_count")) {
    std::cout << "People Count: " << (char *)message->payload << std::endl;
  }

  if (!strcmp(message->topic, "sensor/fan_speed")) {
    std::cout << "Fan Speed: " << (char *)message->payload << std::endl;
  }

  if (!strcmp(message->topic, "sensor/fan_speed")) {
    printf("Fan Speed: %s\n", (char *)message->payload);
  }
}

int main(int argc, char *argv[])
{
  signal(SIGINT, handle_signal);
  signal(SIGTERM, handle_signal);

  mosquitto_lib_init();

  struct mosquitto *mosq = mosquitto_new("subscriber", true, NULL);

  if (mosq)
  {
    mosquitto_connect_callback_set(mosq, connect_callback);
    mosquitto_message_callback_set(mosq, message_callback);

    int rc = mosquitto_connect(mosq, "localhost", 1883, 60);

    mosquitto_subscribe(mosq, NULL, "sensor/temperature", 0);
    mosquitto_subscribe(mosq, NULL, "sensor/people_count", 0);
    mosquitto_subscribe(mosq, NULL, "sensor/fan_speed", 0);

    while (alive)
    {
      if (alive && rc) {
        mosquitto_reconnect(mosq);
      }

      rc = mosquitto_loop(mosq, -1, 1);
    }

    mosquitto_destroy(mosq);
  }

  mosquitto_lib_cleanup();

  return 0;
}