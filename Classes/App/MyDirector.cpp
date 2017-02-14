//
//  MyDirector.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/10/17.
//
//

#include "MyDirector.h"
#include "Global/GameDefines.h"
#include "Scenes/LoadingScene/LoadingScene.h"
#include "Scenes/GameScene/GameScene.h"
#include "../Components/MyComponents.h"

static MyDirector *__myDirectorInstance__ = nullptr;

#pragma mark Initialize
MyDirector * MyDirector::getInstance(){
    if (__myDirectorInstance__ == nullptr) {
        __myDirectorInstance__ = new MyDirector();
        __myDirectorInstance__->init();
    }
    
    return __myDirectorInstance__;
}

bool MyDirector::init(){
    _appState = AppState::NONE;
    _preAppState = AppState::NONE;
    
    return true;
}

void MyDirector::setAppState(MyDirector::AppState appState){
    _preAppState = _appState;
    _appState = appState;
}

#pragma mark Scenes
void MyDirector::onLoadingScene(){
    CCASSERT(!Director::getInstance()->getRunningScene(), "hieunt: HAVE A PROBLEM ...");
    
    this->setAppState(AppState::LOADING);
    
    Director::getInstance()->pushScene(LoadingScene::create());
}

void MyDirector::onGameScene(){
    CCASSERT(Director::getInstance()->getRunningScene(), "hieunt: HAVE A PROBLEM ...");
    
    this->setAppState(AppState::GAME);
    
    Director::getInstance()->pushScene(TransitionFade::create(0.4f, GameScene::create()));
}
