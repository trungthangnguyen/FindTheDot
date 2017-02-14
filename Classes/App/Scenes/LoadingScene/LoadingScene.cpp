//
//  LoadingScene.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/10/17.
//
//

#include "LoadingScene.h"
#include "../../MyDirector.h"
#include "../../Global/GameDefines.h"
#include "../../Global/LangSystem.h"
#include "../../../Components/MyComponents.h"

bool LoadingScene::init(){
    if (Scene::init()) {
        ScreenSettings::getInstance();
        
        // background
        auto bg = LayerColor::create(Color4B(GAMEDEF_COLOR3B_BACKGROUND), SS_DESIGN_WIDTH, SS_DESIGN_HEIGHT);
        bg->setPosition(Point::ZERO);
        this->addChild(bg);
        
        // logo
        auto studioLbl = Label::createWithTTF("LittleFire Studio", GAMEDEF_FONTFILE_TEXT, 32);
        studioLbl->setColor(GAMEDEF_COLOR3B_TEXT);
        studioLbl->setPosition(SS_CENTER);
        this->addChild(studioLbl);
        
        // load resources
        this->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=](){this->loadResources();}), NULL));
        
        return true;
    }
    
    return false;
}

void LoadingScene::loadResources(){
    srand((unsigned)time(NULL));
    
    MyUserDefaults::getInstance();
    SoundSystem::getInstance();
    LangSystem::getInstance();
    
    MYDIRECTOR_INS->onGameScene();
}

Node * LoadingScene::logoCompany(){
    return LayerColor::create(Color4B::RED, 64, 64);
}
