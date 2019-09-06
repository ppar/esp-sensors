cmake_minimum_required(VERSION 3.8)
project(arduino_dht)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        arduino/arduino.ino
        arduino/parameters.example.h
        arduino/parameters.h
        README.md)

add_executable(arduino_dht ${SOURCE_FILES})

