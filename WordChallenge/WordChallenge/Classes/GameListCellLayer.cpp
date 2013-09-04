//
//  GameListCellLayer.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 9/3/13.
//
//

#include "GameListCellLayer.h"


GameListCellLayer* GameListCellLayer::layer()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // Create a default CCNodeLoaderLibrary. As we won't be using
    // code connections in this tutorial don't worry about it.
    extension::CCNodeLoaderLibrary* nodeLoaderLibrary;
    nodeLoaderLibrary = extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLoaderLibrary->registerCCNodeLoader("GameListCellLayer", GameListCellLayerLoader::loader());
    
    
    // Create a new CCBReader with a default CCNodeLoaderLibrary
    // This can take a lot of parameters to use code connections and more
    extension::CCBReader* ccbReader = new extension::CCBReader(nodeLoaderLibrary);
    // Load the main node from the CocosBuilder file
    GameListCellLayer* layer = (GameListCellLayer*)ccbReader->readNodeGraphFromFile("GameListCellLayer");
    
    delete ccbReader;

    return layer;
    // layer->finishSetup();
    
    layer->finishLoad();
    
   
}
bool GameListCellLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

bool GameListCellLayer::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    //CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "gameListScrollView", extension::CCScrollView*, this->m_scrollView);
    // CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "emailPlaceholder", CCControlButton*, this->m_emailPlaceholder);
    return false;
}

cocos2d::extension::SEL_CCControlHandler GameListCellLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    //CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSignupButtonClick", SignupLayer::signupButtonPressed);
    
    return NULL;
    
}

cocos2d::SEL_MenuHandler GameListCellLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}