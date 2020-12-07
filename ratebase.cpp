#include "ratebase.h"


#include <fstream>
#include <string>
#include <conio.h>
#include <cmath>
#include <windows.h>

#include "require.h"
#include "manip.h"
#include "errcheck.h"

using std::string;

const char *RateBase::namearg[] = {"Имя", "Стоимость", "Минуты", "Мегабайты"};

RateBase::RateBase() : MyVector<Rate>(namearg, 4) {
	std::ifstream in("Ratebase.dat");

	if (!in) {
		std::cout << "Создание новой базы тарифов! В случае ошибки обратитесь к администратору." << std::endl;
		return;
	}

	string name, cost, min, mb;
	while (getline(in, name, ':')) {
		getline(in, cost, ':');
		getline(in, min, ':');
		getline(in, mb);
		push_back(Rate(name, cost, min, mb));
	}
}

RateBase::~RateBase() {
	std::ofstream out("Ratebase.dat");
	assure(out, "Ratebase.dat");

	std::vector<Rate>::iterator ptr = begin();
	while (ptr != end()) {
		out << (*ptr).getname() + ':'
			<< (*ptr).getcost() + ':'
			<< (*ptr).getmin() + ':'
			<< (*ptr).getmb() << std::endl;
		ptr++;
	}
}

void RateBase::sort(const int attr) {
	switch (choiceattr(attr)) {
	case name:
		qsort(0, size(), nmcomparison);
		break;
	case cost:
		qsort(0, size(), costcomparison);
		break;
	case min:
		qsort(0, size(), mincomparison);
		break;
	case mb:
		qsort(0, size(), mbcomparison);
		break;
	case none:
		return;
	}
}

void RateBase::srch(const size_t iattr, string asrch, std::vector<size_t> &result) {
	result.clear();

	for (size_t i = 0; i < size(); i++)
		if (std::strstr(operator[](i).getname().c_str(), asrch.c_str()))
				result.push_back(i);

	printarr(std::cout, result);
}


std::string RateBase::chngattr(const size_t attr, const size_t ichng) {
	attribute test = choiceattr(attr);
	std::string newval;

	std::cout << "Введите новое значение: ";
	std::getline(std::cin, newval);

	switch (test) {

	case name:
		operator[](ichng).setname(newval);
		break;

	case cost:
		if (is_f(newval))
			operator[](ichng).setcost(newval);
		else if (newval.empty())
			return "";
		else {
			std::cout << std::endl << "Некорректный ввод, введите действительное число." << std::endl;
			getch();
		}
		break;

	case min:
		operator[](ichng).setmin(newval);
		break;

	case mb:
		//Проверка на цифры
		operator[](ichng).setmb(newval);
		break;

	case none:
		break;
	}

	return newval;
}

Rate &RateBase::getrate(const std::string name) {
	std::vector<Rate>::iterator curr = begin();

	while (curr != end())
		if ((curr++)->getname() == name)
			return *(curr - 1);
#ifndef DEBUG
	return *begin();
#else
	std::cerr << "Тарифа с данным именем не существует." << name << std::endl;
	exit(-2);
#endif
}
