//
//  BoardModel.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 8/21/12.
//
//

#include "WordModel.h"
#include "BoardModel.h"
#include "ProtoDatabase.h"
#include <string>
#include <sstream>
#include <iostream>

WordModel::WordModel(Json::Value protoData_)
{
    m_protoData = protoData_;
    m_cells = new CCMutableArray<CellModel*>();
    
}



WordModel::~WordModel()
{
    m_cells->release();
}


void WordModel::cellChanged(CellModel* cell_)
{
    
}

void WordModel::addCell(CellModel* cell_)
{
    cell_->addToWord(this);

    
    CellModel* current = NULL;
    for ( int i=0;i<m_cells->count();i++ )
    {
        current = m_cells->getObjectAtIndex(i);
        if( cell_->getX() < current->getX() || cell_->getY() > current->getY())
        {
            m_cells->insertObjectAtIndex(cell_, i);
            return;
        }
        
    }
    m_cells->addObject(cell_);
}

bool WordModel::isFull()
{
    for (int i=0;i<m_cells->count();i++)
    {
        if ( !m_cells->getObjectAtIndex(i)->containsLetter()  )
        {
            return false;
        }
    }
    return true;
}


int WordModel::getPoints()
{
    int score = 0;
    for (int i=0;i<m_cells->count();i++)
    {
        CellModel* cell = m_cells->getObjectAtIndex(i);
        if ( !cell->containsLetter()  )
        {
            return 0;
        }
        int letterProto = cell->getLetterProtoId();
        Json::Value letter = ProtoDatabase::shardInstance()->getLetterProtoDataById(letterProto);
        score +=letter["points"].asInt();
        
    }
    return score;
}

std::string WordModel::getWord()
{
    
    std::ostringstream oss;
    
    for (int i=0;i<m_cells->count();i++)
    {
        CellModel* cell = m_cells->getObjectAtIndex(i);
        if ( !cell->containsLetter()  )
        {
            oss << " ";

        }
        oss << cell->getLetter()["label"].asString();
    }
    
    return oss.str().c_str();
        
}

bool WordModel::isCorrect()
{
    return WordDictionary::instance()->wordCorrect( getWord());
    
}

WordModelState WordModel::getState()
{
    if (!isFull())
    {
        return WC_WORD_STATE_INCOMPLETE;
    }
    else
    {
        if ( isCorrect())
        {
            return WC_WORD_STATE_CORRECT_WORD;
        }
        else
        {
            return WC_WORD_STATE_INCORRECT_WORD;
        }
    }
}

CellModel* WordModel::getNextCell(CellModel* cell_)
{
    for ( int i=0;i<m_cells->count();i++ )
    {
        CellModel* current = m_cells->getObjectAtIndex(i);
        if( current->getX() ==  cell_->getX() && current->getY() == cell_->getY() && i < m_cells->count() -1)
        {
            CellModel* next = m_cells->getObjectAtIndex(i+1);
            if( next->isGiven())
            {
                return getNextCell(next);
            }
            else
            {
                return next;
            }
        }

    }
    return NULL;
}

