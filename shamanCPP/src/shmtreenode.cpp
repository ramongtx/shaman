#include "shmtreenode.h"

SHMTreeNode::SHMTreeNode() {
	_lineEnd = 0;
	_lineStart = 0;
}

SHMTreeNode::~SHMTreeNode() {
}

void SHMTreeNode::setLineContents(SHMString string) {
	_lineContents = string;
}

SHMString SHMTreeNode::lineContents() const {
	return _lineContents;
}

void SHMTreeNode::setNodeType(SHMString string) {
	_nodeType = string;
}

SHMString SHMTreeNode::nodeType() const {
	return _nodeType;
}

void SHMTreeNode::setNodeAddress(SHMString string) {
	_nodeAddress = string;
}

SHMString SHMTreeNode::nodeAddress() const {
	return _nodeAddress;
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
		str.append(SHMString(it->first).c_str());
		str.append(": \"");
		str = it->second;
		str.append(str.c_str());
		str.append("\"");
	}
	str.append("}");
	return str;
}

void SHMTreeNode::addAttribute(const SHMString &name, const SHMString &string) {
	_propertyMap[name] = string;
}

void SHMTreeNode::addAttribute(const SHMString &name, int value) {
	_propertyMap.erase(name);
}

#pragma mark XML

SHMString SHMTreeNode::toXML() const {
    
    SHMXMLDocument doc;
    //[code_modify_add
    // add node with some name
    SHMXMLNode node = doc.append_child();

    toXML(node);

    SHMOutputStringStream oss;
    doc.print(oss);
    return oss.str();
}

void SHMTreeNode::toXML(SHMXMLNode &node) const {
	node.set_name("node");

	node.append_attribute("lineStart") = _lineStart;
	node.append_attribute("lineEnd") = _lineEnd;
	node.append_attribute("nodeType") = _nodeType.c_str();

    for(SHMMap<SHMString, SHMString>::const_iterator it = _propertyMap.begin(); it != _propertyMap.end(); ++it) {
		node.append_attribute(SHMString(it->first).c_str()) = SHMString(it->second).c_str();
	}

	for(SHMList<SHMTreeNode>::const_iterator it = _children.begin(); it != _children.end(); ++it) {
		SHMXMLNode newChild = node.append_child();
		(*it).toXML(newChild);
	}
}

void SHMTreeNode::loadXML(const SHMString &contents) {

    SHMXMLDocument doc;
    doc.load(contents.c_str());
    SHMXMLNode node = doc.first_child();
    loadXML(node);
}

void SHMTreeNode::loadXML(const SHMXMLNode &node) {
	static SHMString _lineStartName = "lineStart";
	static SHMString _lineEndName = "lineEnd";
	static SHMString _nodeTypeName = "nodeType";
	for (SHMXMLAttribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
		SHMString name = attr.name();
		if (!name.compare(_lineStartName)) setLineStart(attr.as_int());
		else if (!name.compare(_lineEndName)) setLineEnd(attr.as_int());
		else if (!name.compare(_nodeTypeName)) setNodeType(attr.value());
   	 }

	for (SHMXMLNode child = node.first_child(); child; child = child.next_sibling()) {
		SHMTreeNode childNode;
		childNode.loadXML(child);
		appendChild(childNode);
	}
}