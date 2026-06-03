// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "contactstablemodel.h"
#include "contactstransposeproxymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ContactsTableModel contactsTableModel;
    ContactsTransposeProxyModel transposeModel;

    transposeModel.setSourceModel(&contactsTableModel);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.setInitialProperties({{"contactsTableModel", QVariant::fromValue(&contactsTableModel)},
                                 {"transposeModel", QVariant::fromValue(&transposeModel)}});
    engine.loadFromModule("CppModelsViews_Section6", "Main");

    return app.exec();
}
