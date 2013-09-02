//
//  SignupLayer.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/29/13.
//
//

#ifndef __WordChallenge__SignupLayer__
#define __WordChallenge__SignupLayer__

#include <iostream>

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;

class SignupLayerLoader;


class SignupLayer : public CCLayer,
                    public cocos2d::extension::CCBMemberVariableAssigner,
                    public cocos2d::extension::CCBSelectorResolver

{
protected:
    
    extension::CCControlButton* m_usernamePlaceholder;
    extension::CCControlButton* m_emailPlaceholder;
    
    extension::CCEditBox* m_emailEditBox;
    extension::CCEditBox* m_usernameEditBox;
   
    
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SignupLayer, create);
  
    
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
    
    void signupButtonPressed(cocos2d::CCObject * pSender, cocos2d::extension::CCControlEvent pCCControlEvent)
    {
        CCLOG("signupButtonPressed");
    }
    
    
    void finishSetup()
    {
        m_emailEditBox = extension::CCEditBox::create(m_emailPlaceholder->getPreferredSize(),
                                                      extension::CCScale9Sprite::createWithSpriteFrameName("ccbButton.png") );
        m_emailEditBox->setPosition(m_emailPlaceholder->getPosition());
        this->addChild(m_emailEditBox);
        m_emailPlaceholder->setVisible(false);
        
        
        m_usernameEditBox = extension::CCEditBox::create(m_usernamePlaceholder->getPreferredSize(),
                                                      extension::CCScale9Sprite::createWithSpriteFrameName("ccbButton.png") );
        m_usernameEditBox->setPosition(m_usernamePlaceholder->getPosition());
        this->addChild(m_usernameEditBox);
        m_usernamePlaceholder->setVisible(false);

        
    }
    
    static CCScene* scene();
};



class SignupLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SignupLayerLoader, loader);
    static SignupLayer* load();
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SignupLayer);
    
};
#endif /* defined(__WordChallenge__SignupLayer__) */
