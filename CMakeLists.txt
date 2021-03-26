cmake_minimum_required(VERSION 3.1.0)
project(meminfo)

file(STRINGS "${PROJECT_SOURCE_DIR}/VERSION" VERSION)
string(REGEX REPLACE "([0-9]+)\\.[0-9]+\\.[0-9]+.*" "\\1" VERSION_MAJOR ${VERSION})
string(REGEX REPLACE "[0-9]+\\.([0-9])+\\.[0-9]+.*" "\\1" VERSION_MINOR ${VERSION})
string(REGEX REPLACE "[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH ${VERSION})

message(STATUS "${PROJECT_NAME} version: ${VERSION}")
configure_file("${PROJECT_SOURCE_DIR}/version.h.in" "${PROJECT_SOURCE_DIR}/src/version.h")

include(FindPkgConfig)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES} pthread)

install(TARGETS ${PROJECT_NAME} DESTINATION /bin)
