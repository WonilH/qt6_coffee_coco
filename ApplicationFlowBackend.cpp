#include "ApplicationFlowBackend.h"
#include <QGuiApplication> // For Qt::platform
#include <QDebug>          // For qDebug

// Constructor
ApplicationFlowBackend::ApplicationFlowBackend(QObject *parent) : QObject(parent)
{
    // Initialize platform from Qt::platform
    // Note: Qt::platform itself is a QOperatingSystemVersion, so convert to string
    // This requires a bit more effort than directly accessing Qt.platform.os in QML.
    // For simplicity, we can use QSysInfo::productType() or QSysInfo::kernelType()
    // or conditional compilation. QML's Qt.platform.os is quite general.
    // Let's use QGuiApplication::platformName() for a start, though it might be more detailed.
    m_platform = QGuiApplication::platformName(); // More of a platform description

    // A more direct equivalent to QML's Qt.platform.os might be:
    #if defined(Q_OS_ANDROID)
        m_platform = "android";
    #elif defined(Q_OS_IOS)
        m_platform = "ios";
    #elif defined(Q_OS_MACOS)
        m_platform = "osx"; // QML uses 'osx' for macOS
    #elif defined(Q_OS_LINUX)
        m_platform = "linux";
    #elif defined(Q_OS_WIN)
        m_platform = "windows";
    #else
        m_platform = "unknown";
    #endif

    // Initialize coffee counts (example values)
    m_cappuccinos = 5;
    m_espressos = 5;
    m_lattes = 5;
    m_macchiatos = 5;

    // Initial state
    m_currentState = "Home";
    m_previousState = ""; // No previous state at start
}

// Getter implementations
int ApplicationFlowBackend::animationDuration() const { return m_animationDuration; }
QString ApplicationFlowBackend::platform() const { return m_platform; }
QString ApplicationFlowBackend::mode() const { return m_mode; }
int ApplicationFlowBackend::brewTime() const { return m_brewTime; }
int ApplicationFlowBackend::coffeeAmount() const { return m_coffeeAmount; }
int ApplicationFlowBackend::milkAmount() const { return m_milkAmount; }
int ApplicationFlowBackend::foamAmount() const { return m_foamAmount; }
double ApplicationFlowBackend::sugarAmount() const { return m_sugarAmount; }
QString ApplicationFlowBackend::coffeeName() const { return m_coffeeName; }
QString ApplicationFlowBackend::previousState() const { return m_previousState; }
double ApplicationFlowBackend::progressBarValue() const { return m_progressBarValue; }
QString ApplicationFlowBackend::progressCupState() const { return m_progressCupState; }
int ApplicationFlowBackend::cappuccinos() const { return m_cappuccinos; }
int ApplicationFlowBackend::espressos() const { return m_espressos; }
int ApplicationFlowBackend::lattes() const { return m_lattes; }
int ApplicationFlowBackend::macchiatos() const { return m_macchiatos; }
QString ApplicationFlowBackend::currentState() const { return m_currentState; }

// Setter implementations
void ApplicationFlowBackend::setAnimationDuration(int duration) {
    if (m_animationDuration != duration) {
        m_animationDuration = duration;
        emit animationDurationChanged();
    }
}

void ApplicationFlowBackend::setMode(const QString &mode) {
    if (m_mode != mode) {
        m_mode = mode;
        emit modeChanged();
    }
}

void ApplicationFlowBackend::setBrewTime(int time) {
    if (m_brewTime != time) {
        m_brewTime = time;
        emit brewTimeChanged();
    }
}

void ApplicationFlowBackend::setCoffeeAmount(int amount) {
    if (m_coffeeAmount != amount) {
        m_coffeeAmount = amount;
        emit coffeeAmountChanged();
    }
}

void ApplicationFlowBackend::setMilkAmount(int amount) {
    if (m_milkAmount != amount) {
        m_milkAmount = amount;
        emit milkAmountChanged();
    }
}

void ApplicationFlowBackend::setFoamAmount(int amount) {
    if (m_foamAmount != amount) {
        m_foamAmount = amount;
        emit foamAmountChanged();
    }
}

void ApplicationFlowBackend::setSugarAmount(double amount) {
    if (m_sugarAmount != amount) {
        m_sugarAmount = amount;
        emit sugarAmountChanged();
    }
}

void ApplicationFlowBackend::setCoffeeName(const QString &name) {
    if (m_coffeeName != name) {
        m_coffeeName = name;
        emit coffeeNameChanged();
    }
}

void ApplicationFlowBackend::setPreviousState(const QString &state) {
    if (m_previousState != state) {
        m_previousState = state;
        emit previousStateChanged();
    }
}

void ApplicationFlowBackend::setProgressBarValue(double value) {
    if (m_progressBarValue != value) {
        m_progressBarValue = value;
        emit progressBarValueChanged();
    }
}

void ApplicationFlowBackend::setProgressCupState(const QString &state) {
    if (m_progressCupState != state) {
        m_progressCupState = state;
        emit progressCupStateChanged();
    }
}

void ApplicationFlowBackend::setCappuccinos(int count) {
    if (m_cappuccinos != count) {
        m_cappuccinos = count;
        emit cappuccinosChanged();
    }
}

void ApplicationFlowBackend::setEspressos(int count) {
    if (m_espressos != count) {
        m_espressos = count;
        emit espressosChanged();
    }
}

void ApplicationFlowBackend::setLattes(int count) {
    if (m_lattes != count) {
        m_lattes = count;
        emit lattesChanged();
    }
}

void ApplicationFlowBackend::setMacchiatos(int count) {
    if (m_macchiatos != count) {
        m_macchiatos = count;
        emit macchiatosChanged();
    }
}

void ApplicationFlowBackend::setCurrentState(const QString &state) {
    if (m_currentState != state) {
        setPreviousState(m_currentState); // Automatically set previous state
        m_currentState = state;
        qDebug() << "Current state changed to:" << m_currentState << "Previous state:" << m_previousState;
        emit currentStateChanged();

        // Emit navigation signals based on the new state
        if (state == "Home") emit navigateToHome();
        else if (state == "Coffee-selection") emit navigateToCoffeeSelection();
        else if (state == "Settings") emit navigateToSettings();
        else if (state == "Insert") emit navigateToInsert();
        else if (state == "Progress") emit navigateToProgress();
        else if (state == "Ready") emit navigateToReady();
    }
}


// Q_INVOKABLE method implementations
void ApplicationFlowBackend::themeButton() {
    // This function interacted with a 'Colors' QML singleton.
    // For now, we'll keep it simple and assume 'Colors' might still be a QML item.
    // Direct manipulation of another QML singleton from C++ is complex.
    // A better approach would be for 'Colors.qml' to also have a C++ backend
    // or use signals/properties to communicate.
    // For this step, we'll just log it. QML will need to handle actual theme change.
    qDebug() << "themeButton called. Current mode:" << m_mode;
    // If 'Colors' was also a C++ singleton, you could call its methods here.
    // Or emit a signal that QML connects to, to call Colors.themeButton().
    // Let's assume for now QML handles this via a direct call on 'Colors' singleton.
    // If 'Colors' is purely QML, this function might need to be removed from backend
    // or trigger a signal that ApplicationFlow.qml connects to.
}

void ApplicationFlowBackend::selectCappuccino() {
    setCoffeeName("Cappuccino");
    setCoffeeAmount(60);
    setMilkAmount(60);
    setFoamAmount(60);
    setBrewTime(5000);
    setCurrentState("Settings");
}

void ApplicationFlowBackend::selectEspresso() {
    setCoffeeName("Espresso");
    setCoffeeAmount(80);
    setMilkAmount(0);
    setFoamAmount(0);
    setBrewTime(4000);
    setCurrentState("Settings");
}

void ApplicationFlowBackend::selectLatte() {
    setCoffeeName("Latte");
    setCoffeeAmount(40);
    setMilkAmount(20);
    setFoamAmount(60);
    setBrewTime(6000);
    setCurrentState("Settings");
}

void ApplicationFlowBackend::selectMacchiato() {
    setCoffeeName("Macchiato");
    setCoffeeAmount(100);
    setMilkAmount(5);
    setFoamAmount(10);
    setBrewTime(8000);
    setCurrentState("Settings");
}

void ApplicationFlowBackend::startCoffeeSelection() {
    setCurrentState("Coffee-selection");
}

void ApplicationFlowBackend::backButton() {
    // In QML, this was:
    // stack.pop()
    // applicationFlow.state = applicationFlow.previousState
    // The stack.pop() will be handled in QML via state changes.
    // We just need to revert to the previous state.
    if (!m_previousState.isEmpty()) {
        // Swap current and previous to correctly "go back"
        QString temp = m_currentState;
        m_currentState = m_previousState; // setCurrentState will emit signals
        m_previousState = temp; // This previous state might not be correct after back, QML state machine handles this better.
                                // Let's rely on QML's state machine to set previousState correctly when it transitions.
                                // Or, the QML state machine should define the "previousState" for each state.
                                // For now, just setting current state should be enough.
        emit currentStateChanged(); // Manually emit if not using setCurrentState's full logic for back.
                                    // Or better:
        QString targetState = m_previousState; // Cache it
        // The following logic was a bit tangled. Let's simplify:
        // The goal is to make m_previousState the new m_currentState.
        // And the old m_currentState becomes the new m_previousState for a potential "forward" later (though not typical for "back").
        // More accurately, previousState should be set by the state machine upon entering the new state.
        // So, when going back to 'targetState', the 'previousState' should become what *led* to targetState.
        // This is tricky without a full state history stack.
        // A simpler back model: just set current to previous, and let previous become the one before that.
        // However, setCurrentState already sets previousState = m_currentState.
        
        // Correct logic for a simple back:
        QString oldCurrent = m_currentState;
        m_currentState = m_previousState; // Go to previous
        m_previousState = oldCurrent;     // The state we came from is now the "previous" in terms of "forward" history
                                          // but for "back" operations, this previousState needs to be the one *before* the new currentState.
                                          // This is why a stack or more formal state management is better.
                                          // For this model, setCurrentState(m_previousState) is the most robust.
        
        setCurrentState(targetState); // This will set previousState to what *was* current, and current to target.

    } else {
        qDebug() << "No previous state to go back to.";
        // Default to home if no previous state (or handle as error)
        setCurrentState("Home");
    }
}

void ApplicationFlowBackend::confirmButton() {
    setCurrentState("Insert");
}

void ApplicationFlowBackend::continueBrew() {
    // Original QML logic:
    // stack.push(progress)
    // applicationFlow.state = "Progress"
    // applicationFlow.progressBarValue = 1
    // applicationFlow.progressCupState = "1"
    // if (applicationFlow.coffeeName == "Cappuccino") {
    //     applicationFlow.cappuccinos = applicationFlow.cappuccinos - 1
    // } else if (applicationFlow.coffeeName == "Espresso") {
    //     applicationFlow.espressos = applicationFlow.espressos - 1
    // } // ... and so on

    setProgressBarValue(1.0); // QML had "1", but it's a double now
    setProgressCupState("1");

    if (m_coffeeName == "Cappuccino") {
        if (m_cappuccinos > 0) setCappuccinos(m_cappuccinos - 1);
    } else if (m_coffeeName == "Espresso") {
        if (m_espressos > 0) setEspressos(m_espressos - 1);
    } else if (m_coffeeName == "Latte") {
        if (m_lattes > 0) setLattes(m_lattes - 1);
    } else if (m_coffeeName == "Macchiato") { 
        if (m_macchiatos > 0) setMacchiatos(m_macchiatos - 1);
    }
    setCurrentState("Progress");
}

void ApplicationFlowBackend::cancelButton() {
    // Original QML:
    // applicationFlow.state = "Coffee-selection"
    // stack.pop(stack.get(1)) // This implies popping back to a specific point
    // For C++ backend, we just set the state. QML will handle stack.
    setCurrentState("Coffee-selection");
}

void ApplicationFlowBackend::brewFinished() {
    // Original QML:
    // stack.push(ready)
    // applicationFlow.state = "Ready"
    setCurrentState("Ready");
}

void ApplicationFlowBackend::returnToStart() {
    // Original QML:
    // stack.pop(stack.get(0))
    // applicationFlow.state = "Home"
    // applicationFlow.progressBarValue = 0
    // applicationFlow.progressCupState = "0"
    setProgressBarValue(0.0);
    setProgressCupState("0");
    setCurrentState("Home");
}
