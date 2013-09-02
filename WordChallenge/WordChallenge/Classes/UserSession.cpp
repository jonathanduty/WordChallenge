//
//  UserSession.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 8/30/13.
//
//

#include <UserSession.h>


static UserSession* s_userSession;


UserSession* UserSession::sharedInstance()
{
    if( s_userSession == NULL)
    {
        s_userSession = new UserSession();
        
    }
    return s_userSession;
    
}