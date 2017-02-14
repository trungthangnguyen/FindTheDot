//
//  LangSystem.h
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 2/8/17.
//
//

#ifndef LangSystem_h
#define LangSystem_h

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

#define LANGSYS_INS         LangType::getInstance();
#define LANGSYS_LANGTYPE    LangSystem::LangType

class LangSystem : public Ref {
public:
    enum class LangType {
        ENGLISH,
        JAPANESE,
        VIETNAMESE,
    };
    
private:
    LANGSYS_LANGTYPE _langType;
    
    bool init();
    
public:
    static LangSystem * getInstance();
    
    LANGSYS_LANGTYPE getLangType() {return _langType;};
    
    bool setLangType(LANGSYS_LANGTYPE type);
};

#endif /* LangSystem_h */
