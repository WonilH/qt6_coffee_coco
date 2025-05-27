// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtQuick
import QtQuick.Controls.Basic
import Backend
//! [Set application window size]
ApplicationWindow {
    visible: true
    width: 600
    height: 1000
    title: qsTr("Coffee")
//! [Set application window size]
    ApplicationFlow {
        width: parent.width
        height: parent.height        
    }
}
