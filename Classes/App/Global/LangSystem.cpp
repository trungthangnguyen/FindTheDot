//
//  LangSystem.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/8/17.
//
//

#include "LangSystem.h"
#include "GameDefines.h"
#include "../../Components/MyComponents.h"

static LangSystem * __sharedLangSystem__ = nullptr;

LangSystem * LangSystem::getInstance(){
    if (__sharedLangSystem__ == nullptr) {
        __sharedLangSystem__ = new LangSystem();
        __sharedLangSystem__->init();
    }
    
    return __sharedLangSystem__;
}

bool LangSystem::init(){
    _langType = (LANGSYS_LANGTYPE) MyUserDefaults::getInstance()->getIntegerForKey(NSUD_CUR_LANG_TYPE);
    
    return true;
}

bool LangSystem::setLangType(LANGSYS_LANGTYPE type){
    if (_langType != type) {
        _langType = type;
        
        MyUserDefaults::getInstance()->setIntegerForKey(NSUD_CUR_LANG_TYPE, (int)_langType);
        
        return true;
    }
    
    return false;
}
