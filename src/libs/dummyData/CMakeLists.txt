

add_library(TrackLabelFieldDummyData STATIC
    dummydata.h
    dummydata.cpp
)

# Expose headers (needed for .cpp imports of other files)
target_include_directories(TrackLabelFieldDummyData
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)