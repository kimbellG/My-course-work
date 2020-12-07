#ifndef CLIENT_H
#define CLIENT_H


#include <string>
#include <iostream>
#include <ctime>

#include "rate.h"

namespace cltype {
	typedef long double money;
	typedef time_t date;
	typedef unsigned long long quantity;
}

class Client {
	Rate           &_rate;
	std::string    _contract;
	cltype::date   _connectdate;
	cltype::money  _balance;

protected:
	virtual void print(std::ostream &out) const = 0;

public:
	Client(Rate &rt);
	Client(Rate &rt, std::string contract, cltype::date connectdate, cltype::money balance);
	virtual ~Client();
	virtual std::string linetowrite() const {
		std::string save;
		save += _contract + ':' + std::to_string(_connectdate) + ':' + std::to_string(_balance);
		return save;
	};

	friend std::ostream &
	operator<<(std::ostream &out, const Client &val);

	virtual std::string   getname    () const = 0;
	virtual cltype::money getcost    () const = 0;
	virtual std::string   getphoremp () const = 0;

	virtual void setname (std::string name) = 0;
	virtual void setphoremp(std::string number) = 0;

	cltype::money getbalance    () const {
		return _balance;
	};
	Rate &        getrate       () const {
		return _rate;
	};
	cltype::date  getconnectdate() const {
		return _connectdate;
	}
	std::string   getcontract   () const {
		return _contract;
	}

	void setbalance (const cltype::money nwbalance) {
		_balance = nwbalance;
	};
	void setrate    (const Rate &nwrate) {
		_rate = nwrate;
	}
	void setcontract(const std::string contract) {
		_contract = contract;	}
	void setdate(const cltype::date nw) {
		_connectdate = nw;
	}

	virtual std::string delfrombase() = 0;

	static std::ostream& matrix(std::ostream& stream) {
		stream << std::setw(25) << std::setfill(' ');
		return stream;
	}
};

#endif // CLIENT_H
