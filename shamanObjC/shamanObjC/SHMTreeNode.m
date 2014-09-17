//
//  SHMTreeNode.m
//  shamanObjC
//
//  Created by Ramon Carvalho Maciel on 9/16/14.
//  Copyright (c) 2014 Ramon Carvalho Maciel. All rights reserved.
//

#import "SHMTreeNode.h"

@implementation SHMTreeNode

-(void)addNode:(SHMTreeNode*)childNode {
    [self.children addObject:childNode];
}

@end
