//
//  SceneController.cpp
//  WordChallenge
//
//  Created by Jonathan Duty on 9/4/12.
//
//

#include "SceneController.h"
#include "LoginScene.h"
#include "HelloWorldScene.h"
#include "SignupLayer.h"
#include "UserSession.h"
#include "GameListLayer.h"

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


void SceneController::begin()
{
    if (!UserSession::sharedInstance()->hasValidSession())
    {
        //showSignupScene();
        showGameListScene();
    }
    else
    {
        showGameScene(NULL);
    }
    
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
    CCDirector::sharedDirector()->runWithScene(pScene);
}

void SceneController::showGameListScene( )
{
    if ( m_gameListScene == NULL)
    {
        m_gameListScene =GameListLayer::scene();
        
    }
    
    // create a scene. it's an autorelease object
    //CCScene *pScene = PuzzleListScene::scene();
    
    
    CCDirector::sharedDirector()->runWithScene(m_gameListScene);
}

void SceneController::showSignupScene()
{
    CCScene* pScene = SignupLayer::scene();
    CCDirector::sharedDirector()->runWithScene(pScene);

}

void SceneController::showTournamentSummaryScene(TournamentModel* tournament_)
{
    //CCScene *pScene = TournamentSummaryScene::scene(tournament_);
    //CCDirector::sharedDirector()->replaceScene(pScene);
    
}



void SceneController::notificationLoginCompleteCallback(CCObject* obj)
{
    showGameListScene();
}