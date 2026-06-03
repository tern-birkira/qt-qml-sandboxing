// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CONTACTSIDENTITYPROXYMODEL_H
#define CONTACTSIDENTITYPROXYMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QIdentityProxyModel>

#include "contactslistmodel.h"

class ContactsIdentityProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("ContactsIdentityProxyModel must be instantiated in C++")
public:
    explicit ContactsIdentityProxyModel(QObject *parent = nullptr);
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // CONTACTSIDENTITYPROXYMODEL_H
