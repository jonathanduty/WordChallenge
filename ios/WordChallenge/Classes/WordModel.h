//
//  WordModel.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/21/12.
//
//

#ifndef WordChallenge_WordModel_h
#define WordChallenge_WordModel_h

#include "cocos2d.h"
#include "Json.h"
#include <string>


using namespace cocos2d;

enum {
    WC_WORD_STATE_INCOMPLETE,
    WC_WORD_STATE_INCORRECT_WORD,
    WC_WORD_STATE_CORRECT_WORD
} typedef WordModelState;

class CellModel;
class BoardModel;


class WordModel : public CCObject
{
protected:
    Json::Value m_protoData;
    
    CCMutableArray<CellModel*>* m_cells;
    
public:
    WordModel(Json::Value protoData_);
    
    ~WordModel();
    
    
    void cellChanged(CellModel* cell_);
    
    void addCell(CellModel* cell_);
    
    bool isFull();
    
    bool isCorrect();
    
    WordModelState getState();
    
    CCMutableArray<CellModel*>* getCells() {return m_cells;}
    
    
    int getPoints();
    
    std::string getWord();
    
};



#endif
