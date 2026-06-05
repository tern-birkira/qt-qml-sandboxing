#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "RowListModel.h"
#include "RowCellModel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    // Register RowCellModel so QML can receive it as a typed pointer
    // (the Repeater only needs QAbstractListModel*, but explicit registration
    //  lets you cast and inspect in QML if needed)
    qmlRegisterUncreatableType<RowCellModel>(
        "LayoutEditor", 1, 0,
        "RowCellModel",
        "RowCellModel is created by RowListModel, not directly from QML"
    );

    qmlRegisterUncreatableType<RowListModel>(
        "LayoutEditor", 1, 0,
        "RowListModel",
        "RowListModel is instantiated in C++ and set on context"
    );

    QQmlApplicationEngine engine;

    // Create the single model instance and expose it to QML
    RowListModel layoutModel;
    engine.rootContext()->setContextProperty("layoutModel", &layoutModel);

    engine.load(QUrl(QStringLiteral("qrc:/qml/Main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
