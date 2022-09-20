/*!
    \file       main.mm
    \brief      Client source file

    \author     
    \date
 */

#import "header.h"

int main(int argc, const char *argv[]) {
    @autoreleasepool {
        NSLog(@"Hello, world!");
    }

    Shape2D *shape = [[Shape2D alloc] initWithPoint:CGPoint{3, 4}];;

    NSLog(@"%@", shape);

    [shape release];

    return 0;
}
