#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "client.h"

class Individual : public Client {
	std::string name;

	std::string phonenumber;

protected:
	void print(std::ostream &out) const override;

public:
	Individual(Rate &rt);
	~Individual();

	std::string   getname    () const override;
	cltype::money getcost    () const override;
	std::string   getphoremp () const override {
		return phonenumber;}


	void setphoremp (std::string number) override {
		if (phonenumber.empty())
			phonenumber = number;
	}
	void setname  (std::string name) override;

	std::string delfrombase() override;

	std::string linetowrite() const override {
		std::string save;
		save += "I:";
		save += getrate().getname() + ':';
		save += name + ':';
		save += phonenumber + ':';
		save += Client::linetowrite();
		return save;
	}

};

#endif // INDIVIDUAL_H
