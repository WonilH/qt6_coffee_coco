#ifndef APPLICATIONFLOWBACKEND_H
#define APPLICATIONFLOWBACKEND_H

#include <QObject>

class ApplicationFlowBackend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int animationDuration READ animationDuration WRITE setAnimationDuration NOTIFY animationDurationChanged)
    Q_PROPERTY(QString platform READ platform CONSTANT)
    Q_PROPERTY(QString mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(int brewTime READ brewTime WRITE setBrewTime NOTIFY brewTimeChanged)
    Q_PROPERTY(int coffeeAmount READ coffeeAmount WRITE setCoffeeAmount NOTIFY coffeeAmountChanged)
    Q_PROPERTY(int milkAmount READ milkAmount WRITE setMilkAmount NOTIFY milkAmountChanged)
    Q_PROPERTY(int foamAmount READ foamAmount WRITE setFoamAmount NOTIFY foamAmountChanged)
    Q_PROPERTY(double sugarAmount READ sugarAmount WRITE setSugarAmount NOTIFY sugarAmountChanged)
    Q_PROPERTY(bool darkTheme READ darkTheme WRITE setDarkTheme NOTIFY darkThemeChanged)
    Q_PROPERTY(int cappuccinos READ cappuccinos WRITE setCappuccinos NOTIFY cappuccinosChanged)
    Q_PROPERTY(int lattes READ lattes WRITE setLattes NOTIFY lattesChanged)
    Q_PROPERTY(int espressos READ espressos WRITE setEspressos NOTIFY espressosChanged)
    Q_PROPERTY(int macchiatos READ macchiatos WRITE setMacchiatos NOTIFY macchiatosChanged)

public:
    explicit ApplicationFlowBackend(QObject *parent = nullptr);

    int animationDuration() const { return m_animationDuration; }
    void setAnimationDuration(int value);

    QString platform() const { return m_platform; }

    QString mode() const { return m_mode; }
    void setMode(const QString &value);

    int brewTime() const { return m_brewTime; }
    void setBrewTime(int value);

    int coffeeAmount() const { return m_coffeeAmount; }
    void setCoffeeAmount(int value);

    int milkAmount() const { return m_milkAmount; }
    void setMilkAmount(int value);

    int foamAmount() const { return m_foamAmount; }
    void setFoamAmount(int value);

    double sugarAmount() const { return m_sugarAmount; }
    void setSugarAmount(double value);

    bool darkTheme() const { return m_darkTheme; }
    void setDarkTheme(bool value);

    int cappuccinos() const { return m_cappuccinos; }
    void setCappuccinos(int value);

    int lattes() const { return m_lattes; }
    void setLattes(int value);

    int espressos() const { return m_espressos; }
    void setEspressos(int value);

    int macchiatos() const { return m_macchiatos; }
    void setMacchiatos(int value);

public slots:
    void setRoot(QObject *root);
    void themeButton();
    void cappuccino();
    void espresso();
    void latte();
    void macchiato();
    void getStarted();
    void backButton();
    void confirmButton();
    void continueButton();
    void cancelButton();
    void onFinished();
    void onReturnToStart();

signals:
    void animationDurationChanged();
    void modeChanged();
    void brewTimeChanged();
    void coffeeAmountChanged();
    void milkAmountChanged();
    void foamAmountChanged();
    void sugarAmountChanged();
    void darkThemeChanged();
    void cappuccinosChanged();
    void lattesChanged();
    void espressosChanged();
    void macchiatosChanged();

    // navigation requests handled in QML
    void pushChoosingCoffee();
    void pushSettings();
    void pushInsert();
    void pushProgress();
    void pushReady();
    void pop();
    void popToIndex(int index);

private:
    QObject *m_root = nullptr;
    int m_animationDuration = 400;
    QString m_platform;
    QString m_mode;
    int m_brewTime = 0;
    int m_coffeeAmount = 0;
    int m_milkAmount = 0;
    int m_foamAmount = 0;
    double m_sugarAmount = 0.0;
    bool m_darkTheme = true;
    int m_cappuccinos = 4;
    int m_lattes = 5;
    int m_espressos = 6;
    int m_macchiatos = 4;
};

#endif // APPLICATIONFLOWBACKEND_H
