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
	int depth = indexFirstAlnum(list[pos]);
	root.setLineContents(list[pos].substr(depth));
	setNodePropertiesFromContents(root);
	setNodeLineNumbers(root);
	int i = pos+1;
	while (i<list.size()) {
		int nextDepth = indexFirstAlnum(list[i]);
		if (nextDepth > depth) {
			SHMTreeNode nextSon;
			nextSon.setLineStart(root.lineStart());
			nextSon.setLineEnd(root.lineEnd());
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
	stream >> word;
	node.setNodeAddress(word);
}

void SHMParser::setNodeLineNumbers(SHMTreeNode &node) {
	static SHMRegex reg1("<[^>]*>");
	SHMString str = node.lineContents();

	SHMRegexIterator it(str.begin(), str.end(), reg1);
	SHMRegexIterator it_end;

	if (it != it_end) {
		SHMRegexMatch match = *it;                                                 
		str = match.str(); 
	} else {
		return;
	}


	static SHMRegex reg2("line:([0-9]).");
	SHMString str2 = "";
	SHMRegexIterator it2(str.begin(), str.end(), reg2);
	while (it2 != it_end) {
		SHMRegexMatch match = *it2;  
		SHMString substr = match.str();  
		str2.append(substr);
		str2.append(" ");                                    
		++it2;
	}
	str = str2;

	static SHMRegex reg3("[0-9].");
	SHMList <int> lineNumbers;
	SHMRegexIterator it3(str.begin(), str.end(), reg3);
	while (it3 != it_end) {
		SHMRegexMatch match = *it3;  
		SHMString substr = match.str();                                      
		lineNumbers.push_back(SHMBasic::atoi(substr));
		++it3;
	}

	if (lineNumbers.size() > 0) {
		node.setLineSingle(lineNumbers.at(0));
		if (lineNumbers.size() > 1) {
			node.setLineEnd(lineNumbers.at(1));
		}
	}

	return;

}
