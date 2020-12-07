#include <iostream>

void errcheck(bool require, const char *success, const char *fail, int errorcode = 0, bool successmsg = true) {
	using namespace std;
	if (require && successmsg)
		cout << "[INFO] | */" << success << "/*" << endl;
	else
	if (!require){
		cout << "[ERROR] | */" << fail << errorcode << "/*" << endl;
		;
	}
}



