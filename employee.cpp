#include "employee.h"

Employee::Employee(LegalEntity &link)
	: Individual(link.getrate()), company(link) {
	link.newemp();
	setbalance(0);

}

Employee::~Employee() {
}

void Employee::print(std::ostream &out) const {
	out << matrix << getname() + "* |"
		<< matrix << getphoremp() + " |";
}
