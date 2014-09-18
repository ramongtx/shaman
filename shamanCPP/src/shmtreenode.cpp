#include "shmtreenode.h"

SHMTreeNode::SHMTreeNode() {
	set_name("ASTNode");
}

SHMTreeNode::~SHMTreeNode() {
}

void SHMTreeNode::setLineContents(SHMString string) {
	addAttribute("lineContents", string);
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
	append_copy(child);
}

SHMList<SHMTreeNode> SHMTreeNode::children() {
	return _children;
}

void SHMTreeNode::addAttribute(SHMString name, SHMString string) {
	pugi::xml_attribute attr;
	attr.set_name(name.c_str());
	attr.set_value(string.c_str());
	remove_attribute(name.c_str());
	append_attribute(name.c_str());
}

void SHMTreeNode::addAttribute(SHMString name, int value) {
	pugi::xml_attribute attr;
	attr.set_name(name.c_str());
	attr.set_value(value);
	remove_attribute(name.c_str());
	append_attribute(name.c_str());
}