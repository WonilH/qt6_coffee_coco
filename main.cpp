// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "ApplicationFlowBackend.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    static ApplicationFlowBackend backend;
    qmlRegisterSingletonInstance<ApplicationFlowBackend>("Backend", 1, 0, "FlowBackend", &backend);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qt/qml/demos/coffee/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
