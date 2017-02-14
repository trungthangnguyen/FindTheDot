//
//  MyAds.cpp
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/27/15.
//
//

#include "MyAds.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "../__platforms/ios/MyAds/MyAds.h"
#endif

MYCOMPONENTS_NAMESPACE_BEGIN

void MyAds::showBannerView(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MYADS_NAMESPACE::MyAds::getInstance()->showBannerView();
#endif
}

void MyAds::hideBannerView(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MYADS_NAMESPACE::MyAds::getInstance()->hideBannerView();
#endif
}

void MyAds::removeBannerView(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MYADS_NAMESPACE::MyAds::getInstance()->removeBannerView();
#endif
}

void MyAds::showInterstitialView(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MYADS_NAMESPACE::MyAds::getInstance()->showInterstitialView();
#endif
}

void MyAds::hideInterstitialView(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MYADS_NAMESPACE::MyAds::getInstance()->hideInterstitialView();
#endif
}

void MyAds::removeInterstitial(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MYADS_NAMESPACE::MyAds::getInstance()->removeInterstitial();
#endif
}

MYCOMPONENTS_NAMESPACE_END
