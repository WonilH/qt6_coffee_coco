// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtQuick
import Backend 1.0

CustomToolBarForm {
    backButton.onClicked: FlowBackend.backButton()
    themeButton.onClicked: FlowBackend.themeButton()
    backButton.states: State {
        name: "pressed"
        when: backButton.pressed
        PropertyChanges {
            target: backButton
            scale: 1.1
        }
    }
    themeButton.states: State {
        name: "pressed"
        when: themeButton.pressed
        PropertyChanges {
            target: themeButton
            scale: 1.1
        }
    }

}
