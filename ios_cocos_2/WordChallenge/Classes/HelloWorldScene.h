#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "KeyboardLayer.h"
#include "ScoreHeader.h"
#include "TournamentModel.h"

class HelloWorld : public cocos2d::CCLayer
{
protected:
    cocos2d::CCSprite* m_headerBackground;
    
    KeyboardLayer* m_keyboardLayer;
    
    ScoreHeader* m_scoreHeader;
    
public:
    HelloWorld(TournamentModel* tournament_);

    
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene(TournamentModel* tournament_);
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	
};

#endif // __HELLOWORLD_SCENE_H__
