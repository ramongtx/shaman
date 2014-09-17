//
//  SHMParser.m
//  shamanObjC
//
//  Created by Ramon Carvalho Maciel on 9/16/14.
//  Copyright (c) 2014 Ramon Carvalho Maciel. All rights reserved.
//

#import "SHMParser.h"

@implementation SHMParser

+(NSString*)getFileContents:(NSString*)fileAddress {
    return [NSString stringWithContentsOfFile:fileAddress encoding:NSUTF8StringEncoding error:nil];
}

+(NSArray*)splitLines:(NSString*)contents {
    return [contents componentsSeparatedByString:@"\n"];
}

+(SHMTreeNode*)makeTree:(NSArray*)array {
    SHMTreeNode* node = [[SHMTreeNode alloc] init];
    [node setDepth:0];
    if ([array count] > 0) {
        [node setString:[array objectAtIndex:0]];
        [self addChildrenTo:node withArray:array starting:1];
    }
    for (NSString* str in array) {
        NSString* depth = [NSString stringWithFormat:@"%ld",(long)[SHMParser depthFromString:str]];
        NSLog(str);
        NSLog(depth);
    }
    return node;
}

+(void)addChildrenTo:(SHMTreeNode*)root withArray:(NSArray*)array starting:(NSInteger)startPos {
    if ([array count] == startPos) return;
    
    NSString* string = [array objectAtIndex:startPos];
    NSInteger depth = [self depthFromString:string];
    if (depth > [root depth]) {
        SHMTreeNode* node = [[SHMTreeNode alloc] init];
        [node setString:string];
        [node setDepth:depth];
    }
}

+(NSInteger)depthFromString:(NSString*)string {
    BOOL contains = NO;
    int i;
    for (i = 0; i < [string length]; i++) {
        unichar c = [string characterAtIndex:i];
        if (isalnum(c)) {
            contains = YES;
            break;
        }
    }
    if (!contains) return -1;
    return i/2;
}

@end
