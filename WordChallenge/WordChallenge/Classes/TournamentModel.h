//
//  TournamentModel.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/31/12.
//
//

#ifndef WordChallenge_TournamentModel_h
#define WordChallenge_TournamentModel_h


#include "cocos2d.h"
#include <string>


#include "Player.h"

using namespace cocos2d;
using namespace std;



class PlayerInvolvement : public CCObject
{
protected:
    long long m_id;
    string m_name;
    long m_timestamp;
    
    long m_score;
    
    
public:
    
    PlayerInvolvement(long long id_, string name_)
    {
        m_id = id_;
        m_name = name_;
        m_score = -1;
        m_timestamp = -1;
    }
    
    void setScore(long score_, long timestamp_)
    {
        m_score = score_;
        m_timestamp = timestamp_;
    }
    
    
    bool hasPlayed()
    {
        return m_score > -1;
    }
    
};

class TournamentModel : public CCObject
{
protected:
    long long m_id;
    string m_name;
    
    CCArray* m_players;
    
    int m_iteraton;
    
    int m_buyIn;
    
    double m_deadline;
    
    void init()
    {
        m_players = new CCArray();
        
    }
    
public:
    
    
    TournamentModel(long long id_,string name_,int iteration_, int buyIn_, double deadline_)
    {
        m_id = id_;
        m_name = name_;
        m_iteraton = iteration_;
        m_buyIn = buyIn_;
        m_deadline = deadline_;
        this->init();
    }
    
    
    long long getId() { return m_id; }
    string getName() { return m_name;}
    int getIteration() {return m_iteraton;}
    CCArray* getPlayers() { return m_players;}
    int getBuyIn(){return m_buyIn;}
    double getDeadline() {return m_deadline;}
};


#endif
