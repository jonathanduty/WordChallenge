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
#include "TournamentModel.h"
#include "SceneController.h"

using namespace cocos2d;


class TournamentListButton : public CCNode
{
    TournamentModel* m_model;
    
    CCMenu* m_menu;
    
public:
    TournamentListButton(TournamentModel* model_)
    {
        m_model = model_;
        m_model->retain();
        
        CCSprite* background = CCSprite::create("game_list_cell.png");
        CCSprite* background2 = CCSprite::create("game_list_cell.png");

        CCSize size = background->getContentSize();

        CCLabelTTF* coinLabel =  CCLabelTTF::create("100",WC_DEFAULT_FONT,20);
        coinLabel->setPosition(ccp(60,size.height/2));
        coinLabel->setColor(ccc3(0,0,0));
        this->addChild(coinLabel,2);
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::create(background,
                                                                          background2,
                                                                        this,
                                                                          menu_selector(TournamentListButton::cellPressed));
        m_menu = CCMenu::create(sprite, NULL);
        m_menu->retain();
        
        
        
        this->addChild(m_menu,1);

    }
    
    
    virtual void cellPressed(CCObject* obj)
    {
        SceneController::instance()->showTournamentSummaryScene(m_model);
    }
    
    virtual void setPosition(CCPoint point_)
    {

        m_menu->setPosition(point_);
    }
    
    ~TournamentListButton()
    {
        CC_SAFE_RELEASE(m_model);
        CC_SAFE_RELEASE(m_menu);
    }
    
    
    
};



class PuzzleListScene : public CCLayer
{
protected:
    CCMenu* m_storeButton;
    
    
    
    void buildStoreButton()
    {
        CCSprite* background = CCSprite::create("game_list_button.png");
        CCSprite* selectedBackground = CCSprite::create("game_list_button.png");
        selectedBackground->setScale(1.0);
        
        
        CCSprite* coinIcon = CCSprite::create("coin.png");
        coinIcon->setScale(.5);
        background->addChild(coinIcon);
        CCSize size = background->getContentSize();
        coinIcon->setPosition(ccp(20,size.height/2));
        
        CCLabelTTF* coinLabel =  CCLabelTTF::create("100",WC_DEFAULT_FONT,20);
        coinLabel->setPosition(ccp(60,size.height/2));
        coinLabel->setColor(ccc3(0,0,0));
        background->addChild(coinLabel);
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::create(background,
                                                            selectedBackground,
                                                        this,
                                    menu_selector(PuzzleListScene::storeButtonPressed));
        
        
        m_storeButton = CCMenu::menuWithItems(sprite, NULL);
        m_storeButton->retain();
        this->addChild(m_storeButton, 1);
        
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_storeButton->setPosition(ccp(175,winSize.height - 100));
        
    }
    
    void buildTournamentButtons()
    {
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();

        
        TournamentModel* model = new TournamentModel(1,"test");
        model->autorelease();
        TournamentListButton* button = new TournamentListButton(model);
        button->setPosition(ccp(winSize.width/2,winSize.height - 200));
        this->addChild(button,1);
        button->release();
    }
    
    
public:
    
    
    // a selector callback
	virtual void storeButtonPressed(CCObject* pSender)
    {
        
    }
    
    
    PuzzleListScene()
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
        
        this->buildStoreButton();
        this->buildTournamentButtons();
        
        return true;
        
    }
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene()
    {
        // 'scene' is an autorelease object
        CCScene *scene = CCScene::create();
        
        // 'layer' is an autorelease object
        PuzzleListScene *layer = new PuzzleListScene();
        
        // add layer as a child to scene
        scene->addChild(layer);
        
        // return the scene
        return scene;
    }

	

    
	
    
    
    ~PuzzleListScene()
    {
        CC_SAFE_RELEASE( m_storeButton );
    }
};


#endif
