#include <iostream>
#include <string>

#include "logpass.h"
#include "menu.h"

void _getusertype_from_admin(prsinfo::Users *users) {
	char choice;
	menuf::clear();
	std::cout << "Добавить: " << std::endl
			  << "\t1. Пользователя" << std::endl
			  << "\t2. Админа" << std::endl;
	choice = menuf::getmenunum('2');

	switch (choice) {
	case '1':
		users->add();
		break;
	case '2':
		users->add(admin);
		break;
	}
}


void adminmenu() {
	const char EXIT = '6';
	prsinfo::Users *users = new prsinfo::Users;

	char choice;

	do {
		menuf::clear();
		std::cout << "Возможности администратора: " << std::endl
				  << "\t1. Добавление пользователя" << std::endl
				  << "\t2. Вывод пользователей" << std::endl
				  << "\t3. Поиск" << std::endl
				  << "\t4. Удаление пользователей" << std::endl
				  << "\t5. Изменить пользоваетеля" << std::endl;
		std::cout << std::endl << "6. Выход в главное меню";
		choice = menuf::getmenunum('6');

		switch (choice) {
		case '1':
			_getusertype_from_admin(users);
			break;
		case '2':
			menuf::clear();
			std::cout << *users << std::endl;
			break;
		case '3':
			users->srch();
			break;
		case '4':
			users->dltuser();
			break;
		case '5':
			users->chng();
			break;
		}

	} while (choice != EXIT);

	delete users;

}
