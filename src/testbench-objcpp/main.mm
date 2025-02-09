/*!
    \file       main.mm
    \brief      Client source file

    \author     
    \date
 */

#import "header.h"

#include <string>
#import <Foundation/Foundation.h>

auto findCYACD2DFUFilesFromDocuments() -> NSArray<NSURL *> * {
    NSLog(@"Now searching the Documents directory for CYACD2 files.");
    
    /// Get the path to the Documents directory
    auto documentsDirectory = [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory inDomains:NSUserDomainMask] firstObject];
     
    NSError *error = nil;
    auto directoryContents = [[NSFileManager defaultManager] contentsOfDirectoryAtURL:documentsDirectory
                                                             includingPropertiesForKeys:nil
                                                                                options:NSDirectoryEnumerationSkipsHiddenFiles
                                                                                  error:&error];
    if (error) {
        NSLog(@"Unable to retrieve filepaths from Documents directory. Now returning. Error: %@",
             error.localizedDescription);
        return @[];
    }
     
    /// Filter files with the .cyacd2 extension
    auto predicate = [NSPredicate predicateWithFormat:@"pathExtension == 'txt'"];
    NSArray<NSURL *> *cyacd2Files = [directoryContents filteredArrayUsingPredicate:predicate];
     
     /// Map to file paths as strings
     auto filepaths = [NSMutableArray array];
     for (NSURL *fileURL in cyacd2Files) {
         NSLog(@"Found %@ - success.", [fileURL lastPathComponent]);
         [filepaths addObject:fileURL.path];
     }
    
    if (filepaths.count == 0) {
        NSLog(@"No files for DFU found in %@. Now returning.",
             documentsDirectory.absoluteString);
        return nil;
    }
     
     return [filepaths copy];
}

int main(int argc, const char *argv[]) {

/*
    auto documentsDirectoryPath = [NSSearchPathForDirectoriesInDomains(
        NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];

    NSArray<NSString *> *directoryContents = [[NSFileManager defaultManager]
        contentsOfDirectoryAtPath:documentsDirectoryPath
                            error:nil];

    /// Filter on a predicate: find files with the extension .cyacd2 (DFU files)
    auto predicate = [NSPredicate
        predicateWithFormat:@"pathExtension IN %@", @[ @"txt" ]];

    /// Get all of the filepaths in the Documents directory that have a .cyacd2
    /// file extension.
    NSArray<NSString *> *filenameList =
        [directoryContents filteredArrayUsingPredicate:predicate];

    if (filenameList.count == 0) {
        return 0;
    }

    /// Our expectation/precondition is that there should only be one `.cyacd2`
    /// file in the Documents directory
    /// (`.cyacd2` files are deleted after every DFU), so we'll take the first
    /// element in this list.
    auto filename = [filenameList objectAtIndex:0];
    auto fullpath =
        [NSString stringWithFormat:@"%@/%@", documentsDirectoryPath, filename];

    auto fileSizeInBytes = [[NSFileManager defaultManager] attributesOfItemAtPath:fullpath error:nil].fileSize;
    NSLog(@"size of %@: %llu\n", filename, fileSizeInBytes);
    */

    auto urls = findCYACD2DFUFilesFromDocuments();
    for (NSURL *url in urls) {
        NSLog(@"%@", [url lastPathComponent]);
    }

    return 0;
}
