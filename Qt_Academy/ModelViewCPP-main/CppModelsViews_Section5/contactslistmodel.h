// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CONTACTSLISTMODEL_H
#define CONTACTSLISTMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractListModel>

class ContactsListModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("ContactsListModel must be instantiated in C++")
public:
    enum ContactsRoles {
        FirstName = 0,
        LastName,
        Age,
        PhoneNumber
    };

    explicit ContactsListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Q_INVOKABLE bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationRow) override;
    Q_INVOKABLE bool insertRows(int row, int count, const QModelIndex &parent) override;
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex &parent) override;
    Q_INVOKABLE bool appendRow(int rowNumber);
    Q_INVOKABLE bool clearModel(int rowNumber);

private:
    QStringList firstNames;
    QStringList lastNames;
    QList<int> ages;
    QStringList phoneNumbers;
};

#endif // CONTACTSLISTMODEL_H
