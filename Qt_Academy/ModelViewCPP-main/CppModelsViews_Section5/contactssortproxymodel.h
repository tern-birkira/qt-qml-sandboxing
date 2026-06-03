// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CONTACTSSORTPROXYMODEL_H
#define CONTACTSSORTPROXYMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSortFilterProxyModel>

#include "contactslistmodel.h"

class ContactsSortProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("ContactsFilterProxyModel must be instantiated in C++")
public:
    explicit ContactsSortProxyModel(QObject *parent = nullptr);

protected:
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;
};

#endif // CONTACTSSORTPROXYMODEL_H
