#include "shmindex.h"

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
		SHMXMLNode childNode = node.append_child();
		_nodeList.at(i).toXML(childNode);
	}

	SHMOutputStringStream oss;
	doc.print(oss);
	return oss.str();
}
