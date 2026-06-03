// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "contactsidentityproxymodel.h"

ContactsIdentityProxyModel::ContactsIdentityProxyModel(QObject *parent)
    : QIdentityProxyModel{parent}
{}

QVariant ContactsIdentityProxyModel::data(const QModelIndex &index, int role) const
{
    const QVariant data = QIdentityProxyModel::data(index, role);
    const QVariant age = QIdentityProxyModel::data(index, ContactsListModel::ContactsRoles::Age);

    if ((role == ContactsListModel::ContactsRoles::FirstName || role == ContactsListModel::ContactsRoles::PhoneNumber) && (age.toInt() < 18)) {
        const QString infoToRedact = data.toString();
        return "********";
    }

    return data;
}
