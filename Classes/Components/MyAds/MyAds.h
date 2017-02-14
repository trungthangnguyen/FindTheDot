//
//  MyAds.hpp
//
//
//  Created by Hieu Nguyen Trung on 11/27/15.
//
//

#include <stdio.h>
#include "../__config/MyComponentConfig.h"

MYCOMPONENTS_NAMESPACE_BEGIN

class MyAds {
    
public:
    static void showBannerView();
    static void hideBannerView();
    static void removeBannerView();
    static void showInterstitialView();
    static void hideInterstitialView();
    static void removeInterstitial();
};

MYCOMPONENTS_NAMESPACE_END
