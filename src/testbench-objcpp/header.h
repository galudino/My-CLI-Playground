/*!
    \file       header.h
    \brief      Header file

    \author     
    \date
 */

#ifndef HEADER_H
#define HEADER_H

#import <Foundation/Foundation.h>

@protocol EuclideanProtocol

@property(readonly) NSUInteger area;
@property(readonly) NSUInteger perimeter;

- (NSUInteger)distanceFrom:(id)other;

@end

@interface Shape2D : NSObject<EuclideanProtocol>

- (instancetype)init;
- (instancetype)initWithPoint:(CGPoint)position;

@property(nonatomic) CGFloat x;
@property(nonatomic) CGFloat y;

@property(readonly) NSUInteger area;
@property(readonly) NSUInteger perimeter;

- (NSUInteger)distanceFrom:(id)other;

@end

#endif /* HEADER_H */
