#ifndef APPLICATIONFLOWBACKEND_H
#define APPLICATIONFLOWBACKEND_H

#include <QObject>
#include <QString>
#include <QtQml/qqml.h>

class ApplicationFlowBackend : public QObject
{
    Q_OBJECT
    QML_ELEMENT // Makes it known to QML under its class name

    // Properties from ApplicationFlow.qml
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)
    Q_PROPERTY(QString platform READ platform CONSTANT) // platform is unlikely to change at runtime
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(int brewTime READ brewTime WRITE setBrewTime NOTIFY brewTimeChanged)
    Q_PROPERTY(int coffeeAmount READ coffeeAmount WRITE setCoffeeAmount NOTIFY coffeeAmountChanged)
    Q_PROPERTY(int milkAmount READ milkAmount WRITE setMilkAmount NOTIFY milkAmountChanged)
    Q_PROPERTY(int foamAmount READ foamAmount WRITE setFoamAmount NOTIFY foamAmountChanged)
    Q_PROPERTY(double sugarAmount READ sugarAmount WRITE setSugarAmount NOTIFY sugarAmountChanged)
    Q_PROPERTY(QString coffeeName READ coffeeName WRITE setCoffeeName NOTIFY coffeeNameChanged)
    Q_PROPERTY(QString previousState READ previousState WRITE setPreviousState NOTIFY previousStateChanged)
    Q_PROPERTY(double progressBarValue READ progressBarValue WRITE setProgressBarValue NOTIFY progressBarValueChanged) // QML uses progressBarValue, so double is safer
    Q_PROPERTY(QString progressCupState READ progressCupState WRITE setProgressCupState NOTIFY progressCupStateChanged)

    // Coffee counts - assuming these were tracked somewhere or should be
    Q_PROPERTY(int cappuccinos READ cappuccinos WRITE setCappuccinos NOTIFY cappuccinosChanged)
    Q_PROPERTY(int espressos READ espressos WRITE setEspressos NOTIFY espressosChanged)
    Q_PROPERTY(int lattes READ lattes WRITE setLattes NOTIFY lattesChanged)
    Q_PROPERTY(int macchiatos READ macchiatos WRITE setMacchiatos NOTIFY macchiatosChanged)

    // Current application state, to be managed by this backend
    Q_PROPERTY(QString currentState READ currentState WRITE setCurrentState NOTIFY currentStateChanged)


public:
    explicit ApplicationFlowBackend(QObject *parent = nullptr);

    // Getter methods
    int animationDuration() const;
    QString platform() const;
    QString mode() const;
    int brewTime() const;
    int coffeeAmount() const;
    int milkAmount() const;
    int foamAmount() const;
    double sugarAmount() const;
    QString coffeeName() const;
    QString previousState() const;
    double progressBarValue() const;
    QString progressCupState() const;
    int cappuccinos() const;
    int espressos() const;
    int lattes() const;
    int macchiatos() const;
    QString currentState() const;


    // Setter methods
    void setAnimationDuration(int duration);
    // No setter for platform as it's constant
    void setMode(const QString &mode);
    void setBrewTime(int time);
    void setCoffeeAmount(int amount);
    void setMilkAmount(int amount);
    void setFoamAmount(int amount);
    void setSugarAmount(double amount);
    void setCoffeeName(const QString &name);
    void setPreviousState(const QString &state);
    void setProgressBarValue(double value);
    void setProgressCupState(const QString &state);
    void setCappuccinos(int count);
    void setEspressos(int count);
    void setLattes(int count);
    void setMacchiatos(int count);
    void setCurrentState(const QString &state);

    // Q_INVOKABLE methods (mirrors of QML functions)
    Q_INVOKABLE void themeButton();
    Q_INVOKABLE void selectCappuccino();
    Q_INVOKABLE void selectEspresso();
    Q_INVOKABLE void selectLatte();
    Q_INVOKABLE void selectMacchiato();

    Q_INVOKABLE void backButton();      // Corresponds to QML backButton
    Q_INVOKABLE void confirmButton();   // Corresponds to QML confirmButton
    Q_INVOKABLE void continueBrew();    // Corresponds to QML continueButton
    Q_INVOKABLE void cancelButton();    // Corresponds to QML cancelButton
    Q_INVOKABLE void brewFinished();    // Corresponds to QML onFinished
    Q_INVOKABLE void returnToStart();   // Corresponds to QML onReturnToStart
    Q_INVOKABLE void startCoffeeSelection(); // Corresponds to home.getStartedbutton.onClicked

signals:
    void animationDurationChanged();
    void modeChanged();
    void brewTimeChanged();
    void coffeeAmountChanged();
    void milkAmountChanged();
    void foamAmountChanged();
    void sugarAmountChanged();
    void coffeeNameChanged();
    void previousStateChanged();
    void progressBarValueChanged();
    void progressCupStateChanged();
    void cappuccinosChanged();
    void espressosChanged();
    void lattesChanged();
    void macchiatosChanged();
    void currentStateChanged(); // Signal for state changes

    // Signals to QML to trigger StackView transitions (optional, but good practice)
    // These could also be handled by currentStateChanged and QML bindings.
    void navigateToHome();
    void navigateToCoffeeSelection();
    void navigateToSettings();
    void navigateToInsert();
    void navigateToProgress();
    void navigateToReady();


private:
    int m_animationDuration = 400;
    QString m_platform; // Initialized in constructor
    QString m_mode = "";
    int m_brewTime = 0;
    int m_coffeeAmount = 0;
    int m_milkAmount = 0;
    int m_foamAmount = 0;
    double m_sugarAmount = 0.0;
    QString m_coffeeName = "";
    QString m_previousState = "";
    double m_progressBarValue = 0.0;
    QString m_progressCupState = "0";

    // Initialize coffee counts (example values, adjust as needed)
    int m_cappuccinos = 10;
    int m_espressos = 10;
    int m_lattes = 10;
    int m_macchiatos = 10;

    QString m_currentState = "Home"; // Initial state
};

#endif // APPLICATIONFLOWBACKEND_H
