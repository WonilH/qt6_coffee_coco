#include "ApplicationFlowBackend.h"
#include <QGuiApplication>
#include <QMetaObject>
#include <QVariant>
#include <QSysInfo>

ApplicationFlowBackend::ApplicationFlowBackend(QObject *parent)
    : QObject(parent)
{
    m_platform = QSysInfo::prettyProductName();
}

void ApplicationFlowBackend::setAnimationDuration(int value)
{
    if (m_animationDuration == value)
        return;
    m_animationDuration = value;
    emit animationDurationChanged();
}

void ApplicationFlowBackend::setMode(const QString &value)
{
    if (m_mode == value)
        return;
    m_mode = value;
    emit modeChanged();
}

void ApplicationFlowBackend::setBrewTime(int value)
{
    if (m_brewTime == value)
        return;
    m_brewTime = value;
    emit brewTimeChanged();
}

void ApplicationFlowBackend::setCoffeeAmount(int value)
{
    if (m_coffeeAmount == value)
        return;
    m_coffeeAmount = value;
    emit coffeeAmountChanged();
}

void ApplicationFlowBackend::setMilkAmount(int value)
{
    if (m_milkAmount == value)
        return;
    m_milkAmount = value;
    emit milkAmountChanged();
}

void ApplicationFlowBackend::setFoamAmount(int value)
{
    if (m_foamAmount == value)
        return;
    m_foamAmount = value;
    emit foamAmountChanged();
}

void ApplicationFlowBackend::setSugarAmount(double value)
{
    if (qFuzzyCompare(m_sugarAmount, value))
        return;
    m_sugarAmount = value;
    emit sugarAmountChanged();
}

void ApplicationFlowBackend::setDarkTheme(bool value)
{
    if (m_darkTheme == value)
        return;
    m_darkTheme = value;
    emit darkThemeChanged();
}

void ApplicationFlowBackend::setCappuccinos(int value)
{
    if (m_cappuccinos == value)
        return;
    m_cappuccinos = value;
    emit cappuccinosChanged();
}

void ApplicationFlowBackend::setLattes(int value)
{
    if (m_lattes == value)
        return;
    m_lattes = value;
    emit lattesChanged();
}

void ApplicationFlowBackend::setEspressos(int value)
{
    if (m_espressos == value)
        return;
    m_espressos = value;
    emit espressosChanged();
}

void ApplicationFlowBackend::setMacchiatos(int value)
{
    if (m_macchiatos == value)
        return;
    m_macchiatos = value;
    emit macchiatosChanged();
}

void ApplicationFlowBackend::setRoot(QObject *root)
{
    m_root = root;
}

void ApplicationFlowBackend::themeButton()
{
    setDarkTheme(!m_darkTheme);
}

void ApplicationFlowBackend::cappuccino()
{
    if (!m_root)
        return;
    m_root->setProperty("state", "Settings");
    m_root->setProperty("coffeeName", "Cappuccino");
    setCoffeeAmount(60);
    setMilkAmount(60);
    setFoamAmount(60);
    setBrewTime(5000);
    emit pushSettings();
}

void ApplicationFlowBackend::espresso()
{
    if (!m_root)
        return;
    m_root->setProperty("state", "Settings");
    m_root->setProperty("coffeeName", "Espresso");
    setCoffeeAmount(80);
    setMilkAmount(0);
    setFoamAmount(0);
    setBrewTime(4000);
    emit pushSettings();
}

void ApplicationFlowBackend::latte()
{
    if (!m_root)
        return;
    m_root->setProperty("state", "Settings");
    m_root->setProperty("coffeeName", "Latte");
    setCoffeeAmount(40);
    setMilkAmount(20);
    setFoamAmount(60);
    setBrewTime(6000);
    emit pushSettings();
}

void ApplicationFlowBackend::macchiato()
{
    if (!m_root)
        return;
    m_root->setProperty("state", "Settings");
    m_root->setProperty("coffeeName", "Macchiato");
    setCoffeeAmount(100);
    setMilkAmount(5);
    setFoamAmount(10);
    setBrewTime(8000);
    emit pushSettings();
}

void ApplicationFlowBackend::getStarted()
{
    if (!m_root)
        return;
    m_root->setProperty("state", "Coffee-selection");
    emit pushChoosingCoffee();
}

void ApplicationFlowBackend::backButton()
{
    if (!m_root)
        return;
    emit pop();
    QString prev = m_root->property("previousState").toString();
    m_root->setProperty("state", prev);
}

void ApplicationFlowBackend::confirmButton()
{
    if (!m_root)
        return;
    emit pushInsert();
    m_root->setProperty("state", "Insert");
}

void ApplicationFlowBackend::continueButton()
{
    if (!m_root)
        return;
    emit pushProgress();
    m_root->setProperty("state", "Progress");
    m_root->setProperty("progressBarValue", 1);
    m_root->setProperty("progressCupState", "1");
    QString coffee = m_root->property("coffeeName").toString();
    if (coffee == "Cappuccino") {
        setCappuccinos(m_cappuccinos - 1);
    } else if (coffee == "Espresso") {
        setEspressos(m_espressos - 1);
    } else if (coffee == "Latte") {
        setLattes(m_lattes - 1);
    } else {
        setMacchiatos(m_macchiatos - 1);
    }
}

void ApplicationFlowBackend::cancelButton()
{
    if (!m_root)
        return;
    m_root->setProperty("state", "Coffee-selection");
    emit popToIndex(1);
}

void ApplicationFlowBackend::onFinished()
{
    if (!m_root)
        return;
    emit pushReady();
    m_root->setProperty("state", "Ready");
}

void ApplicationFlowBackend::onReturnToStart()
{
    if (!m_root)
        return;
    emit popToIndex(0);
    m_root->setProperty("state", "Home");
    m_root->setProperty("progressBarValue", 0);
    m_root->setProperty("progressCupState", "0");
}

