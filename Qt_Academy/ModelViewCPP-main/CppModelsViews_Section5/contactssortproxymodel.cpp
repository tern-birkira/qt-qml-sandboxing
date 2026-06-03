// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "contactssortproxymodel.h"

ContactsSortProxyModel::ContactsSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    sort(0, Qt::AscendingOrder);
}

bool ContactsSortProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    const int leftData = source_left.data(ContactsListModel::ContactsRoles::Age).toInt();
    const int rightData = source_right.data(ContactsListModel::ContactsRoles::Age).toInt();
    return (leftData < rightData) ? true : false;
}
