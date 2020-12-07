#include <string>
#include <iostream>

typedef unsigned long long ull;

bool is_ull(const std::string str) {

	if (str.size() > 18)
		return false;

	for (size_t i = 0; i < str.size(); i++) {
		if (!(isdigit(str[i]))) {
			return false;
		}
	}
	return true;
}

bool is_f(const std::string str) {

	float f;
	try {
		f = std::stof(str);
	} catch (std::invalid_argument) {
		return false;
	} catch (std::out_of_range) {
		return false;
	}

	return true;
}

int _ull_comprison(std::string left, std::string right) {
		ull lft, rgh;
		try {
			lft = std::stoull(left);
		} catch(std::invalid_argument) {
			return 1;
		}

		try {
			rgh = std::stoull(right);
		} catch(std::invalid_argument) {
			return -1;
		}

		return lft - rgh;
}

int _f_comprison(std::string left, std::string right) {
	float lft, rgh;

	try {
		lft = std::stof(left);
	}  catch (std::invalid_argument) {
		return 1;
	}

	try {
		rgh = std::stof(right);
	}  catch (std::invalid_argument) {
		return -1;
	}

	return lft - rgh;
}
