# CMakeLists.txt in the root directory

cmake_minimum_required(VERSION 3.14)

project( LogByThread_demo LANGUAGES CXX)


# Add the include directory for the EasyQSettings library
add_subdirectory(include)

# Add the demo directory
add_subdirectory(demo)