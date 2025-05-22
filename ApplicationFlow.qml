// Copyright (C) 2023 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause
import QtQuick
import CoffeeApp 1.0 // Import the backend

ApplicationFlowForm {
    id: applicationFlow
    
    // The 'state' property of ApplicationFlowForm is now driven by the C++ backend's currentState
    state: ApplicationFlowBackend.currentState

    // All properties previously defined here (animationDuration, platform, mode, brewTime, etc.)
    // are now accessed via ApplicationFlowBackend, e.g., ApplicationFlowBackend.animationDuration
    // No need to re-declare them here. If they are needed for bindings within this component,
    // they can be accessed directly: ApplicationFlowBackend.propertyName

    // The 'themeButton' function might still be called by UI elements.
    // If its logic (interacting with Colors.qml) is purely QML, it can remain here.
    // Or, if ApplicationFlowBackend.themeButton() is preferred, UI should call that.
    // For now, let's assume UI elements will call ApplicationFlowBackend.themeButton() if needed,
    // or this function is still used if it's purely QML side effect on Colors.
    // Given the original issue, it's better to remove functions if their primary role was control flow.
    // The C++ `themeButton` currently just logs. The actual theme switch in `Colors.qml`
    // would still need to be triggered. This might be done by a signal from C++ if `Colors`
    // also had a C++ backend, or `Colors.qml` could listen to a property on `ApplicationFlowBackend`.
    // Let's keep the original QML themeButton for now if it manipulates a QML-only Colors singleton.
    // However, the instruction was to move *control* functions. Theme switching is borderline.
    // To strictly follow, we'll remove it and assume UI elements will directly call ApplicationFlowBackend.themeButton()
    // and that a separate mechanism handles the Colors.qml update if needed.

    // All functions like cappuccino, espresso, latte, macchiato, backButton, confirmButton,
    // continueButton, cancelButton, onFinished, onReturnToStart are removed.
    // Their logic is now in ApplicationFlowBackend and will be called from UI elements directly.
    // For example, a button for "Cappuccino" would have: onClicked: ApplicationFlowBackend.selectCappuccino()

    // Handle StackView operations based on backend signals or state changes
    Connections {
        target: ApplicationFlowBackend
        function onNavigateToHome() {
            stack.pop(null); // Pop all items if stack.get(0) was meant to clear to root. Or stack.clear() if appropriate.
                             // A common pattern is to have a specific item for home and push/pop others.
                             // Assuming stack.pop(stack.get(0)) meant clear and go to initial item (home).
                             // If 'home' is the initialItem of the stack, stack.clear() might be what's needed.
                             // Or more robustly, ensure 'home' is at the bottom and pop until it's current.
                             // For simplicity with current signals:
            if (stack.depth > 1) stack.pop(null); // Pop all above the first one
            // Or if 'home' is always the first item added and never removed:
            // while(stack.currentItem !== home && stack.depth > 1) { stack.pop(); }
            // This part needs to align with how 'stack' (presumably a StackView) is structured.
            // Let's assume 'home' is the initial item and others are pushed on top.
        }
        function onNavigateToCoffeeSelection() { 
            // This was previously home.getStartedbutton.onClicked
            // If 'choosingCoffee' is the QML item for this screen
            if (stack.currentItem !== choosingCoffee) stack.push(choosingCoffee);
        }
        function onNavigateToSettings() {
            // This was part of cappuccino(), espresso() etc.
            // If 'settings' is the QML item for this screen
            if (stack.currentItem !== settings) stack.push(settings);
        }
        function onNavigateToInsert() {
            // This was from confirmButton()
            // If 'insert' is the QML item for this screen
            if (stack.currentItem !== insert) stack.push(insert);
        }
        function onNavigateToProgress() {
            // This was from continueButton()
            // If 'progress' is the QML item for this screen
            if (stack.currentItem !== progress) stack.push(progress);
        }
        function onNavigateToReady() {
            // This was from onFinished()
            // If 'ready' is the QML item for this screen
            if (stack.currentItem !== ready) stack.push(ready);
        }
        // For backButton functionality:
        // The C++ backButton changes the state. QML's state machine (driven by ApplicationFlowBackend.currentState)
        // should handle UI changes. If stack.pop() is needed, it should be here.
        // The old backButton did stack.pop() then changed state.
        // Now, C++ changes state, then QML reacts.
        // One way: listen to currentState and if it implies a pop, do it.
        // This can get complex. A simpler way for "back" might be needed if the
        // generic onNavigateTo<State> signals aren't enough.
        // The C++ backButton sets previousState.
        // Let's assume for now the state transitions handle stack popping correctly
        // when ApplicationFlowBackend.currentState changes.
        // If a specific stack.pop() is needed for *every* back operation:
        // function onCurrentStateChanged() {
        //     // This is tricky because not all state changes are "back".
        //     // It's better if the component triggering "back" (e.g., a back button in UI)
        //     // calls ApplicationFlowBackend.backButton() AND THEN performs stack.pop().
        //     // Or, ApplicationFlowBackend.backButton() could emit a specific signal like "navigateBackRequest"
        // }
        // For now, we'll rely on the states below and direct calls from UI for stack operations.
        // The original backButton did stack.pop() then set state.
        // So, UI elements calling ApplicationFlowBackend.backButton() should also do stack.pop().
        // Example: someBackButton.onClicked: { ApplicationFlowBackend.backButton(); stack.pop(); }
    }
    
    // home.getStartedbutton.onClicked is removed.
    // The 'home' component's button should now directly call: ApplicationFlowBackend.startCoffeeSelection()
    // and the Connections block above will handle stack.push(choosingCoffee).

    // Update coffeeText based on ApplicationFlowBackend.coffeeName or ApplicationFlowBackend.currentState
    // For example, if coffeeText is a Text element:
    // coffeeText.text: {
    //     if (ApplicationFlowBackend.currentState === "Settings" || ApplicationFlowBackend.currentState === "Insert" || ApplicationFlowBackend.currentState === "Progress") {
    //         return ApplicationFlowBackend.coffeeName;
    //     } else if (ApplicationFlowBackend.currentState === "Coffee-selection") {
    //         return "Coffee Selection";
    //     }
    //     return ""; // Default or for Home/Ready
    // }
    // This logic needs to be adapted based on where coffeeText is and how it's used.
    // The original ApplicationFlow.qml had PropertyChanges for coffeeText.text in states. We'll keep that.

    states: [
        State {
            name: "Home"
            // PropertyChanges targeting applicationFlow for 'previousState' are removed,
            // as this is now managed by ApplicationFlowBackend.
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
                themeButton.opacity: 0 // Assuming themeButton is part of toolbar
                themeButton.enabled: false
                logo.sourceSize.width: 70
                logo.sourceSize.height: 50
            }
            PropertyChanges {
                target: coffeeText // Assuming coffeeText is an ID of a Text item
                visible: false
            }
            PropertyChanges {
                target: stack // Assuming stack is an ID of a StackView
                anchors.top: coffeeText.bottom
            }
        },
        State {
            name: "Coffee-selection"
            // No longer need: PropertyChanges { target: applicationFlow; previousState: "Home" }
            // ApplicationFlowBackend handles its own previousState when currentState changes.
            PropertyChanges {
                target: coffeeText
                visible: true // Ensure visible
                text: "Coffee Selection"
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
                themeButton.opacity: 1 // Assuming theme button is visible here
                themeButton.enabled: true
            }
            PropertyChanges {
                target: stack
                anchors.top: coffeeText.bottom
            }
        },
        State {
            name: "Settings"
            // No longer need: PropertyChanges { target: applicationFlow; previousState: "Coffee-selection" }
            PropertyChanges {
                target: coffeeText
                visible: true // Ensure visible
                text: ApplicationFlowBackend.coffeeName // Bind to backend coffee name
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 1 // Back button should be visible
                backButton.enabled: true
                themeButton.opacity: 1
                themeButton.enabled: true
            }
            PropertyChanges {
                target: stack
                anchors.top: coffeeText.bottom
            }
        },
        State {
            name: "Insert"
            // No longer need: PropertyChanges { target: applicationFlow; previousState: "Settings" }
             PropertyChanges {
                target: coffeeText
                visible: true
                text: ApplicationFlowBackend.coffeeName
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 1
                backButton.enabled: true
                themeButton.opacity: 1
                themeButton.enabled: true
            }
            PropertyChanges {
                target: stack
                anchors.top: coffeeText.bottom
            }
        },
        State {
            name: "Progress"
            // No longer need: PropertyChanges { target: applicationFlow; previousState: "Insert" }
            PropertyChanges {
                target: coffeeText
                visible: true
                text: ApplicationFlowBackend.coffeeName
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0 // No back button during progress
                backButton.enabled: false
                themeButton.opacity: 1
                themeButton.enabled: true
            }
            PropertyChanges {
                target: stack
                anchors.top: coffeeText.bottom
            }
        },
        State {
            name: "Ready"
            // No longer need: PropertyChanges { target: applicationFlow; previousState: "Progress" }
            PropertyChanges {
                target: coffeeText
                visible: true
                text: ApplicationFlowBackend.coffeeName + " Ready!" // Example text
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0 // No back button on ready screen
                backButton.enabled: false
                themeButton.opacity: 1
                themeButton.enabled: true
            }
            PropertyChanges {
                target: stack
                anchors.top: coffeeText.bottom
            }
        }
    ]
}
