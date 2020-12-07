#include "rate.h"

#include "../require.h"
#include "errcheck.h"

Rate::Rate(string nm, string cst, string minute, string mbyte) :name(nm), cost(cst), min(minute), mb(mbyte) {
	if (!is_f(cost)) {
		std::cerr << "У стоимости тарифа должно быть положительное значение: setcost()" << std::endl;
		exit(-3);
	}
}
Rate::Rate(const Rate &val) : name(val.name), cost(val.cost), min(val.min), mb(val.mb) {}
Rate::~Rate() {}


void Rate::setcost(const string newcost) {
	if (is_f(newcost))
		cost = newcost;
	else {
		std::cerr << "У стоимости тарифа должно быть положительное значение: setcost()" << std::endl;
		exit(-3);
	}
}
void Rate::setname(const string newname) {
	name = newname;
}
void Rate::setmb(const string newmb) {
	mb = newmb;
}
void Rate::setmin(const string newmin) {
	min = newmin;
}

string Rate::getcost() const {
	return cost;
}
string Rate::getmin() const {
	return min;
}
string Rate::getname() const {
	return name;
}
string Rate::getmb() const {
	return mb;
}

std::ostream &operator<<(std::ostream &out, const Rate &val) {
	out << matrix << val.name + " |";
	out << matrix << val.cost + " |";
	out << matrix << val.min + " |";
	out << matrix << val.mb + " |";
	out << " " << std::endl;

	return out;
}
