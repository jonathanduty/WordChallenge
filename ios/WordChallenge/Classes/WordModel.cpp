//
//  BoardModel.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 8/21/12.
//
//

#include "WordModel.h"
#include "BoardModel.h"

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
    m_cells->addObject(cell_);
    cell_->addToWord(this);
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

bool WordModel::isCorrect()
{
    // todo fix.
    if ( isFull() )
    {
        return true;
    }
    return false;
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

