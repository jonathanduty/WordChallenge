//
//  SceneController.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 9/4/12.
//
//

#include "SceneController.h"
#include "LoginScene.h"
#include "PuzzleListScene.h"
#include "TournamentSummaryScene.h"
#include "HelloWorldScene.h"

static SceneController* s_sceneController = NULL;


SceneController::SceneController()
{
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SceneController::notificationLoginCompleteCallback), WC_EVENT_LOGIN_COMPLETE, NULL);
}

SceneController::~SceneController()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, WC_EVENT_LOGIN_COMPLETE);
}

SceneController* SceneController::instance()
{
    if (s_sceneController == NULL)
    {
        s_sceneController = new SceneController();
    }
    return s_sceneController;
}

void SceneController::showLoginScene()
{
    
    
    // create a scene. it's an autorelease object
    CCScene *pScene = LoginScene::scene();
    
    // run
    CCDirector::sharedDirector()->runWithScene(pScene);
    
}

void SceneController::showGameScene(TournamentModel* tournament_)
{
    // create a scene. it's an autorelease object
    CCScene *pScene = HelloWorld::scene(tournament_);
    
    // run
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void SceneController::showGameListScene( )
{
    // create a scene. it's an autorelease object
    CCScene *pScene = PuzzleListScene::scene();
    
    // run
    CCDirector::sharedDirector()->replaceScene(pScene);
}


void SceneController::showTournamentSummaryScene(TournamentModel* tournament_)
{
    CCScene *pScene = TournamentSummaryScene::scene(tournament_);
    CCDirector::sharedDirector()->replaceScene(pScene);
    
}



void SceneController::notificationLoginCompleteCallback(CCObject* obj)
{
    showGameListScene();
}