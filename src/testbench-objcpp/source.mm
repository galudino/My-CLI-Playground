/*!
    \file       source.m
    \brief      Source file

    \author     
    \date
 */

#import "header.h"

@interface Shape2D () {
    CGPoint _pos;
}

@end

@implementation Shape2D

- (instancetype)init {
    if (!(self = [super init])) {
        return nil;
    }

    self->_pos.x = self->_pos.y = 0.0f;

    return self;
}

- (instancetype)initWithPoint:(CGPoint)position {    
    if (!(self = [super init])) {
        return nil;
    }

    self->_pos = position; 

    return self;
}

- (NSUInteger)area {
    return 0;
}

- (NSUInteger)perimeter {
    return 0;
}

- (NSUInteger)distanceFrom:(id)other {
    return 0;
}

- (CGFloat)x {
    return self->_pos.x;
}

- (CGFloat)y {
    return self->_pos.y;
}

- (void)setX:(CGFloat)x {
    self->_pos.x = x;
}

- (void)setY:(CGFloat)y {
    self->_pos.y = y;
}

@end
