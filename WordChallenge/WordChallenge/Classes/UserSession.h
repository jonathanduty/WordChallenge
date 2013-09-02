//
//  User.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/29/13.
//
//

#ifndef __WordChallenge__UserSession__
#define __WordChallenge__UserSession__

#include <iostream>
#include "cocos2d.h"
#include <string>
#include "json/json.h"
using namespace cocos2d;
using namespace std;

class UserSession : public CCObject
{
protected:
        
    bool m_validSession = false;

    
    void loadFromDefaults()
    {
    
    }
    
public:
    
    static UserSession* sharedInstance();
    
    
    bool hasValidSession()
    {
        return m_validSession;
    }
    
    
    string m_userName;
    string m_email;
    bool m_fbConnected;
    bool m_fbId;
    string m_fbtoken;
    
    string m_kumacoreSession;
    string m_kumacoreId;
    
    
    
    
    void save()
    {
       
        
        
    }
    
    
    static void Load()
    {
        
        
    }
};
#endif /* defined(__WordChallenge__UserSession__) */
