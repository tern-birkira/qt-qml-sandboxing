# modules/commontypes/CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(common_types LANGUAGES CXX)

qt_add_qml_module(common_types
    URI "TrackLabel.Common"
    VERSION 1.0
    NO_PLUGIN                # Kept as a static or shared linking target
    CLASSNAME CommonTypesMoc
    HEADERS
        types.h
)
