# include/CMakeLists.txt

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(LIBNAME ${PROJECT_NAME})

message(STATUS "Configuring ${LIBNAME}")

file(GLOB LIB_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

file(GLOB LIB_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")


source_group("header" FILES ${LIB_HEADERS})
source_group("src" FILES ${LIB_SOURCES})


add_library(${LIBNAME} STATIC ${LIB_HEADERS} ${LIB_SOURCES}) # for dynamic library use SHARED

# Set include directories for the library
target_include_directories(${LIBNAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link any necessary libraries (e.g., Qt if required)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS  Core Concurrent)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS  Core Concurrent )
target_link_libraries(${LIBNAME} PRIVATE  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent)
target_link_libraries(${LIBNAME} PRIVATE ${QT_LIBRARIES})


install(TARGETS ${LIBNAME}
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin )