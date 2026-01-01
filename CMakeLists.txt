cmake_minimum_required(VERSION 3.22)

project(c-wspp)

set_property(GLOBAL PROPERTY BUILD_RPATH_USE_ORIGIN ON)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Asio REQUIRED)
find_package(websocketpp REQUIRED)

add_library(c-wspp src/c-wspp.cpp)

target_link_libraries(c-wspp PRIVATE asio)
target_link_libraries(c-wspp PRIVATE websocketpp::websocketpp)

target_sources(c-wspp
  PRIVATE
    src/c-wspp.cpp

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/c-wspp.h
)
