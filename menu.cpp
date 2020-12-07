#include <iostream>
#include <conio.h>

#include "menu.h"

char menuf::getmenunum(const char end, const char start) {
	char c;
	while ((c = getch()) < start || c > end);
	return c;
}

void menuf::pause() {
	getch();
}

void menuf::clear() {
#ifndef WIN64
	system("clear");
#else
	system("cls");
#endif
}
