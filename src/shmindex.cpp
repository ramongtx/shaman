#include "shmindex.h"


SHMIndex::SHMIndex() {
	_goodRes = "";
	SHMList<int> list;
	_checkMap["Ramon"] = list;
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
	SHMString res = "";
	for (int i=0; i<_checkFileList.size(); i++) {
		int count = 1;
		if(std::find(alreadyVisited.begin(), alreadyVisited.end(), i) == alreadyVisited.end()) {
			bool good = (res == goodResult());
			res += _checkFileList.at(i);
			for (int j=(i+1); j<_checkFileList.size(); j++) {
				if (_checkFileList.at(j) == _checkFileList.at(i)) {
					count++;
					alreadyVisited.push_back(j);
				}
			}
			if (good) res+= " GOOD ";
			res += " " + SHMBasic::toString(count) + "\n";
		}
	}
	return res;
}

SHMString SHMIndex::goodResult() {
	if (_goodRes.length() > 0) return _goodRes;
	for (int i=0; i<_checkFileList.at(0).length(); i++) {
		_goodRes += "0";
	}
	return _goodRes;
}

void SHMIndex::run() {

}


