//
//  BoardConfig.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef WordChallenge_BoardConfig_h
#define WordChallenge_BoardConfig_h

#include "cocos2d.h"
#include "json.h"

using namespace cocos2d;

class BoardConfig : public CCObject 
{
protected:
    Json::Value m_protoData;
    
    int m_width;
    int m_height;

    
    protected void setup()
    {
        m_width = m_protoData["width"].asInt();
        m_height = m_protoData["height"].asInt();
    }
    
public:
    BoardConfig(Json::Value protoData)
    {
        m_protoData = protoData;
        
    }
    
    int getWidth() { return m_width;}
    int getHeight() {return m_height;}
    
};


#endif
