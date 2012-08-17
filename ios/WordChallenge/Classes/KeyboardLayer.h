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
#include "UIConstants.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace cocos2d;

#define WC_KEYBOARD_ROW_SIZE 9

#define WC_KEYBOARD_BUTTON_WIDTH 32
#define WC_KEYBOARD_BUTTON_MARGIN 5

class KeyboardButton : public CCSprite
{
protected:
    Json::Value m_letter;
    
public:
    static std::string stringForNum(int num_)
    {
        std::ostringstream oss;
        oss << num_;
        return oss.str();
    }

    
    KeyboardButton(Json::Value letter_)
    {
        m_letter = letter_;
        this->initWithFile("keyboard_button.png");
        
        
        
        CCLabelTTF* label =  CCLabelTTF::labelWithString(m_letter["label"].asString().c_str(),WC_DEFAULT_FONT_BOLD,20);
        label->setPosition(ccp(WC_KEYBOARD_BUTTON_WIDTH*.5,WC_KEYBOARD_BUTTON_WIDTH*.5));
        this->addChild(label);
        
        
        CCLabelTTF* points =  CCLabelTTF::labelWithString(stringForNum(m_letter["points"].asInt()).c_str(),WC_DEFAULT_FONT,10);
        points->setPosition(ccp(WC_KEYBOARD_BUTTON_WIDTH*.8,WC_KEYBOARD_BUTTON_WIDTH*.2));
        this->addChild(points);

        
    }
    
    ~KeyboardButton()
    {
    
    }
    
};


class KeyboardLayer : public CCSprite
{
protected:
    
    
    
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
                                    140-(row * WC_KEYBOARD_BUTTON_WIDTH)));
            this->addChild(button);
            
        }
    }
    
public:
    
    KeyboardLayer()
    {
        this->initWithFile("keyboard_background.png");
        this->setPosition(ccp(160,70));
        
        this->buildKeyboard();
    }
    
    
    ~KeyboardLayer()
    {
    }
    
};


#endif
