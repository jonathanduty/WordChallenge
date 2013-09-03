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

using namespace cocos2d;


class GameListTableDataSource : public extension::CCTableViewDataSource, public CCObject
{
    
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
    CCSize cellSizeForTable(extension::CCTableView *table) {
        return CCSize(100, 100);
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
            CCLabelTTF* label = CCLabelTTF::create("I'm a cell", "Helvetica", 20);
            label->setPosition(CCPointZero);
            label->setAnchorPoint(CCPointZero);
            cell->addChild(label);
            
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
};

#endif /* defined(__WordChallenge__GameListTableDataSource__) */
