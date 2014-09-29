#include "shmbasic.h"
#include "pugixml.hpp"

class SHMTreeNode {
public:
	SHMTreeNode();
	SHMTreeNode(SHMXMLNode& node);
	SHMTreeNode(SHMString& xmlString);

	void setLineContents(SHMString string);

	void setLineSingle(int line);
	void setLineStart(int line);
	void setLineEnd(int line);

	void setNodeType(SHMString string);
	void setNodeFamily(SHMString string);
	void setNodeAddress(SHMString string);
	void setJoker(bool joker);

	void appendChild(SHMTreeNode& child);

	SHMString lineContents() const;

	int lineEnd() const;
	int lineStart() const;

	SHMString nodeType() const;
	SHMString nodeFamily() const;
	SHMString nodeAddress() const;
	bool joker() const;

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


protected:
	void addAttribute(const SHMString &name, const SHMString &string);
	void addAttribute(const SHMString &name, int value);

private:
	SHMList<SHMTreeNode> _children;
	SHMMap<SHMString,SHMString> _propertyMap;
	SHMString _lineContents, _nodeAddress, _nodeType, _nodeFamily;
	int _lineStart, _lineEnd;
	bool _joker;

};