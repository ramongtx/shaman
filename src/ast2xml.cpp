#include "shmparser.h"

int main (int argc, char *argv[]) {
	SHMList<SHMString> list;

	if ( argc > 2 ) {
		printf ("usage: %s <ast-filename>\n", argv[0]);
		return 1;
	}

	if ( argc == 1 ) {
    	char* line = NULL;
    	size_t len = 0;
    	int line_num = 0;
		while (getline(&line, &len, stdin) != -1) {
			SHMString newLine = line;
			list.push_back(newLine);
		}
	} else {
		SHMString fileAddress = argv[1];

		SHMString contents = SHMParser::getFileContents(fileAddress);
		list = SHMParser::splitNewlines(contents);
	}

	SHMTreeNode root;
	SHMParser::generateTree(list,0,root);

	printf ("%s\n",root.toXMLString().c_str());

	return 0;
}