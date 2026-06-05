find_package(Qt6 REQUIRED COMPONENTS Qml Quick Core)

# REQUIRED: enables metatype generation for qt_add_qml_module
set(CMAKE_AUTOMOC ON)

qt_add_qml_module(TrackLabelUI
    URI TrackLabel.UI
    VERSION 1.0
    QML_FILES
        RowContainer.qml
        TrackLabelField.qml
        TrackLabel.qml
)

target_link_libraries(TrackLabelUI
    PRIVATE
        Qt6::Quick
        TrackLabelModels
)
