#include <iostream>
#include <string>

#include "rate.h"
#include "ratebase.h"
#include "menu.h"

Rate _getrate_from_user() {
	std::string ratename;
	std::string cost;
	std::string min;
	std::string mb;

	menuf::clear();

	std::cout << "Введите имя тарифа: ";
	std::getline(std::cin, ratename);

	do {
	std::cout << "Введите его абонентную плату: ";
	std::getline(std::cin, cost);
	} while (!is_f(cost));

	std::cout << "Введите колличество бесплатных минут: ";
	std::getline(std::cin, min);

	std::cout << "Введите количество бесплатных мегабайт: ";
	std::getline(std::cin, mb);

	return Rate(ratename, cost, min, mb);
}

int _getattr_from_user() {
	char attr;

	menuf::clear();

	std::cout << "Выберите параметр для сотировки: " << std::endl
			  << "\t1. Имя" << std::endl
			  << "\t2. Стоимость" << std::endl
			  << "\t3. Бесплатные минуты" << std::endl
			  << "\t4. Бесплатные мегабайты" << std::endl;

	attr = menuf::getmenunum('4');
	return attr - '0' - 1;
}

int ratemenu() {
	RateBase *rates = new RateBase;
	char choice;

	do {
		menuf::clear();
		std::cout << "Тарифы: " << std::endl
				  << "\t1. Добавить новый" << std::endl
				  << "\t2. Редактировать" << std::endl
				  << "\t3. Сортировать" << std::endl
				  << std::endl
				  << "4. Выйти в главное меню" << std::endl;
		choice = menuf::getmenunum('4');

		switch (choice) {
		case '1':
			rates->push_back(_getrate_from_user());
			break;
		case '2':
			rates->edit();
			break;
		case '3':
			rates->sort(_getattr_from_user());
			break;
		}
	} while (choice != '4');

	delete rates;
	return 0;
}


