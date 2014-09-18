#include <iostream>
#include "shmtypes.h"
#include "shmtreenode.h"

class SHMParser {
	
public:
    static SHMString getFileContents(SHMString address);
    static SHMList<SHMString> splitNewlines(SHMString contents);
    
};
