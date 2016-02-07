set(SOURCES PVRRecording.cpp
            PVRRecordings.cpp)

set(HEADERS PVRRecording.h
            PVRRecordings.h)

core_add_library(pvr_recordings)
add_dependencies(pvr_recordings libcpluff)
