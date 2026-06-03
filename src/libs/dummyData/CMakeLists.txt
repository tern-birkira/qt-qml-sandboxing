
find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

add_library(TrackLabelFieldDummyData STATIC
    DummyTrackLabelData.h
    DummyTrackLabelData.cpp
)

target_link_libraries(TrackLabelFieldDummyData
    PRIVATE 
        Qt6::Quick
        Qt6::Core
        TrackLabelModels        
)


# Expose headers (needed for .cpp imports of other files)
target_include_directories(TrackLabelFieldDummyData
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)