//
//  PuzzleListScene.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/26/12.
//
//

#ifndef WordChallenge_PuzzleListScene_h
#define WordChallenge_PuzzleListScene_h


#include "cocos2d.h"

using namespace cocos2d;

class PuzzleListScene : public CCLayer
{
protected:
    CCMenu* m_storeButton;
    
    
    
    void buildStoreButton()
    {
        CCSprite* background = CCSprite::spriteWithFile("game_list_button.png");
        CCSprite* selectedBackground = CCSprite::spriteWithFile("game_list_button.png");
        selectedBackground->setScale(1.0);
        
        
        CCSprite* coinIcon = CCSprite::spriteWithFile("coin.png");
        coinIcon->setScale(.5);
        background->addChild(coinIcon);
        CCSize size = background->getContentSize();
        coinIcon->setPosition(ccp(20,size.height/2));
        
        CCLabelTTF* coinLabel =  CCLabelTTF::labelWithString("100",WC_DEFAULT_FONT,20);
        coinLabel->setPosition(ccp(60,size.height/2));
        coinLabel->setColor(ccc3(0,0,0));
        background->addChild(coinLabel);
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::itemFromNormalSprite(background,
                                                                          selectedBackground,
                                                                          NULL, this,
                                                                          menu_selector(PuzzleListScene::storeButtonPressed));
        
        
        m_storeButton = CCMenu::menuWithItems(sprite, NULL);
        m_storeButton->retain();
        this->addChild(m_storeButton, 1);
        
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_storeButton->setPosition(ccp(175,winSize.height - 100));
        
    }
    
    
    
    
public:
    
    
    // a selector callback
	virtual void storeButtonPressed(CCObject* pSender)
    {
        
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
        
        this->buildStoreButton();
        
        
        return true;
        
    }
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene()
    {
        // 'scene' is an autorelease object
        CCScene *scene = CCScene::node();
        
        // 'layer' is an autorelease object
        PuzzleListScene *layer = PuzzleListScene::node();
        
        // add layer as a child to scene
        scene->addChild(layer);
        
        // return the scene
        return scene;
    }

	

    
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(PuzzleListScene);
    
    
    ~PuzzleListScene()
    {
        CC_SAFE_RELEASE( m_storeButton );
    }
};


#endif
