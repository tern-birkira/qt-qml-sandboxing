#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "models/editor_grid.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("birkis.models", "Main");

    // EditorTrackLabelModel trackLabel;
    // engine.rootContext()->setContextProperty("trackLabel", &trackLabel);


    return QGuiApplication::exec();
}

