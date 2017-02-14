//
//  MyInAppPurchase.cpp
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/25/15.
//
//

#include "MyInAppPurchase.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "../__platforms/ios/MyInAppPurchase-apple.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// ...
#endif

MYCOMPONENTS_NAMESPACE_BEGIN

void MyInAppPurchase::init(std::vector<const char *> identifiers){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyInAppPurchaseApple::init(identifiers);
#endif
}

void MyInAppPurchase::setDelegate(MyInAppPurchaseDelegate *delegate){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyInAppPurchaseApple::setDelegate(delegate);
#endif
}

void MyInAppPurchase::removeDelegate(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyInAppPurchaseApple::removeDelegate();
#endif
}

std::vector<const char *> MyInAppPurchase::getProductIdentifiers(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return MyInAppPurchaseApple::getProductIdentifiers();
#endif
}

bool MyInAppPurchase::isProductPurchased(const char *identifier){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return MyInAppPurchaseApple::isProductPurchased(identifier);
#endif
}

void MyInAppPurchase::reloadPurchase(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyInAppPurchaseApple::reloadPurchase();
#endif
}

void MyInAppPurchase::onRestorePurchased(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyInAppPurchaseApple::onRestorePurchased();
#endif
}

void MyInAppPurchase::onPurchaseProduct(const char *identifier){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyInAppPurchaseApple::onPurchaseProduct(identifier);
#endif
}

MYCOMPONENTS_NAMESPACE_END
