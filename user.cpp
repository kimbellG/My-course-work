#include "logpass.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

#include "errcheck.h"
#include "require.h"

#include <iomanip>



static std::ostream& matrix(std::ostream& stream) {
	stream << std::setw(20) << std::setfill(' ');
	return stream;
}
static std::ostream& width(std::ostream& stream){
	stream << std::setw(20) << std::setfill('_');
	return stream;
}


using namespace prsinfo;

const char* prsinfo::textpos[] = {"consultant", "accountant", "analyst", "devrate", "admin"};
const char* Users::namearg[] = {"Фамилия", "Имя", "Отчество", "Номер паспорта", "Номер договора", "Логин", "Пароль", "Должность"};

Users::Users() : manip(25, 3) {
	std::ifstream in("PersonalData.dat");

	if (!in) {

		std::cout << "Первый запуск. Создание первого админа." << std::endl;
		getch();
		add(1);
		return;
	}

	in.seekg(0);
	personaldata tmp;

	while(std::getline(in, tmp.surname, ':')) {
		std::getline(in, tmp.name, ':');
		std::getline(in, tmp.midname, ':');
		std::getline(in, tmp.numpassport, ':');
		std::string contract;

		std::getline(in, contract, ':');
		tmp.contract = std::stoi(contract);
		std::getline(in, tmp.userlog.login, ':');
		std::getline(in, tmp.userlog.password, ':');

		int pos;
		in >> pos;
		tmp.userlog.pos = checkpos(pos);

//		in.read(reinterpret_cast<char*>(&tmp), sizeof (personaldata));
		std::getline(in, contract);

		userbase.push_back(tmp);
	} ;
}

const personaldata Users::crtuser(bool isadmin) {
	personaldata new_worker;

	const int wid = 30;

	std::cout << std::setfill(' ');
	std::cout << "Заполните все поля данными сотрудника." << std::endl;
	std::cout << std::setw(wid) << std::right << "Фамилия: ";
	std::getline(std::cin, new_worker.surname);
	std::cout << std::setw(wid) << std::right << "Имя: ";
	std::getline(std::cin, new_worker.name);
	std::cout << std::setw(wid) << std::right << "Отчество: ";
	std::getline(std::cin, new_worker.midname);
	std::cout << std::setw(wid) << std::right << "Номер паспорта: ";
	std::getline(std::cin, new_worker.numpassport);
	std::cout << std::setw(wid) << std::right << "Номер контракта: ";
	new_worker.contract = getpositivenum("", (std::string("Введите число от 0 до ") + std::to_string(INT_MAX)).c_str());

	std::cin.ignore(32767, '\n');
	std::cout << std::setw(wid) << std::right << "Логин: ";
	std::getline(std::cin, new_worker.userlog.login);
	std::cout << std::setw(wid) << std::right << "Пароль(Менее 20 символов): ";
	char buf[20];
	unsigned char hash[100];
	input_password(buf);
	SHA1((unsigned char *)buf, strlen(buf), hash);
	new_worker.userlog.password = std::string((char *)hash);

	if (!isadmin) {
		std::cout << std::endl;
		std::cout << std::setw(wid - 10) << std::right
				  << "1." << " Консультант" << std::endl

				  << std::setw(wid - 10) << std::right
				  << "2." << " Бухгалтер" << std::endl

				  << std::setw(wid - 10) << std::right
				  << "3." <<" Аналитик" << std::endl

				  << std::setw(wid - 10) << std::right
				  << "4." << " Создатель тарифов" << std::endl

				  << std::setw(wid - 10) << std::right
				  << "5." << " Админ" << std::endl;
	}
	new_worker.userlog.pos = (!isadmin) ?
				checkpos(getnum_in_interval("Выберите должность: ", 1, 6, "Выберите от одного до четырёх.", wid) - 1) : admin;

	return new_worker;
}

void Users::add() {
	system("cls");
	userbase.push_back(crtuser(false));
}
void Users::add(int) {
	system("cls");
	userbase.push_back(crtuser(true));
}

void Users::content(std::ostream &os) const {
	os << " __";
	for (int k = 0; k < 8; k++)
		os << width << '_';
	os << ' ' << std::endl;

	os << "|  |";
	for (size_t i = 0; i < 8; i++)
		os << matrix << std::string(Users::namearg[i]) + "|";
	os << " " << std::endl << '|' << "__|";

	for (int k = 0; k < 8; k++)
		os << width << "|";
	os << std::endl;
}
void Users::printel(std::ostream &os, size_t index) const {

		os << "|" << index + 1 << " |";
		os << matrix << userbase[index].surname + "|";
		os << matrix << userbase[index].name + "|";
		os << matrix << userbase[index].midname + "|";
		os << matrix << userbase[index].numpassport + "|";
		os << matrix << std::to_string(userbase[index].contract) + "|";
		os << matrix << userbase[index].userlog.login + "|";
		os << matrix << "x|";
		os << matrix << std::string(textpos[userbase[index].userlog.pos]) + "|";
		os << " " << std::endl << "|__|";

		for (int k = 0; k < 8; k++)
			os << width << "|";
		os << std::endl;
}
std::ostream& prsinfo::operator<<(std::ostream &os, const Users& info) {
	system("cls");
	info.content(os);
	for (size_t i = 0; i < info.userbase.size(); i++)
		info.printel(os, i);
	getch();
	return os;
}

void Users::srch() {
	system("cls");
	std::cout << "ПОИСК." << std::endl;

	for (size_t i = 0, j = 0; i < 6; i++, j++) {
		std::cout << std::setw(10) << std::right << std::setfill(' ') << std::to_string(j + 1) + '.' << namearg[i] << std::endl;
		if (i == 0)
			i += 3;
	}

	std::string needed;
	int choice = getnum_in_interval("Выберите параметр для поиска: ", 1, 3, (std::string("Введите число от 0 до ") + std::to_string(INT_MAX)).c_str(),10);

	std::cout << ((choice == 1) ? namearg[0] : (choice == 2) ? namearg[4] : namearg[5]) << ": ";
	COORD before = manip.GetConsoleCursorPosition();
	COORD after;
	std::vector<size_t> result;

	char c;
	while ((c = getch()) != '\r') {

		if (c == '\b' && needed.size() != 0) {
			needed.pop_back();
			manip.backspace();
			before.X--;
		} else if (c != '\b'){
			std::cout << c;
			needed.push_back(c);
			before.X++;
		}

		COORD before_output = {0, short(before.Y + 1)};
		manip.clear_window(before_output, userbase.size());
		content(std::cout);

		srch(needed, choice, result);
		after = manip.GetConsoleCursorPosition();
		manip.SetConsoleCursorPosition(before);
	}

	manip.SetConsoleCursorPosition(after);

	std::cout << std::endl
			  << '\t' << "1. Удалить" << std::endl
			  << '\t' << "2. Изменить" << std::endl
			  << '\t' << "3. Выйти" << std::endl
			  << "Выберите действие: ";
	choice = getnum_in_interval("", 1, 3, "Введите число от одного до трёх.");

	if (choice == 3)
		return;

	size_t index = getnum_in_arr("Введите индекс: ", result, "Введите индексы, которые есть в таблице.");
	switch (choice) {
	case 1:
		dltuser(index);
		break;
	case 2:
		chng(index);
		break;
	}

}
void Users::srch(std::string need, const int choice, std::vector<size_t> &result) {
	result.clear();
	for (size_t i = 0; i < userbase.size(); i++) {
		if (std::strstr(( (choice == 1) ? userbase[i].surname.c_str() :
						  (choice == 2) ? std::to_string(userbase[i].contract).c_str() :
						  userbase[i].userlog.login.c_str()), need.c_str())) {
			printel(std::cout, i);
			result.push_back(i);
		}
	}
}

void Users::chng(const size_t index) {
	userbase[index - 1] = crtuser(false);
}

void Users::dltuser() {
	system("cls");
	std::cout << *this;

	size_t index;
	index = getnum_in_interval("Введите индекс, который необходимо удалить: ", 1, userbase.size(), "Введите индекс из таблицы.");
	userbase.erase(userbase.begin() + index - 1);
}
void Users::dltuser(const size_t index) {
	userbase.erase(userbase.begin() + index);
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
				 << (*iter).userlog.login  << ':' << (*iter).userlog.password << ':' << (*iter).userlog.pos << std::endl;
//		datafile.write(reinterpret_cast<char *>(&(*iter)), sizeof (personaldata));
		flog << (*iter).userlog.login << ":" << (*iter).userlog.password << ':' << (*iter).userlog.pos << std::endl;
		*iter++;
	}
	userbase.clear();
}

prsinfo::position Users::authentication(std::string login, std::string password) {

	unsigned char hash[100];
	SHA1((unsigned char *) password.c_str(), password.size(), hash);

	std::string hashpass = std::string((char *) hash);

	std::vector<personaldata>::iterator ptr = userbase.begin();

	while (ptr != userbase.end()) {
		if (login == ptr->userlog.login) {
			if (ptr->userlog.password == hashpass) {
				return ptr->userlog.pos;
			}
		}
		ptr++;
	}

	return prsinfo::none;
}


