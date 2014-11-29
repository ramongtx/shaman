#include "shmindex.h"

SHMIndex::SHMIndex() {
	_seedNode = NULL;
}

SHMIndex::~SHMIndex() {
	// if (_seedNode) {
	// 	_seedNode->deleteChildren();
	// 	delete _seedNode;
	// }
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
	SHMTreeNode *node = new SHMTreeNode(content);
	cleanNodeForFamily(node, "VarDecl");
	_nodeList.push_back(node);
	addOutputFile(outputFile);

	if (!_seedNode && (_outputList.at(_outputList.size()-1))==goodOutput()) {
		_seedNode = node;
	}
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

SHMTreeNode* SHMIndex::translate(SHMTreeNode* node) {
	for (auto it = _translateIndex.begin(); it != _translateIndex.end(); it++) {
		if (*(it->similar) == (*node)) return (it->seed);
	}
	return node;
}

bool SHMIndex::isEqualTranslated  (SHMTreeNode *a, SHMTreeNode* b) {
	return (isEqual(translate(a),translate(b)));
}

bool SHMIndex::isEqual (SHMTreeNode* a, SHMTreeNode* b) {
	if (a->joker() || b->joker()) return true;

	if (a->nodeFamily() != b->nodeFamily()) return false;
	// if (a->nodeType() != b->nodeType()) return false;
	// if (a->nodeAttributes() != b->nodeAttributes()) return false;

	if (a->children().size() != b->children().size()) return false;
	for(int i = 0; i<a->children().size(); i++){
		if (!isEqualTranslated(a->children().at(i),b->children().at(i))) return false;
		// if (!isEqual(a->children().at(i),b->children().at(i))) return false;
	}
	return true;
}


SHMString SHMIndex::run() {
	SHMString resultString;
	// generateTranslations();
	resultString+= "[[["+SHMBasic::toString(_translateIndex.size())+"]]]\n";
	for (auto it = _outputMap.begin(); it != _outputMap.end(); it++) {
		if ((it->first) == goodOutput()) continue;

		SHMList<int> indexList = it->second;
		for (int i=0; i<indexList.size(); i++) {
			SHMTreeNode *diff;
			int bestMatch;
			int comp = compareToGood(indexList.at(i), bestMatch, diff);
			bool equal = (comp > 3);
			if (equal) {
				resultString += printCompare(indexList.at(i), bestMatch, comp, diff) + "\n";
			}
		}
	}

	return resultString;
}

SHMString SHMIndex::printCompare(int index, int bestMatch, int comp, SHMTreeNode* diff) {
	SHMString badFile = _fileNameList[index];
	SHMTreeNode *badNode = _nodeList[index];
	SHMString badOutput = _outputList[index];
	SHMString goodFile = _fileNameList[bestMatch];
	SHMTreeNode *goodNode = _nodeList[bestMatch];

	diff->setJoker(true);
	SHMTreeNode* goodDiff = findContext(goodNode, badNode);
	diff->setJoker(false);

	SHMString badLines = "?";
	if (diff) badLines = SHMBasic::toString(diff->lineStart()) + "~" + SHMBasic::toString(diff->lineEnd());

	SHMString goodLines = "?";
	if (goodDiff) goodLines = SHMBasic::toString(goodDiff->lineStart()) + "~" + SHMBasic::toString(goodDiff->lineEnd());

	SHMString badFamily = "?";
	if (diff) badFamily = diff->nodeFamily();

	SHMString goodFamily = "?";
	if (goodDiff) goodFamily = goodDiff->nodeFamily();

	SHMString resultString = SHMBasic::toString(comp) + " = " + badFile + " > " + goodFile;
	resultString += "\t{" + badOutput + "}"; 
	resultString += "\t(" + badLines + " > " + goodLines + ")";
	resultString += "\t[" + badFamily + " > " + goodFamily + "]";

	return resultString;
}

int SHMIndex::compareToGood(int a, int &bestMatch, SHMTreeNode* &diff) {
	int res = 0;
	bestMatch = a;
	SHMList<int> goodList = _outputMap[goodOutput()];
	for (int i=0; i<goodList.size(); i++) {
		SHMTreeNode *childDiff;
		int childRes = compare(a, goodList.at(i), childDiff);
		if (childRes > res) {
			res = childRes;
			diff = childDiff;
			bestMatch = goodList.at(i);
		}
	}
	return res;
}


int SHMIndex::compare(int a, int b, SHMTreeNode* &diff) {
	SHMTreeNode* nodeA = _nodeList[a];
	SHMTreeNode* nodeB = _nodeList[b];
	int comp = compare(nodeA, nodeB, diff);
	return comp;
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
		// bool equal = ((*root) == (*rhs));
		bool equal = isEqualTranslated(root, rhs);
		current->setJoker(false);
		if (equal) {
			diff = current;
			return 1;
		}
	}
	return 0;

}

void SHMIndex::generateTranslations() {
	SHMList<int> goodList = _outputMap[goodOutput()];
	for (int i=0; i<goodList.size(); i++) {
		if (_nodeList.size() <= goodList.at(i)) {
			fprintf(stderr,"PROBLEM\n");
		}
		SHMTreeNode* other = _nodeList.at(goodList.at(i));
		if (_seedNode == other) continue;
		generateTranslations(_seedNode, other);
	}
}

void SHMIndex::generateTranslations(SHMTreeNode* seed, SHMTreeNode* other) {
	SHMTreeNode *res = NULL;
	for(int i = 0; i<seed->children().size(); i++){
		SHMTreeNode *seedChild = seed->children().at(i);

		generateTranslations(seedChild,other);

		seedChild->setJoker(true);
		if ((*_seedNode) == (*other)) {
			res = findContext(other, _seedNode);
			SHMTreePair pair;
			pair.seed = seedChild;
			pair.similar = res;
			_translateIndex.push_back(pair);
		}
		seedChild->setJoker(false);
	}
}


SHMTreeNode * SHMIndex::findContext(SHMTreeNode *&root, SHMTreeNode *&context) {
	if (context->joker()) return root;
	if (root->children().size() != context->children().size()) return NULL;

	SHMTreeNode *res = NULL;
	for(int i = 0; i<root->children().size(); i++){
		res = findContext(root->children().at(i), context->children().at(i));
		if (res) break;
	}
	return res;
}

void SHMIndex::cleanNodes() {
	for (int i=0; i<_nodeList.size(); i++) {
		cleanNodeForFamily(_nodeList.at(i),"VarDecl");
	}
}

void SHMIndex::cleanNodeForFamily(SHMTreeNode* &root, const SHMString &family) {
	int i=0;
	while (i<root->children().size()) {
		SHMTreeNode* child = root->children().at(i);
		if (child->nodeFamily() == family) {
			root->eraseChild(i);
		} else {
			cleanNodeForFamily(child,family);
			i++;
		}
	}
}