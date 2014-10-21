#include "shmindex.h"

int main (int argc, char *argv[]) {
	SHMIndex index;

	for (int i = 1; i<argc ; i++) {
		SHMString fileAddress = argv[i];
		index.addNode(fileAddress);
	}
	
	printf ("%s\n",index.toXMLString().c_str());

	return 0;
}