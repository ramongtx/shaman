#include "shmtreenode.h"

SHMTreeNode::SHMTreeNode() {
}

SHMTreeNode::~SHMTreeNode() {
}

void SHMTreeNode::setLineContents(SHMString string) {
	addAttribute("lineContents", string);
}

SHMString SHMTreeNode::lineContents() const {
	return _propertyMap.find("lineContents")->second;
}

void SHMTreeNode::setNodeType(SHMString string) {
	addAttribute("nodeType", string);
}

SHMString SHMTreeNode::nodeType() const {
	return _propertyMap.find("nodeType")->second;
}

void SHMTreeNode::setLineSingle(int line) {
	setLineEnd(line);
	setLineStart(line);
}

void SHMTreeNode::setLineStart(int line) {
	addAttribute("lineStart", line);
}

void SHMTreeNode::setLineEnd(int line) {
	addAttribute("lineEnd", line);
}

void SHMTreeNode::appendChild(SHMTreeNode& child) {
	_children.push_back(child);
}

SHMList<SHMTreeNode> SHMTreeNode::children() const {
	return _children;
}

SHMString SHMTreeNode::toString() const {
	SHMString str = nodeType();
	for(SHMList<SHMTreeNode>::const_iterator it = _children.begin(); it != _children.end(); ++it) {
		str.append("\n\t");
		str.append(SHMSupport::replaceSubstring((*it).toString(),"\n\t","\n\t\t"));
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