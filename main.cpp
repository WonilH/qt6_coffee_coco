// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "ApplicationFlowBackend.h" // Include the new backend header

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    static ApplicationFlowBackend backend;
    // Register the C++ backend as a QML singleton
    // Usage in QML: import CoffeeApp 1.0; ApplicationFlowBackend.propertyName
    qmlRegisterSingletonInstance<ApplicationFlowBackend>("CoffeeApp", 1, 0, "ApplicationFlowBackend", &backend);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qt/qml/demos/coffee/main.qml"))); // Assuming main.qml is the entry point
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
