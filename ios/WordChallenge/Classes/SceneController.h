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

using namespace cocos2d;


enum {
    SCENE_CONTROLLER_GAME_LIST = 0,
    SCENE_CONTROLLER_GAME,
    SCENE_CONTROLLER_STORE
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
    
    
    void showGameScene()
    {
        
    }
    
    void showGameListScene( )
    {
            
    }
};

#endif
