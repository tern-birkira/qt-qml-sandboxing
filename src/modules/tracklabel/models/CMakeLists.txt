# Add this at the top
find_package(Qt6 REQUIRED COMPONENTS Core Qml)

# Create static library for models
add_library(TrackLabelModels STATIC
    tracklabel.h
    tracklabel.cpp
)

target_link_libraries(TrackLabelModels
    PUBLIC
        Qt6::Core
        Qt6::Qml
)

# Expose headers (needed for .cpp imports of other files)
target_include_directories(TrackLabelModels
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)