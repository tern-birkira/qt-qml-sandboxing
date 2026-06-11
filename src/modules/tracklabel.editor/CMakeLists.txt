find_package(Qt6 REQUIRED COMPONENTS Qml Core)

set(CMAKE_AUTOMOC ON)

add_subdirectory(models)
add_subdirectory(ui)


qt_add_qml_module(TrackLabel
    URI TrackLabel
    VERSION 1.0
    QML_FILES
        MainTrackLabel.qml
)

target_link_libraries(TrackLabelplugin
    PRIVATE
        TrackLabelModels
        TrackLabelUI
)

target_include_directories(TrackLabelplugin
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/models
)