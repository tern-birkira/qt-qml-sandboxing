#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "editor_grid.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // Dummy data: all known track label fields keyed by field-name.
    QMap<QString, LabelField> fields = createDummyLabelFields(&app);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qt_qml_sandboxing", "Main");

    return QGuiApplication::exec();
}

