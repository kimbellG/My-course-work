#include "clientbase.h"

#include <fstream>

#include "individual.h"
#include "legalentity.h"
#include "menu.h"

const char *ClientBase::namearg[] = {"Имя", "Номер/Кол. работников", "Номер договора",  "Тариф", "Дата регистрации", "Баланс счета"};
unsigned long long ClientBase::lastfreenumber = 1000000;
std::stack<std::string> ClientBase::freenum;


ClientBase::ClientBase(RateBase &rate) : MyVector<Client *>(namearg, 6, 25, 2), rates(rate) {
	std::ifstream in("clientbase.dat");
	std::ifstream forstack("freenumbers.dat");
	std::ifstream lastnumber("lastfree.num");

	string tmp;

	if (!in) {
		std::cout << "Создание новой базы клиентов! В случае ошибки обратитесь к администратору." << std::endl;
		return;
	}

	if (forstack)
		while (std::getline(forstack, tmp))
			freenum.push(tmp);
	if (lastnumber) {
		std::getline(lastnumber, tmp);
		lastfreenumber = std::stoull(tmp);
	}

	forstack.close();
	lastnumber.close();

	Client *newuser;
	while (getline(in, tmp, ':')) {

		if (tmp == "I") {
			getline(in, tmp, ':');
			newuser = new Individual(rates.getrate(tmp));
		} else if (tmp == "L") {
			getline(in, tmp, ':');
			newuser = new LegalEntity(rates.getrate(tmp));
		}

		getline(in, tmp, ':');
		newuser->setname(tmp);
		getline(in, tmp, ':');
		newuser->setphoremp(tmp);
		getline(in, tmp, ':');
		newuser->setcontract(tmp);
		getline(in, tmp, ':');
		newuser->setdate(std::stoll(tmp));
		getline(in, tmp);
		newuser->setbalance(std::stold(tmp));

		push_back(newuser);
	}
}

ClientBase::~ClientBase() {
	std::ofstream out("clientbase.dat");
	std::ofstream st("freenumbers.dat");
	std::ofstream lastnumfile("lastfree.num");

	while (!freenum.empty()) {
		st << freenum.top() << std::endl;
		freenum.pop();
	}

	lastnumfile << lastfreenumber << std::endl;

	st.close();
	lastnumfile.close();

	std::vector<Client *>::iterator it = begin();
	while (it != end()) {
		out << (*it)->linetowrite() << std::endl;
		it++;
	}

	it = begin();
	while (it != end())
		delete *it++;
}

void ClientBase::srch(const size_t iattr, std::string asrch, std::vector<size_t> &result) {
	result.clear();

	for (size_t i = 0;  i < size(); i++) {
		switch (choiceattr(iattr)) {
		case name:
			if (strstr(operator[](i)->getname().c_str(), asrch.c_str()))
				result.push_back(i);
			break;
		case phoremp:
			if (strstr(operator[](i)->getphoremp().c_str(), asrch.c_str()))
				result.push_back(i);
			break;
		case contract:
			if (strstr(operator[](i)->getcontract().c_str(), asrch.c_str()))
				result.push_back(i);
			break;
		default:
			std::cerr << "По этим параметрам сортировки нету." << std::endl;
			exit(-3);
		}
	}

	printarr(std::cout, result);
}

std::string ClientBase::chngattr(const size_t attr, const size_t ichng) {
	attribute choice = choiceattr(attr + 1);

	std::string newval = "next";
	switch(choice) {
	case date:
		return newval;
	case balance:
		return newval;
	default:
		break;
	}

	std::cout << "Введите новое значение: ";
	std::getline(std::cin, newval);

	if (newval.empty())
		return "";

	switch (choice) {
	case name:
		operator[](ichng)->setname(newval);
		break;
	case rate:
		if (rates.is_rate(newval))
			operator[](ichng)->setrate(rates.getrate(newval));
		else {
			std::cout << "Тарифа с таким именем не существует. Повторите попытку." << std::endl;
			menuf::pause();
		}
		break;
	case contract:
		operator[](ichng)->setcontract(newval);
		break;
	case phoremp:
		operator[](ichng)->setphoremp(newval);
	default:
		break;
	}
	return newval;
}

void ClientBase::generatecl(typecl type, std::string name, std::string contract) {
	Client *nwcl;

	switch (type) {
	case individual:
		nwcl = new Individual(rates.chooserate());
		nwcl->setphoremp(getnumber());
		break;
	case legalentity:
		nwcl = new LegalEntity(rates.chooserate());
		break;
	}

	nwcl->setname(name);
	nwcl->setcontract(contract);

	push_back(nwcl);
}

void ClientBase::dlt(const size_t index) {
	Client *delptr = operator[](index);
	if (!delptr->delfrombase().empty())
		freenum.push(delptr->getphoremp());
	delete delptr;
	erase(begin() + index);
}

void ClientBase::printarr(std::ostream &out, const std::vector<size_t> &result) {
	std::string tab;
	for (size_t i = 0; i < result.size(); i++) {
		out << '|' << result[i];
		for (int i = 0; i < log(size()) / log(10) - log(result[i]) / log(10); i++)
			tab.push_back(' ');
		tab.push_back('|');
		out << tab << (*operator[](result[i]));
		out << "|" << manip.gettab(size(), '_') << "|";
		for (int k = 0; k < 6; k++)
			out << width << "|";
		std::cout << std::endl;
		tab.clear();
	}
}

