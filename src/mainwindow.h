#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "Menu.h"

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

    Menu* masterMenu;
    Menu* mainMenuOG;
    QListWidget *activeQListWidget;

    Ui::MainWindow *ui;


private slots:

    void pressedBackButton();
    void pressedMenuButton();
    void pressedUpButton();
    void pressedLeftButton();
    void pressedOkButton();
    void pressedRightButton();
    void pressedDownButton();
    void pressedPowerButton();

};
#endif // MAINWINDOW_H
