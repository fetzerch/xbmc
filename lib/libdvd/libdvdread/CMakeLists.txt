cmake_minimum_required(VERSION 3.0)
project(dvdread)

include(CheckIncludeFiles)

check_include_files(dlfcn.h HAVE_DLFCN_H)
check_include_files(limits.h HAVE_LIMITS_H)
check_include_files(sys/param.h HAVE_SYS_PARAM_H)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(SOURCES src/bitreader.c
            src/dvd_input.c
            src/dvd_reader.c
            src/dvd_udf.c
            src/ifo_print.c
            src/ifo_read.c
            src/md5.c
            src/nav_print.c
            src/nav_read.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)

if(TARGET dvdcss)
  target_link_libraries(${PROJECT_NAME} PRIVATE dvdcss)
endif()
