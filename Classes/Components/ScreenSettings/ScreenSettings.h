//
//  ScreenSettings.h
//
//
//  Created by Hieu Nguyen Trung on 4/28/15.
//
//

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

#pragma mark
// MARK: Defines
#define SS                      ScreenSettings::getInstance()
#define SS_DESIGN_SIZE          SS->getDesignSize()
#define SS_DESIGN_WIDTH         SS->getDesignSize().width
#define SS_DESIGN_HEIGHT        SS->getDesignSize().height
#define SS_SCALE_FACTOR         SS->getScaleFactor()
#define SS_SCALE_FACTOR_X       SS->getScaleFactorX()
#define SS_SCALE_FACTOR_Y       SS->getScaleFactorY()
#define SS_CENTER               Point(SS_DESIGN_WIDTH/2, SS_DESIGN_HEIGHT/2)

#define SS_STANDARD_SIZE_LONG   1136.0f
#define SS_STANDARD_SIZE_SHORT  640.0f

#define SS_PATH_HD              "images/HD"         // used by iPhone 4+ and iPad non-retina
#define SS_PATH_HDR             "images/HDR"        // used by iPad retina
#define SS_PATH_SD              "images/SD"         // used by old iPhone
#define SS_PATH_IPH6            "images/iPh6"       // used by iPhone 6
//#define SS_PATH_IPH6PLUS        "images/iPh6Plus"        // used by iPhone 6 Plus

class ScreenSettings {
#pragma mark
// MARK: Public methods
public:
    enum class ScreenType {
        NONE,               //
        IPHONE,             // 480 x 320
        IPHONE_RETINA,      // 960 x 640
        IPHONE_RETINA_1136, // 1136 x 640
        IPHONE_6,           // 1334 x 750
        IPHONE_6PLUS,       // 1920 x 1080
        IPAD,               // 1024 x 768
        IPAD_RETINA,        // 2048 x 1536
        ANDROID_ALL,        // not specified - dat ten ANDROID khong build cho Android duoc, chac do tu khoa :))
    };
    
    enum class OrientationType {
        NONE,
        PORTRAIT,
        LANDSCAPE,
    };
    
    static ScreenSettings * getInstance();
    
    ScreenType getScreenType() {return _screenType;};
    OrientationType getOrientationType() {return _orientationType;};
    Size getStandardSize() {return _standardSize;};
    float getScaleFactor() {return _scaleFactor;};
    float getScaleFactorX() {return _scaleFactorX;};
    float getScaleFactorY() {return _scaleFactorY;};
    
    Size getDesignSize();
    void resetScreenSettings();
    
#pragma mark
// MARK: Protected methods
protected:
    ScreenType      _screenType;
    OrientationType _orientationType;
    Size            _standardSize;
    
    float           _scaleFactor;
    float           _scaleFactorX;
    float           _scaleFactorY;
    
    void init();
    void resetScreenType();
    void resetSearchPaths(float width, float height);
    void resetScreenSettings(float width, float height);
};
