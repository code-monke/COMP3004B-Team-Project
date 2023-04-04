#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "Menu.h"
#include "Record.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HRVGraph;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    void initializeMainMenu(Menu*);
    void navigateBack();

    bool powerStatus;

    Menu* masterMenu;
    Menu* mainMenuOG;
    QListWidget *activeQListWidget;

    QVector<Record*> recordings;
    QStringList allRecordings;

    Ui::MainWindow *ui;
    HRVGraph *graph;


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
    void updateMenu(const QString selectedMenuItem, const QStringList menuItems);

};
#endif // MAINWINDOW_H
