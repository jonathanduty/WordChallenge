//
//  UIConstants.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/17/12.
//
//

#ifndef WordChallenge_UIConstants_h
#define WordChallenge_UIConstants_h


#include "cocos2d.h"

using namespace cocos2d;

#define WC_DEFAULT_FONT_BOLD "HelveticaBold"
#define WC_DEFAULT_FONT "Helvetica"

#define WC_EVENT_KEYBOARD_PRESSED "WC_EVENT_KEYBOARD_PRESSED"

#define WC_EVENT_LETTER_PLACED "WC_EVENT_LETTER_PLACED"

#define WC_EVENT_LOGIN_COMPLETE "WC_EVENT_LOGIN_COMPLETE"

class ButtonPushedEvent : public CCObject
{
protected:
    int m_letterId;
    
public:
    ButtonPushedEvent(int letterId_)
    {
        m_letterId = letterId_;
    }
    
    static ButtonPushedEvent* eventWithLetterId(int letterId_)
    {
        ButtonPushedEvent* event = new ButtonPushedEvent(letterId_);
        event->autorelease();
        return event;
    }

    int getLetterId() { return m_letterId;}
    
};




#endif
