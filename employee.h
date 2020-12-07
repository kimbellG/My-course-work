#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "individual.h"
#include "legalentity.h"

class Employee : public Individual {
	LegalEntity &company;

protected:
	void print(std::ostream &out) const override;

public:
	Employee (LegalEntity &link);
	~Employee();

	std::string linetowrite() const override {
		std::string save;
		save += "E:";
		save += company.getname() + ":";
		save += getname() + ':';
		save += getphoremp()+ ':';
		save += Client::linetowrite();
		return save;
	}


	void setbalance(cltype::money nw) {
		if (nw) {
			std::cerr << "Произведено изменение баланса работника предприятия! " << getname() << std::endl;
			std::exit(-3);
		}
	}
	cltype::money getbalae() {
		return 0;
	}
};

#endif // EMPLOYEE_H
