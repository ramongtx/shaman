#ifndef _SHM_TYPES
#define _SHM_TYPES

#include <iostream>
#include <sstream>
#include <fstream>
#define SHMOutputStringStream std::ostringstream
#define SHMOutputFileStream std::ofstream
typedef std::ifstream SHMInputFileStream;
typedef std::istringstream SHMInputStringStream;
typedef std::stringstream SHMStringStream;

#include <vector>
#define SHMList std::vector

#include <map>
#define SHMMap std::map

#include <regex>
typedef std::regex SHMRegex;
typedef std::sregex_iterator SHMRegexIterator;
typedef std::smatch SHMRegexMatch;
typedef std::string SHMString;

#include "pugixml.hpp"
typedef pugi::xml_document SHMXMLDocument;
typedef pugi::xml_node SHMXMLNode;
typedef pugi::xml_attribute SHMXMLAttribute;


class SHMBasic {
public:
	static SHMString replaceSubstring(SHMString subject, const SHMString& search, const SHMString& replace) {
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos) {
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	static SHMString toString(int f) {
		SHMString str;
		str = std::to_string(f);
		return str;
	}

	static int atoi (SHMString str) {
		return std::atoi(str.c_str());
	}
};


#endif