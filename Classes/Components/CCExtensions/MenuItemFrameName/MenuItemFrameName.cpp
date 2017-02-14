//
//  MenuItemFrameName.cpp
//  Math100
//
//  Created by Hieu Nguyen Trung on 5/18/14.
//
//

#include "MenuItemFrameName.h"

const unsigned int kZoomActionTag = 12042014;

#pragma mark Initialize
MenuItemFrameName::MenuItemFrameName(){
    _originalScale = 1.0f;
}

MenuItemFrameName * MenuItemFrameName::create(const std::string& filename, const Rect& rect, const ccMenuCallback& callback){
    
    Texture2D::TexParams params = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    
    Sprite *normalSprite = Sprite::create(filename, rect);
    normalSprite->getTexture()->setTexParameters(params);
    
    Sprite *selectedSprite = Sprite::create(filename, rect);
    selectedSprite->getTexture()->setTexParameters(params);
    
    MenuItemFrameName *ret = new MenuItemFrameName();
    
    if (ret) {
        ret->autorelease();
        
        if (ret->initWithNormalSprite(normalSprite, selectedSprite, nullptr, callback)) {
            return ret;
        }
    }
    
    return nullptr;
}

MenuItemFrameName * MenuItemFrameName::create(const char *normalFrameName, const char *selectedFrameName, const ccMenuCallback& callback){
    return MenuItemFrameName::create(normalFrameName, selectedFrameName, nullptr, callback);
}

MenuItemFrameName * MenuItemFrameName::create(const char *normalFrameName, const char *selectedFrameName, const char *disabledFrameName, const ccMenuCallback& callback){
    
    Sprite *normalSprite = nullptr;
    Sprite *selectedSprite = nullptr;
    Sprite *disabledSprite = nullptr;
    
    if (normalFrameName) {
        normalSprite = Sprite::createWithSpriteFrameName(normalFrameName);
    }
    
    if (selectedFrameName) {
        selectedSprite = Sprite::createWithSpriteFrameName(selectedFrameName);
    }
    
    if (disabledFrameName) {
        disabledSprite = Sprite::createWithSpriteFrameName(disabledFrameName);
    }
    
    MenuItemFrameName *ret = new MenuItemFrameName();
    
    if (ret) {
        ret->autorelease();
        
        if (ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback)) {
            return ret;
        }
    }
    
    return nullptr;
}

#pragma mark Zzz
void MenuItemFrameName::activate(){
    if(_enabled){
        this->stopAllActions();
        this->setScale( _originalScale );
        MenuItem::activate();
    }
}

void MenuItemFrameName::selected(){
    // subclass to change the default action
    if(_enabled){
        MenuItem::selected();
        
        Action *action = getActionByTag(kZoomActionTag);
        
        if (action) {
            this->stopAction(action);
        } else {
            _originalScale = this->getScale();
        }
        
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale * 0.9f);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void MenuItemFrameName::unselected(){
    // subclass to change the default action
    if(_enabled){
        MenuItem::unselected();
        this->stopActionByTag(kZoomActionTag);
        Action *zoomAction = ScaleTo::create(0.1f, _originalScale);
        zoomAction->setTag(kZoomActionTag);
        this->runAction(zoomAction);
    }
}

void MenuItemFrameName::setContentSize(cocos2d::Size contentSize){
    MenuItemSprite::setContentSize(contentSize);
    
    if (_normalImage) {
        _normalImage->setPosition(_contentSize.width/2 - _normalImage->getContentSize().width/2, _contentSize.height/2 - _normalImage->getContentSize().height/2);
    }
    
    if (_selectedImage) {
        _selectedImage->setPosition(_contentSize.width/2 - _selectedImage->getContentSize().width/2, _contentSize.height/2 - _selectedImage->getContentSize().height/2);
    }
    
    if (_disabledImage) {
        _disabledImage->setPosition(_contentSize.width/2 - _disabledImage->getContentSize().width/2, _contentSize.height/2 - _disabledImage->getContentSize().height/2);
    }
}

void MenuItemFrameName::setColorOfImages(const cocos2d::Color3B &color){
    if (_normalImage) {
        _normalImage->setColor(color);
    }
    
    if (_selectedImage) {
        _selectedImage->setColor(color);
    }
    
    if (_disabledImage) {
        _disabledImage->setColor(color);
    }
}
