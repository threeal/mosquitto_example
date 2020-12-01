cmake_minimum_required(VERSION 3.10)

project(mosquitto_example)

add_executable(publisher publisher.cpp)
target_link_libraries(publisher mosquitto)

add_executable(subscriber subscriber.cpp)
target_link_libraries(subscriber mosquitto)