#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Menu.h"

#define CMD_UP 1
// etc

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    powered = false;

    ui->setupUi(this);

    mainMenuSection = new Menu(nullptr, {"Start new session", "Settings", "Log"}, ui->listWidget);
    initMainMenu();
    currentSection = mainMenuSection;

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

void MainWindow::initMainMenu(){

}

//void MainWindow::initSections(Section* menuSection){
//    this->menuSection = menuSection;

//    currentSection = menuSection;
//}

void MainWindow::pressedBackButton(){
    qInfo() << "back";
    Command command = back;
    inputCommand(command);
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
    powered = true;
}

void MainWindow::inputCommand(Command command){
    currentSection->inputCommand(command);
}
