set(SOURCES WinEvents.cpp
            WinSystem.cpp)

set(HEADERS WindowingFactory.h
            WinEvents.h
            WinSystem.h
            XBMC_events.h)

# TODO: Move to X11?
if(CORE_SYSTEM_NAME STREQUAL linux AND NOT MIR_FOUND)
  list(APPEND SOURCES WinEventsLinux.cpp)
  list(APPEND HEADERS WinEventsLinux.h)
endif()

core_add_library(windowing)
