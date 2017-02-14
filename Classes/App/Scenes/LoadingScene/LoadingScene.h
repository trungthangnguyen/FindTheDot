//
//  LoadingScene.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/10/17.
//
//

#ifndef LoadingScene_h
#define LoadingScene_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class LoadingScene : public Scene {
    bool init() override;
    
    void loadResources();
    
    Node * logoCompany();
    
public:
    CREATE_FUNC(LoadingScene);
};

#endif /* LoadingScene_h */
