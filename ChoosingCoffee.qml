// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

ChoosingCoffeeForm {
    cappuccino.button.onClicked: ApplicationFlowBackend.cappuccino()
    macchiato.button.onClicked: ApplicationFlowBackend.macchiato()
    espresso.button.onClicked: ApplicationFlowBackend.espresso()
    latte.button.onClicked: ApplicationFlowBackend.latte()
}
