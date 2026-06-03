// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CONTACTSFILTERPROXYMODEL_H
#define CONTACTSFILTERPROXYMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QSortFilterProxyModel>

#include "contactslistmodel.h"

class ContactsFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("ContactsFilterProxyModel must be instantiated in C++")
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged FINAL)
public:
    explicit ContactsFilterProxyModel(QObject *parent = nullptr);

    QString lastName() const;
    void setLastName(const QString &newLastName);

signals:
    void lastNameChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

private:
    QString m_lastName;
};

#endif // CONTACTSFILTERPROXYMODEL_H
