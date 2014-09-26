#include "shmtreenode.h"

class SHMParser {
	
public:
    static SHMString getFileContents(SHMString address);
    static SHMList<SHMString> splitNewlines(SHMString contents);
  	static int indexFirstAlnum(SHMString line);
	static int generateTree(SHMList<SHMString> list, int pos, SHMTreeNode& root);
	static void setNodePropertiesFromContents(SHMTreeNode &node);
	static void setNodeLineNumbers(SHMTreeNode &node);


protected:

};
