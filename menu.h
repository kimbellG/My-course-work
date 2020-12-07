#ifndef MENU_H
#define MENU_H


#include "ratebase.h"
#include "clientbase.h"
#include "logpass.h"

namespace menuf {
	char getmenunum(const char end, const char start = '1'); //Основная функция взаимодействия с интерфейсом
	void pause();                                            //Функция ожидания ввода пользователя. Применяется для остановки после выбора.
	void clear();
}

//Функции подменю
int ratemenu();
int clientmenu();
void adminmenu();

#endif // MENU_H
