#include "shmtypes.h"
#include "pugixml.hpp"

class SHMTreeNode : pugi::xml_node{
public:
	SHMTreeNode();
	~SHMTreeNode();

	void setLineContents(SHMString string);
	void setLineSingle(int line);
	void setLineStart(int line);
	void setLineEnd(int line);
	void appendChild(SHMTreeNode& child);

	SHMString lineContents();
	int lineEnd();
	int lineStart();
	SHMList<SHMTreeNode> children();

protected:
	void addAttribute(SHMString name, SHMString string);
	void addAttribute(SHMString name, int value);

private:
	SHMList<SHMTreeNode> _children;

	/* data */
};