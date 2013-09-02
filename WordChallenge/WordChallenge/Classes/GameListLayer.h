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

using namespace cocos2d;

class GameListLayer :  public CCLayer,
    public cocos2d::extension::CCBMemberVariableAssigner,
    public cocos2d::extension::CCBSelectorResolver
{
    
    
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
        return true;
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
