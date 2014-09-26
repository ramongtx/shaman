#include "shmparser.h"

int main (int argc, char *argv[]) {

	if ( argc != 3 ) {
		printf ("usage: %s <ast-filename> <destination-filename>\n", argv[0]);
	} else {

		SHMString fileAddress = argv[1];
		SHMString destination = argv[2];

		SHMString contents = SHMParser::getFileContents(fileAddress);
		SHMList<SHMString> list = SHMParser::splitNewlines(contents);
		SHMTreeNode root;
		SHMParser::generateTree(list,0,root);

		SHMOutputFileStream file(destination);
		file << root.toXML().c_str();
		file.close();
	}
	return 0;
}