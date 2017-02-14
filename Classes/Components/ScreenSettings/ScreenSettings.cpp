//
//  ScreenSettings.cpp
//
//
//  Created by Hieu Nguyen Trung on 4/28/15.
//
//

#include "ScreenSettings.h"

static ScreenSettings *__sharedScreenSettings__ = nullptr;

#pragma mark Initialize
ScreenSettings * ScreenSettings::getInstance(){
    if (__sharedScreenSettings__ == nullptr) {
        __sharedScreenSettings__ = new ScreenSettings();
        __sharedScreenSettings__->init();
    }
    
    return __sharedScreenSettings__;
}

void ScreenSettings::init(){
    this->resetScreenSettings();
    
    CCLOG("hieunt: realWidth = %f", Director::getInstance()->getOpenGLView()->getFrameSize().width);
    CCLOG("hieunt: realHeight = %f", Director::getInstance()->getOpenGLView()->getFrameSize().height);
    CCLOG("hieunt: designWidth = %f", SS_DESIGN_WIDTH);
    CCLOG("hieunt: designHeight = %f", SS_DESIGN_HEIGHT);
    CCLOG("hieunt: scaleFactor = %f", SS_SCALE_FACTOR);
    CCLOG("hieunt: scaleFactorX = %f", SS_SCALE_FACTOR_X);
    CCLOG("hieunt: scaleFactorY = %f", SS_SCALE_FACTOR_Y);
}

void ScreenSettings::resetScreenSettings(){
    // screenSettings
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    this->resetScreenSettings(frameSize.width, frameSize.height);
}

void ScreenSettings::resetScreenSettings(float width, float height){
    // orientation & standardSize
    if (width > height) {
        _orientationType = OrientationType::LANDSCAPE;
        _standardSize = Size(SS_STANDARD_SIZE_LONG, SS_STANDARD_SIZE_SHORT);
    } else if (width < height) {
        _orientationType = OrientationType::PORTRAIT;
        _standardSize = Size(SS_STANDARD_SIZE_SHORT, SS_STANDARD_SIZE_LONG);
    } else {
        _orientationType = OrientationType::NONE;
    }
    
    // screenType
    this->resetScreenType();
    
    // scaleFactor
    _scaleFactorX = width/_standardSize.width;
    _scaleFactorY = height/_standardSize.height;
    
    if (_screenType == ScreenType::IPHONE) {
        _scaleFactor = 0.5f;
    } else if (_screenType == ScreenType::IPHONE_RETINA) {
        _scaleFactor = 1.0f;
    } else if (_screenType == ScreenType::IPHONE_RETINA_1136) {
        _scaleFactor = 1.0f;
    } else if (_screenType == ScreenType::IPHONE_6) {
        _scaleFactor = MIN(_scaleFactorX, _scaleFactorY);
    } else if (_screenType == ScreenType::IPHONE_6PLUS) {
        _scaleFactor = MIN(_scaleFactorX, _scaleFactorY);
    } else if (_screenType == ScreenType::IPAD) {
        _scaleFactor = 1.0f;
    } else if (_screenType == ScreenType::IPAD_RETINA) {
        _scaleFactor = 2.0f;
    } else if (_screenType == ScreenType::ANDROID_ALL) {
        _scaleFactor = MIN(_scaleFactorX, _scaleFactorY);
    }
    
    // designSize
    float designWidth = roundf(width/_scaleFactor);
    float designHeight = roundf(height/_scaleFactor);
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(designWidth, designHeight, ResolutionPolicy::SHOW_ALL);
    
    // searchPaths - gọi cuối cùng, sau khi đã thiết lập các giá trị scaleFactor, designSize
    this->resetSearchPaths(width, height);
}

void ScreenSettings::resetScreenType(){
    float screenWidth = Director::getInstance()->getOpenGLView()->getFrameSize().width;
    float screenHeight = Director::getInstance()->getOpenGLView()->getFrameSize().height;
    Application::Platform platform = Application::getInstance()->getTargetPlatform();
    
    // iPhone
    if (platform == Application::Platform::OS_IPHONE) {
        if (_orientationType == OrientationType::LANDSCAPE) {
            if (screenHeight < 321.0f) {
                _screenType = ScreenType::IPHONE;
            } else if (screenHeight < 641.0f && screenWidth < 961.0f) {
                _screenType = ScreenType::IPHONE_RETINA;
            } else if (screenHeight < 641.0f && screenWidth < 1137.0f) {
                _screenType = ScreenType::IPHONE_RETINA_1136;
            } else if (screenHeight < 751.0f) {
                _screenType = ScreenType::IPHONE_6;
            } else if (screenHeight < 1243.0f) {
                _screenType = ScreenType::IPHONE_6PLUS;
            }
        } else if (_orientationType == OrientationType::PORTRAIT) {
            if (screenWidth < 321.0f) {
                _screenType = ScreenType::IPHONE;
            } else if (screenWidth < 641.0f && screenHeight < 961.0f) {
                _screenType = ScreenType::IPHONE_RETINA;
            } else if (screenWidth < 641.0f && screenHeight < 1137.0f) {
                _screenType = ScreenType::IPHONE_RETINA_1136;
            } else if (screenWidth < 751.0f) {
                _screenType = ScreenType::IPHONE_6;
            } else if (screenWidth < 1243.0f) {
                _screenType = ScreenType::IPHONE_6PLUS;
            }
        }
        
    // iPad
    } else if (platform == Application::Platform::OS_IPAD) {
        if ((_orientationType == OrientationType::LANDSCAPE && screenWidth < 1025.0f) || (_orientationType == OrientationType::PORTRAIT && screenWidth < 769.0f)) {
            _screenType = ScreenType::IPAD;
        } else {
            _screenType = ScreenType::IPAD_RETINA;
        }
        
    // Android
    } else if (platform == Application::Platform::OS_ANDROID) {
        _screenType = ScreenType::ANDROID_ALL;
    }
}

void ScreenSettings::resetSearchPaths(float width, float height){
    // search paths
    std::vector<std::string> searchPaths;
    
    float shorter = MIN(width, height);
    
    if (shorter < 321.0f) {
        searchPaths.push_back(SS_PATH_SD);
    } else if (shorter < 641.0f) {
        searchPaths.push_back(SS_PATH_HD);
    } else if (shorter < 751.0f) {
        searchPaths.push_back(SS_PATH_IPH6);
    } else {
        searchPaths.push_back(SS_PATH_HDR);
    }
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    
    // resource scale
    float resourceScale = 1.0f;
    
    if (_screenType == ScreenType::IPHONE) {
        resourceScale = _scaleFactor;
    } else if (_screenType == ScreenType::IPHONE_RETINA) {
        resourceScale = _scaleFactor;
    } else if (_screenType == ScreenType::IPHONE_RETINA_1136) {
        resourceScale = _scaleFactor;
    } else if (_screenType == ScreenType::IPHONE_6) {
        resourceScale = _scaleFactor;
    } else if (_screenType == ScreenType::IPHONE_6PLUS) {
        resourceScale = 1280.0f/MIN(SS_DESIGN_WIDTH, SS_DESIGN_HEIGHT);
    } else if (_screenType == ScreenType::IPAD) {
        resourceScale = _scaleFactor;
    } else if (_screenType == ScreenType::IPAD_RETINA) {
        resourceScale = _scaleFactor;
    } else if (_screenType == ScreenType::ANDROID_ALL) {
        float shorter = MIN(SS_DESIGN_WIDTH, SS_DESIGN_HEIGHT);
        
        if (shorter < 321.0f) {
            resourceScale = 320.0f/shorter;
        } else if (shorter < 641.0f) {
            resourceScale = 640.0f/shorter;
        } else if (shorter < 751.0f) {
            resourceScale = 750.0f/shorter;
        } else {
            resourceScale = 1280.0f/shorter;
        }
    }
    
    Director::getInstance()->setContentScaleFactor(resourceScale);
}

#pragma mark Methods
Size ScreenSettings::getDesignSize(){
    return Director::getInstance()->getOpenGLView()->getDesignResolutionSize();
}
