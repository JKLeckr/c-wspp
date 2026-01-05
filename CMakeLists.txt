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

if(APPLE)
  set(OPENSSL_USE_STATIC_LIBS TRUE)
endif()

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

add_library(asio INTERFACE)
target_include_directories(asio
  INTERFACE lib/asio/asio/include
)
target_compile_definitions(asio
  INTERFACE
    ASIO_STANDALONE
)
target_link_libraries(asio
  INTERFACE
    Threads::Threads
    OpenSSL::SSL
)

add_library(websocketpp INTERFACE)
target_include_directories(websocketpp INTERFACE lib/websocketpp)
target_compile_definitions(websocketpp
  INTERFACE
    _WEBSOCKETPP_CPP11_THREAD_
)
target_link_libraries(websocketpp
  INTERFACE
    Threads::Threads
    OpenSSL::SSL
    ZLIB::ZLIB
)

add_library(c-wspp SHARED src/c-wspp.cpp)

set_target_properties(c-wspp
  PROPERTIES
    PREFIX ""
    IMPORT_PREFIX ""
)

target_sources(c-wspp
  PRIVATE
    src/config.hpp
    src/ClientWebSocket.hpp
    src/c-wspp.cpp

  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS
      include
    FILES
      include/c-wspp.h
)

target_link_libraries(c-wspp
  PRIVATE
    Threads::Threads
    OpenSSL::SSL
    ZLIB::ZLIB
    asio
    websocketpp
)

if (WIN32)
  target_compile_definitions(c-wspp
    PRIVATE
      WIN32_LEAN_AND_MEAN
      C_WSPP_BUILD
  )
  
  target_link_libraries(c-wspp
    PRIVATE
      ws2_32
      crypt32
  )
endif()

add_executable(c-wspp-test EXCLUDE_FROM_ALL test/test.c)
target_link_libraries(c-wspp-test PRIVATE c-wspp)
enable_testing()

add_test(
  NAME c-wspp-test
  COMMAND $<TARGET_FILE:c-wspp-test>
)
add_custom_target(check
  COMMAND ${CMAKE_CTEST_COMMAND}
  DEPENDS c-wspp-test
)
