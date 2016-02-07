cmake_minimum_required(VERSION 3.0)
project(dvdcss VERSION 1.2.13)

include(CheckIncludeFiles)
include(CheckStructHasMember)
include(CheckSymbolExists)

check_include_files(errno.h HAVE_ERRNO_H)
check_include_files(fnctl.h HAVE_FNCTL_H)
check_include_files(io.h HAVE_IO_H)
check_include_files(inttypes.h HAVE_INTTYPES_H)
check_include_files(limits.h HAVE_LIMITS_H)
check_include_files(pwd.h HAVE_PWD_H)
check_include_files(stdint.h HAVE_STDINT_H)
check_include_files(sys/param.h HAVE_SYS_PARAM_H)
check_include_files(sys/stat.h HAVE_SYS_STAT_H)
check_include_files(sys/types.h HAVE_SYS_TYPES_H)
check_include_files(sys/uio.h HAVE_SYS_UIO_H)
check_include_files(unistd.h HAVE_SYS_UNISTD_H)

check_struct_has_member(dvd_struct type linux/cdrom.h HAVE_LINUX_DVD_STRUCT)
check_symbol_exists(O_BINARY "fcntl.h;sys/types.h;sys/stat.h" HAVE_O_BINARY)
check_include_files(IOKit/storage/IODVDMediaBSDClient.h DARWIN_DVD_IOCTL)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)

set(SOURCES src/css.c
            src/error.c
            src/device.c
            src/ioctl.c
            src/libdvdcss.c)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_compile_definitions(${PROJECT_NAME} INTERFACE HAVE_DVDCSS_DVDCSS_H)
if(APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework CoreFoundation"
                                                "-framework IOKit")
endif()
