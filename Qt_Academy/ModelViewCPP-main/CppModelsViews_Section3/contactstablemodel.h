// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#ifndef CONTACTSTABLEMODEL_H
#define CONTACTSTABLEMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <QAbstractTableModel>

class ContactsTableModel : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
public:
    enum ContactsRoles {
        FirstName = 0,
        LastName,
        Age,
        PhoneNumber
    };

    explicit ContactsTableModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;

    Q_INVOKABLE bool insertRows(int row, int count, const QModelIndex &parent);
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex &parent);
    Q_INVOKABLE bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationRow);
    Q_INVOKABLE bool appendRow();
    Q_INVOKABLE bool removeColumns(int column, int count, const QModelIndex &parent);
    Q_INVOKABLE bool clearModel();

signals:
    void columnRemoved();

private:
    QStringList firstNames;
    QStringList lastNames;
    QList<int> ages;
    QStringList phoneNumbers;
    int columnNumber = 4;
};

#endif // CONTACTSTABLEMODEL_H
