#ifndef LOGPASS_H
#define LOGPASS_H


#include <string>
#include <vector>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <openssl/sha.h>

#include "errcheck.h"
#include "consolemanipulator.h"

const int admin = 0;


namespace prsinfo {

	enum position{
		consultant,
		accountant,
		analyst,
		devrate,
		admin,
		none
	};

	extern const char* textpos[];

	inline position checkpos(const int num) {
		switch (num) {
		case 0:
			return consultant;
			break;
		case 1:
			return accountant;
			break;
		case 2:
			 return analyst;
			break;
		case 3:
			return devrate;
			break;
		case 4:
			return admin;
			break;
		};
		std::cerr << "Incorrect num" << std::endl;
		exit(-1);
	}

	struct log {
		std::string login;
		std::string password;
		position pos;
	};

	struct personaldata {
		std::string surname;
		std::string name;
		std::string midname;
		std::string numpassport;

		long long   contract;
		log         userlog;
	};

	class Users {
		std::vector<personaldata> userbase;
		ConsoleManipulator manip;
		static const char *namearg[];

		void printel(std::ostream &os, size_t index) const ;
		void content(std::ostream &os) const;
		void srch(std::string need, const int choice, std::vector<size_t> &result);
		void dltuser(const size_t index);
		void chng(const size_t index);
		const personaldata crtuser(bool isadmin);
	public:
		Users();
//		size_t countuser();

		void add();
		void add(int);
		friend std::ostream&
		operator<<(std::ostream &os, const Users& printarg);

		void dltuser();
		void chng() {
			std::cout << *this << std::endl << std::endl;
			size_t i = getindex("¬ведите индекс: ", userbase.size());
			chng(i);
		}
		void srch();

		prsinfo::position authentication(std::string login, std::string password);

		~Users();
	};
};


inline void input_password(char *pass) {

	int c;
	int i = 0;
	while ((c = getch()) != '\r') {
		if (c == '\b' && i != 0) {
			i--;
		} else if (c != '\b'){
			pass[i] = c;
			i++;
		}
		if (i > 19) {
			i = 0;
			std::cout << std::setw(20) << "\nTry again. pass < 20 char\n";
		}

	}
	putch('\n');
	pass[i] = '\0';
}



#endif // LOGPASS_H
