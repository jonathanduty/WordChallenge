//
//  SceneController.h
//  WordChallenge
//
//  Created by Jonathan Duty on 8/28/12.
//
//

#ifndef WordChallenge_SceneController_h
#define WordChallenge_SceneController_h

#include "cocos2d.h"
#include "UIConstants.h"
#include "TournamentModel.h"

using namespace cocos2d;

class TournamentSummaryScene;

enum {
    SCENE_CONTROLLER_GAME_LIST = 0,
    SCENE_CONTROLLER_GAME,
    SCENE_CONTROLLER_STORE,
    SCENE_LOGIN_SCENE,
    SCENE_SIGNUP_SCENE
} typedef SceneControllerState;




class SceneController : public CCObject
{
protected:
    
    CCScene* m_signupScene;
    CCScene* m_GameScene;

    SceneController();

public:
    
    ~SceneController();
    
    static SceneController* instance();
    
    void showSignupScene();
    void showLoginScene();
    void showGameScene(TournamentModel* tournament_);
    
    void showGameListScene( );
    
    
    void showTournamentSummaryScene(TournamentModel* tournament_);
    
    virtual void notificationLoginCompleteCallback(CCObject* obj);
};

#endif
