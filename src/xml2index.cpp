#include "shmindex.h"

int main (int argc, char *argv[]) {
	SHMIndex index;

	for (int i = 1; i<argc ; i+=2) {
		SHMString fileAddress = argv[i];
		SHMString checkFile = argv[i+1];
		index.addNode(fileAddress);
		index.addCheckFile(checkFile);
	}
	
	printf ("%s\n",index.toXMLString().c_str());
	fprintf(stderr,"%s\n",index.checkResults().c_str());

	return 0;
}