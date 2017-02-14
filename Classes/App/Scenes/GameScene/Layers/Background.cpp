//
//  Background.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/13/17.
//
//

#include "Background.h"
#include "../GameScene.h"
#include "../../../Global/GameDefines.h"
#include "../../../../Components/MyComponents.h"

Background * Background::createWith(GameScene *theGame){
    auto layer = new Background();
    
    if (layer && layer->initWith(theGame)) {
        layer->autorelease();
        return layer;
    }
    
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool Background::initWith(GameScene *theGame){
    if (Node::init()) {
        _theGame = theGame;
        
        auto bg = LayerColor::create(Color4B(GAMEDEF_COLOR3B_BACKGROUND), SS_DESIGN_WIDTH, SS_DESIGN_HEIGHT);
        bg->setPosition(Point::ZERO);
        this->addChild(bg);
        
        return true;
    }
    
    return false;
}
