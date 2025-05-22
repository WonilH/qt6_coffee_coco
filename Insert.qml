// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import Backend 1.0

InsertForm {
    continueButton.onClicked: FlowBackend.continueButton()
    cancelButton.onClicked: FlowBackend.cancelButton()
}
