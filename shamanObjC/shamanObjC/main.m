//
//  main.m
//  shamanObjC
//
//  Created by Ramon Carvalho Maciel on 9/16/14.
//  Copyright (c) 2014 Ramon Carvalho Maciel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SHMParser.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        
        // insert code here...
        if (argc > 1) {
            NSString* path = [NSString stringWithUTF8String:argv[1]];
            NSString* fileContents = [SHMParser getFileContents:path];
            NSArray *brokenByLines = [SHMParser splitLines:fileContents];
            [SHMParser makeTree:brokenByLines];
        }
    }
    return 0;
}

