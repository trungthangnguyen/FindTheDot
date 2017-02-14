//
//  Background.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/13/17.
//
//

#ifndef Background_h
#define Background_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class Background : public Node {
    GameScene *_theGame;
    
    bool initWith(GameScene *theGame);
    
public:
    static Background * createWith(GameScene *theGame);
};

#endif /* Background_h */
