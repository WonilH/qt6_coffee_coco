// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

InsertForm {
    continueButton.onClicked: ApplicationFlowBackend.continueButton()
    cancelButton.onClicked: ApplicationFlowBackend.cancelButton()
}
