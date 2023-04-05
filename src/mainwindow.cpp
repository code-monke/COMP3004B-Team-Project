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

    //power off at the start of sim
    powerStatus = false;
    setPower();

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

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {

    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);

    ui->menuLabel->setText(selectedMenuItem);
}

void MainWindow::pressedBackButton(){
    qInfo() << "back";

    if (masterMenu->getName() == "MAIN MENU") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        masterMenu = masterMenu->getParent();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}
void MainWindow::pressedMenuButton(){
    qInfo() << "menu";

    while (masterMenu->getName() != "MAIN MENU") {
        masterMenu = masterMenu->getParent();
    }

    updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
}
void MainWindow::pressedUpButton(){
    qInfo() << "up";

    int nextIndex = activeQListWidget->currentRow() - 1;

    if(nextIndex < 0){
        nextIndex = activeQListWidget->count()-1;
    }

    activeQListWidget->setCurrentRow(nextIndex);

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

    int nextIndex = activeQListWidget->currentRow() + 1;

    if (nextIndex > activeQListWidget->count() - 1) {
        nextIndex = 0;
    }

    activeQListWidget->setCurrentRow(nextIndex);
}
void MainWindow::setPower(){
    qInfo() << "power";

    activeQListWidget->setVisible(powerStatus);
    ui->menuLabel->setVisible(powerStatus);
    ui->programViewWidget->setVisible(powerStatus);

    ui->upButton->setEnabled(powerStatus);
    ui->downButton->setEnabled(powerStatus);
    ui->leftButton->setEnabled(powerStatus);
    ui->rightButton->setEnabled(powerStatus);
    ui->menuButton->setEnabled(powerStatus);
    ui->okButton->setEnabled(powerStatus);
    ui->backButton->setEnabled(powerStatus);
}

void MainWindow::pressedPowerButton(){
    powerStatus = !powerStatus;
    setPower();
}
