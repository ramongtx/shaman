#include "shmparser.h"

int main () {
	printf("Converting files from input folder\n");
	SHMString contents = SHMParser::getFileContents("/Users/Ramon/Documents/Repositories/shaman/shamanCPP/input/teste2.ast");
	SHMList<SHMString> list = SHMParser::splitNewlines(contents);
   SHMTreeNode root;
   SHMParser::generateTree(list,0,root);
   printf("Printing: %lu\n%s\n",root.children().size(),root.toString().c_str());
}