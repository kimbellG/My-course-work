#include "individual.h"

Individual::Individual(Rate &rt) : Client(rt), phonenumber("") {}

Individual::~Individual() {}

void Individual::print(std::ostream &out) const {
	out << matrix << name + " |"
		<< matrix << phonenumber + " |";
}

std::string Individual::getname() const {
	return name;
}

cltype::money Individual::getcost() const {
	return std::stoull(getrate().getcost());
}

void Individual::setname(std::string sur) {
	name = sur;
}

std::string Individual::delfrombase() {
	return phonenumber;
}
