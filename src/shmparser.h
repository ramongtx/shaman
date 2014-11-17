#include "shmtreenode.h"

class SHMParser {
	
public:
    static SHMString getFileContents(SHMString address);
    static SHMList<SHMString> splitNewlines(SHMString contents);
  	static int indexFirstAlnum(SHMString line);
	static int generateTree(SHMList<SHMString> list, int pos, SHMTreeNode& root, bool first = true);
	static void setNodeFamily(SHMTreeNode &node);
	static void setNodeType(SHMTreeNode &node);
	static void setNodeLineNumbers(SHMTreeNode &node);
	static void setNodeAttributes(SHMTreeNode &node);

	static void normalizeAttributes(SHMString &rawAttr, const SHMString &nodeFamily);


protected:

};
