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
#include "CCLayerPanZoom.h"
#include "ProtoDatabase.h"
using namespace cocos2d;


#define WC_NOTIFICATION_REFRESH_FROM_MODEL "WC_NOTIFICATION_REFRESH_FROM_MODEL"

#define WC_CELL_WIDTH 57

#define WC_DEFAULT_FONT_BOLD "HelveticaBold"
#define WC_DEFAULT_FONT "Helvetica"


class BoardLayerCell : public CCNode
{
protected:
    int m_x;
    int m_y;
    
    CCSprite* m_background;
    CCLabelTTF* m_letterLabel;
    CCLabelTTF* m_pointsLabel;
    std::string m_key;
    
public:
    
    static std::string keyForCoords(int x_, int y_)
    {
        std::ostringstream oss;
        oss << x_ << "_" << y_;
        return oss.str(); 
    }
    
    BoardLayerCell( int x_, int y_) : m_background(NULL)
    {
        
        m_x = x_;
        m_y = y_;
        m_key = keyForCoords(m_x,m_y);
        
        this->setContentSize(CCSizeMake(WC_CELL_WIDTH,WC_CELL_WIDTH));
        
        CCNotificationCenter::sharedNotifCenter()->addObserver(this,callfuncO_selector(BoardLayerCell::refreshFromModelNotification),WC_NOTIFICATION_REFRESH_FROM_MODEL,NULL);

        
    }
    
    ~BoardLayerCell()
    {
        CCNotificationCenter::sharedNotifCenter()->removeObserver(this, WC_NOTIFICATION_REFRESH_FROM_MODEL);
    }
    
    
    void refreshFromModel()
    {
        CellModel* cellModel = BoardModel::instance()->getCellModel(m_x, m_y);
        if ( cellModel != NULL)
        {
            m_background = CCSprite::spriteWithFile("open_tile.png");
            this->addChild(m_background);
            
            
            int proto_id = cellModel->getLetterProtoId();
            if (proto_id != WC_NO_LETTER ) 
            {
                
                Json::Value letter = ProtoDatabase::shardInstance()->getLetterProtoDataById(proto_id);
                m_letterLabel =  CCLabelTTF::labelWithString(letter["label"].asString().c_str(),WC_DEFAULT_FONT_BOLD,40);
                this->addChild(m_letterLabel);
                
            }
        }
        else 
        {
            m_background = CCSprite::spriteWithFile("closed_tile.png");
            this->addChild(m_background);
        }
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
    
    CCMutableDictionary<std::string,BoardLayerCell*>* m_cells;
    
    
    void setupBoard()
    {
        
        m_width = BoardModel::instance()->getWidth();
        m_height = BoardModel::instance()->getHeight();

        setIsTouchEnabled(true);
        
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
        m_cells = new CCMutableDictionary<std::string,BoardLayerCell*>();
        this->refreshFromModel();
    }
    
  
    
    ~BoardLayer()
    {
        m_cells->release();
    }
    
    
    BoardLayerCell* getCell(int x, int y)
    {
        return m_cells->objectForKey(BoardLayerCell::keyForCoords(x, y));
    }
    
    
    void handleTouchAtPoint(CCPoint point_)
    {
        int x =  static_cast<int>(point_.x / WC_CELL_WIDTH);
        int y =  static_cast<int>(point_.y / WC_CELL_WIDTH);
        
        BoardLayerCell* cell = this->getCell(x,y);
        int count = m_cells->count();
        if ( cell != NULL) 
        {
            cell->handleTouch();
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
            
            CCPoint point = touch->locationInView(touch->view());
            
            
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
        
        CCNotificationCenter::sharedNotifCenter()->postNotification(WC_NOTIFICATION_REFRESH_FROM_MODEL);
        
        this->setContentSize(CCSizeMake(m_width*WC_CELL_WIDTH,m_height*WC_CELL_WIDTH));
        
    }
    
};

#endif
