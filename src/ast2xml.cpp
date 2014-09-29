#include "shmparser.h"

int main (int argc, char *argv[]) {

	if ( argc != 2 ) {
		printf ("usage: %s <ast-filename>\n", argv[0]);
	} else {

		SHMString fileAddress = argv[1];

		SHMString contents = SHMParser::getFileContents(fileAddress);
		SHMList<SHMString> list = SHMParser::splitNewlines(contents);
		SHMTreeNode root;
		SHMParser::generateTree(list,0,root);

		printf ("%s\n",root.toXMLString().c_str());
	}
	return 0;
}