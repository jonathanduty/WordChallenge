//
//  ScoreHeader.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/22/12.
//
//

#ifndef WordChallenge_ScoreHeader_h
#define WordChallenge_ScoreHeader_h

#include "cocos2d.h"
#include "UIConstants.h"
#include "BoardModel.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace cocos2d;

class ScoreHeader : public CCNode
{
protected:
    
    CCLabelTTF* m_scoreLabel;
    
    
public:
    
    ScoreHeader()
    {
        m_scoreLabel = CCLabelTTF::labelWithString("Score: 0", WC_DEFAULT_FONT, 14);
        m_scoreLabel->setColor(ccc3(0,0,0));
        this->addChild(m_scoreLabel);
        this->setPosition(ccp(160,470));
        
        CCNotificationCenter::sharedNotifCenter()->addObserver(this,callfuncO_selector(ScoreHeader::letterPlaced),WC_EVENT_LETTER_PLACED,NULL);

    }
    
    ~ScoreHeader()
    {
        CCNotificationCenter::sharedNotifCenter()->removeObserver(this,WC_EVENT_LETTER_PLACED);

    }
    
    void letterPlaced(CCObject* obj)
    {
        this->refreshScore();
    }
    
    void refreshScore()
    {
        int score = BoardModel::instance()->getScore();
        std::ostringstream oss;
        oss << "Score: " << score;
        
        m_scoreLabel->setString( oss.str().c_str());
    }
    
    
};


#endif
