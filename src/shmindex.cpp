#include "shmindex.h"

SHMIndex::SHMIndex() {
	_seedNode = NULL;
}

SHMIndex::~SHMIndex() {
	if (_seedNode) {
		_seedNode->deleteChildren();
		delete _seedNode;
	}
	for (int i=0; i<_nodeList.size(); i++) {
		_nodeList.at(i)->deleteChildren();
		delete _nodeList.at(i);
	}
	_nodeList.clear();
}

void SHMIndex::addNode(const SHMString &fileName, const SHMString &outputFile) {
	SHMInputFileStream ifs(fileName.c_str());
	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
		(std::istreambuf_iterator<char>()    ) );
	_fileNameList.push_back(fileName);
	_nodeList.push_back(new SHMTreeNode(content));
	addOutputFile(outputFile);
}

void SHMIndex::setSeedNode(const SHMString &fileName, const SHMString &outputFile) {
	SHMInputFileStream ifs(fileName.c_str());
	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
		(std::istreambuf_iterator<char>()    ) );
	_seedFileName = fileName;
	_seedNode = new SHMTreeNode(content);
	_seedOutput = getOutputContents(outputFile);
}

void SHMIndex::addOutputFile(const SHMString &outputFile) {
	SHMString content = getOutputContents(outputFile);
	_outputList.push_back(content);

	int pos = _outputList.size()-1;
	if (_outputMap.find(content) == _outputMap.end()) {
		SHMList<int> list;
		list.push_back(pos);
		_outputMap[content] = list;
	} else {
		SHMList<int> list = _outputMap.at(content);
		list.push_back(pos);
		_outputMap[content] = list;
	}
}

SHMString SHMIndex::getOutputContents(const SHMString &outputFile) {
	SHMInputFileStream ifs(outputFile.c_str());
	SHMString content( (std::istreambuf_iterator<char>(ifs) ),
		(std::istreambuf_iterator<char>()    ) );
	content = SHMBasic::replaceSubstring(content, "\n", "");
	return content;
}


SHMString SHMIndex::toXMLString() const {
	SHMXMLDocument doc;
	SHMXMLNode node = doc.append_child();

	for (int i = 0; i<_nodeList.size(); i++) {
		SHMXMLNode node = doc.append_child();
		node.set_name("entry");
		node.append_attribute("file") = _fileNameList.at(i).c_str();
		node.append_attribute("output") = _outputList.at(i).c_str();
		SHMXMLNode childNode = node.append_child();
		_nodeList.at(i)->toXML(childNode);
	}

	SHMOutputStringStream oss;
	doc.print(oss);
	return oss.str();
}

SHMString SHMIndex::checkResults() {
	SHMList<int> alreadyVisited;
	SHMString res = ""+ SHMBasic::toString(_outputList.size())+ "\n";
	for (auto it = _outputMap.begin(); it != _outputMap.end(); it++) {
		res += it->first + " ";
		res += SHMBasic::toString((it->second).size()) + "\n";
	}
	return res;
}

SHMString SHMIndex::goodOutput() {
	if (_seedOutput.length() > 0) return _seedOutput;
	for (int i=0; i<_outputList.at(0).length(); i++) {
		_seedOutput += "0";
	}
	return _seedOutput;
}

SHMString SHMIndex::run() {
	SHMString resultString;
	for (auto it = _outputMap.begin(); it != _outputMap.end(); it++) {
		// if ((it->first) == goodOutput()) continue;
		resultString += it->first + "\n";
		SHMList<int> indexList = it->second;
		for (int i=0; i<indexList.size(); i++) {
			resultString += printCompareToGood(indexList.at(i));
		}
		resultString += "\n";
	}

	return resultString;
}

SHMString SHMIndex::printCompareToGood(int a) {
	SHMString res = "";
	SHMList<int> goodList = _outputMap[goodOutput()];
	for (int i=0; i<goodList.size(); i++) {
		res += printCompare(a, goodList.at(i));
	}
	return res;
}

SHMString SHMIndex::printCompare(int a, int b) {
	SHMTreeNode* nodeA = _nodeList[a];
	SHMTreeNode* nodeB = _nodeList[b];
	SHMTreeNode* diffNode = NULL;

	SHMString res = "";
	if (a == b) return res;
	int comp = compare(nodeA, nodeB, diffNode);
	// res += SHMBasic::toString(equal);
	bool equal = (comp > 1);
	if (equal) {
		res += "(" + _fileNameList[a] + " - " + _fileNameList[b] + ") " + SHMBasic::toString(comp) + "\n";
		res += "\t"+ SHMBasic::toString(diffNode->lineStart()) + "~" + SHMBasic::toString(diffNode->lineEnd()) + "\n";
	}
	return res;
}

int SHMIndex::compare(SHMTreeNode* &root, SHMTreeNode* &rhs, SHMTreeNode* &diff, SHMTreeNode* current) {
	if (!current) return compare(root, rhs, diff, root);
	int numChildren = current->children().size();
	int res = 0;
	for (int i=0; i<numChildren; i++) {
		SHMTreeNode *diffChild;
		int childRes = compare(root, rhs, diffChild, current->children().at(i));
		if (childRes > res) {
			res = childRes;
			diff = diffChild;
		}
	}
	if (res) return res+1;
	else {
		current->setJoker(true);
		bool equal = ((*root) == (*rhs));
		current->setJoker(false);
		if (equal) {
			diff = current;
			return 1;
		}
	}
	return 0;

}