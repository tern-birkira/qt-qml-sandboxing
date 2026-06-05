cmake_minimum_required(VERSION 3.16)
project(LayoutEditor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_add_executable(LayoutEditor
    cpp/main.cpp
    cpp/TrackLabelField.h
    cpp/RowCellModel.h
    cpp/RowCellModel.cpp
    cpp/RowListModel.h
    cpp/RowListModel.cpp
)

qt_add_qml_module(LayoutEditor
    URI LayoutEditor
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/RowContainer.qml
        qml/TrackLabelField.qml
)

target_link_libraries(LayoutEditor PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)
