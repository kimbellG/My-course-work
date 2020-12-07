#ifndef MYVECTOR_H
#define MYVECTOR_H


#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <conio.h>

#include "consolemanipulator.h"
#include "manip.h"
#include "errcheck.h"

template<class Type>
class MyVector : public std::vector<Type> {
	const char **namearg;
	const size_t numattr;
protected:
	ConsoleManipulator manip;
	MyVector(const char **nargs, const int szattr, const size_t stepx = 25, const size_t stepy = 2)
		: std::vector<Type>(), namearg(nargs), numattr(szattr), manip(stepx, stepy) {}
	virtual ~MyVector() {}

	void chg   (std::vector<size_t> result);
	void qsort (int start, int end, int (*compare)(const Type &, const Type &));

	void edit  (const size_t attr) {

		std::vector<size_t> *result = srchindex(attr);

		if (std::vector<Type>::empty()) {
			getch();
			return;
		}

		size_t choice;
		std::cout << std::endl
				  << '\t' << "1. Удалить" << std::endl
				  << '\t' << "2. Изменить" << std::endl
				  << '\t' << "3. Выйти" << std::endl
				  << "Выберите действие: ";
		choice = getnum_in_interval("", 1, 3, "Введите число от одного до трёх.");

		if (choice == 3)
			return;

		switch (choice) {
		case 1:
		{
			size_t index = getnum_in_arr("Введите индекс: ", *result, "Введите индексы, которые есть в таблице.");
			dlt(index);
		}
			break;
		case 2:
			chg(*result);
			break;
		}

		delete result;
	}

	std::vector<size_t> *srchindex(const size_t attr);

	virtual void dlt(const size_t index) {
		std::vector<Type>::erase(std::vector<Type>::begin() + index);
	}

	void swap_elements (Type &left, Type &right) {
		Type tmp = left;
		left = right;
		right = tmp;
	}

	virtual void srch    (const size_t attr, std::string asrch, std::vector<size_t> &result) = 0;
	virtual std::string chngattr(const size_t attr, const size_t ichng) = 0;

	void content(std::ostream &os) {
		os << ' ' << manip.gettab(std::vector<Type>::size(), '_');
		for (size_t k = 0; k < numattr; k++)
			os << width << '_';
		os << ' ' << std::endl;

		os << '|' << manip.gettab(std::vector<Type>::size()) << '|';

		for (size_t i = 0; i < numattr; i++)
			os << matrix << std::string(namearg[i]) + "|";
		os << " " << std::endl << '|' << manip.gettab(std::vector<Type>::size(), '_') << '|';

		for (size_t k = 0; k < numattr; k++)
			os << width << "|";
		os << std::endl;
	}
	virtual void printarr(std::ostream &out, const std::vector<size_t> &result) {
		std::string tab;
		for (size_t i = 0; i < result.size(); i++) {
			out << '|' << result[i];
			for (int i = 0; i < log(std::vector<Type>::size()) / log(10) - log(result[i]) / log(10); i++)
				tab.push_back(' ');
			tab.push_back('|');
			out << tab << (std::vector<Type>::operator[](result[i]));
			out << "|" << manip.gettab(std::vector<Type>::size(), '_') << "|";
			for (int k = 0; k < numattr; k++)
				out << width << "|";
			std::cout << std::endl;
			tab.clear();
		}
	}
};

template <class Type> inline
void MyVector<Type>::qsort(int start, int end, int (*compare)(const Type &, const Type &)) {

	if (start >= end)
		return;

	const int pivot = (start + end) / 2;
	int last;

	swap_elements(std::vector<Type>::operator[](start), std::vector<Type>::operator[](pivot));
	last = start;
	for (int i = start + 1; i < end; i++)
		if ((*compare)(std::vector<Type>::operator[](i), std::vector<Type>::operator[](start)) < 0) {
			swap_elements(std::vector<Type>::operator[](++last), std::vector<Type>::operator[](i));
		}

	swap_elements(std::vector<Type>::operator[](start), std::vector<Type>::operator[](last));
	qsort(start, last, compare);
	qsort(last + 1, end, compare);

}

template <class Type> inline
void MyVector<Type>::chg(std::vector<size_t> result) {

	COORD pos = {(short)(manip.gettab(std::vector<Type>::size()).size() + 25), 3};
	size_t ichng = 0;
	size_t field = 0;
	do {
		system("cls");
		content(std::cout);
		printarr(std::cout, result);
		std::cout << std::endl
				  << "Выберите поле и нажмите ВВОД, для выхода нажмите \"ВВОД\"." << std::endl;

		manip.mvtable(ichng, field, pos, result.size(), numattr);

		std::string newvalue = "";
		newvalue = chngattr(field, result[ichng]);

		if (newvalue == "")
			return;


	} while(true);

	return;
}

template <class Type> inline
std::vector<size_t> *MyVector<Type>::srchindex(const size_t attr) {
	std::string needed("");

	COORD before = manip.GetConsoleCursorPosition();
	std::vector<size_t> *result = new std::vector<size_t>;

	char c;
	 do {
		system("cls");
		content(std::cout);
		srch(attr, needed, *result);
		std::cout << std::endl;
		std::cout << "Input: " << needed;
		c = getch();

		if (c == '\b' && needed.size() != 0) {
			needed.pop_back();
			manip.backspace();
			before.X--;
		} else if (c != '\b') {
			std::cout << c;
			needed.push_back(c);
			before.X++;
		}

	} while (c != '\r');

	if (result->empty()) {
		needed = "";
		system("cls");
		content(std::cout);
		srch(attr, needed, *result);
		std::cout << std::endl;
	}

	return result;

}


#endif // MYVECTOR_H
