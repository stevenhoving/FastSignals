cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(FastSignals)

option(LIBFASTSIGNALS_ENABLE_TEST "Enable unit testing" ON)

# Use `-DBUILD_TESTING=OFF` to disable testing/benchmarking.
enable_testing()

include(cmake/functions.cmake)

add_subdirectory(libfastsignals)

if(LIBFASTSIGNALS_ENABLE_TEST)
  add_subdirectory(tests)
endif()
