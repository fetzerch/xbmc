cmake_minimum_required(VERSION 3.3)


# Marks header file as being overridden on a certain list of platforms.
#
# This avoids globbing as overriding for a new platform has to me marked explicitly,
# CMakeFile is touched and project is reconfigured.
#
# Usage: add_override(${PROJECT_NAME} settings.h PLATFORMS android linux osx)
function(add_override target filename)
  cmake_parse_arguments(ARG "" "" "PLATFORMS" ${ARGN})
  if(NOT ARG_PLATFORMS)
    message(FATAL_ERROR "Missing parameter PLATFORMS")
  endif()

  if(${PLATFORM} IN_LIST ARG_PLATFORMS)
    message(STATUS "Override active for ${filename} on ${PLATFORM}")

    # Set define so that the _override.h get's included
    target_compile_definitions(${target} PRIVATE SETTINGS_OVERRIDE)

    # Copy right _override.h in place
    string(REPLACE ".h" "_override.h" ${override_file} ${filename})
    configure_file(overrides/${PLATFORM}/${filename} ${override_file} COPYONLY)
  else()
    message(STATUS "Override disabled for ${filename}, using generic implementation")
  endif()
endfunction()


# Project starts here
# override with -DPLATFORM=android for testing
project(platform_override)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(PLATFORM linux CACHE STRING "The platform we build for")

set(SOURCES main.cpp settings.h)
add_executable(${PROJECT_NAME} ${SOURCES})
add_override(${PROJECT_NAME} settings.h PLATFORMS android)
