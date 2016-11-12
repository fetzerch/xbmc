cmake_minimum_required(VERSION 3.3)


# Marks header file as being overridden on a certain list of platforms.
#
# Usage: add_override(${PROJECT_NAME} Settings.cmake settings.h PLATFORMS android linux osx)
function(add_override target cmakefile headerfile)
  cmake_parse_arguments(ARG "" "" "PLATFORMS" ${ARGN})
  if(NOT ARG_PLATFORMS)
    message(FATAL_ERROR "Missing parameter PLATFORMS")
  endif()

  # Include generic settings first
  include(${cmakefile})

  if(${PLATFORM} IN_LIST ARG_PLATFORMS)
    message(STATUS "Override active for ${cmakefile} on ${PLATFORM}")

    # Include override
    include(overrides/${PLATFORM}/${cmakefile})

  else()
    message(STATUS "Override disabled for ${cmakefile}, using generic implementation")
  endif()

  # Includes above pull in settings into cmake, now generate header
  configure_file(${headerfile}.in ${headerfile})
endfunction()


# Project starts here
# override with -DPLATFORM=android for testing
project(platform_override)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

set(PLATFORM linux CACHE STRING "The platform we build for")

set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
add_override(${PROJECT_NAME} Settings.cmake settings.h PLATFORMS android)
