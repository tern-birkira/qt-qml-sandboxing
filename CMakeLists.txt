cmake_minimum_required(VERSION 3.16)

project(qt_qml_sandboxing VERSION 0.1 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/home/birkira/Qt/6.11.1/gcc_64")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(QT_QML_GENERATE_QMLLS_INI ON)




find_package(Qt6 REQUIRED COMPONENTS Quick)
add_subdirectory(src/modules/tracklabel)
add_subdirectory(src/libs/dummyData)


qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable("app${PROJECT_NAME}" src/main.cpp)

qt6_add_qml_module("app${PROJECT_NAME}"
    URI sandboxing
    QML_FILES src/Main.qml
)


# Only enable for Debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(appqt_qml_sandboxing PRIVATE QT_QML_DEBUG)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqt_qml_sandboxing PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt_qml_sandboxing
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries("app${PROJECT_NAME}"
    PRIVATE
        Qt6::Quick
        Qt6::Qml
        Qt6::Core
        TrackLabel
)

target_include_directories("app${PROJECT_NAME}" PRIVATE src/models)

install(TARGETS appqt_qml_sandboxing
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
