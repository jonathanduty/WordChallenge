//
//  GameListTableDataSource.h
//  WordChallenge
//
//  Created by Jonathan Duty on 9/3/13.
//
//

#ifndef __WordChallenge__GameListTableDataSource__
#define __WordChallenge__GameListTableDataSource__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameListCellLayer.h"
using namespace cocos2d;


class GameListTableDataSource :
    public extension::CCTableViewDataSource,
    public extension::CCTableViewDelegate,
    public CCObject
{
    
    virtual bool hasFixedCellSize()
    {
        return false;
    }
    
    
    /**
     * cell size for a given index
     *
     * @param idx the index of a cell to get a size
     * @return size of a cell at given index
     */
    CCSize tableCellSizeForIndex(extension::CCTableView *table, unsigned int idx) {
        return cellSizeForTable(table);
    };
    /**
     * cell height for a given table.
     *
     * @param table table to hold the instances of Class
     * @return cell size
     */
    CCSize cellSizeForTable(extension::CCTableView *table)
    {
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        
        return CCSize(size.width,100 );
    };
    /**
     * a cell instance at a given index
     *
     * @param idx index to search for a cell
     * @return cell found at idx
     */
    extension::CCTableViewCell* tableCellAtIndex(extension::CCTableView *table, unsigned int idx)
    {
        extension::CCTableViewCell* cell = table->dequeueCell();
        
        if (!cell)
        {
            cell = new extension::CCTableViewCell();
            cell->autorelease();
            GameListCellLayer* layer = GameListCellLayer::layer();
            
            layer->setPosition(CCPointZero);
            layer->setAnchorPoint(CCPointZero);
                
            
            cell->addChild(layer);
            
        }
        return cell;
        
        
        
    }
    /**
     * Returns number of cells in a given table view.
     *
     * @return number of cells
     */
    unsigned int numberOfCellsInTableView(extension::CCTableView *table)
    {
        return 20;
    }
    
    
    /**
     * Delegate to respond touch event
     *
     * @param table table contains the given cell
     * @param cell  cell that is touched
     */
     void tableCellTouched(extension::CCTableView* table, extension::CCTableViewCell* cell)
    {
        CCLog("tableCellTouched");
    }
    
    /**
     * Delegate to respond a table cell press event.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
     void tableCellHighlight(extension::CCTableView* table, extension::CCTableViewCell* cell)
    {
    }
    
    /**
     * Delegate to respond a table cell release event
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
     void tableCellUnhighlight(extension::CCTableView* table, extension::CCTableViewCell* cell){};
    
    /**
     * Delegate called when the cell is about to be recycled. Immediately
     * after this call the cell will be removed from the scene graph and
     * recycled.
     *
     * @param table table contains the given cell
     * @param cell  cell that is pressed
     */
     void tableCellWillRecycle(extension::CCTableView* table, extension::CCTableViewCell* cell){};
    
    
    void scrollViewDidScroll(extension::CCScrollView* view)
    {
        
    }
    virtual void scrollViewDidZoom(extension::CCScrollView* view)
    {
        
    }

    
};

#endif /* defined(__WordChallenge__GameListTableDataSource__) */
