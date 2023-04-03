#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
}
