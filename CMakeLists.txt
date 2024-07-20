# CMakeLists.txt in the root directory

cmake_minimum_required(VERSION 3.14)

project( LogByThread LANGUAGES CXX)

option(LOG_BY_THREAD_BUILD_DEMO "Build the demo" OFF)

# Add the include directory for the EasyQSettings library
add_subdirectory(include)

# Add the demo directory
add_subdirectory(demo)