#include "shmtreenode.h"

SHMTreeNode::SHMTreeNode() {
	_lineEnd = 0;
	_lineStart = 0;
}

SHMTreeNode::~SHMTreeNode() {
}

void SHMTreeNode::setLineContents(SHMString string) {
	addAttribute("lineContents", string);
}

SHMString SHMTreeNode::lineContents() const {
	SHMMap<SHMString, SHMString>::const_iterator it = _propertyMap.find("lineContents");
	if (it == _propertyMap.end()) return "";
	return it->second;
}

void SHMTreeNode::setNodeType(SHMString string) {
	addAttribute("nodeType", string);
}

SHMString SHMTreeNode::nodeType() const {
	SHMMap<SHMString, SHMString>::const_iterator it = _propertyMap.find("nodeType");
	if (it == _propertyMap.end()) return "";
	return it->second;}

void SHMTreeNode::setNodeAddress(SHMString string) {
	addAttribute("nodeAddress", string);
}

SHMString SHMTreeNode::nodeAddress() const {
	SHMMap<SHMString, SHMString>::const_iterator it = _propertyMap.find("nodeAddress");
	if (it == _propertyMap.end()) return "";
	return it->second;
}

void SHMTreeNode::setLineSingle(int line) {
	setLineEnd(line);
	setLineStart(line);
}

int SHMTreeNode::lineStart() const {
	return _lineStart;
}

int SHMTreeNode::lineEnd() const {
	return _lineEnd;
}

void SHMTreeNode::setLineStart(int line) {
	_lineStart = line;
}

void SHMTreeNode::setLineEnd(int line) {
	_lineEnd = line;
}

void SHMTreeNode::appendChild(SHMTreeNode& child) {
	_children.push_back(child);
}

SHMList<SHMTreeNode> SHMTreeNode::children() const {
	return _children;
}

SHMString SHMTreeNode::toString() const {
	SHMString str = nodeType();
	str.append(" (");
	str.append(SHMBasic::toString(lineStart()));
	str.append("->");
	str.append(SHMBasic::toString(lineEnd()));
	str.append(") ");
	str.append(nodeAddress());
	for(SHMList<SHMTreeNode>::const_iterator it = _children.begin(); it != _children.end(); ++it) {
		str.append("\n\t");
		str.append(SHMBasic::replaceSubstring((*it).toString(),"\n\t","\n\t\t"));
	}
	return str;
}

SHMString SHMTreeNode::mapToString () const {
	SHMString str = "{";
	for(SHMMap<SHMString, SHMString>::const_iterator it = _propertyMap.begin(); it != _propertyMap.end(); ++it) {
		str.append(it->first);
		str.append(": \"");
		str.append(it->second);
		str.append("\"");
	}
	str.append("}");
	return str;
}

void SHMTreeNode::addAttribute(SHMString name, SHMString &string) {
	_propertyMap[name] = string;
}

void SHMTreeNode::addAttribute(SHMString name, int value) {
	_propertyMap.erase(name);
}