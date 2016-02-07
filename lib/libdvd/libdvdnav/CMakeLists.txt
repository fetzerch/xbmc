cmake_minimum_required(VERSION 3.0)
project(dvdnav VERSION 4.2.1)

set(SOURCES src/dvdnav.c
            src/highlight.c
            src/navigation.c
            src/read_cache.c
            src/remap.c
            src/searching.c
            src/settings.c
            src/vm/decoder.c
            src/vm/vm.c
            src/vm/vmcmd.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_definitions(${PROJECT_NAME} PRIVATE VERSION="${PROJECT_VERSION}")
target_link_libraries(${PROJECT_NAME} PRIVATE dvdread)
