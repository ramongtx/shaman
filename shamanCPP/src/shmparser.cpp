#include "shmparser.h"
#include <fstream>
#include <sstream>

SHMString SHMParser::getFileContents(SHMString address) {
	SHMInputFileStream ifs(address.c_str());
  	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
    return content;
}

SHMList<SHMString> SHMParser::splitNewlines(SHMString contents) {
	SHMInputStringStream stream(contents);
	SHMList<SHMString> list;
    while (!stream.eof())
    {
        SHMString s1;
        getline(stream, s1);
        list.push_back(s1);
    }
    return list;
}

int SHMParser::indexFirstAlnum(SHMString line) {
	for (int i = 0; i<line.size(); i++) {
		if (isalnum(line[i])) {
			return i;
		}
	}
	return -1;
}

int SHMParser::generateTree(SHMList<SHMString> list, int pos, SHMTreeNode& root) {
	if (pos > list.size()) return -1;
	root = SHMTreeNode();
	int depth = indexFirstAlnum(list[pos]);
	root.setLineContents(list[pos].substr(depth));
	setNodePropertiesFromContents(root);
	int i = pos+1;
	while (i<list.size()) {
		int nextDepth = indexFirstAlnum(list[i]);
		if (nextDepth > depth) {
			SHMTreeNode nextSon;
			i = generateTree(list, i,nextSon);
			root.appendChild(nextSon);
		} else {
			break;
		}
	}
	return i;
}

void SHMParser::setNodePropertiesFromContents(SHMTreeNode &node) {
	SHMStringStream stream (node.lineContents());
	SHMString word;
	stream >> word;
	node.setNodeType(word);
}
