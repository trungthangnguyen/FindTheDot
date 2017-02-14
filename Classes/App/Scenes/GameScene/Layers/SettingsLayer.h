//
//  SettingsLayer.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/13/17.
//
//

#ifndef SettingsLayer_h
#define SettingsLayer_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class SettingsLayer : public Node {
    GameScene *_theGame;
    
    bool initWith(GameScene *theGame);
    
public:
    static SettingsLayer * createWith(GameScene *theGame);
};

#endif /* SettingsLayer_h */
