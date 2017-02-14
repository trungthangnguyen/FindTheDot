//
//  MyDirector.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/10/17.
//
//

#ifndef MyDirector_h
#define MyDirector_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

#define MYDIRECTOR_INS              MyDirector::getInstance()
#define MYDIRECTOR_GET_APPSTATE     MyDirector::getInstance()->getAppState()

class MyDirector {
public:
    enum class AppState {
        NONE,
        LOADING,
        HOME,
        GAME,
    };
    
private:
    AppState    _appState;
    AppState    _preAppState;
    
    bool init();
    void setAppState(AppState appState);
    
public:
    static MyDirector * getInstance();
    
    AppState getAppState() {return _appState;};
    AppState getPreAppState() {return _preAppState;};
    
    // scenes
    void onLoadingScene();
    void onGameScene();
};

#endif /* MyDirector_h */
