//
//  PlatformHelper_ios.mm
//  WordChallenge
//
//  Created by Jonathan Duty on 8/24/12.
//
//

#include "PlatformHelper.h"

#include "cocos2d.h"



 std::string getFullPath(std::string file)
{
     NSString*  fileObjc = [NSString stringWithCString:file.c_str() encoding:NSUTF8StringEncoding];
    
    NSString* pathAndFileName = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileObjc];
    if ( [[NSFileManager defaultManager] fileExistsAtPath:pathAndFileName] )
    {
        cocos2d::CCLog("FIle exists!");
        
    }
    
    
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"letters" ofType:@"json"];
    NSString *fileContent = [[NSString alloc] initWithContentsOfFile:filePath];  
    cocos2d::CCLog([fileContent cStringUsingEncoding:NSUTF8StringEncoding]);
    return [[[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fileObjc] fileSystemRepresentation];
}


std::string getJsonFileContents(std::string fileName)
{
    NSString*  fileObjc = [NSString stringWithCString:fileName.c_str() encoding:NSUTF8StringEncoding];
    NSString *filePath = [[NSBundle mainBundle] pathForResource:fileObjc ofType:@"json"];
    NSString *fileContent = [[NSString alloc] initWithContentsOfFile:filePath];
    return [fileContent cStringUsingEncoding:NSUTF8StringEncoding];
}