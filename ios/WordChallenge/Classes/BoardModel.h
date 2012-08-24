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
#include "ProtoDatabase.h"
#include "WordModel.h"
#include "json.h"
#include <string>
#include <sstream>
#include <iostream>
#include "WordDictionary.h"
using namespace cocos2d;






#define WC_NO_LETTER -1

class CellModel : public CCObject
{
friend BoardModel;
    
    
protected:
    int m_x;
    int m_y;
    std::string m_key;
    int m_letterProtoId;
    Json::Value m_letter;
    
    
    bool m_given;
    
    CCMutableArray<WordModel*>* m_words;
    
    void notifyWords()
    {
        for (int i=0;i<m_words->count();i++)
        {
            m_words->getObjectAtIndex(i)->cellChanged(this);
        }
    }
    
    
    void setLetterProtoId(int protoId_)
    {
        if ( protoId_ == WC_NO_LETTER)
        {
            m_letterProtoId=protoId_;

            m_letter = NULL;
        }
        m_letterProtoId=protoId_;
        m_letter = ProtoDatabase::shardInstance()->getLetterProtoDataById(protoId_);
        
        
    }
    
    
public:
    CellModel(int x, int y)
    {
        m_x = x;
        m_y = y;
        m_key = keyForCoords(x,y);
        m_given = false;
        m_letterProtoId = WC_NO_LETTER;
        
        m_words = new CCMutableArray<WordModel*>();
    }
    
    ~CellModel()
    {
        m_words->release();
    }
    
    
    int getLetterProtoId() {return m_letterProtoId;}
    Json::Value getLetter() { return m_letter;}
    
    void setGiven(bool given_) {m_given = given_;}
    bool isGiven() {return m_given;}
    
    int getX() {return m_x;}
    int getY() {return m_y;}
    std::string getKey() { return m_key;}
    
    CCMutableArray<WordModel*>* getWords() { return m_words;}
    
    bool containsLetter()
    {
        return m_letterProtoId != WC_NO_LETTER;
    }
    
    static std::string keyForCoords(int x_, int y_)
    {
        std::ostringstream oss;
        oss << x_ << "_" << y_;
        return oss.str(); 
    }
    
    void addToWord(WordModel* word_)
    {
        m_words->addObject(word_);
    }

    
    WordModelState getWordState()
    {
        bool incompleteFound = false;
        for (int i=0;i<m_words->count();i++)
        {
            WordModelState state = m_words->getObjectAtIndex(i)->getState();
            if ( state == WC_WORD_STATE_INCORRECT_WORD)
            {
                return WC_WORD_STATE_INCORRECT_WORD;
            }
            else if ( state == WC_WORD_STATE_INCOMPLETE)
            {
                incompleteFound = true;
            }
        }
        
        if (incompleteFound )
        {
            return WC_WORD_STATE_INCOMPLETE;
        }
        return WC_WORD_STATE_CORRECT_WORD;
    }
    
};


class BoardModel;

static BoardModel* s_globalModel;


class BoardModel : public CCObject
{
protected:
    Json::Value m_protoData;
    
    CCMutableDictionary<std::string,CellModel*>* m_cells;
    CCMutableArray<WordModel*>* m_words;
    
    int m_width;
    int m_height;
    
    int m_score;
    
    BoardModel(Json::Value protoData)
    {
        m_protoData = protoData;
        
        m_score = 0;
        
        m_cells = new CCMutableDictionary<std::string,CellModel*>();
        m_words = new CCMutableArray<WordModel*>();
        
        m_width = m_protoData["width"].asInt();
        m_height = m_protoData["height"].asInt();
        
        Json::Value words = m_protoData["words"];
        for ( int i=0;i < words.size();i++)
        {
            Json::Value word = words[i];
            WordModel* wordModel = new WordModel(word);
            m_words->addObject(wordModel);
            CellModel* cell = NULL;

            if ( word["orientation"].asString() == "horizontal" )
            {
                for ( int x=word["begin_x"].asInt(); x< word["begin_x"].asInt() + word["length"].asInt();x++)
                {
                    cell = getCellModel(x,word["begin_y"].asInt());
                    if ( cell == NULL)
                    {
                        cell = new CellModel(x,word["begin_y"].asInt());
                    }
                    m_cells->setObject(cell,cell->getKey());
                    wordModel->addCell(cell);
                    cell->release();
                }
            }
            else
            {
                for ( int y=word["begin_y"].asInt(); y< word["begin_y"].asInt() + word["length"].asInt();y++)
                {
                    cell = getCellModel(word["begin_x"].asInt(), y);
                    if ( cell == NULL)
                    {
                        cell = new CellModel(word["begin_x"].asInt(),y);
                    }
                    m_cells->setObject(cell,cell->getKey());
                    wordModel->addCell(cell);
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
        
        this->refreshScore();
    }
    
    void refreshScore()
    {
        int score = 0;
        for (int i = 0;i<m_words->count();i++)
        {
            WordModel* word = m_words->getObjectAtIndex(i);
            score+= word->getPoints();
        }
        m_score = score;
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
        m_words->release();
    }
    
    
    CellModel* getCellModel(int x,int y)
    {
        return m_cells->objectForKey(CellModel::keyForCoords(x,y));
    }
    
    
    void placeLetterInCell(int x, int y, int letterId_)
    {
        CellModel* cell = this->getCellModel(x, y);
        if (cell != NULL)
        {
            cell->setLetterProtoId(letterId_);
        }
        
        this->refreshScore();
    }
    
    int getWidth() {return m_width;}
    int getHeight(){return m_height;}
    
    int getScore() {return m_score;}
        
};


#endif
