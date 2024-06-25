# include/CMakeLists.txt

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# Define the library target (assuming the library name is LogByThread)
add_library(LogByThread_lib  # Renamed to avoid confusion with the target name
    logger.cpp
    logger.h
    logworker.cpp
    logworker.h
)

# Set include directories for the library
target_include_directories(LogByThread_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link any necessary libraries (e.g., Qt if required)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS  Core Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS  Core Concurrent )
target_link_libraries(LogByThread_lib PRIVATE  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent)
