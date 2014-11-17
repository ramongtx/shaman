#include "shmtreenode.h"
#include "pugixml.hpp"

class SHMIndex {

public:
	SHMIndex();
	~SHMIndex();

	void addNode(const SHMString &fileName, const SHMString &xmlString);

	void addNode(const SHMString &fileName);

	void addCheckFile(const SHMString &checkFile);

	SHMString toXMLString() const;

	SHMString checkResults();

	SHMString goodResult();

	void run();

private:
	SHMList<SHMTreeNode> _nodeList;
	SHMList<SHMString> _fileNameList;
	SHMList<SHMString> _checkFileList;
	SHMString _goodRes;
	SHMList<int> _badCodes;
	SHMMap <SHMString, SHMList<int> > _checkMap;

};