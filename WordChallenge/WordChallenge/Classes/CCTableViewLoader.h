//
//  CCListViewLoader.h
//  WordChallenge
//
//  Created by Jonathan Duty on 9/2/13.
//
//

#ifndef WordChallenge_CCListViewLoader_h
#define WordChallenge_CCListViewLoader_h

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;

class CCTableViewLoader : public  cocos2d::extension::CCLayerLoader{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCTableViewLoader, loader);
protected:
    virtual CCListView * createCCNode(cocos2d::CCNode * pParent, cocos2d::extension::CCBReader * pCCBReader) {
        CCListView *pRet = cocos2d::extension::CCTableView:create(CCListViewModeHorizontal);
        return pRet;
    }
    
};

#endif
