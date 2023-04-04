#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include "Command.h"
#include "Section.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void init_sections(Section*, Section*, Section*, Section*);
    void initSections(Section*);

    void inputCommand(Command);

private:
    void initMainMenu();

    Ui::MainWindow *ui;

    Section* currentSection;
    Section* mainMenuSection;
    //etc
    QListWidget* listView;
    bool powered;

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
