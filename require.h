#ifndef REQUIRE_H
#define REQUIRE_H

#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <string>

inline void require(bool requirement, const std::string& message="Requiremet fault") {
    using namespace std;
    if (!requirement) {
        fputs(message.c_str(), stderr);
        fputs("\n", stderr);
        exit(1);
    }
}

inline void require_args(int argc, int args, const std::string& msg = "Must use %d arg") {
    using namespace std;
    if (argc != args + 1) {
        fprintf(stderr, msg.c_str(), args);
        fputs("\n", stderr);
        exit(1);
    }
}

inline void reqminarg(int argc, int minargs, const std::string& msg = "Must use at least &d arg") {
    using namespace std;
    if (argc < minargs + 1) {
        fprintf(stderr, msg.c_str(), minargs);
        fputs("\n", stderr);
        exit(1);
    }
}

inline void assure(std::ifstream& in, const std::string& filename = "") {
    using namespace std;
    if(!in) {
        fprintf(stderr, "Couldn't open file %s\n", filename.c_str());
        exit(1);
    }
}

inline void assure(std::ofstream& out, const std::string filename = "") {
    using namespace std;
    if (!out) {
        fprintf(stderr, "Couldn't open file %s\n", filename.c_str());
    }
}


#endif // REQUIRE_H
