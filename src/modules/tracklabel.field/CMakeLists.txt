find_package(Qt6 REQUIRED COMPONENTS Core Qml)

qt_add_qml_module(TrackLabelFieldLib
    URI TrackLabel.Models
    VERSION 1.0
    QML_FILES 
        qmldummy.qml
    SOURCES
        FieldAppearance.h   FieldAppearance.cpp
        FieldInterface.h   FieldInterface.cpp
        FieldLayout.h   FieldLayout.cpp
        FieldText.h   FieldText.cpp
)

target_link_libraries(TrackLabelModelsLib
    PUBLIC
        Qt6::Core
        Qt6::Qml
    PRIVATE
        common_types
)

# # Expose headers (needed for .cpp imports of other files)
# target_include_directories(TrackLabelModels
#     PUBLIC
#         ${CMAKE_CURRENT_SOURCE_DIR}
# )