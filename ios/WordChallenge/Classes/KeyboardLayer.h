//
//  Header.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef WordChallenge_KeyboardLayer_h
#define WordChallenge_KeyboardLayer_h

#include "cocos2d.h"
#include "ProtoDatabase.h"
#include "json.h"

using namespace cocos2d;

class KeyboardLayer : public CCLayer
{
protected:
    
    CCSprite* m_keyboardBackground;
    
    
    void buildKeyboard()
    {
        ProtoDatabase* proto = ProtoDatabase::sharedInstance();
        
        for (int i=0;proto->getLettersProtoDataSize();i++)
        {
            Json::Value letter = proto->getLettersProtoDataById(i);
            
        }
    }
    
public:
    
    KeyboardLayer()
    {
        init();
        
        m_keyboardBackground = CCSprite::spriteWithFile("keyboard_background.png");
        m_keyboardBackground->retain();
        m_keyboardBackground->setPosition(ccp(160,70));
        this->addChild(m_keyboardBackground);
        
        
    }
    
    
    ~KeyboardLayer()
    {
        m_keyboardBackground->release();
    }
    
};


#endif
