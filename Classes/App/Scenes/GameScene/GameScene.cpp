//
//  GameScene.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/10/17.
//
//

#include "GameScene.h"
#include "../../Global/GameDefines.h"
#include "../../../Components/MyComponents.h"

#pragma mark Initialize
bool GameScene::init(){
    if (Scene::init()) {
        // background
        _background = Background::createWith(this);
        _background->setPosition(Point::ZERO);
        this->addChild(_background, kGameSceneZidxBackground);
        
        // gameMenu
        _gameMenu = GameMenu::createWith(this);
        _gameMenu->setPosition(Point::ZERO);
        this->addChild(_gameMenu, kGameSceneZidxGameMenu);
        
        // gameLayer
        _gameLayer = Node::create();
        _gameLayer->setPosition(Point::ZERO);
        this->addChild(_gameLayer, kGameSceneZidxGameLayer);
        
        // create new game
        this->createNewGame();
        
        return true;
    }
    
    return false;
}

void GameScene::onEnter(){
    Scene::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit(){
    _eventDispatcher->removeEventListenersForTarget(this);
    
    Scene::onExit();
}

void GameScene::setGameState(GameScene::GameState gameState){
    if (_gameState != gameState) {
        _preGameState = _gameState;
        _gameState = gameState;
    }
}

#pragma mark Gameplay
void GameScene::createNewGame(){
    this->setGameState(GameState::NONE);
    _gameLayer->removeAllChildrenWithCleanup(true);
    _pinNodes.clear();
    
    float targetPadding = GAMEDEF_GAMEPLAY_RADIUS * 0.4f;
    _targetPos = Point(targetPadding + CCRANDOM_0_1()*(SS_DESIGN_WIDTH - targetPadding*2),
                       GAMEDEF_GAMEPLAY_MENU_PADDING + CCRANDOM_0_1()*(SS_DESIGN_HEIGHT - GAMEDEF_GAMEPLAY_MENU_PADDING*2));
    
    this->setGameState(GameState::PLAY);
}

void GameScene::gameOver(){
    this->setGameState(GameState::PLAY);
}

void GameScene::pinLocation(Point pos){
    for (int i=0; i<_pinNodes.size(); i++) {
        if (i == 0) {
            _pinNodes.at(i)->setOpacity(128);
        } else if (i == 1) {
            _pinNodes.at(i)->setOpacity(64);
        }
    }
    
    if (_pinNodes.size() >= 3) {
        _pinNodes.at(0)->removeFromParentAndCleanup(true);
        _pinNodes.erase(_pinNodes.begin()+0);
    }
    
    auto pin = LayerColor::create(Color4B(GAMEDEF_COLOR3B_TEXT), 16, 16);
    pin->setPosition(pos - pin->getContentSize()/2);
    _gameLayer->addChild(pin);
    _pinNodes.push_back(pin);
}

#pragma mark EventListenerTouchOneByOne
bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event){
    if (_gameState == GameState::PLAY) {
        this->pinLocation(touch->getLocation());
    }
    
    return false;
}
