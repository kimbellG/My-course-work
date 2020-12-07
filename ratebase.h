#ifndef RATEBASE_H
#define RATEBASE_H

#include <cstring>

#include "errcheck.h"
#include "rate.h"
#include "myvector.h"


class RateBase : public MyVector<Rate> {
public:
	static const char* namearg[];
	enum attribute {
		name = 0,
		cost = 1,
		mb = 2,
		min = 3,
		none = 4
	};

private:

	static int nmcomparison  (const Rate &left, const Rate &right) {
		return std::strcmp(left.getname().c_str(), right.getname().c_str());
	};
	static int costcomparison(const Rate &left, const Rate &right) {
		return _ull_comprison(left.getcost(), right.getcost());
	};
	static int mincomparison (const Rate &left, const Rate &right) {
		return _ull_comprison(left.getmin(), right.getmin());
	};
	static int mbcomparison  (const Rate &left, const Rate &right) {
		return _ull_comprison(left.getmb(), right.getmb());
	};

	void srch(const size_t iattr, string asrch, std::vector<size_t> &result) override;

	attribute choiceattr(const int iattr) {
		switch (iattr) {
		case 0:
			return name;
		case 1:
			return cost;
		case 2:
			return min;
		case 3:
			return mb;
		default:
			std::cerr << "Incorrect iattr in RateBase::cha" << std::endl;
			exit(-1);
		}
	}
	std::string chngattr(const size_t attr, const size_t ichng) override;

public:
	RateBase();
	~RateBase();

	void sort(const int attr);
	void edit() {
		MyVector<Rate>::edit(1);
	};
	Rate &getrate(std::string name);
	Rate & chooserate() {
		std::vector<size_t> *res = srchindex(1);
		size_t index = getnum_in_arr("¬ведите индекс: ", *res, "¬ведите индексы, которые есть в таблице.");
		delete res;
		return operator[](index);
	}

	bool is_rate(const std::string &nameval) {
		for (size_t i = 0; i < size(); i++)
			if (nameval == operator[](i).getname())
				return true;
		return false;
	}
};

#endif // RATEBASE_H
