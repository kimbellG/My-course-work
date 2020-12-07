#ifndef LEGALENTITY_H
#define LEGALENTITY_H

#include "client.h"
#include "errcheck.h"

class LegalEntity : public Client {
	std::string name;

	cltype::quantity employees;

protected:
	void print(std::ostream &out) const override;

public:
	LegalEntity(Rate &rt);
	~LegalEntity();

	std::string   getname    () const override;
	cltype::money getcost    () const override;
	std::string   getphoremp () const override {
		return std::to_string(employees);
	}

	void setname(std::string name) override;
	void setphoremp(std::string emp) override;

	std::string linetowrite() const override {
		std::string save;
		save += "L:";
		save += getrate().getname() + ':';
		save += name + ':';
		save += std::to_string(employees) + ':';
		save += Client::linetowrite();
		return save;
	}

	std::string delfrombase() override {
		return "";
	}
};

#endif // LEGALENTITY_H
