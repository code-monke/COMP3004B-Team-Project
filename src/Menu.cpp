
#include <QApplication>
#include "Menu.h"


Menu::Menu(Menu* parentMenu, QStringList items, QListWidget* listWidget){

    this->parentMenu = parentMenu;
    this->items = items;
    this->listWidget = listWidget;
    listWidget->addItems(items);
    listWidget->setCurrentRow(0);
}
Menu::~Menu(){

}

void Menu::inputCommand(Command command){
    qInfo() << "menu: " << command;

}
