// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtQuick
import Backend 1.0

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"
    Component.onCompleted: FlowBackend.setRoot(applicationFlow)

    home.getStartedbutton.onClicked: FlowBackend.getStarted()
    //! [States]
    states: [
        State {
            name: "Home"
            toolbar.backButton.opacity: 0
            toolbar.backButton.enabled: false
            toolbar.themeButton.opacity: 0
            toolbar.themeButton.enabled: false
            toolbar.logo.sourceSize.width: 70
            toolbar.logo.sourceSize.height: 50
            //! [States]
            coffeeText.visible: false
            stack.anchors.top: coffeeText.bottom
        },
        State {
            name: "Coffee-selection"
            applicationFlow.previousState: "Home"
            coffeeText.text: "Coffee Selection"
            toolbar.backButton.opacity: 0
            toolbar.backButton.enabled: false
            stack.anchors.top: coffeeText.bottom
        },
        State {
            name: "Settings"
            applicationFlow.previousState: "Coffee-selection"
            stack.anchors.top: coffeeText.bottom
        },
        State {
            name: "Insert"
            applicationFlow.previousState: "Settings"
            stack.anchors.top: coffeeText.bottom
        },
        State {
            name: "Progress"
            applicationFlow.previousState: "Insert"
            toolbar.backButton.opacity: 0
            toolbar.backButton.enabled: false
            stack.anchors.top: coffeeText.bottom
        },
        State {
            name: "Ready"
            applicationFlow.previousState: "Progress"
            toolbar.backButton.opacity: 0
            toolbar.backButton.enabled: false
            stack.anchors.top: coffeeText.bottom
        }

    ]
}
