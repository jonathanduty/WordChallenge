//
//  TournamentManager.h
//  WordChallenge
//
//  Created by Jonathan Duty on 9/1/12.
//
//

#ifndef WordChallenge_TournamentManager_h
#define WordChallenge_TournamentManager_h

#include "cocos2d.h"
#include "TournamentModel.h"

using namespace cocos2d;

class TournamentManager;

TournamentManager* g_tournamentManager = NULL;

class TournamentManager : public CCObject {
  
    // mocking this out for now.
    CCMutableArray<TournamentModel*>* m_tournaments;
    
    
    
    TournamentManager()
    {
        m_tournaments = new CCMutableArray<TournamentModel*>();
    }
    
public:
    
    static TournamentManager* instance()
    {
        if (g_tournamentManager == NULL)
        {
            g_tournamentManager = new TournamentManager();
        }
        return g_tournamentManager;
    }
    
    
    
    CCMutableArray<TournamentModel*>* getOpenTournaments()
    {
        return m_tournaments;
    }
    
    
    
    
};

#endif
