# Mosquitto Example

[MQTT](https://mqtt.org/) publisher and subscriber example using [Eclipse Mosquitto](https://mosquitto.org/)

## Quick Start

- Install Eclipse Mosquitto [here](https://mosquitto.org/download/).
- Build from the source code.
  ```bash
  $ mkdir -p build && cd build
  $ cmake ..
  $ make
  ```
- Run any of the publishers and subscriber on different terminal.
  ```bash
  $ ./temperature_publisher
  # or
  $ ./people_count_publisher
  # or
  $ ./fan_speed_publisher
  ```
  ```bash
  $ ./subscriber
  ```