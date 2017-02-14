//
//  MyAds.h
//
//
//  Created by Hieu Nguyen Trung on 2/14/15.
//
//

#include <stdio.h>
#include "MyAdDefines.h"

MYADS_NAMESPACE_BEGIN

#define MYADS_RANDOM_0_1() ((float)rand()/RAND_MAX)

enum class MyAdsBannerService {
    NONE,
    IAD,
    ADMOB,
};

enum class MyAdsInterstitialService {
    NONE,
    IAD,
    ADMOB,
};

class MyAds {
private:
    MyAdsBannerService          _bannerService;
    MyAdsInterstitialService    _interstitialService;
    
    bool init();
    
public:
    static MyAds * getInstance();
    
    MyAdsBannerService getBannerService() {return _bannerService;};
    MyAdsInterstitialService getInterstitialService() {return _interstitialService;};

#pragma mark General
    void showBannerView();
    void hideBannerView();
    void removeBannerView();
    void showInterstitialView();
    void hideInterstitialView();
    void removeInterstitial();
    
#pragma mark iAd
    void showIAdBannerView();
    void hideIAdBannerView();
    void removeIAdBannerView();
    void showIAdInterstitialView();
    void hideIAdInterstitialView();
    void removeIAdInterstitialView();
    
#pragma mark AdMob
    void showAdMobBannerView();
    void hideAdMobBannerView();
    void removeAdMobBannerView();
    void showAdMobInterstitialView();
    void hideAdMobInterstitialView();
    void removeAdMobInterstitialView();
};

MYADS_NAMESPACE_END
