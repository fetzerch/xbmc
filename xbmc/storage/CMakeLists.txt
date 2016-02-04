set(SOURCES AutorunMediaJob.cpp
            cdioSupport.cpp
            DetectDVDType.cpp
            IoSupport.cpp
            MediaManager.cpp)

set(HEADERS AutorunMediaJob.h
            cdioSupport.h
            DetectDVDType.h
            IoSupport.h
            IStorageProvider.h
            MediaManager.h)

core_add_library(storage)

if(ENABLE_INTERNAL_FFMPEG)
  add_dependencies(storage ffmpeg)
endif()

if(NOT CMAKE_SYSTEM_NAME MATCHES "Windows")
  add_dependencies(storage dvdnav)
endif()
