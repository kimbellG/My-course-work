#include "client.h"

#include <fstream>
#include <ctime>
#include <cstring>

#include "manip.h"


Client::Client(Rate &rt) : _rate(rt), _balance(0) {
	_connectdate = time(nullptr);
};

Client::Client(Rate &rt, std::string cntrct, cltype::date connectdate, cltype::money balance)
	: _rate(rt) {
	_contract = cntrct;
	_connectdate = connectdate;
	_balance = balance;
}

Client::~Client() {}

std::ostream &
operator<<(std::ostream &out, const Client &val) {
	val.print(out);
	string tm = ctime(&(val._connectdate));
	tm.pop_back();
	tm += "|";

	out << matrix << val._contract + " |"
		<< matrix << val._rate.getname() + " |"
		<< matrix << tm
		<< matrix << std::to_string(val._balance) + " |" << std::endl;

	return out;
}


