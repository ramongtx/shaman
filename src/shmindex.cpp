#include "shmindex.h"


SHMIndex::SHMIndex() {
	_goodRes = "";
}

SHMIndex::~SHMIndex() {

}

void SHMIndex::addNode(const SHMString &fileName, const SHMString &xmlString) {
	_fileNameList.push_back(fileName);
	_nodeList.push_back(SHMTreeNode(xmlString));
}

void SHMIndex::addNode(const SHMString &fileName) {
	SHMInputFileStream ifs(fileName.c_str());
	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
		(std::istreambuf_iterator<char>()    ) );
	_fileNameList.push_back(fileName);
	_nodeList.push_back(SHMTreeNode(content));
}


SHMString SHMIndex::toXMLString() const {
	SHMXMLDocument doc;
	SHMXMLNode node = doc.append_child();

	for (int i = 0; i<_nodeList.size(); i++) {
		SHMXMLNode node = doc.append_child();
		node.set_name("entry");
		node.append_attribute("file") = _fileNameList.at(i).c_str();
		node.append_attribute("check") = _checkFileList.at(i).c_str();
		SHMXMLNode childNode = node.append_child();
		_nodeList.at(i).toXML(childNode);
	}

	SHMOutputStringStream oss;
	doc.print(oss);
	return oss.str();
}

void SHMIndex::addCheckFile(const SHMString &checkFile) {
	SHMInputFileStream ifs(checkFile.c_str());
	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
		(std::istreambuf_iterator<char>()    ) );
	content = SHMBasic::replaceSubstring(content, "\n", "");
	_checkFileList.push_back(content);

	int pos = _checkFileList.size()-1;
	if (_checkMap.find(content) == _checkMap.end()) {
		SHMList<int> list;
		list.push_back(pos);
		_checkMap[content] = list;
	} else {
		SHMList<int> list = _checkMap.at(content);
		list.push_back(pos);
		_checkMap[content] = list;
	}
}

SHMString SHMIndex::checkResults() {
	SHMList<int> alreadyVisited;
	SHMString res = ""+ SHMBasic::toString(_checkFileList.size())+ "\n";
	for (auto it = _checkMap.begin(); it != _checkMap.end(); it++) {
		res += it->first + " ";
		res += SHMBasic::toString((it->second).size()) + "\n";
	}
	return res;
}

SHMString SHMIndex::goodResultCheck() {
	if (_goodRes.length() > 0) return _goodRes;
	for (int i=0; i<_checkFileList.at(0).length(); i++) {
		_goodRes += "0";
	}
	return _goodRes;
}



SHMString SHMIndex::run() {
	SHMString resultString;
	for (auto it = _checkMap.begin(); it != _checkMap.end(); it++) {
		if ((it->first) == goodResultCheck()) continue;
		resultString += it->first + "\n";
		SHMList<int> indexList = it->second;
		for (int i=0; i<indexList.size(); i++) {
			resultString += compareToGood(indexList.at(i));
		}
	}

	return resultString;
}

SHMString SHMIndex::compareToGood(int a) {
	SHMString res = "";
	SHMList<int> goodList = _checkMap[goodResultCheck()];
	for (int i=0; i<goodList.size(); i++) {
		res += compare(a, goodList.at(i));
	}
	return res+"\n";
}

SHMString SHMIndex::compare(int a, int b) {
	SHMTreeNode nodeA = _nodeList[a];
	SHMTreeNode nodeB = _nodeList[b];

	SHMString res = "";
	bool equal = (nodeA == nodeB);
	// res += SHMBasic::toString(equal);

	if (equal) {
		res += "(" + _fileNameList[a] + " - " + _fileNameList[b] + ")\n";
	}
	return res;
}