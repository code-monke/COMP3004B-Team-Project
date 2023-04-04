#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Menu.h"

#define CMD_UP 1
// etc

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // Create menu tree
    masterMenu = new Menu("MAIN MENU", {"Start new session","Settings","Log"}, nullptr);
    mainMenuOG = masterMenu;
    initializeMainMenu(masterMenu);

    // Initialize the main menu view
    activeQListWidget = ui->listWidget;
    activeQListWidget->addItems(masterMenu->getMenuItems());
    activeQListWidget->setCurrentRow(0);
    ui->menuLabel->setText(masterMenu->getName());

    connect(ui->backButton, SIGNAL(released()), this, SLOT(pressedBackButton()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(pressedMenuButton()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(pressedUpButton()));
    connect(ui->leftButton, SIGNAL(released()), this, SLOT(pressedLeftButton()));
    connect(ui->okButton, SIGNAL(released()), this, SLOT(pressedOkButton()));
    connect(ui->rightButton, SIGNAL(released()), this, SLOT(pressedRightButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(pressedDownButton()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(pressedPowerButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeMainMenu(Menu* m) {



//    QStringList programsList;
//    for (Therapy* p : this->programs) {
//        programsList.append(p->getName());
//    }
//    Menu* programs = new Menu("PROGRAMS", programsList, m);
//    Menu* history = new Menu("HISTORY", {"VIEW","CLEAR"}, m);
//    m->addChildMenu(programs);
//    m->addChildMenu(history);
//    Menu* viewHistory = new Menu("VIEW",{}, history);
//    Menu* clearHistory = new Menu("CLEAR", {"YES","NO"}, history);
//    history->addChildMenu(viewHistory);
//    history->addChildMenu(clearHistory);
}

void MainWindow::pressedBackButton(){
    qInfo() << "back";
}
void MainWindow::pressedMenuButton(){
    qInfo() << "menu";
}
void MainWindow::pressedUpButton(){
    qInfo() << "up";
}
void MainWindow::pressedLeftButton(){
    qInfo() << "left";
}
void MainWindow::pressedOkButton(){
    qInfo() << "ok";
}
void MainWindow::pressedRightButton(){
    qInfo() << "right";
}
void MainWindow::pressedDownButton(){
    qInfo() << "down";
}
void MainWindow::pressedPowerButton(){
    qInfo() << "power";
//    powered = true;
}
