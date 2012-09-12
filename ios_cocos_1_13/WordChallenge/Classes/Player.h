//
//  Player.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/29/12.
//
//

#ifndef WordChallenge_Player_h
#define WordChallenge_Player_h


#include "cocos2d.h"
#include <string>

using namespace std;
using namespace cocos2d;


class Player;

static Player* g_player;


class Player : public CCObject
{
protected:
    string m_fbId;
    string m_name;
    bool m_facebookConnected;
    bool m_initialized;
    
    Player()
    {
        m_facebookConnected = false;
        m_initialized = false;
    }
    
    void setFBData(string fb_id, string name)
    {
        m_facebookConnected = true;
        m_fbId = fb_id;
        m_name = name;
    }
    
    
    
    
public:
    
    static Player* currentPlayer()
    {
        if (g_player == NULL )
        {
            g_player = new Player();
        }
        return g_player;
    }
    
    static void initCurrentPlayerWithFacebook(string fb_id, string name)
    {
        currentPlayer()->setFBData(fb_id,name);
    }
    
};

#endif
