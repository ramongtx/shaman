#include "shmtreenode.h"

SHMTreeNode::SHMTreeNode() {
	_lineEnd = 0;
	_lineStart = 0;
	_joker = false;
}

SHMTreeNode::SHMTreeNode(SHMXMLNode& node) {
	_lineEnd = 0;
	_lineStart = 0;
	_joker = false;
	loadXML(node);
}

SHMTreeNode::SHMTreeNode(SHMString& xmlString) {
	_lineEnd = 0;
	_lineStart = 0;
	_joker = false;
	loadXML(xmlString);
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

void SHMTreeNode::setNodeFamily(SHMString string) {
	_nodeFamily = string;
}

SHMString SHMTreeNode::nodeFamily() const {
	return _nodeFamily;
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

bool SHMTreeNode::joker() const {
	return _joker;
}

void SHMTreeNode::setJoker(bool joker) {
	_joker = joker;
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
	node.append_attribute("nodeFamily") = _nodeFamily.c_str();
	node.append_attribute("joker") = _joker;

    for(SHMMap<SHMString, SHMString>::const_iterator it = _propertyMap.begin(); it != _propertyMap.end(); ++it) {
		node.append_attribute(SHMString(it->first).c_str()) = SHMString(it->second).c_str();
	}

	if (!joker()) {
		for(SHMList<SHMTreeNode>::const_iterator it = _children.begin(); it != _children.end(); ++it) {
			SHMXMLNode newChild = node.append_child();
			(*it).toXML(newChild);
		}
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
	static SHMString _nodeFamilyName = "nodeFamily";
	static SHMString _jokerName = "joker";
	for (SHMXMLAttribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
		SHMString name = attr.name();

		if (!name.compare(_lineStartName)) setLineStart(attr.as_int());
		else if (!name.compare(_lineEndName)) setLineEnd(attr.as_int());
		else if (!name.compare(_nodeTypeName)) setNodeType(attr.value());
		else if (!name.compare(_nodeFamilyName)) setNodeFamily(attr.value());
		else if (!name.compare(_jokerName)) setJoker(attr.as_bool());
   	 }

   	 if (!joker()) {
   	 	for (SHMXMLNode child = node.first_child(); child; child = child.next_sibling()) {
   	 		SHMTreeNode childNode;
   	 		childNode.loadXML(child);
   	 		appendChild(childNode);
   	 	}
   	 }
}

bool SHMTreeNode::operator==(const SHMTreeNode& rhs) const {
	if (joker() || rhs.joker()) return true;

	if (rhs.nodeFamily() != nodeFamily()) return false;
	if (rhs.nodeType() != nodeType()) return false;
	if (rhs.children().size() != children().size()) return false;
	for(int i = 0; i<children().size(); i++){
		if (rhs.children().at(i) != children().at(i)) return false;
	}
	return true;
}

bool SHMTreeNode::operator<(const SHMTreeNode& rhs) const {
	return false;
}
