//
//  SHMTreeNode.h
//  shamanObjC
//
//  Created by Ramon Carvalho Maciel on 9/16/14.
//  Copyright (c) 2014 Ramon Carvalho Maciel. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SHMTreeNode : NSObject

@property NSInteger depth;
@property NSString* string;
@property NSMutableArray* children;

@end
