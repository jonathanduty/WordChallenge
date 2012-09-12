//
//  PlatformHelper_ios.mm
//  WordChallenge
//
//  Created by Jonathan Duty on 8/24/12.
//
//

#include "PlatformHelper.h"

#include "cocos2d.h"
#include "UIConstants.h"
#include "SceneController.h"
#include "Player.h"
#import <FacebookSDK/FacebookSDK.h>


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

void facebookMe()
{
    [FBRequestConnection startForMeWithCompletionHandler:^(FBRequestConnection *connection,
                                                           id<FBGraphUser> user,
                                                           NSError *error) {
        Player::initCurrentPlayerWithFacebook(
                    [user.id cStringUsingEncoding:NSUTF8StringEncoding],
                    [user.name cStringUsingEncoding:NSUTF8StringEncoding]);
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(WC_EVENT_LOGIN_COMPLETE);
    }];
}


void facebookLogin()
{
    [FBSession openActiveSessionWithPermissions:nil allowLoginUI:YES
                              completionHandler:^(FBSession *session,
                                                  FBSessionState status,
                                                  NSError *error) {
                                  facebookMe();
                              }];
}
