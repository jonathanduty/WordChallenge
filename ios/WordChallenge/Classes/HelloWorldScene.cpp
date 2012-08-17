#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "BoardLayer.h"
#include "CCLayerPanZoom.h"

#include "json.h"
#include "BoardModel.h"
#include <fstream>
#include "ProtoDatabase.h"

using namespace cocos2d;
using namespace CocosDenshion;


#define WC_HUD_ZORDER 10
#define WC_BOARD_ZORDER 5


CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
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
    fstream is;
    is.open(CCFileUtils::fullPathFromRelativePath("board.json"));
    bool parsingSuccessful = reader.parse(is, root );
    if ( !parsingSuccessful ) 
    {
        CCLog("Failed to Parse Protodata file");
        return NULL;
    }
    BoardModel::loadNewModel(root);
    
    CCLayerPanZoom* scrollLayer = CCLayerPanZoom::layer();
    
	BoardLayer* layer = new BoardLayer();
    layer->refreshFromModel();
    scrollLayer->addChild(layer);
    this->addChild(scrollLayer,WC_BOARD_ZORDER);
	//layer->setPosition(ccp(20*57/2,20*57/2));
    //layer->setPosition(ccp(0,0));
    
    scrollLayer->setMaxScale(1);
    //scrollLayer->setScale(.25);
    scrollLayer->setMinScale(.35);
    
    scrollLayer->setContentSize(layer->getContentSize());
    scrollLayer->setPanBoundsRect(CCRect(0,140,320, 
                            320));
    scrollLayer->settopFrameMargin(0.0);

    
    m_headerBackground = CCSprite::spriteWithFile("header.png");
    m_headerBackground->retain();
    m_headerBackground->setPosition(ccp(160,470));
    this->addChild(m_headerBackground,WC_HUD_ZORDER);
    
    
    m_keyboardBackground = CCSprite::spriteWithFile("keyboard_background.png");
    m_keyboardBackground->retain();
    m_keyboardBackground->setPosition(ccp(160,70));
    this->addChild(m_keyboardBackground,WC_HUD_ZORDER);
    
	return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
