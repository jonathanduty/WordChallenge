//
//  BoardLayer.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef WordChallenge_BoardLayer_h
#define WordChallenge_BoardLayer_h

#include "cocos2d.h"
#include <string>
#include <sstream>
#include <iostream>
#include "BoardModel.h"
//#include "CCLayerPanZoom.h"
#include "ProtoDatabase.h"
#include "UIConstants.h"

using namespace cocos2d;


#define WC_NOTIFICATION_REFRESH_FROM_MODEL "WC_NOTIFICATION_REFRESH_FROM_MODEL"

#define WC_CELL_WIDTH 57


#define WC_CELL_BACKGROUND_PRIORITY 0
#define WC_CELL_WORD_STATE_PRIORITY 5
#define WC_CELL_SELECTED_PRIORITY 10
#define WC_CELL_LETTER_BACKGROUND_PRIORITY 20
#define WC_CELL_LABEL_PRIORITY 30
#define WC_CELL_POINTS_PRIORITY 40

class BoardLayerCell : public CCNode
{
protected:
    int m_x;
    int m_y;
    
    CCSprite* m_background;
    CCSprite* m_letter;
    CCSprite* m_stateSprite;
    
    CCSprite* m_selectedBackground;

    std::string m_key;
    
    bool m_selected;
    bool m_open;
    bool m_given;
    
    
    
    void drawLetterInCell(int letterId_)
    {
        
        if ( m_letter != NULL)
        {
            m_letter->removeFromParentAndCleanup(true);
        }
        
        if ( letterId_ == WC_NO_LETTER)
        {
            return;
        }
        
        Json::Value letter = ProtoDatabase::shardInstance()->getLetterProtoDataById(letterId_);
        
        
        
        m_letter = CCSprite::spriteWithFile("letter_background.png");
        m_letter->retain();
        
        
        CCLabelTTF* label =  CCLabelTTF::labelWithString(letter["label"].asString().c_str(),WC_DEFAULT_FONT_BOLD,40);
        
        if ( m_given)
        {
            label->setColor(ccc3(0 ,255,2));
        }
        
        label->setPosition(ccp(WC_CELL_WIDTH*.5,WC_CELL_WIDTH*.5));
        m_letter->addChild(label, WC_CELL_LABEL_PRIORITY);
        
        
        
        CCLabelTTF* points =  CCLabelTTF::labelWithString(stringForNum(letter["points"].asInt()).c_str(),WC_DEFAULT_FONT,20);
        points->setPosition(ccp(WC_CELL_WIDTH*.8,WC_CELL_WIDTH*.2));
        m_letter->addChild(points, WC_CELL_POINTS_PRIORITY);
        this->addChild(m_letter, WC_CELL_LETTER_BACKGROUND_PRIORITY);
    }

    
public:
    
    static std::string keyForCoords(int x_, int y_)
    {
        std::ostringstream oss;
        oss << x_ << "_" << y_;
        return oss.str(); 
    }
    
    static std::string stringForNum(int num_)
    {
        std::ostringstream oss;
        oss << num_;
        return oss.str();
    }
    
    BoardLayerCell( int x_, int y_) : m_background(NULL), m_letter(NULL), m_given(false), m_stateSprite(NULL)
    {
        m_selected = false;
        m_x = x_;
        m_y = y_;
        m_key = keyForCoords(m_x,m_y);
        m_open = false;
        
        this->setContentSize(CCSizeMake(WC_CELL_WIDTH,WC_CELL_WIDTH));
        
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BoardLayerCell::refreshFromModelNotification),WC_NOTIFICATION_REFRESH_FROM_MODEL,NULL);

        
    }
    
    ~BoardLayerCell()
    {
        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, WC_NOTIFICATION_REFRESH_FROM_MODEL);
    }
    
    
    bool isGiven() { return m_given;}
    
        
    void refreshFromModel()
    {
        
        if ( m_stateSprite != NULL)
        {
            m_stateSprite->removeFromParentAndCleanup(true);
            m_stateSprite = NULL;
        }
        
        CellModel* cellModel = BoardModel::instance()->getCellModel(m_x, m_y);
        if ( cellModel != NULL)
        {
            m_open = true;
            m_background = CCSprite::spriteWithFile("open_tile.png");
            this->addChild(m_background,WC_CELL_BACKGROUND_PRIORITY);
            
            int proto_id = cellModel->getLetterProtoId();
            
            m_given = cellModel->isGiven();

            
            this->drawLetterInCell(proto_id);
            
            WordModelState wordState = cellModel->getWordState();
            this->displayBoardState(wordState);
        }
        else 
        {
            m_open = false;
            m_background = CCSprite::spriteWithFile("closed_tile.png");
            this->addChild(m_background);
        }
    }
    
    void displayBoardState(WordModelState state_)
    {
        
        if ( m_stateSprite != NULL)
        {
            m_stateSprite->removeFromParentAndCleanup(true);
            m_stateSprite = NULL;
        }
        
        if ( state_ == WC_WORD_STATE_CORRECT_WORD )
        {
            m_stateSprite = CCSprite::spriteWithFile("word_made_tile.png");
            this->addChild(m_stateSprite,WC_CELL_WORD_STATE_PRIORITY);
        }
    }
    
    void placeLetterInCell(int letterId_)
    {
        BoardModel::instance()->placeLetterInCell(m_x, m_y, letterId_);
        
        this->refreshFromModel();

    }
    
    virtual void refreshFromModelNotification()
    {
        this->refreshFromModel();
    }
    
  
    std::string getKey()
    {
        return m_key;
    }
    
    
    void handleTouch()
    {
        CCLog(m_key.c_str());
    }
    
    CellModel* getCellModel()
    {
        return BoardModel::instance()->getCellModel(m_x, m_y);

    }
    
    void setUnselected()
    {
        if ( m_selectedBackground != NULL)
        {
            m_selectedBackground->removeFromParentAndCleanup(true);
        }
        m_selected = false;
    }
    
    void setSelected()
    {
        if (m_selected || m_given)
        {
            return;
        }
        m_selectedBackground = CCSprite::spriteWithFile("selected_tile.png");
        this->addChild(m_selectedBackground,WC_CELL_SELECTED_PRIORITY);
        m_selected = true;
        
    }
    
    bool isSelected() {return m_selected;}
    bool isOpen() {return m_open;}

};



class BoardLayer : public CCLayer
{
    
protected:
    
    int m_width;
    int m_height;
    
    /**
     * state variable to remember if the current touch is a drag.
     **/
    int m_movingTouch;
    
    CCDictionary* m_cells;
    
    BoardLayerCell* m_selectedCell;
    
    WordModel* m_currentWord;
    
    void setupBoard()
    {
        m_selectedCell = NULL;
        m_currentWord = NULL;
        
        m_width = BoardModel::instance()->getWidth();
        m_height = BoardModel::instance()->getHeight();

        setTouchEnabled(true);
        
        for (int x=0;x<m_width;x++)
        {
            for (int y=0;y<m_height;y++)
            {
                BoardLayerCell* cell = new BoardLayerCell(x,y);
                cell->setPosition(ccp(x*WC_CELL_WIDTH+WC_CELL_WIDTH/2,y*WC_CELL_WIDTH+WC_CELL_WIDTH/2));
                this->addChild(cell);
                
                m_cells->setObject(cell,cell->getKey());
                cell->release();
            }
        }
    }
    
public:
    
    BoardLayer()
    {
        init();
        m_cells = new CCDictionary();
        this->refreshFromModel();
        
        
        CCNotificationCenter::sharedNotificationCenter()->addObserver(this,callfuncO_selector(BoardLayer::keyboardButtonPressed),WC_EVENT_KEYBOARD_PRESSED,NULL);
        
    }
    
  
    
    ~BoardLayer()
    {
        m_cells->release();
        CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, WC_EVENT_KEYBOARD_PRESSED);
    }
    
    virtual void keyboardButtonPressed(ButtonPushedEvent* event)
    {
        
        if (m_selectedCell != NULL && !m_selectedCell->isGiven())
        {
            m_selectedCell->placeLetterInCell(event->getLetterId());
            
            
            // refresh the board state
            CellModel* cellModel = m_selectedCell->getCellModel();
            CCArray* words = cellModel->getWords();
            for (int i = 0;i<words->count();i++)
            {
                WordModel* word = (WordModel*) words->objectAtIndex(i);
                
                WordModelState state = word->getState();
                CCArray* cells = word->getCells();
                for ( int x=0;x<cells->count();x++)
                {
                    CellModel* cell = (CellModel*)cells->objectAtIndex(x);
                    BoardLayerCell* layerCell = this->getCell(cell->getX(),cell->getY());
                    layerCell->displayBoardState(cell->getWordState());
                }
                
            }
            
            if (words->count() == 1 )
            {
                m_currentWord = (WordModel*)words->objectAtIndex(0);
                selectCell(m_currentWord->getNextCell(m_selectedCell->getCellModel()));
            }
            else if ( m_currentWord != NULL)
            {
                selectCell(m_currentWord->getNextCell(m_selectedCell->getCellModel()));
            }
            
            
            CCNotificationCenter::sharedNotificationCenter()->postNotification(WC_EVENT_LETTER_PLACED);
            
        }
        
        
    }
    
    
    BoardLayerCell* getCell(int x, int y)
    {
        return (BoardLayerCell*)m_cells->objectForKey(BoardLayerCell::keyForCoords(x, y));
    }
    
    void unselectCell()
    {
        if (m_selectedCell != NULL)
        {
            m_selectedCell->setUnselected();
            m_selectedCell = NULL;
        }
    }
    
    
    void selectCell(CellModel* cell_)
    {
        if (cell_ == NULL)
        {
            return;
        }
        
        this->selectCell(getCell(cell_->getX(),cell_->getY()));
    }
    
    void selectCell(BoardLayerCell* cell_)
    {
        unselectCell();
        cell_->setSelected();
        m_selectedCell = cell_;
    }
    
    void handleTouchAtPoint(CCPoint point_)
    {
        
        int x =  static_cast<int>(point_.x / WC_CELL_WIDTH);
        int y =  static_cast<int>(point_.y / WC_CELL_WIDTH);
        
        BoardLayerCell* cell = this->getCell(x,y);
        if ( cell != NULL && cell->isOpen())
        {
            selectCell(cell);
        }
        
    }
    
    
    
    void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        m_movingTouch = false;        
    }

    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        m_movingTouch = true;
    }
    
    
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
    {
        if ( m_movingTouch) 
        {
            return;
        }
        
        CCSetIterator it;
        CCTouch* touch;
        
        
        // ignore multi-touches
        if ( pTouches->count() > 1 )
            return;
        
        for( it = pTouches->begin(); it != pTouches->end(); it++) 
        {
            
            touch = (CCTouch*)(*it);
            
            if(!touch)
                break;
            
            CCPoint point = touch->getLocationInView();
            
            
            point = CCDirector::sharedDirector()->convertToGL(point);
            point = this->convertToNodeSpace(point);
            this->handleTouchAtPoint(point);
            
            
            
        }

    }
    
    
    
    void ccTouchesCancelled(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent){}
    
    
    void refreshFromModel()
    {
        m_cells->removeAllObjects();
        
        this->setupBoard();
        
        CCNotificationCenter::sharedNotificationCenter()->postNotification(WC_NOTIFICATION_REFRESH_FROM_MODEL);
        
        this->setContentSize(CCSizeMake(m_width*WC_CELL_WIDTH,m_height*WC_CELL_WIDTH));
        
    }
    
};

#endif