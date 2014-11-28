#include "shmtreenode.h"
#include "pugixml.hpp"

typedef struct _SHMTreePair {
	SHMTreeNode* seed;
	SHMTreeNode* similar;
} SHMTreePair;

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

	void generateTranslations();

	void cleanNodes();

	void cleanNodeForFamily(SHMTreeNode* &root, const SHMString &family);

	int compareToGood(int a, int &bestMatch, SHMTreeNode* &diff);

	int compare(int a, int b, SHMTreeNode* &diff);

	SHMTreeNode *translate(SHMTreeNode* node);

	bool isEqual  (SHMTreeNode *a, SHMTreeNode* b);

	bool isEqualTranslated (SHMTreeNode *a, SHMTreeNode* b);

	int compare(SHMTreeNode* &root, SHMTreeNode* &rhs, SHMTreeNode* &diff, SHMTreeNode* current = NULL);

	SHMTreeNode * findContext(SHMTreeNode *&root, SHMTreeNode *&context);

	SHMString printCompare(int index, int bestMatch, int comp, SHMTreeNode* diff);

protected:

	void addOutputFile(const SHMString &outputFile);

	SHMString getOutputContents(const SHMString &outputFile);

	void generateTranslations(SHMTreeNode* seed, SHMTreeNode* other);

private:

	SHMList<SHMTreeNode*> _nodeList;
	SHMList<SHMString> _fileNameList;
	SHMList<SHMString> _outputList;
	SHMList<SHMTreePair> _translateIndex;

	SHMMap <SHMString, SHMList<int> > _outputMap;

	SHMTreeNode* _seedNode;
	SHMString _seedFileName;
	SHMString _seedOutput;
};