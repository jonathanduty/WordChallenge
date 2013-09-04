//
//  GameListLayer.h
//  WordChallenge
//
//  Created by Jonathan Duty on 9/2/13.
//
//

#ifndef __WordChallenge__GameListLayer__
#define __WordChallenge__GameListLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"
//#include "CCListViewLoader.h"

#include "GameListTableDataSource.h"
using namespace cocos2d;

class GameListLayer :  public CCLayer,
    public cocos2d::extension::CCBMemberVariableAssigner,
    public cocos2d::extension::CCBSelectorResolver
{
protected:
    extension::CCScrollView* m_scrollView;
    extension::CCTableView* m_tableView;
    
    GameListTableDataSource* m_dataSource;
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameListLayer, create);

    
    // on "init" you need to initialize your instance
    bool init()
    {
        //////////////////////////////
        // 1. super init first
        if ( !CCLayer::init() )
        {
            return false;
        }
        
        m_dataSource = new GameListTableDataSource();
        
        return true;
    }
    
    ~GameListLayer()
    {
        m_dataSource->release();
    }
    
    void finishLoad()
    {
        extension::CCTableView* tableView = extension::CCTableView::create(m_dataSource, m_scrollView->getViewSize());
        tableView->setDirection(extension::kCCScrollViewDirectionVertical);
        tableView->setPosition(m_scrollView->getPosition());
        tableView->setAnchorPoint(m_scrollView->getAnchorPoint());
        tableView->setDelegate(m_dataSource);
        tableView->setVerticalFillOrder(extension::kCCTableViewFillTopDown);
        tableView->setClippingToBounds(true);
        this->addChild(tableView);
        
        this->removeChild(m_scrollView);
        
    }
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);

    
    static CCScene* scene();

};

class GameListLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameListLayerLoader, loader);
    static GameListLayer* load();
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameListLayer);
    
};

#endif /* defined(__WordChallenge__GameListLayer__) */
