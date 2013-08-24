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
    m_cells = new CCArray();
    
}



WordModel::~WordModel()
{
    m_cells->release();
}


void WordModel::cellChanged(CellModel* cell_)
{
    m_correct = WordDictionary::instance()->wordCorrect( getWord());
}

void WordModel::addCell(CellModel* cell_)
{
    cell_->addToWord(this);

    
    CellModel* current = NULL;
    for ( int i=0;i<m_cells->count();i++ )
    {
        current = (CellModel*)m_cells->objectAtIndex(i);
        if( cell_->getX() < current->getX() || cell_->getY() > current->getY())
        {
            m_cells->insertObject(cell_, i);
            return;
        }
        
    }
    m_cells->addObject(cell_);
}

bool WordModel::isFull()
{
    for (int i=0;i<m_cells->count();i++)
    {
        if ( !((CellModel*)m_cells->objectAtIndex(i))->containsLetter()  )
        {
            return false;
        }
    }
    return true;
}


int WordModel::getPoints()
{
    
    if ( !isCorrect())
    {
        return 0;
    }
    
    int score = 0;
    for (int i=0;i<m_cells->count();i++)
    {
        CellModel* cell = (CellModel*)m_cells->objectAtIndex(i);
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
        CellModel* cell = (CellModel*)m_cells->objectAtIndex(i);
        if ( !cell->containsLetter()  )
        {
            oss << " ";

        }
        oss << cell->getLetter()["label"].asString();
    }
    
    return oss.str().c_str();
        
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
        CellModel* current = (CellModel*)m_cells->objectAtIndex(i);
        if( current->getX() ==  cell_->getX() && current->getY() == cell_->getY() && i < m_cells->count() -1)
        {
            CellModel* next = (CellModel*)m_cells->objectAtIndex(i+1);
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

