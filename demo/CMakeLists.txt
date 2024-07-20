# demo/CMakeLists.txt

set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "" )


set(EXEC_NAME ${PROJECT_NAME}-demo)

message(STATUS "Configuring ${EXEC_NAME}")

file(GLOB EXEC_HEADERS
  "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp")

file(GLOB EXEC_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")


source_group("header" FILES ${EXEC_HEADERS})
source_group("src" FILES ${EXEC_SOURCES})



# Add executable with all source files
add_executable(${EXEC_NAME} ${EXEC_HEADERS} ${EXEC_SOURCES})

target_include_directories(${EXEC_NAME} PRIVATE
						${CMAKE_CURRENT_SOURCE_DIR}
						${CMAKE_CURRENT_SOURCE_DIR}/../include
						)

target_link_libraries(${EXEC_NAME} PRIVATE ${PROJECT_NAME})

# Link Qt libraries
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Concurrent) # Qt6::Concurrent
target_link_libraries(${EXEC_NAME} PRIVATE  Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Concurrent)


set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Install rules
include(GNUInstallDirs)
install(TARGETS ${EXEC_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)