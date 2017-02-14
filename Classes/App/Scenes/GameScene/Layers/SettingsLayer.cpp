//
//  SettingsLayer.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/13/17.
//
//

#include "SettingsLayer.h"
#include "../GameScene.h"

SettingsLayer * SettingsLayer::createWith(GameScene *theGame){
    auto layer = new SettingsLayer();
    
    if (layer && layer->initWith(theGame)) {
        layer->autorelease();
        return layer;
    }
    
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool SettingsLayer::initWith(GameScene *theGame){
    if (Node::init()) {
        _theGame = theGame;
        
        return true;
    }
    
    return false;
}
