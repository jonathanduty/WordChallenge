//
//  GameListCellLayer.h
//  WordChallenge
//
//  Created by Jonathan Duty on 9/3/13.
//
//

#ifndef __WordChallenge__GameListCellLayer__
#define __WordChallenge__GameListCellLayer__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;

class GameListCellLayer :  public CCLayer,
public cocos2d::extension::CCBMemberVariableAssigner,
public cocos2d::extension::CCBSelectorResolver
{
protected:
        
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(GameListCellLayer, create);
    
    
    // on "init" you need to initialize your instance
    bool init()
    {
        //////////////////////////////
        // 1. super init first
        if ( !CCLayer::init() )
        {
            return false;
        }
        
        
        return true;
    }
    
    GameListCellLayer()
    {
    }
    
    void finishLoad()
    {
        
        
    }
    
    virtual cocos2d::SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual cocos2d::extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName);
    
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual bool onAssignCCBCustomProperty(CCObject* pTarget, const char* pMemberVariableName, cocos2d::extension::CCBValue* pCCBValue);
    
    
    static GameListCellLayer* layer();
    
};



class GameListCellLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(GameListCellLayerLoader, loader);
    static GameListCellLayer* load();
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(GameListCellLayer);
    
};


#endif /* defined(__WordChallenge__GameListCellLayer__) */
