//
//  MenuItemFrameName.h
//  Math100
//
//  Created by Hieu Nguyen Trung on 5/18/14.
//
//

#ifndef __Math100__MenuItemFrameName__
#define __Math100__MenuItemFrameName__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class MenuItemFrameName : public MenuItemSprite {
protected:
    float _originalScale;
    
    MenuItemFrameName();
    
public:
    static MenuItemFrameName * create(const std::string& filename, const cocos2d::Rect& rect, const ccMenuCallback& callback);
    static MenuItemFrameName * create(const char *normalFrameName, const char *selectedFrameName, const ccMenuCallback& callback);
    static MenuItemFrameName * create(const char *normalFrameName, const char *selectedFrameName, const char *disabledFrameName, const ccMenuCallback& callback);
    
    virtual void activate();
    virtual void selected();
    virtual void unselected();
    virtual void setContentSize(cocos2d::Size contentSize);
    virtual void setColorOfImages(const cocos2d::Color3B &color);
    
};

#endif /* defined(__Math100__MenuItemFrameName__) */
