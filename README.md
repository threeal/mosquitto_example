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
- Run both `publisher` and `subscriber` on different terminal.
  ```bash
  $ ./publisher
  ```
  ```bash
  $ ./subscriber
  ```