//
//  TournamentSummaryScene.h
//  WordChallenge
//
//  Created by Jonathan Duty on 9/4/12.
//
//

#ifndef WordChallenge_TournamentSummaryScene_h
#define WordChallenge_TournamentSummaryScene_h

#include "cocos2d.h"
#include "SceneController.h"

using namespace cocos2d;
using namespace std;

class TournamentSummaryScene : public CCLayer
{
protected:
    CCMenu* m_playButton;
    TournamentModel* m_tournament;
    
    
    void buildPlayButton()
    {
        CCSprite* background = CCSprite::spriteWithFile("game_list_cell.png");
        CCSprite* selectedBackground = CCSprite::spriteWithFile("game_list_cell.png");
        selectedBackground->setScale(1.0);
        
        
        CCSprite* coinIcon = CCSprite::spriteWithFile("coin.png");
        coinIcon->setScale(.5);
        background->addChild(coinIcon);
        CCSize size = background->getContentSize();
        coinIcon->setPosition(ccp(20,size.height/2));
        
        CCLabelTTF* coinLabel =  CCLabelTTF::labelWithString("Play",WC_DEFAULT_FONT,20);
        coinLabel->setPosition(ccp(60,size.height/2));
        coinLabel->setColor(ccc3(0,0,0));
        background->addChild(coinLabel);
        
        CCMenuItemSprite* sprite = CCMenuItemSprite::itemFromNormalSprite(background,
                                                                          selectedBackground,
                                                                          NULL, this,
                                                                          menu_selector(TournamentSummaryScene::playButtonPressed));
        
        
        m_playButton = CCMenu::menuWithItems(sprite, NULL);
        m_playButton->retain();
        this->addChild(m_playButton, 1);
        
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        m_playButton->setPosition(ccp(175,winSize.height - 100));
        
    }
    
  


    
public:

    
    
    TournamentSummaryScene(TournamentModel* model_)
    {
        this->init();
        m_tournament = model_;
        m_tournament->retain();
        
        
        CCLabelTTF* nameLabel =  CCLabelTTF::labelWithString(m_tournament->getName().c_str(),WC_DEFAULT_FONT,20);
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        nameLabel->setPosition(ccp(winSize.width/2,winSize.height/2));
        
        this->addChild(nameLabel);
        
    }
    
    // a selector callback
	virtual void playButtonPressed(CCObject* pSender)
    {
        SceneController::instance()->showGameScene(m_tournament);
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
        
        this->buildPlayButton();
        
        return true;
        
    }
    
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(TournamentModel* model_)
    {
        // 'scene' is an autorelease object
        CCScene *scene = CCScene::node();
        
        // 'layer' is an autorelease object
        TournamentSummaryScene *layer = new TournamentSummaryScene(model_);
        
        layer->autorelease();
        
        // add layer as a child to scene
        scene->addChild(layer);
        // return the scene
        return scene;
    }
    
	
    
    
	
    
    
    ~TournamentSummaryScene()
    {
        CC_SAFE_RELEASE( m_playButton );
        CC_SAFE_RELEASE(m_tournament);

    }
    

};



#endif
