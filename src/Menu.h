#ifndef MENU_H
#define MENU_H

#include <QListWidget>

#include "Section.h"

class Menu : public Section{

public:
    Menu(Menu* parentMenu, QStringList items, QListWidget*);
    ~Menu();
    void inputCommand(Command);
//    void init();

private:
    Menu* parentMenu;
    QStringList items;
    QListWidget* listWidget;
};

#endif // MENU_H
