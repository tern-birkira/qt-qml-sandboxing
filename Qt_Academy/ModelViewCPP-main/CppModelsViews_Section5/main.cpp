// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "contactslistmodel.h"
#include "contactsfilterproxymodel.h"
#include "contactssortproxymodel.h"
#include "contactsidentityproxymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ContactsListModel contactsListModel;
    ContactsFilterProxyModel filterModel;
    ContactsSortProxyModel sortModel;
    ContactsIdentityProxyModel identityModel;

    filterModel.setSourceModel(&contactsListModel);
    sortModel.setSourceModel(&filterModel);
    identityModel.setSourceModel(&sortModel);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.setInitialProperties({{"contactsListModel", QVariant::fromValue(&contactsListModel)},
                                 {"filterModel", QVariant::fromValue(&filterModel)},
                                 {"sortModel", QVariant::fromValue(&sortModel)},
                                 {"identityModel", QVariant::fromValue(&identityModel)}});
    engine.loadFromModule("CppModelsViews_Section5", "Main");

    return app.exec();
}
