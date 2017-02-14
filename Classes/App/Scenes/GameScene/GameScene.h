//
//  GameScene.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/10/17.
//
//

#ifndef GameScene_h
#define GameScene_h

#include <stdio.h>
#include "cocos2d.h"
#include "Layers/Background.h"
#include "Layers/GameMenu.h"
#include "Layers/SettingsLayer.h"

USING_NS_CC;

enum {
    kGameSceneZidxBackground,
    kGameSceneZidxGameLayer,
    kGameSceneZidxGameMenu,
    kGameSceneZidxSettings,
};

class GameScene : public Scene {
public:
    enum class GameState {
        NONE,
        PLAY,
        OVER,
    };
    
private:
    Background          *_background;
    GameMenu            *_gameMenu;
    Node                *_gameLayer;
    SettingsLayer       *_settingsLayer;
    
    std::vector<Node *> _pinNodes;
    
    GameState           _gameState;
    GameState           _preGameState;
    Point               _targetPos;
    
    bool init() override;
    
    void setGameState(GameState gameState);
    void createNewGame();
    void gameOver();
    void pinLocation(Point pos);
    
public:
    CREATE_FUNC(GameScene);
    
    GameState getGameState() {return _gameState;};
    GameState getPreGameState() {return _preGameState;};
    
    void onEnter() override;
    void onExit() override;
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event) {};
    void onTouchEnded(Touch *touch, Event *unused_event) {};
    void onTouchCancelled(Touch *touch, Event *unused_event) {};
};

#endif /* GameScene_h */
