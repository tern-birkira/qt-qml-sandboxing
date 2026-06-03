// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "contactsfilterproxymodel.h"

ContactsFilterProxyModel::ContactsFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{}

QString ContactsFilterProxyModel::lastName() const
{
    return m_lastName;
}

void ContactsFilterProxyModel::setLastName(const QString &newLastName)
{
    if (m_lastName == newLastName)
        return;
    m_lastName = newLastName;
    emit lastNameChanged();
    invalidateFilter();
}

bool ContactsFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex index = sourceModel()->index(source_row, 0, source_parent);
    const QString lastName = index.data(ContactsListModel::ContactsRoles::LastName).toString();
    return (lastName == m_lastName);
}
