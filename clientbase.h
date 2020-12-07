#ifndef USERBASE_H
#define USERBASE_H


#include <stack>

#include "myvector.h"
#include "client.h"
#include "ratebase.h"

class ClientBase : public MyVector<Client *> {

	static std::stack<std::string> freenum;
	static unsigned long long lastfreenumber;

	static const char *namearg[];
	enum attribute {
		name = 1,
		phoremp,
		rate,
		contract,
		date,
		balance,
		none
	};

	std::string getnumber() {
		if (freenum.empty())
			return "+37529" + std::to_string(lastfreenumber++);

		std::string tmp = freenum.top();
		freenum.pop();
		return tmp;
	}

	RateBase &rates;

	void printarr(std::ostream &out, const std::vector<size_t> &result) override;
	void srch(const size_t iattr, std::string asrch, std::vector<size_t> &result) override;
	std::string chngattr(const size_t attr, const size_t ichng) override;

	static int _name_comprison(Client * const &left, Client * const &right) {
		return std::strcmp(left->getname().c_str(), right->getname().c_str());
	}
	static int _rate_comprison(Client * const &left, Client * const &right) {
		return std::strcmp(left->getrate().getname().c_str(), right->getrate().getname().c_str());
	}
	static int _balance_comprison(Client * const &left, Client * const &right) {
		return left->getbalance() - right->getbalance();
	}


	attribute choiceattr(const size_t index) {
		switch (index) {
		case 1:
			return name;
		case 2:
			return phoremp;
		case 3:
			return contract;
		case 4:
			return rate;
		case 5:
			return date;
		case 6:
			return balance;
		default:
			return none;
		}
	}
public:
	ClientBase(RateBase &rates);
	~ClientBase();

	enum typecl {
		individual,
		legalentity,
	};

	void generatecl(typecl type, std::string name, std::string contract);
	void dlt(const size_t index) override;
	void edit() {
		system("cls");
		std::cout << "Доступные параметры для поиска: " << std::endl;
		std::cout << "\t1. Имя" << std::endl
				  << "\t2. Номер договора или колличество работников" << std::endl
				  << "\t3. Номер договора" << std::endl;
		char c;
		while ((c = getch()) < '1' || c > '3');

		MyVector<Client *>::edit(c - '0');
	}
	void sort(const int index) {
		switch (index) {
		case 1:
			qsort(0, size(), _name_comprison);
			break;
		case 2:
			qsort(0, size(), _rate_comprison);
			break;
		case 3:
			qsort(0, size(), _balance_comprison);
		}
	}
};

#endif // USERBASE_H
