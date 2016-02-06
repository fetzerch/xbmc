set(SOURCES main.cpp)

if(NOT CORE_SYSTEM_NAME STREQUAL windows)
  list(APPEND SOURCES MessagePrinter.cpp)
endif()

core_add_library(platform_posix)
