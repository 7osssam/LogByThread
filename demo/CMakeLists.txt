# demo/CMakeLists.txt

cmake_minimum_required(VERSION 3.14)

# Set the project name
project(demo LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Concurrent) # Qt6::Concurrent

# Add executable with all source files
add_executable(${PROJECT_NAME}
  main.cpp
)

# Link the EasyQSettings library
target_link_libraries(${PROJECT_NAME} LogByThread_lib)

# Link Qt libraries
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${PROJECT_NAME} Qt${QT_VERSION_MAJOR}::Concurrent) # Qt6::Concurrent

# Install rules
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)