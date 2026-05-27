#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "models/editor_grid.h"
#include <QQmlContext>

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

    // EditorTrackLabelModel trackLabel;
    // engine.rootContext()->setContextProperty("trackLabel", &trackLabel);


    return QGuiApplication::exec();
}

