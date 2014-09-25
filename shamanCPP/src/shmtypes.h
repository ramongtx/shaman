#ifndef _SHM_TYPES
#define _SHM_TYPES

#include <iostream>
#include <sstream>
#include <vector>
#include "pugixml.hpp"
#include <map>


#define SHMList std::vector
#define SHMMap std::map
#define SHMOutputStringStream std::ostringstream
typedef std::ifstream SHMInputFileStream;
typedef std::istringstream SHMInputStringStream;
typedef std::stringstream SHMStringStream;
typedef std::string SHMString;

class SHMSupport {
public:
	static SHMString replaceSubstring(SHMString subject, const SHMString& search, const SHMString& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}
};


#endif