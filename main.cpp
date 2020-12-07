#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <windows.h>

#include "logpass.h"
#include "ratebase.h"
#include "clientbase.h"
#include "menu.h"

prsinfo::position authentication(std::string login, std::string password);

using namespace std;
using namespace menuf;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	prsinfo::Users *users = new prsinfo::Users;

	string login;
	char pass[20];
	prsinfo::position pos;


	do {
		cout << "Введите логин: ";
		std::getline(cin, login);
		cout << "Введите пароль: ";
		input_password(pass);

		pos = users->authentication(login, pass);

		if (pos == prsinfo::position::none){
			cout << "Неверный логин или пароль! Повторите попытку." << std::endl;
			getch();
		}
		clear();
	} while (pos == prsinfo::position::none);

	delete users;

	cout << "Доброго времени суток, давайте начнем работу!" << std::endl;
	pause();

	char choice;

	bool isadmin = pos == prsinfo::position::admin;
	do {
		clear();
		cout << "Выберите необходимый пункт меню." << std::endl
			 << "\t1. Работа над тарифами" << std::endl
			 << "\t2. Работа над информацией пользователей" << std::endl
			 << "\t3. Выход из программы" << std::endl << std::endl
			 << ((isadmin) ? "\t4. Фунции администрирования" : "") << std::endl;

		choice = getmenunum((isadmin) ? '4' : '3');

		switch (choice) {
		case '1':
			ratemenu();
			break;

		case '2':
			clientmenu();
			break;

		case '4':
			adminmenu();
			break;

		}
	} while (choice != '3');

	return 0;
}
