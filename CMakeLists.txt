cmake_minimum_required(VERSION 3.22)

project(c-wspp)

# TODO: Remove this eventually when no longer needed (dependencies no longer target a deprecated version of cmake)
set_property(GLOBAL PROPERTY CMAKE_POLICY_VERSION_MINIMUM 3.22)

set_property(GLOBAL PROPERTY CMAKE_SKIP_INSTALL_RULES ON)
set_property(GLOBAL PROPERTY BUILD_RPATH_USE_ORIGIN ON)
set_property(GLOBAL PROPERTY CMAKE_COLOR_DIAGNOSTICS ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options(-fcolor-diagnostics)
endif()

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(asio INTERFACE)
target_include_directories(asio
  INTERFACE lib/asio/asio/include
)
target_compile_definitions(asio
  INTERFACE
    ASIO_STANDALONE
)
target_link_libraries(asio INTERFACE Threads)

add_subdirectory(lib/websocketpp)
add_library(Websockets INTERFACE)
target_include_directories(Websockets INTERFACE lib/websocketpp)
target_link_libraries(Websockets INTERFACE Threads)

add_library(c-wspp src/c-wspp.cpp)

target_link_libraries(c-wspp PRIVATE asio)
target_link_libraries(c-wspp PRIVATE Websockets)

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

if (WIN32)
  target_compile_definitions(c-wspp PRIVATE WIN32_LEAN_AND_MEAN)
endif()
