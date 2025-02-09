/*!
    \file       main.m
    \brief      Client source file

    \author     
    \date
 */

#import "header.h"

#import <Foundation/Foundation.h>

#if defined(DEBUG) && DEBUG == 1
#define DLog(fmt, ...)                                                         \
    [logQueue                                                                  \
        addObject:[NSString stringWithFormat:@"[%s:%d] %s " fmt @"\n", __FILE__,    \
                                             __LINE__, __PRETTY_FUNCTION__,    \
                                             ##__VA_ARGS__]];\
NSLog((@"[%s:%d] %s " fmt), __FILE__, __LINE__, __PRETTY_FUNCTION__,       \
          ##__VA_ARGS__)
#else
#define DLog(...)
#endif

void writeLogToFile(NSArray *logQueue);
void deleteFirmwareFile(void);

int main() {
    uint32_t u = 23;
    int32_t v = 23;
    NSLog(@"%u, %d", u, v);
    NSMutableArray *logQueue = [NSMutableArray new];

    DLog();
    DLog();
    DLog(@"with text");

    writeLogToFile(logQueue);
    deleteFirmwareFile();

    NSString *str = @"abcdEfghijk";
    NSRange range = [str rangeOfString:@"E"];
    NSLog(@"%lu, %lu", range.location, range.length);

    return 0;
}

void writeLogToFile(NSArray<NSString *> *logQueue) {
    /// Create the string that we will write to a file.
    NSMutableString *logQueueAsString = [NSMutableString new];
   
    /// Iterate over all elements in `logQueue` and append each element to `logQueueAsString`.
    for (NSString *line in logQueue) {
        [logQueueAsString appendString:line];
    }
   
    /// Create a date formatter.
    NSDateFormatter *dateFormatter = [NSDateFormatter new];    
    [dateFormatter setDateFormat:@"yyyy-MM-dd_HH;mm;ss"];
    [dateFormatter setTimeZone:[NSTimeZone localTimeZone]];
   
    /// Create the desired identifier for the log file, using a formatted name with the date/time.
    NSDate *date = [NSDate date];

    NSString *dateTime = [dateFormatter stringFromDate:date];
    NSString *filename = [NSString stringWithFormat:@"voomair-dfu-log_%@.txt", dateTime];

    NSLog(@"%@", dateTime);
    
    /// Retrieve the Documents directory, save it as a string.
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
                                                         NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    /// Create the destination filepath string where the file will be written.
    NSString *documentsDirectoryFilePath =
        [documentsDirectory stringByAppendingPathComponent:filename];
   
    /// Write to the file - destination: Documents directory.
    [logQueueAsString writeToFile:documentsDirectoryFilePath
                       atomically:TRUE
                         encoding:NSUTF8StringEncoding
                            error:nil];
}

void deleteFirmwareFile(void) {
    NSMutableArray *fileList = [NSMutableArray new];

    NSArray *documentPaths = NSSearchPathForDirectoriesInDomains(
        NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirPath = [documentPaths objectAtIndex:0];

    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSArray *dirContents =
        [fileManager contentsOfDirectoryAtPath:documentsDirPath error:nil];

    NSPredicate *predicate = [NSPredicate
        predicateWithFormat:@"pathExtension IN %@",
                            [NSArray
                                arrayWithObjects:@"cyacd", @"cyacd2", nil]];
    NSArray *fileNameList =
        (NSMutableArray *)[dirContents filteredArrayUsingPredicate:predicate];

    for (NSString *fileName in fileNameList) {
        NSString *fullFilePath = [NSString stringWithFormat:@"%@/%@", documentsDirPath, fileName];
        NSLog(@"Deleting file at %@", fullFilePath);
        [fileManager removeItemAtPath:fullFilePath error: nil];
    }
}
