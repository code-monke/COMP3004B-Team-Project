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

    sessionStatus = false;

    //default setting at 5 secconds
    breathIntervalSetting = 5;

    interval = -(100/breathIntervalSetting);

    //Graph
    ui->customPlot->hide();

    // Create menu tree
    masterMenu = new Menu("Main menu", {"Start new session","Settings","Log"}, nullptr);
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

    Menu* startNewSession = new Menu("Start new session", {"HRV Session"}, m);
    Menu* settings = new Menu("Settings", {"Challenge level","Breath pacer settings"}, m);
    Menu* log = new Menu("Log", {"View", "Clear"}, m);
    m->addChildMenu(startNewSession);
    m->addChildMenu(settings);
    m->addChildMenu(log);

    Menu* HRVSession = new Menu("HRV Session", {}, startNewSession);
    startNewSession->addChildMenu(HRVSession);

    Menu* challengeLevel = new Menu("Challenge level", {"?","?","?","?"}, settings);
    Menu* breathPacerSettings = new Menu("Breath pacer settings", {"5","10","15","20"}, settings);
    settings->addChildMenu(challengeLevel);
    settings->addChildMenu(breathPacerSettings);

    Menu* viewLog = new Menu("View",{}, log);
    Menu* clearLog = new Menu("Clear", {"Yes","No"}, log);
    log->addChildMenu(viewLog);
    log->addChildMenu(clearLog);
}

void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {

    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);

    ui->menuLabel->setText(selectedMenuItem);
}

void MainWindow::pressedBackButton(){
    qInfo() << "back";

    if (sessionStatus){
        currentSession->stop();
        sessionStatus = false;
        ui->breathPacer->setValue(0);
        ui->lengthLabel->setText("0:00");
        pastSessions.push_back(currentSession);
        ui->customPlot->hide();
        ui->listWidget->show();
    }
    this->navigateBack();
}
void MainWindow::navigateBack(){
    if (masterMenu->getName() == "Main menu") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        masterMenu = masterMenu->getParent();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}
void MainWindow::pressedMenuButton(){
    qInfo() << "menu";

    if (sessionStatus){
        currentSession->stop();
        sessionStatus = false;
        ui->breathPacer->setValue(0);
        ui->lengthLabel->setText("0:00");
        pastSessions.push_back(currentSession);
        ui->customPlot->hide();
        ui->listWidget->show();
    }

    while (masterMenu->getName() != "Main menu") {
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

    int index = activeQListWidget->currentRow();
    if (index < 0) return;

    // Prevent crash if ok button is selected in view and during the session
    if (masterMenu->getName() == "View" || masterMenu->getName() == "HRV Session") {
        return;
    }

    //Logic for starting a new session
    if (masterMenu->getName() == "Main menu" && index == 0){
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu(masterMenu->getMenuItems()[0], {});

        currentSession = new Session(ui->customPlot);
        currentSession->start();

        int currentTimerCount = currentSession->getTime();
        timeString = QString::number(currentTimerCount/60) + ((currentTimerCount%60 < 10) ? + ":0" + QString::number(currentTimerCount%60) : + ":" + QString::number(currentTimerCount%60));

        ui->lengthLabel->setText(timeString);
        connect(currentSession->getTimer(), &QTimer::timeout, this, &MainWindow::updateTimer);

        sessionStatus = true;
        ui->customPlot->show();
        ui->listWidget->hide();
    }

    //Logic for when the menu is the delete menu.
    if (masterMenu->getName() == "Clear") {
        if (masterMenu->getMenuItems()[index] == "Yes") {
//            db->deleteRecords();
            allRecordings.clear();

            for (int x = 0; x < recordings.size(); x++) {
                delete recordings[x];
            }

            recordings.clear();
            navigateBack();
            return;
        }
        else {
            navigateBack();
            return;
        }
    }

    //If the menu is a parent and clicking on it should display more menus.
    if (masterMenu->get(index)->getMenuItems().length() > 0) {
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu(masterMenu->getName(), masterMenu->getMenuItems());


    }
//    //If the menu is not a parent and clicking on it should start a therapy
//    else if (masterMenu->get(index)->getMenuItems().length() == 0 && (masterMenu->getName() == "FREQUENCIES" || masterMenu->getName() == "PROGRAMS")) {
//        if (masterMenu->getName() == "PROGRAMS") {
//            //Update new menu info
//            masterMenu = masterMenu->get(index);
//            MainWindow::updateMenu(programs[index]->getName(), {});
//            MainWindow::beginTherapy(programs[index]);
//        }
//        else if (masterMenu->getName() == "FREQUENCIES") {
//            masterMenu = masterMenu->get(index);
//            MainWindow::updateMenu(frequencies[index]->getName(), {});
//            MainWindow::beginTherapy(frequencies[index]);
//        }
//    }
    //If the button pressed should display the device's recordings.
    else if (masterMenu->get(index)->getName() == "View") {
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu("Recordings", allRecordings);
    }
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
    MainWindow::pressedMenuButton();

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
    qInfo() << "power";

    powerStatus = !powerStatus;
    setPower();
}

void MainWindow::breathPacer(){
    //while the session is still running
    //increase the breathPacer progress bar by an increment of 20 every seccond. Once it reaches 100, decrement it by 20 every second.

    if(sessionStatus){
        if(ui->breathPacer->value() == 100 || ui->breathPacer->value() == 0){
            interval = -interval;
        }
        ui->breathPacer->setValue(ui->breathPacer->value() + interval);
    }
}

void MainWindow::updateTimer(){
    int currentTimerCount = currentSession->getTime();

    timeString = QString::number(currentTimerCount/60) + ((currentTimerCount%60 < 10) ? + ":0" + QString::number(currentTimerCount%60) : + ":" + QString::number(currentTimerCount%60));

    ui->lengthLabel->setText(timeString);

    breathPacer();
}
