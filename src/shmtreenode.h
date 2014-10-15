#include "shmbasic.h"
#include "pugixml.hpp"

class SHMTreeNode {
public:
	SHMTreeNode();
	SHMTreeNode(SHMXMLNode& node);
	SHMTreeNode(SHMString& xmlString);

	SHMTreeNode copy(const SHMTreeNode &obj);

	void setLineContents(SHMString string);

	void setLineSingle(int line);
	void setLineStart(int line);
	void setLineEnd(int line);

	void setNodeType(SHMString string);
	void setNodeFamily(SHMString string);
	void setNodeAddress(SHMString string);
	void setNodeAttributes(SHMString string);
	void setJoker(bool joker);

	void appendChild(SHMTreeNode& child);

	SHMString lineContents() const;

	int lineEnd() const;
	int lineStart() const;

	SHMString nodeType() const;
	SHMString nodeFamily() const;
	SHMString nodeAddress() const;
	SHMString nodeAttributes() const;
	bool joker() const;

	void setParent(SHMTreeNode *parent);
	SHMTreeNode *parent();
	SHMTreeNode *root();

	SHMList<SHMTreeNode> children() const;

	SHMString toXMLString() const;
	void toXML(SHMXMLNode &node) const;

	void loadXML(const SHMString &contents);
	void loadXML(const SHMXMLNode &node);

	bool operator==(const SHMTreeNode& rhs) const;
	bool operator< (const SHMTreeNode& rhs) const;
	inline bool operator!=(const SHMTreeNode& rhs) const {return !operator==(rhs);}
	inline bool operator> (const SHMTreeNode& rhs) const {return rhs.operator< (*this);}
	inline bool operator<=(const SHMTreeNode& rhs) const {return !operator> (rhs);}
	inline bool operator>=(const SHMTreeNode& rhs) const {return !operator< (rhs);}

private:
	SHMList<SHMTreeNode> _children;
	SHMString _lineContents, _nodeAddress, _nodeType, _nodeFamily, _nodeAttributes;
	int _lineStart, _lineEnd;
	bool _joker;

	SHMTreeNode* _parent;

};