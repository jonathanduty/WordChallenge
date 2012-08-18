//
//  BoardModel.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef WordChallenge_BoardModel_h
#define WordChallenge_BoardModel_h

#include "cocos2d.h"
#include "json.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace cocos2d;



#define WC_NO_LETTER -1

class CellModel : public CCObject
{
protected:
    int m_x;
    int m_y;
    std::string m_key;
    int m_letterProtoId;
    bool m_given;
    
public:
    CellModel(int x, int y)
    {
        m_x = x;
        m_y = y;
        m_key = keyForCoords(x,y);
        m_given = false;
        m_letterProtoId = WC_NO_LETTER;
    }
    
    
    void setLetterProtoId(int protoId_) {m_letterProtoId=protoId_;}
    int getLetterProtoId() {return m_letterProtoId;}
    void setGiven(bool given_) {m_given = given_;}
    bool getGiven() {return m_given;}
    
    int getX() {return m_x;}
    int getY() {return m_y;}
    std::string getKey() { return m_key;}
    
    
    
    static std::string keyForCoords(int x_, int y_)
    {
        std::ostringstream oss;
        oss << x_ << "_" << y_;
        return oss.str(); 
    }

};



class BoardModel;

static BoardModel* s_globalModel;


class BoardModel : public CCObject
{
protected:
    Json::Value m_protoData;
    
    CCMutableDictionary<std::string,CellModel*>* m_cells;
    
    int m_width;
    int m_height;
    
    BoardModel(Json::Value protoData)
    {
        m_protoData = protoData;
        
        m_cells = new CCMutableDictionary<std::string,CellModel*>();
        
        
        m_width = m_protoData["width"].asInt();
        m_height = m_protoData["height"].asInt();
        
        Json::Value words = m_protoData["words"];
        for ( int i=0;i < words.size();i++)
        {
            Json::Value word = words[i];
            CellModel* cell = NULL;

            if ( word["orientation"].asString() == "horizontal" )
            {
                for ( int x=word["begin_x"].asInt(); x< word["begin_x"].asInt() + word["length"].asInt();x++)
                {
                    cell = new CellModel(x,word["begin_y"].asInt());
                    m_cells->setObject(cell,cell->getKey());
                    cell->release();
                }
            }
            else
            {
                for ( int y=word["begin_y"].asInt(); y< word["begin_y"].asInt() + word["length"].asInt();y++)
                {
                    cell = new CellModel(word["begin_x"].asInt(),y);
                    m_cells->setObject(cell,cell->getKey());
                    cell->release();
                }
            }
            
            
        }
        
        
        Json::Value letters = m_protoData["letters"];
        for ( int i=0;i < letters.size();i++)
        {
            Json::Value letter = letters[i];
            CellModel* cell = this->getCellModel(letter["x"].asInt(), letter["y"].asInt());
            if ( cell != NULL) 
            {
                cell->setLetterProtoId(letter["proto_id"].asInt());
                cell->setGiven(letter["given"].asBool());
            }
        }
        
        
    }
    
    
public:
    
    
    static void loadNewModel(Json::Value protoData)
    {
        if ( s_globalModel != NULL) {
            s_globalModel->release();
        }
        
        s_globalModel = new BoardModel(protoData);
        
    }
    
    static BoardModel* instance()
    {
        return s_globalModel;
    }
    
    
    ~BoardModel()
    {
        m_cells->release();
    }
    
    
    CellModel* getCellModel(int x,int y)
    {
        return m_cells->objectForKey(CellModel::keyForCoords(x,y));
    }
    
    
    int getWidth() {return m_width;}
    int getHeight(){return m_height;}
    
};


#endif