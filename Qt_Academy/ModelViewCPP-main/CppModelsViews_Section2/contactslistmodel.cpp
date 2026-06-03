// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "contactslistmodel.h"

ContactsListModel::ContactsListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    firstNames = {"John", "Jane", "George", "Lily", "Sarah", "Bob", "Julia", "Jose", "Joe"};
    lastNames = {"Doe", "Doe", "Doe", "Doe", "Smith", "Smith", "Smith", "Wolf", "Wolf"};
    ages = {49, 48, 12, 10, 14, 45, 51, 38, 35};
    phoneNumbers = {"111-111-1111", "222-222-2222", "333-333-3333", "444-444-4444", "555-555-5555",
                    "666-666-6666", "777-777-7777", "888-888-8888", "999-999-9999"};
}

int ContactsListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return firstNames.count();
}

QVariant ContactsListModel::data(const QModelIndex &index, int role) const
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant();

    if (!index.isValid())
        return QVariant();

    int row = index.row();

    switch (role) {
    case FirstName:
        return firstNames[row];
    case LastName:
        return lastNames[row];
    case Age:
        return ages[row];
    case PhoneNumber:
        return phoneNumbers[row];
    }

    return QVariant();
}

QHash<int, QByteArray> ContactsListModel::roleNames() const
{
    QHash<int, QByteArray> mapping {
        {ContactsRoles::FirstName, "firstName"},
        {ContactsRoles::LastName, "lastName"},
        {ContactsRoles::Age, "age"},
        {ContactsRoles::PhoneNumber, "phoneNumber"}
    };

    return mapping;
}

Qt::ItemFlags ContactsListModel::flags(const QModelIndex &index) const
{
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable;
}

bool ContactsListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || value.toString().isEmpty())
        return false;
    const int row = index.row();

    QStringList contact = value.toString().split(", ");
    firstNames[row] = contact[0];
    lastNames[row] = contact[1];
    ages[row] = contact[2].toInt();
    phoneNumbers[row] = contact[3];

    emit dataChanged(index, index);
    return true;
}

bool ContactsListModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationRow)
{
    int newDestination = destinationRow;
    if (sourceRow < destinationRow) {
        newDestination++;
    }

    beginMoveRows(sourceParent, sourceRow, sourceRow, destinationParent, newDestination);
    firstNames.move(sourceRow, destinationRow);
    lastNames.move(sourceRow, destinationRow);
    ages.move(sourceRow, destinationRow);
    phoneNumbers.move(sourceRow, destinationRow);
    endMoveRows();

    return true;
}

bool ContactsListModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);
    firstNames.insert(row, "");
    lastNames.insert(row, "");
    ages.insert(row, 0);
    phoneNumbers.insert(row, "");
    endInsertRows();
    return true;
}

bool ContactsListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);
    firstNames.removeAt(row);
    lastNames.removeAt(row);
    ages.removeAt(row);
    phoneNumbers.removeAt(row);
    endRemoveRows();
    return true;
}

bool ContactsListModel::appendRow(int rowNumber)
{
    beginInsertRows(QModelIndex(), rowNumber, rowNumber);
    firstNames.append("");
    lastNames.append("");
    ages.append(0);
    phoneNumbers.append("");
    endInsertRows();
    return true;
}

bool ContactsListModel::clearModel(int rowNumber)
{
    beginRemoveRows(QModelIndex(), 0, rowNumber - 1);
    firstNames.remove(0, rowNumber - 1);
    lastNames.remove(0, rowNumber - 1);
    ages.remove(0, rowNumber - 1);
    phoneNumbers.remove(0, rowNumber - 1);
    endRemoveRows();
    return true;
}
