#include <iostream>
#include <fstream>
#include <string>

#include "logpass.h"
#include "posworker.h"
#include "../require.h"

prsinfo::position authentication(std::string login, std::string password) {
	std::ifstream logpass("users.dat");

	std::string tmplog;

	unsigned char hash[100];
	SHA1((unsigned char *) password.c_str(), password.size(), hash);

	std::string hashpass = std::string((char *) hash);

	while (std::getline(logpass, tmplog, ':')) {
		if (login == tmplog) {
			std::getline(logpass, tmplog, ':');
			if (tmplog == hashpass) {
				std::getline(logpass, tmplog);
				return prsinfo::checkpos(std::stoi(tmplog));
			}
		}

		std::getline(logpass, tmplog);
	}

	return prsinfo::none;
}

