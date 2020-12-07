#include "logpass.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "errcheck.h"
#include "require.h"

using namespace prsinfo;

Users::Users() {
	std::ifstream in("PersonalData.dat");

	if (!in) {
		std::cout << "Первый запуск. Создание первого админа." << std::endl;
		add(admin);
		return;
	}

	in.seekg(0);
	personaldata tmp;

	while(!in.eof()) {
		std::getline(in, tmp.surname, ':');
		std::getline(in, tmp.name, ':');
		std::getline(in, tmp.midname, ':');
		std::getline(in, tmp.numpassport, ':');
		std::string contract;
		std::getline(in, contract, ':');

		tmp.contract = std::stoi(contract);
		std::getline(in, tmp.userlog.login, ':');
		std::getline(in, tmp.userlog.password, ':');
		in >> tmp.userlog.position;
//		in.read(reinterpret_cast<char*>(&tmp), sizeof (personaldata));
		std::getline(in, contract);

		userbase.push_back(tmp);
	} ;
}

void Users::add() {
	personaldata new_worker;

	const int wid = 30;

	std::cout << "Заполните все поля данными сотрудника." << std::endl;
	std::cout << std::setw(wid) << std::right << "Фамилия: ";
	std::getline(std::cin, new_worker.surname);
	std::cout << std::setw(wid) << std::right << "Имя: ";
	std::getline(std::cin, new_worker.name);
	std::cout << std::setw(wid) << std::right << "Отчество: ";
	std::getline(std::cin, new_worker.midname);
	std::cout << std::setw(wid) << std::right << "Номер паспорта: ";
	std::getline(std::cin, new_worker.numpassport);
	std::cout << std::setw(wid) << std::right << "Номер договора: ";
	std::cin >> new_worker.contract;
	std::cout << std::endl;

	std::cout << std::setw(wid) << std::right << "Логин: ";
	std::getline(std::cin, new_worker.userlog.login);
	std::getline(std::cin, new_worker.userlog.login);
	std::cout << std::setw(wid) << std::right << "Пароль(до 20-ти символов): ";
	char buf[20];
	input_password(buf);
	new_worker.userlog.password = std::string(buf);

	std::cout << std::endl;
	std::cout << std::setw(wid - 10) << std::right
			  << "1." << " Консультант" << std::endl

			   << std::setw(wid - 10) << std::right
			  << "2." << " Бухгалтер" << std::endl

			  << std::setw(wid - 10) << std::right
			  << "3." <<" Аналитик" << std::endl

			  << std::setw(wid - 10) << std::right
			  << "4." << " Создатель тарифов" << std::endl;

	new_worker.userlog.position = getnum_in_interval("Выберите должность: ", 1, 4, wid) - 1 + '0';
	userbase.push_back(new_worker);
}
void Users::add(int) {
	personaldata new_worker;

	const int wid = 30;

	std::cout << "Заполните все поля данными сотрудника." << std::endl;
	std::cout << std::setw(wid) << std::right << "Фамилия: ";
	std::getline(std::cin, new_worker.surname);
	std::cout << std::setw(wid) << std::right << "Имя: ";
	std::getline(std::cin, new_worker.name);
	std::cout << std::setw(wid) << std::right << "Отчество: ";
	std::getline(std::cin, new_worker.midname);
	std::cout << std::setw(wid) << std::right << "Номер паспорта: ";
	std::getline(std::cin, new_worker.numpassport);
	std::cout << std::setw(wid) << std::right << "Номер договора: ";
	std::cin >> new_worker.contract;
	std::cout << std::endl;

	std::cout << std::setw(wid) << std::right << "Логин: ";
	std::getline(std::cin, new_worker.userlog.login);
	std::getline(std::cin, new_worker.userlog.login);
	std::cout << std::setw(wid) << std::right << "Пароль(до 20-ти символов): ";
	char buf[20];
	input_password(buf);
	new_worker.userlog.password = std::string(buf);

	new_worker.userlog.position = '4';
	userbase.push_back(new_worker);
}

Users::~Users() {
	std::ofstream datafile("PersonalData.dat");
	std::ofstream flog("users.dat");
	assure(datafile, "PersonalData.dat");
	assure(flog, "users.dat");

	std::vector<personaldata>::iterator iter;
	iter = userbase.begin();
	while (iter != userbase.end()) {
		datafile << (*iter).surname << ':' << (*iter).name << ':' <<(*iter).midname << ':'
				 << (*iter).numpassport << ':' << (*iter).contract << ':'
				 << (*iter).userlog.login  << ':' << (*iter).userlog.password << ':' << (*iter).userlog.position << std::endl;
//		datafile.write(reinterpret_cast<char *>(&(*iter)), sizeof (personaldata));
		flog << (*iter).userlog.login << ":" << (*iter).userlog.password << ':' << (*iter).userlog.position << std::endl;
		*iter++;
	}
	userbase.clear();
}
