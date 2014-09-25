#include "shmbasic.h"
#include "pugixml.hpp"

class SHMTreeNode {
public:
	SHMTreeNode();
	~SHMTreeNode();

	void setLineContents(SHMString string);
	void setLineSingle(int line);
	void setLineStart(int line);
	void setLineEnd(int line);
	void setNodeType(SHMString string);
	void setNodeAddress(SHMString string);
	void appendChild(SHMTreeNode& child);

	SHMString lineContents() const;
	int lineEnd() const;
	int lineStart() const;
	SHMString nodeType() const;
	SHMString nodeAddress() const;
	SHMList<SHMTreeNode> children() const;

	SHMString toString() const;
	SHMString mapToString() const;

protected:
	void addAttribute(SHMString name, SHMString &string);
	void addAttribute(SHMString name, int value);

private:
	SHMList<SHMTreeNode> _children;
	SHMMap<SHMString,SHMString> _propertyMap;
	int _lineStart, _lineEnd;

	/* data */
};