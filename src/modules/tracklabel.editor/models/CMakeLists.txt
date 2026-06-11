find_package(Qt6 REQUIRED COMPONENTS Core Qml)

# # Create static library for models
# add_library(TrackLabelModels STATIC
#     RowCellModel.h
#     RowCellModel.cpp
#     RowListModel.h
#     RowListModel.cpp
#     TrackLabelField.h
# )

qt_add_qml_module(TrackLabelModels
    URI TrackLabel.Models
    VERSION 1.0
    SOURCES
        RowCellModel.h  RowCellModel.cpp
        RowListModel.h  RowListModel.cpp
        TrackLabelFieldEditor.h  TrackLabelFieldEditor.cpp
)

target_link_libraries(TrackLabelModels
    PUBLIC
        Qt6::Core
        Qt6::Qml
        TrackLabelFieldLib
    PRIVATE
        common_types
)

# # Expose headers (needed for .cpp imports of other files)
# target_include_directories(TrackLabelModels
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}
# )