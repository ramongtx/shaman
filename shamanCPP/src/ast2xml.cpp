#include "shmparser.h"

int main () {
	printf("Converting files from input folder\n");
	SHMString contents = SHMParser::getFileContents("/Users/Ramon/Documents/Repositories/shaman/shamanCPP/input/teste2.ast");
	SHMList<SHMString> list = SHMParser::splitNewlines(contents);
	int i = 0;
	for (SHMList<SHMString>::iterator iterator = list.begin(); iterator != list.end(); ++iterator) {
		SHMString str = *iterator;
		printf("%03d %03d %s\n",i++, SHMParser::indexFirstAlnum(str), str.c_str());
   }
   SHMTreeNode root;
   SHMParser::generateTree(list,0,root);
   printf("Printing: %lu\n%s\n",root.children().size(),root.toString().c_str());
}