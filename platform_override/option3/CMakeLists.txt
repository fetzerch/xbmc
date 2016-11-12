cmake_minimum_required(VERSION 3.3)


# Project starts here
# override with -DPLATFORM=android for testing
project(platform_override)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(PLATFORM linux CACHE STRING "The platform we build for")

set(SOURCES main.cpp settings.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM=${PLATFORM})
