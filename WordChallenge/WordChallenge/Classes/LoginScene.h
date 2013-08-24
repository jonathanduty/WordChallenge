//
//  LoginScene.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/29/12.
//
//

#ifndef WordChallenge_LoginScene_h
#define WordChallenge_LoginScene_h

#include "cocos2d.h"
#include "UIConstants.h"
#include "PlatformHelper.h"

using namespace cocos2d;

class LoginScene : public CCLayer
{
protected:
    
    
    CCMenu* m_loginButton;
    
    void buildLoginButton()
    {
        CCSprite* background = CCSprite::create("game_list_cell.png");
        CCSprite* selectedBackground = CCSprite::create("game_list_cell.png");
        selectedBackground->setScale(1.0);
        
        
        CCSize size = background->getContentSize();
        
        CCLabelTTF* coinLabel =  CCLabelTTF::create("Login",WC_DEFAULT_FONT,20);
        coinLabel->setPosition(ccp(size.width/2,size.height/2));
        coinLabel->setColor(ccc3(0,0,0));
        background->addChild(coinLabel);
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::create(background,
                                                            selectedBackground,
                                                                 this,
                                            menu_selector(LoginScene::loginButtonPressed));
        
        
        m_loginButton = CCMenu::create(sprite, NULL);
        m_loginButton->retain();
        this->addChild(m_loginButton, 1);
        
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_loginButton->setPosition(ccp(winSize.width/2,winSize.height/2));
        
    }

    
    
public:
    
    
    virtual void loginButtonPressed(CCObject* obj)
    {
        CCLog("Pressed");
        facebookLogin();
    }
    
    LoginScene()
    {
        this->init();
    }
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init()
    {
        //////////////////////////////
        // 1. super init first
        if ( !CCLayer::init() )
        {
            return false;
        }
        
        this->buildLoginButton();
        
        return true;
        
    }
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene()
    {
        // 'scene' is an autorelease object
        CCScene *scene = CCScene::create();
        
        // 'layer' is an autorelease object
        LoginScene *layer = new LoginScene();
        
        // add layer as a child to scene
        scene->addChild(layer);
        
        // return the scene
        return scene;
    }
    
	
    
    
	
    
    
    ~LoginScene()
    {
        CC_SAFE_RELEASE( m_loginButton );

    }

    
};


#endif
