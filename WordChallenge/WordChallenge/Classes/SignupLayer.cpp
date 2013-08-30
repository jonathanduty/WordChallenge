//
//  SignupLayer.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 8/29/13.
//
//

#include "SignupLayer.h"

using namespace cocos2d::extension;

CCScene* SignupLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // Create a default CCNodeLoaderLibrary. As we won't be using
    // code connections in this tutorial don't worry about it.
    extension::CCNodeLoaderLibrary* nodeLoaderLibrary;
    nodeLoaderLibrary = extension::CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    nodeLoaderLibrary->registerCCNodeLoader("SignupLayer", SignupLayerLoader::loader());
    
    
    // Create a new CCBReader with a default CCNodeLoaderLibrary
    // This can take a lot of parameters to use code connections and more
    extension::CCBReader* ccbReader = new extension::CCBReader(nodeLoaderLibrary);
    // Load the main node from the CocosBuilder file
    CCNode* node = ccbReader->readNodeGraphFromFile("SignupLayer");
    scene->addChild(node); // Add the loaded node to the scene (this)
    // As nobody called ccbReader->autoRelease(), returning now would cause
    // a memory leak. We can call autoRelease or delete it ourselves.
    delete ccbReader;
    
    
    // return the scene
    return scene;
}
bool SignupLayer::onAssignCCBCustomProperty(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::extension::CCBValue *pCCBValue)
{
    return false;
}

bool SignupLayer::onAssignCCBMemberVariable(cocos2d::CCObject *pTarget, const char *pMemberVariableName, cocos2d::CCNode *pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "usernameAnchor", CCNode*, this->m_usernameAnchor);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "emailAnchor", CCNode*, this->m_emailAnchor);
    return false;
}

cocos2d::extension::SEL_CCControlHandler SignupLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onSignupButtonClick", SignupLayer::signupButtonPressed);

    return NULL;
    
}

cocos2d::SEL_MenuHandler SignupLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    return NULL;
}