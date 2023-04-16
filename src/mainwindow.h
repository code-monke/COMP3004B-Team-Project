#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include "Menu.h"
#include "Record.h"
#include "session.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void initializeMainMenu(Menu*);
    void navigateBack();

    int interval;
    int breathIntervalSetting;

    bool powerStatus;
    bool sessionStatus;

    QString timeString;

    QString highBatteryHealth;
    QString mediumBatteryHealth;
    QString lowBatteryHealth;

    Menu* masterMenu;
    Menu* mainMenuOG;
    QListWidget *activeQListWidget;

    QVector<Record*> recordings;
    QStringList allRecordings;

    Ui::MainWindow *ui;
    //QVector<Session*> pastSessions;
    Session* currentSession;


private slots:

    void pressedBackButton();
    void pressedMenuButton();
    void pressedUpButton();
    void pressedLeftButton();
    void pressedOkButton();
    void pressedRightButton();
    void pressedDownButton();
    void pressedPowerButton();
    void setPower();
    void breathPacer();
    void updateTimer();
    void updateMenu(const QString selectedMenuItem, const QStringList menuItems);
    void changeBatteryLevel();
    void onSessionUpdated(double achieveScore, double cohScore, int curCohLvl);
    void onSessionFinished(Record *record);

};
#endif // MAINWINDOW_H
