//
//  MyInAppPurchase-apple.m
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/25/15.
//
//

#include "MyInAppPurchase-apple.h"

#import "InAppPurchase/IAPManager.h"

static std::vector<const char *> __productIdentifiers__ = std::vector<const char *>{};
static IAPManager * __iapManagerInstance__ = nil;

static IAPManager * IAPMANAGER_INSTANCE(){
    if (__iapManagerInstance__ == nil && __productIdentifiers__.size() > 0) {
        NSMutableSet *idSet = [NSMutableSet set];
        
        for (int i=0; i<__productIdentifiers__.size(); i++) {
            [idSet addObject:[NSString stringWithUTF8String:__productIdentifiers__.at(i)]];
        }
        
        __iapManagerInstance__ = [[IAPManager alloc] initWithProductIdentifiers:idSet];
    }
    
    return __iapManagerInstance__;
}

void MyInAppPurchaseApple::init(std::vector<const char *> identifiers){
    __productIdentifiers__ = identifiers;
    IAPMANAGER_INSTANCE();
}

void MyInAppPurchaseApple::setDelegate(MyInAppPurchaseDelegate *delegate){
    if (IAPMANAGER_INSTANCE()) {
        IAPMANAGER_INSTANCE().delegate = delegate;
    }
}

void MyInAppPurchaseApple::removeDelegate(){
    MyInAppPurchaseApple::setDelegate(nullptr);
}

std::vector<const char *> MyInAppPurchaseApple::getProductIdentifiers(){
    return __productIdentifiers__;
}

bool MyInAppPurchaseApple::isProductPurchased(const char *identifier){
    return [IAPMANAGER_INSTANCE() isProductPurchased:[NSString stringWithFormat:@"%s", identifier]];
}

void MyInAppPurchaseApple::reloadPurchase(){
    [IAPMANAGER_INSTANCE() reloadPurchase];
}

void MyInAppPurchaseApple::onRestorePurchased(){
    [IAPMANAGER_INSTANCE() onRestorePurchased];
}

void MyInAppPurchaseApple::onPurchaseProduct(const char *identifier){
    [IAPMANAGER_INSTANCE() onPurchaseProduct:[NSString stringWithFormat:@"%s", identifier]];
}
