#ifndef MANIP_H
#define MANIP_H


#include <iostream>
#include <iomanip>

inline std::ostream& matrix(std::ostream& stream) {
	stream << std::setw(25) << std::setfill(' ');
	return stream;
}
inline std::ostream& width(std::ostream& stream){
	stream << std::setw(25) << std::setfill('_');
	return stream;
}

#endif // MANIP_H
