
cmake_minimum_required (VERSION 3.8)

project ("Wrapper")

add_executable (Wrapper "engine.cpp" "engine.h" "wrapper.h" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

