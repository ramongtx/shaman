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
	setNodeFamily(root);
	setNodeType(root);
	setNodeLineNumbers(root);
	setNodeAttributes(root);
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

void SHMParser::setNodeFamily(SHMTreeNode &node) {
	SHMStringStream stream (node.lineContents());
	SHMString word;
	stream >> word;
	node.setNodeFamily(word);
	stream >> word;
	node.setNodeAddress(word);
}

void SHMParser::setNodeType(SHMTreeNode &node) {
	static SHMRegex reg1("\'([^\']+)\'");
	SHMString str = node.lineContents();

	SHMRegexIterator it(str.begin(), str.end(), reg1);
	SHMRegexIterator it_end;


	node.setNodeType("none");

	if (it != it_end) {
		SHMRegexMatch match = *it;
		if (match.size() > 1) {
		    SHMRegexSubMatch sub_match = match[1];
			SHMString str = sub_match.str();
			node.setNodeType(str);
		}
	}
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

	SHMList <int> lineNumbers;
	static SHMRegex reg2("line:([0-9].)");
	SHMString str2 = "";
	SHMRegexIterator it2(str.begin(), str.end(), reg2);
	while (it2 != it_end) {
		SHMRegexMatch match = *it2;  
		if (match.size() > 1) {
		    SHMRegexSubMatch sub_match = match[1];                
			lineNumbers.push_back(SHMBasic::atoi(sub_match.str()));
		}
		++it2;
	}

	if (lineNumbers.size() > 0) {
		node.setLineSingle(lineNumbers.at(0));
		if (lineNumbers.size() > 1) {
			node.setLineEnd(lineNumbers.at(1));
		}
	}

	return;

}

void SHMParser::setNodeAttributes(SHMTreeNode& node) {
		static SHMRegex reg1("[0-9]+> (.*)");
	SHMString str = node.lineContents();

	SHMRegexIterator it(str.begin(), str.end(), reg1);
	SHMRegexIterator it_end;

	if (it != it_end) {
		SHMRegexMatch match = *it;
		if (match.size() > 1) {
		    SHMRegexSubMatch sub_match = match[1];                
			str = sub_match.str().c_str();
		}
	} else {
		return;
	}

	normalizeAttributes(str, node.nodeFamily());

	node.setNodeAttributes(str);
}

void SHMParser::normalizeAttributes(SHMString& rawAttr, const SHMString &nodeFamily) {
	if (nodeFamily == "DeclRefExpr") {
		SHMRegex reg(" 0x[0-9a-fA-F]* '[^']+'");
		rawAttr = regex_replace(rawAttr, reg, "");
	} else if (nodeFamily == "VarDecl") {
		int i = 0;
		while (isblank(rawAttr[i])) i++;
		while (!isblank(rawAttr[i])) i++;
		while (isblank(rawAttr[i])) i++;
		rawAttr = rawAttr.substr(i);
	} else if (nodeFamily == "FunctionDecl") {
		int i = 0;
		while (isblank(rawAttr[i])) i++;
		while (!isblank(rawAttr[i])) i++;
		while (isblank(rawAttr[i])) i++;
		rawAttr = rawAttr.substr(i);
	}
}