// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CONTACTSTRANSPOSEPROXYMODEL_H
#define CONTACTSTRANSPOSEPROXYMODEL_H

#include <QObject>
#include <QTransposeProxyModel>

#include "contactstablemodel.h"

class ContactsTransposeProxyModel : public QTransposeProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("ContactsTransposeProxyModel must be instantiated in C++")
public:
    explicit ContactsTransposeProxyModel(QObject *parent = nullptr);

signals:
};

#endif // CONTACTSTRANSPOSEPROXYMODEL_H
