#include "shmindex.h"

int main (int argc, char *argv[]) {
	SHMIndex index;

	for (int i = 1; i<argc ; i+=2) {
		SHMString fileAddress = argv[i];
		SHMString outputFile = argv[i+1];
		index.addNode(fileAddress,outputFile);
	}
	
	printf ("%s\n",index.toXMLString().c_str());
	// fprintf(stderr,"%s\n",index.checkResults().c_str());
	fprintf(stderr,"%s",index.run().c_str());

	return 0;
}