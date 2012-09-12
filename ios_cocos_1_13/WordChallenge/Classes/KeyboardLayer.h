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


class KeyboardLayer;

class KeyboardButton : public CCNode
{
protected:
    Json::Value m_letter;
    CCMenu* m_menu;
    int m_letterId;
    
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
        m_letterId = m_letter["id"].asInt();
        
        CCSprite* background = CCSprite::spriteWithFile("keyboard_button.png");
        CCSprite* selectedBackground = CCSprite::spriteWithFile("keyboard_button.png");
        selectedBackground->setScale(1.5);
        
        
        CCLabelTTF* label =  CCLabelTTF::labelWithString(m_letter["label"].asString().c_str(),WC_DEFAULT_FONT_BOLD,20);
        label->setPosition(ccp(WC_KEYBOARD_BUTTON_WIDTH*.5,WC_KEYBOARD_BUTTON_WIDTH*.5));
        background->addChild(label);
        
        
        CCLabelTTF* points =  CCLabelTTF::labelWithString(stringForNum(m_letter["points"].asInt()).c_str(),WC_DEFAULT_FONT,10);
        points->setPosition(ccp(WC_KEYBOARD_BUTTON_WIDTH*.8,WC_KEYBOARD_BUTTON_WIDTH*.2));
        background->addChild(points);
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::itemFromNormalSprite(background,
                                                                          selectedBackground,
                                                                          NULL, this,
                                                                          menu_selector(KeyboardButton::keyPressed));
        
        
        m_menu = CCMenu::menuWithItems(sprite, NULL);
        m_menu->retain();
        this->addChild(m_menu, 1);
        
    }
    
    
    virtual void setPosition(CCPoint point_)
    {
        
        m_menu->setPosition(point_);
    }
    
    virtual void keyPressed()
    {
        CCNotificationCenter::sharedNotifCenter()->postNotification(WC_EVENT_KEYBOARD_PRESSED,
                                                                    ButtonPushedEvent::eventWithLetterId(m_letterId));
    }
    
    ~KeyboardButton()
    {
        m_menu->release();
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
            button->release();
        }
    }
    
public:
    
    KeyboardLayer()
    {
        this->initWithFile("keyboard_background.png");
        this->setPosition(ccp(160,60));
        
        this->buildKeyboard();
    }
    
    
    ~KeyboardLayer()
    {
    }
    
};


#endif
