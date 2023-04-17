#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "Menu.h"
#include <iostream>

using namespace std;

#define CMD_UP 1
// etc

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    //variable which tracks session status
    sessionStatus = false;

    //default setting at 10 secconds
    breathIntervalSetting = 10;

    //amount of time between inhaling and exhaling
    interval = -(100/breathIntervalSetting);

    //Graph
    ui->customPlot->hide();

    //Light
    ui->cohLight->setStyleSheet("");

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

    // UI Connections
    connect(ui->backButton, SIGNAL(released()), this, SLOT(pressedBackButton()));
    connect(ui->menuButton, SIGNAL(released()), this, SLOT(pressedMenuButton()));
    connect(ui->upButton, SIGNAL(released()), this, SLOT(pressedUpButton()));
    connect(ui->leftButton, SIGNAL(released()), this, SLOT(pressedLeftButton()));
    connect(ui->okButton, SIGNAL(released()), this, SLOT(pressedOkButton()));
    connect(ui->rightButton, SIGNAL(released()), this, SLOT(pressedRightButton()));
    connect(ui->downButton, SIGNAL(released()), this, SLOT(pressedDownButton()));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(pressedPowerButton()));
    connect(ui->chargeAdminButton, SIGNAL(released()), this, SLOT(changeBatteryLevel()));

    //battery bar color style sheet
    highBatteryHealth = "QProgressBar { selection-background-color: rgb(78, 154, 6); background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); }";
    mediumBatteryHealth = "QProgressBar { selection-background-color: rgb(196, 160, 0); background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); }";
    lowBatteryHealth = "QProgressBar { selection-background-color: rgb(164, 0, 0); background-color: rgb(0, 0, 0); color: rgb(255, 255, 255); }";
}

MainWindow::~MainWindow()
{
    delete mainMenuOG;
    delete ui;

    for (int i = 0; i < recordings.size(); i++) {
        delete recordings[i];
    }
}

void MainWindow::initializeMainMenu(Menu* m) {

    //Creating 3 main menus with their sub menus
    Menu* startNewSession = new Menu("Start new session", {"High Coherence Test", "Medium Coherence Test", "Low Coherence Test"}, m);
    Menu* settings = new Menu("Settings", {"Challenge level","Breath pacer settings"}, m);
    Menu* log = new Menu("Log", {"View", "Clear"}, m);
    m->addChildMenu(startNewSession);
    m->addChildMenu(settings);
    m->addChildMenu(log);

    //new session sub menus, 3 different tests
    Menu* HCTSession = new Menu("High Coherence Test", {}, startNewSession);
    Menu* MCTSession = new Menu("Medium Coherence Test", {}, startNewSession);
    Menu* LCTSession = new Menu("Low Coherence Test", {}, startNewSession);
    startNewSession->addChildMenu(HCTSession);
    startNewSession->addChildMenu(MCTSession);
    startNewSession->addChildMenu(LCTSession);

    //setting submenus
    Menu* challengeLevel = new Menu("Challenge level", {"?","?","?","?"}, settings);
    Menu* breathPacerSettings = new Menu("Breath pacer settings", {"4","5","10","20"}, settings);
    settings->addChildMenu(challengeLevel);
    settings->addChildMenu(breathPacerSettings);

    //log submenus
    Menu* viewLog = new Menu("View",{}, log);
    Menu* clearLog = new Menu("Clear", {"Yes","No"}, log);
    log->addChildMenu(viewLog);
    log->addChildMenu(clearLog);

    //making labels 0 or 0:00
    ui->lengthLabel->setText("0:00");
    ui->achievementLabel->setText("0");
    ui->coherenceLabel->setText("0");
}

//updating the listwidget with menu items
void MainWindow::updateMenu(const QString selectedMenuItem, const QStringList menuItems) {

    activeQListWidget->clear();
    activeQListWidget->addItems(menuItems);
    activeQListWidget->setCurrentRow(0);

    ui->menuLabel->setText(selectedMenuItem);
}

//actions took upon back button press
void MainWindow::pressedBackButton(){

    //if the session is ruinning, save the session and exit back. Otherwise navigate back
    if (sessionStatus){
        currentSession->finish();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
    else{
        this->navigateBack();
    }
}

//going back to parent menu of current menu
void MainWindow::navigateBack(){
    if (masterMenu->getName() == "Main menu") {
        activeQListWidget->setCurrentRow(0);
    }
    else {
        masterMenu = masterMenu->getParent();
        updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
    }
}

//actions took upon pressing menu button
void MainWindow::pressedMenuButton(){

    //if session is running, save session
    if (sessionStatus){
        currentSession->finish();
    }

    //going back to main menu
    while (masterMenu->getName() != "Main menu") {
        masterMenu = masterMenu->getParent();
    }

    updateMenu(masterMenu->getName(), masterMenu->getMenuItems());
}

//actions made upon pressing the up button
void MainWindow::pressedUpButton(){

    //above row if not less than 0
    int nextIndex = activeQListWidget->currentRow() - 1;

    if(nextIndex < 0){
        nextIndex = activeQListWidget->count()-1;
    }

    activeQListWidget->setCurrentRow(nextIndex);

}
void MainWindow::pressedLeftButton(){

}

//actions made upon pressing the ok button
void MainWindow::pressedOkButton(){


    int index = activeQListWidget->currentRow();
    if (index < 0) return;

    // Prevent crash if ok button is selected in view
    if (masterMenu->getName() == "View") {
        return;
    }

    //Logic for starting a new session
    if (masterMenu->getName() == "Start new session" && ui->hrContactComboBox->currentIndex() == 1){
        if(index == 0){
            currentSession = new Session(ui->customPlot, HIGH_COH);
            MainWindow::updateMenu("High Coherence Test", {});
        }
        else if(index == 1){
            currentSession = new Session(ui->customPlot, MED_COH);
            MainWindow::updateMenu("Medium Coherence Test", {});
        }
        else if(index == 2){
            currentSession = new Session(ui->customPlot, LOW_COH);
            MainWindow::updateMenu("Low Coherence Test", {});
        }

        //Load Session
        currentSession->start();
        connect(currentSession, &Session::sessionUpdated, this, &MainWindow::onSessionUpdated);
        connect(currentSession, &Session::sessionFinished, this, &MainWindow::onSessionFinished);

        //creating time string
        int currentTimerCount = currentSession->getTime();
        timeString = QString::number(currentTimerCount/60) + ((currentTimerCount%60 < 10) ? + ":0" + QString::number(currentTimerCount%60) : + ":" + QString::number(currentTimerCount%60));
        ui->lengthLabel->setText(timeString);

        //using signal to work with timer used in session class
        connect(currentSession->getTimer(), &QTimer::timeout, this, &MainWindow::updateTimer);

        //session status is true and list widget is hidden and custom plot is shown
        sessionStatus = true;
        ui->customPlot->show();
        ui->listWidget->hide();
        return;
    }
    //Message box is displayed if hr contact is not on and when trying to start session
    else if(masterMenu->getName() == "Start new session" && ui->hrContactComboBox->currentIndex() == 0){
        QMessageBox hrContact;
        hrContact.setText("HR Contact Disconnected");
        hrContact.setIcon(QMessageBox::Warning);
        hrContact.setWindowTitle("HR Disconnected");
        hrContact.setStandardButtons(QMessageBox::Ok);
        hrContact.setDefaultButton(QMessageBox::Ok);
        hrContact.exec();
        return;
    }

    //logic for setting breath interval
    if(masterMenu->getName() == "Breath pacer settings"){
        breathIntervalSetting = (activeQListWidget->currentItem()->text()).toInt();
        interval = -(100/breathIntervalSetting);
        navigateBack();
        return;
    }

    //Logic for when the menu is the clear menu.
    if (masterMenu->getName() == "Clear") {
        if (masterMenu->getMenuItems()[index] == "Yes") {
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
    //If the button pressed should display the device's recordings.
    else if (masterMenu->get(index)->getName() == "View") {
        masterMenu = masterMenu->get(index);
        MainWindow::updateMenu("Recordings", allRecordings);
    }
}
void MainWindow::pressedRightButton(){

}

//actions done upon pressing down button
void MainWindow::pressedDownButton(){

    //selects row below selected row
    int nextIndex = activeQListWidget->currentRow() + 1;

    if (nextIndex > activeQListWidget->count() - 1) {
        nextIndex = 0;
    }

    activeQListWidget->setCurrentRow(nextIndex);
}

//turning off/on buttons and widgets based on power status
void MainWindow::setPower(){
    MainWindow::pressedMenuButton();

    activeQListWidget->setVisible(powerStatus);
    ui->menuLabel->setVisible(powerStatus);
    ui->programViewWidget->setVisible(powerStatus);
    ui->hrContactComboBox->setCurrentIndex(0);

    ui->upButton->setEnabled(powerStatus);
    ui->downButton->setEnabled(powerStatus);
    ui->leftButton->setEnabled(powerStatus);
    ui->rightButton->setEnabled(powerStatus);
    ui->menuButton->setEnabled(powerStatus);
    ui->okButton->setEnabled(powerStatus);
    ui->backButton->setEnabled(powerStatus);
}

//actions made upon pressing power button
void MainWindow::pressedPowerButton(){

    //changing power status when power button is pressed
    if(ui->batteryBar->value() == 0){
        powerStatus = false;
    }
    else{
        powerStatus = !powerStatus;
    }

    setPower();
}

//breathpacer logic
void MainWindow::breathPacer(){

    //if session is running, make the breathpacer increase at an interval and decrease at an interval. (breathing in and breating out)
    if(sessionStatus){
        if(ui->breathPacer->value() == 100 || ui->breathPacer->value() == 0){
            interval = -interval;
        }
        ui->breathPacer->setValue(ui->breathPacer->value() + interval);
    }
}

//This method updates different things correlated with the timer
void MainWindow::updateTimer(){

    //creating time string
    int currentTimerCount = currentSession->getTime();
    timeString = QString::number(currentTimerCount/60) + ((currentTimerCount%60 < 10) ? + ":0" + QString::number(currentTimerCount%60) : + ":" + QString::number(currentTimerCount%60));
    ui->lengthLabel->setText(timeString);

    //discharging battery
    ui->batteryLevelAdminSpinBox->setValue(ui->batteryLevelAdminSpinBox->value()-0.5);
    int newLevelInt = int(ui->batteryLevelAdminSpinBox->value());
    ui->batteryBar->setValue(newLevelInt);

    //if no more battery, turn off the device
    if(ui->batteryLevelAdminSpinBox->value() == 0){
        pressedPowerButton();
        return;
    }

    //if the battery level is 10, warn the user to charge the battery
    if(ui->batteryLevelAdminSpinBox->value() == 10){
        QMessageBox batteryWarning;
        batteryWarning.setText("10% Battery charge left\n\nConnect to charger");
        batteryWarning.setIcon(QMessageBox::Warning);
        batteryWarning.setWindowTitle("Battery Level Low Warning");
        batteryWarning.setStandardButtons(QMessageBox::Ok);
        batteryWarning.setDefaultButton(QMessageBox::Ok);
        batteryWarning.exec();
    }

    //switching style sheet based on battery percentage
    int batteryLevel = ui->batteryBar->value();
    if (batteryLevel >= 50) {
        ui->batteryBar->setStyleSheet(highBatteryHealth);
    }
    else if (batteryLevel >= 20) {
        ui->batteryBar->setStyleSheet(mediumBatteryHealth);
    }
    else {
        ui->batteryBar->setStyleSheet(lowBatteryHealth);
    }

    //if hr is disconnect while session, display warning message
    if(ui->hrContactComboBox->currentIndex() == 0){
        QMessageBox hrContact;
        hrContact.setText("HR Contact Disconnected");
        hrContact.setIcon(QMessageBox::Warning);
        hrContact.setWindowTitle("HR Disconnected");
        hrContact.setStandardButtons(QMessageBox::Ok);
        hrContact.setDefaultButton(QMessageBox::Ok);
        hrContact.exec();
        pressedBackButton();
    }

    //change breath pacer
    breathPacer();
}

//changing battery level upon pressing recharge button
void MainWindow::changeBatteryLevel(){

    //getting integer value and setting it to batterybar
    int newLevelInt = int(ui->batteryLevelAdminSpinBox->value());
    ui->batteryBar->setValue(newLevelInt);

    //switching the style sheet
    if (newLevelInt >= 50) {
        ui->batteryBar->setStyleSheet(highBatteryHealth);
    }
    else if (newLevelInt >= 20) {
        ui->batteryBar->setStyleSheet(mediumBatteryHealth);
    }
    else {
        ui->batteryBar->setStyleSheet(lowBatteryHealth);
    }

    //turning off the device if battery is at 0%
    if(ui->batteryBar->value() == 0){
        pressedPowerButton();
    }
}

/*
 * Update coherence and achievement score labels
 * Update coherence level light
*/
void MainWindow::onSessionUpdated(double achieveScore, double cohScore, int curCohLvl){
    if (cohScore != -1) ui->coherenceLabel->setText(QString::number(cohScore));
    ui->achievementLabel->setText(QString::number(achieveScore));

    // Update light
    if (curCohLvl == HIGH_COH) {
        QString style = "background-color: green;";
        ui->cohLight->setStyleSheet(style);
        qInfo() << "Beep!";
    }
    else if (curCohLvl == MED_COH) {
        QString style = "background-color: blue;";
        ui->cohLight->setStyleSheet(style);
        qInfo() << "Beep!";
    }
    else if (curCohLvl == LOW_COH){
        QString style = "background-color: red;";
        ui->cohLight->setStyleSheet(style);
        qInfo() << "Beep!";
    }
}

/*
 * Reset UI
 * Showing summary view
 * Updating log history
*/
void MainWindow::onSessionFinished(Record *record){
    //Reset UI
    sessionStatus = false;
    ui->coherenceLabel->setText(QString::number(0));
    ui->achievementLabel->setText(QString::number(0));
    ui->cohLight->setStyleSheet(QString(""));
    ui->breathPacer->setValue(0);
    ui->lengthLabel->setText("0:00");

    //updating records
    recordings.append(record);
    allRecordings += recordings.last()->toString();

    //hiding plot and showing listwidget
    ui->customPlot->hide();
    ui->listWidget->show();
}
