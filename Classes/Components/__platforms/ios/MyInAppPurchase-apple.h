//
//  MyInAppPurchase-apple.h
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/25/15.
//
//

#include <vector>

class MyInAppPurchaseDelegate;

class MyInAppPurchaseApple {
    
public:
    static std::vector<const char *> getProductIdentifiers();
    static bool isProductPurchased(const char *identifier);
    
    static void init(std::vector<const char *> identifiers);
    static void setDelegate(MyInAppPurchaseDelegate *delegate);
    static void removeDelegate();
    static void reloadPurchase();
    static void onRestorePurchased();
    static void onPurchaseProduct(const char *identifier);
};
