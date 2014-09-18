#include "shmparser.h"

int main () {
	printf("Converting files from input folder\n");
	SHMString contents = SHMParser::getFileContents("/Users/Ramon/Documents/Repositories/shaman/shamanCPP/input/teste.ast");
	SHMList<SHMString> list = SHMParser::splitNewlines(contents);
	for (SHMList<SHMString>::iterator iterator = list.begin(); iterator != list.end(); ++iterator) {
		SHMString str = *iterator;
		printf("%s\n",str.c_str());
   }
}