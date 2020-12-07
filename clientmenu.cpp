#include <iostream>
#include <string>

#include "client.h"
#include "clientbase.h"
#include "menu.h"
#include "errcheck.h"

void _getclient_from_user(ClientBase *clients) {


	menuf::clear();

	ClientBase::typecl type;
	char tpchoice;
	std::cout << "Выберите наименования пользователя:" << std::endl
			  << "\t1. Физическое лицо" << std::endl
			  << "\t2. Юридическое лицо" << std::endl;
	tpchoice = menuf::getmenunum('2');
	switch (tpchoice) {
	case '1':
		type = ClientBase::individual;
		break;
	case '2':
		type = ClientBase::legalentity;
	}

	std::string name;
	std::cout << std::endl << "Введите ФИО или название юр. лица: ";
	std::getline(std::cin, name);

	std::string contract;
	std::cout << "Введите номер договора с клиентом: ";
	std::getline(std::cin, contract);

	clients->generatecl(type, name, contract);
}

int _getsattr_from_user() {
	menuf::clear();

	char choice;

	std::cout << "Параметр для сортировки: " << std::endl
			  << "\t1. Имя" << std::endl
			  << "\t2. Тариф" << std::endl
			  << "\t3. Баланс" << std::endl;
	choice = menuf::getmenunum('3');
	return choice - '0';
}

int clientmenu() {
	RateBase *rates = new RateBase;
	ClientBase *clients = new ClientBase(*rates);
	char choice;

	do {
		menuf::clear();
		std::cout << "Пользователи: " << std::endl
				  << "\t1. Добавить нового" << std::endl
				  << "\t2. Редактировать" << std::endl
				  << "\t3. Сортировать" << std::endl
				  << std::endl
				  << "4. Выйти в главное меню" << std::endl;
		choice = menuf::getmenunum('4');

		switch (choice) {
		case '1':
			_getclient_from_user(clients);
			break;
		case '2':
			clients->edit();
			break;
		case '3':
			clients->sort(_getsattr_from_user());
			break;
		}
	} while (choice != '4');

	delete clients;
	delete rates;
	return 0;
}
