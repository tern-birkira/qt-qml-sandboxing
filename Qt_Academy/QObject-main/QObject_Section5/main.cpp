// Copyright (C) 2026 Qt Group.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QCoreApplication>
#include <QDebug>
#include <QMetaProperty>
#include "myqobject.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MyQObject *object = new MyQObject();

    object->setProperty("value", 50);
    object->setProperty("information", "Hello World!");
    object->setProperty("information", 10);

    qInfo() << "Value property:" << object->property("value");
    qInfo() << "Information property:" << object->property("information");

    return a.exec();
}
