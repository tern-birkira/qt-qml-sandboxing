// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include "contactstablemodel.h"

ContactsTableModel::ContactsTableModel(QObject *parent)
    : QAbstractTableModel{parent}
{
    firstNames = {"John", "Jane", "George", "Lily", "Sarah", "Bob", "Julia", "Jose", "Joe"};
    lastNames = {"Doe", "Doe", "Doe", "Doe", "Smith", "Smith", "Smith", "Wolf", "Wolf"};
    ages = {49, 48, 12, 10, 14, 45, 51, 38, 35};
    phoneNumbers = {"111-111-1111", "222-222-2222", "333-333-3333", "444-444-4444", "555-555-5555",
                    "666-666-6666", "777-777-7777", "888-888-8888", "999-999-9999"};
}

int ContactsTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return firstNames.length();
}

int ContactsTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return columnNumber;
}

QVariant ContactsTableModel::data(const QModelIndex &index, int role) const
{
    if (!checkIndex(index, CheckIndexOption::IndexIsValid))
        return QVariant();

    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int column = index.column();

    switch (column) {
    case FirstName:
        if(!firstNames.isEmpty()) {
            return firstNames[row];
        }
        break;
    case LastName:
        if(!lastNames.isEmpty()) {
            return lastNames[row];
        }
        break;
    case Age:
        if(!ages.isEmpty()) {
            return ages[row];
        }
        break;
    case PhoneNumber:
        if(!phoneNumbers.isEmpty()) {
            return phoneNumbers[row];
        }
        break;
    }

    return QVariant();
}

bool ContactsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole || value.toString().isEmpty())
        return false;

    int row = index.row();
    int column = index.column();

    switch (column) {
    case FirstName:
        firstNames[row] = value.toString();
        break;
    case LastName:
        lastNames[row]= value.toString();
        break;
    case Age:
        ages[row]= value.toInt();
        break;
    case PhoneNumber:
        phoneNumbers[row] = value.toString();
        break;
    }

    emit dataChanged(index, index);
    return true;
}

Qt::ItemFlags ContactsTableModel::flags(const QModelIndex &index) const
{
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool ContactsTableModel::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row + count - 1);

    if (!firstNames.isEmpty()) {
        firstNames.insert(row, "");
    }
    if (!lastNames.isEmpty()) {
        lastNames.insert(row, "");
    }
    if (!ages.isEmpty()) {
        ages.insert(row, 0);
    }
    if (!phoneNumbers.isEmpty()) {
        phoneNumbers.insert(row, "");
    }

    if (firstNames.isEmpty() && lastNames.isEmpty()
        && ages.isEmpty() && phoneNumbers.isEmpty()) {
        firstNames.insert(row, "");
        lastNames.insert(row, "");
        ages.insert(row, 0);
        phoneNumbers.insert(row, "");
    }

    endInsertRows();
    return true;
}

bool ContactsTableModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    if(!firstNames.isEmpty()) {
        firstNames.removeAt(row);
    }
    if(!lastNames.isEmpty()) {
        lastNames.removeAt(row);
    }
    if(!ages.isEmpty()) {
        ages.removeAt(row);
    }
    if(!phoneNumbers.isEmpty()) {
        phoneNumbers.removeAt(row);
    }
    endRemoveRows();
    return true;
}

bool ContactsTableModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationRow)
{
    int newDestination = destinationRow;
    if (sourceRow < destinationRow) {
        newDestination++;
    }

    beginMoveRows(sourceParent, sourceRow, sourceRow, destinationParent, newDestination);

    if(!firstNames.isEmpty()) {
        firstNames.move(sourceRow, destinationRow);
    }

    if(!lastNames.isEmpty()) {
        lastNames.move(sourceRow, destinationRow);
    }

    if(!ages.isEmpty()) {
        ages.move(sourceRow, destinationRow);
    }
    if(!phoneNumbers.isEmpty()) {
        phoneNumbers.move(sourceRow, destinationRow);
    }

    endMoveRows();
    return true;
}

bool ContactsTableModel::appendRow()
{
    int row = this->rowCount(QModelIndex());
    beginInsertRows(QModelIndex(), row, row);
    firstNames.append("");
    lastNames.append("");
    ages.append(0);
    phoneNumbers.append("");
    endInsertRows();
    return true;
}

bool ContactsTableModel::clearModel()
{
    while (this->rowCount(QModelIndex()) != 0) {
        this->removeRows(0, 1, QModelIndex());
    }
    return true;
}

bool ContactsTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);
    switch (column) {
    case FirstName:
        firstNames.clear();
        columnNumber--;
        break;
    case LastName:
        lastNames.clear();
        columnNumber--;
        break;
    case Age:
        ages.clear();
        columnNumber--;
        break;
    case PhoneNumber:
        phoneNumbers.clear();
        columnNumber--;
        break;
    }
    endRemoveRows();
    emit columnRemoved();
    return true;
}
