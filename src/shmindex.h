#include "shmtreenode.h"
#include "pugixml.hpp"

class SHMIndex {

public:

	SHMIndex();

	~SHMIndex();

	void addNode(const SHMString &fileName, const SHMString &outputFile);

	void setSeedNode(const SHMString &fileName, const SHMString &outputFile);

	SHMString toXMLString() const;

	SHMString checkResults();

	SHMString goodOutput();

	SHMString run();

	SHMString printCompareToGood(int a);

	SHMString printCompare(int a, int b);

	int compare(SHMTreeNode* &root, SHMTreeNode* &rhs, SHMTreeNode* &diff, SHMTreeNode* current = NULL);

protected:

	void addOutputFile(const SHMString &outputFile);

	SHMString getOutputContents(const SHMString &outputFile);

private:

	SHMList<SHMTreeNode*> _nodeList;
	SHMList<SHMString> _fileNameList;
	SHMList<SHMString> _outputList;

	SHMMap <SHMString, SHMList<int> > _outputMap;

	SHMTreeNode* _seedNode;
	SHMString _seedFileName;
	SHMString _seedOutput;
};