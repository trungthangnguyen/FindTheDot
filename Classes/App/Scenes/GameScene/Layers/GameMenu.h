//
//  GameMenu.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/13/17.
//
//

#ifndef GameMenu_h
#define GameMenu_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class GameMenu : public Node {
    GameScene   *_theGame;
    Label       *_scoreLabel;
    Label       *_introLabel;
    Label       *_noticeLabel;
    
    bool initWith(GameScene *theGame);
    
public:
    static GameMenu * createWith(GameScene *theGame);
    
    void updateScoreLabel(const int score);
    void updateNoticeLabel(const char *text);
};

#endif /* GameMenu_h */
