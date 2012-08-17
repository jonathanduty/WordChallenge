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

#define WC_KEYBOARD_ROW_SIZE 9

#define WC_KEYBOARD_BUTTON_WIDTH 32
#define WC_KEYBOARD_BUTTON_MARGIN 5

class KeyboardButton : public CCSprite
{
protected:
    Json::Value m_letter;
    
public:
    
    KeyboardButton(Json::Value letter_)
    {
        m_letter = letter_;
        this->initWithFile("keyboard_button.png");
    }
    
    
    
};


class KeyboardLayer : public CCLayer
{
protected:
    
    CCSprite* m_keyboardBackground;
    
    
    void buildKeyboard()
    {
        ProtoDatabase* proto = ProtoDatabase::shardInstance();
        
        int row=0;
        int col=0;
        
        for (int i=0;i < proto->getLettersProtoDataSize();i++)
        {
            col = i % WC_KEYBOARD_ROW_SIZE;
            row = (int) (i / WC_KEYBOARD_ROW_SIZE);
            
            Json::Value letter = proto->getLetterProtoDataById(i);
            KeyboardButton* button = new KeyboardButton(letter);
            button->setPosition(ccp(WC_KEYBOARD_BUTTON_WIDTH/2 +  col * WC_KEYBOARD_BUTTON_WIDTH ,
                                    130-(row * WC_KEYBOARD_BUTTON_WIDTH)));
            this->addChild(button);
            
            //)
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
        
        this->buildKeyboard();
    }
    
    
    ~KeyboardLayer()
    {
        m_keyboardBackground->release();
    }
    
};


#endif
