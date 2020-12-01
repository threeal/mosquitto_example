cmake_minimum_required(VERSION 3.10)

project(mosquitto_example)

add_executable(publisher src/publisher.cpp)
target_link_libraries(publisher mosquitto)

add_executable(subscriber src/subscriber.cpp)
target_link_libraries(subscriber mosquitto)