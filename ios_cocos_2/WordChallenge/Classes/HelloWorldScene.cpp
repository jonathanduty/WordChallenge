#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BoardLayer.h"
//#include "CCLayerPanZoom.h"

#include "json.h"
#include "BoardModel.h"
#include <fstream>
#include "ProtoDatabase.h"

using namespace cocos2d;
using namespace CocosDenshion;


#define WC_HUD_ZORDER 10
#define WC_BOARD_ZORDER 5


CCScene* HelloWorld::scene(TournamentModel* tournament_)
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = new HelloWorld(tournament_);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


HelloWorld::HelloWorld(TournamentModel* tournament_)
{
    this->init();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayer::init() )
	{
		return false;
	}
    
    
    
    // preload the protodatabase.
    ProtoDatabase::shardInstance();
    
    Json::Value root;
    Json::Reader reader;
    
    bool parsingSuccessful = reader.parse(getJsonFileContents("board"), root );
    if ( !parsingSuccessful ) 
    {
        CCLog("Failed to Parse Protodata file");
        return NULL;
    }
    BoardModel::loadNewModel(root);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
	BoardLayer* layer = new BoardLayer();
    layer->refreshFromModel();
    layer->setScale(0.56);
    layer->setPosition(-125,15);
    this->addChild(layer,WC_BOARD_ZORDER);
	
   

    
    m_headerBackground = CCSprite::create("header.png");
    m_headerBackground->retain();
    m_headerBackground->setPosition(ccp(winSize.width/2,470));
    this->addChild(m_headerBackground,WC_HUD_ZORDER);
    
    m_scoreHeader = new ScoreHeader();
    m_scoreHeader->retain();
    m_scoreHeader->setPosition(ccp(winSize.width/2,470));
    this->addChild(m_scoreHeader,WC_HUD_ZORDER+1);
    
    m_keyboardLayer = new KeyboardLayer();
    this->addChild(m_keyboardLayer,WC_HUD_ZORDER);
    
	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
