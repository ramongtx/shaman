#include "shmparser.h"
#include <fstream>
#include <sstream>

SHMString SHMParser::getFileContents(SHMString address) {
	SHMFileStream ifs(address.c_str());
  	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    return content;
}

SHMList<SHMString> SHMParser::splitNewlines(SHMString contents) {
	SHMStringStream stream(contents);
	SHMList<SHMString> list;
    while (!stream.eof())
    {
        SHMString s1;
        getline(stream, s1);
        list.push_back(s1);
    }
    return list;
}
