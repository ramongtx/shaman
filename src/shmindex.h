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

	void cleanNodes();

	void cleanNodeForFamily(SHMTreeNode* &root, const SHMString &family);

	int compareToGood(int a, int &bestMatch, SHMTreeNode* &diff);

	int compare(int a, int b, SHMTreeNode* &diff);

	int compare(SHMTreeNode* &root, SHMTreeNode* &rhs, SHMTreeNode* &diff, SHMTreeNode* current = NULL);

	SHMTreeNode * findContext(SHMTreeNode *&root, SHMTreeNode *&context);

	SHMString printCompare(int index, int bestMatch, int comp, SHMTreeNode* diff);

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