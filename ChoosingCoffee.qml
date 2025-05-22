// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import Backend 1.0

ChoosingCoffeeForm {
    cappuccino.button.onClicked: FlowBackend.cappuccino()
    macchiato.button.onClicked: FlowBackend.macchiato()
    espresso.button.onClicked: FlowBackend.espresso()
    latte.button.onClicked: FlowBackend.latte()
}
