#include "legalentity.h"

LegalEntity::LegalEntity(Rate &rt) : Client(rt), employees(0) {}

LegalEntity::~LegalEntity() {
}

void LegalEntity::print(std::ostream &out) const {
	out << matrix << name + " |"
		<< matrix << std::to_string(employees) + " |";
}

std::string LegalEntity::getname() const {
	return name;
}

cltype::money LegalEntity::getcost() const {
	return std::stoll(getrate().getcost()) * employees;
}

void LegalEntity::setname(std::string nm) {
	name = nm;
}

void LegalEntity::setphoremp(std::string emp) {
	if (is_ull(emp) && emp.size() < 9)
		employees = std::stoull(emp);
}
