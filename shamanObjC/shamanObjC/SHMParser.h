//
//  SHMParser.h
//  shamanObjC
//
//  Created by Ramon Carvalho Maciel on 9/16/14.
//  Copyright (c) 2014 Ramon Carvalho Maciel. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SHMTreeNode.h"

@interface SHMParser : NSObject

+(NSString*)getFileContents:(NSString*)fileAddress;
+(NSArray*)splitLines:(NSString*)contents;
+(SHMTreeNode*)makeTree:(NSArray*)array;

@end
