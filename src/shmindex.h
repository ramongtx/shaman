#include "shmtreenode.h"
#include "pugixml.hpp"

class SHMIndex {

public:
	void addNode(const SHMString &fileName, const SHMString &xmlString);

	void addNode(const SHMString &fileName);

	SHMString toXMLString() const;

private:
	SHMList<SHMTreeNode> _nodeList;
	SHMList<SHMString> _fileNameList;

};