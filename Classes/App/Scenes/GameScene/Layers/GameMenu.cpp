//
//  GameMenu.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/13/17.
//
//

#include "GameMenu.h"
#include "../GameScene.h"
#include "../../../Global/GameDefines.h"
#include "../../../Global/Texts.h"
#include "../../../../Components/MyComponents.h"

GameMenu * GameMenu::createWith(GameScene *theGame){
    auto layer = new GameMenu();
    
    if (layer && layer->initWith(theGame)) {
        layer->autorelease();
        return layer;
    }
    
    CC_SAFE_DELETE(layer);
    return nullptr;
}

bool GameMenu::initWith(GameScene *theGame){
    if (Node::init()) {
        _theGame = theGame;
        
        _introLabel = Label::createWithTTF(TEXT_INTRO, GAMEDEF_FONTFILE_TEXT, 24);
        _introLabel->setColor(GAMEDEF_COLOR3B_TEXT);
        _introLabel->setPosition(Point(SS_DESIGN_WIDTH/2, SS_DESIGN_HEIGHT - 24));
        this->addChild(_introLabel);
        
        _scoreLabel = Label::createWithTTF("0", GAMEDEF_FONTFILE_TEXT, 32);
        _scoreLabel->setColor(GAMEDEF_COLOR3B_TEXT);
        _scoreLabel->setPosition(_introLabel->getPosition() - Point(0, 48));
        this->addChild(_scoreLabel);
        
        _noticeLabel = Label::createWithTTF(" ", GAMEDEF_FONTFILE_TEXT, 32);
        _noticeLabel->setColor(GAMEDEF_COLOR3B_TEXT);
        _noticeLabel->setPosition(Point(SS_DESIGN_WIDTH/2, GAMEDEF_GAMEPLAY_MENU_PADDING - 24));
        this->addChild(_noticeLabel);
        
        // lines
        auto topLine = LayerColor::create(Color4B(darkenColor(GAMEDEF_COLOR3B_TEXT, 64)), SS_DESIGN_WIDTH, 4);
        topLine->setPosition(Point(0, SS_DESIGN_HEIGHT - GAMEDEF_GAMEPLAY_MENU_PADDING));
        this->addChild(topLine);
        
        auto bottomLine = LayerColor::create(Color4B(darkenColor(GAMEDEF_COLOR3B_TEXT, 64)), SS_DESIGN_WIDTH, 4);
        bottomLine->setPosition(Point(0, GAMEDEF_GAMEPLAY_MENU_PADDING));
        this->addChild(bottomLine);
        
        return true;
    }
    
    return false;
}

void GameMenu::updateScoreLabel(const int score){
    _scoreLabel->setString(__String::createWithFormat("%d", score)->getCString());
}

void GameMenu::updateNoticeLabel(const char *text){
    _noticeLabel->setString(text);
}
