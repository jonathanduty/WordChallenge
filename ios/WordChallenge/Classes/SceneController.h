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
#include "LoginScene.h"
#include "PuzzleListScene.h"
using namespace cocos2d;


enum {
    SCENE_CONTROLLER_GAME_LIST = 0,
    SCENE_CONTROLLER_GAME,
    SCENE_CONTROLLER_STORE,
    SCENE_LOGIN_SCENE
} typedef SceneControllerState;


class SceneController;

static SceneController* s_sceneController = NULL;

class SceneController : public CCObject
{
protected:
    SceneController()
    {
        
    }
    
public:
    
    static SceneController* instance()
    {
        if (s_sceneController == NULL)
        {
            s_sceneController = new SceneController();
        }
        return s_sceneController;
    }
    
    void showLoginScene()
    {
        
        
        // create a scene. it's an autorelease object
        CCScene *pScene = LoginScene::scene();
        
        // run
        CCDirector::sharedDirector()->runWithScene(pScene);

    }
    
    void showGameScene()
    {
        
    }
    
    void showGameListScene( )
    {
        // create a scene. it's an autorelease object
        CCScene *pScene = PuzzleListScene::scene();
        
        // run
        CCDirector::sharedDirector()->replaceScene(pScene);
    }
};

#endif
