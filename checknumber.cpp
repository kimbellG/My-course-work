#include <iostream>
#include <iomanip>
#include <vector>

int getpositivenum(const char *str, const char *errstr = "Некорректный ввод") {
	using namespace std;
	int number;
	bool isnotcorrect = false;
	do {
		isnotcorrect = true;
		cout << str;
		cin >> number;
		if (cin.fail() or number < 0 or number > INT_MAX) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << errstr << endl;
			isnotcorrect = false;
		} else
			cin.ignore(32767, '\n');
	} while (!isnotcorrect);
	return number;
}

int getnum_in_interval(const char *str, const int start, const int stop,
							  const char *errstr = "Некорректный ввод", const short wid = 0) {
	using namespace std;
	int number;
	bool isnotcorrect = false;
	do {
		isnotcorrect = true;
		cout << setw(wid) << right  << setfill(' ') << str;
		cin >> number;
		if (cin.fail() or number < start or number > stop) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << setw(wid) << right << errstr << endl;
			isnotcorrect = false;
		} else
			cin.ignore(32767, '\n');
	} while (!isnotcorrect);
	return number;
}
int getnum_in_arr(const char *str, std::vector<size_t> arr, const char *errstr = "Некорректный ввод", const int wid = 0) {
	using namespace std;
	size_t number;
	bool isnotcorrect = false;
	do {
		isnotcorrect = true;
		cout << setw(wid) << right << str;
		cin >> number;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(32767, '\n');
			isnotcorrect = false;
		} else
			cin.ignore(32767, '\n');
		for (size_t i = 0; i < arr.size(); i++) {
			isnotcorrect = false;
			if (number == arr[i]) {
				isnotcorrect = true;
				break;
			}
		}
		if (!isnotcorrect)
			cout << setw(wid) << right << errstr << endl;
	} while (!isnotcorrect);
	return number;
}

int getindex(const char *str, const int size) {
	using namespace std;
	int number;
	bool iscorrect = false;
	do {
		iscorrect = true;
		cout << str;
		cin >> number;
		if (cin.fail() or number < 0 or number >= size) {
			cin.clear();
			cin.ignore(32767, '\n');
			cout << "Wrong number." << endl;
			iscorrect = false;
		} else
			cin.ignore(32767, '\n');
	} while (!iscorrect);
	return number;
}
