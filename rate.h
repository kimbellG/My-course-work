#ifndef RATE_H
#define RATE_H


#include <string>
#include <ostream>

#include "manip.h"

using std::string;

class Rate {
	string name;
	string cost;
	string min;
	string mb;

public:
	Rate(string nm, string cost, string min, string mb);
	Rate(const Rate &val);
	~Rate();

	void setname(const string newname);
	void setcost(const string newcost);
	void setmin(const string newmin);
	void setmb(const string newmb);

	string getname() const;
	string getcost() const;
	string getmin() const;
	string getmb() const;

	friend std::ostream &
	operator<<(std::ostream &out, const Rate &outval);

};

#endif // RATE_H
