//
//  MyAds.cpp
//
//
//  Created by Hieu Nguyen Trung on 2/14/15.
//
//

#include "MyAds.h"
#include "AdMob/MyAdMob.h"
#include "iAd/MyIAd.h"

using namespace MYADS_NAMESPACE;

@interface MyIAdDelegate : NSObject <MyIAdDelegate, ADBannerViewDelegate, ADInterstitialAdDelegate> {
    MyAds *_myAds;
}
@property(nonatomic, assign) MyAds *myAds;

@end

@interface MyAdMobDelegate : NSObject <GADBannerViewDelegate, GADInterstitialDelegate> {
//@interface MyAdMobDelegate : NSObject <ADBannerViewDelegate, ADInterstitialAdDelegate> {
    MyAds *_myAds;
}
@property(nonatomic, assign) MyAds *myAds;

@end

static MyAds            *__sharedMyAds = nullptr;
static MyIAdDelegate    *__sharedMyIAdDelegate = nil;
static MyAdMobDelegate  *__sharedMyAdMobDelegate = nil;

#pragma mark
// MARK: MyIAdDelegate
@implementation MyIAdDelegate
@synthesize myAds = _myAds;

+ (MyIAdDelegate *) sharedMyIAdDelegate{
    if (__sharedMyIAdDelegate == nil) {
        @synchronized(self) {
            __sharedMyIAdDelegate = [[MyIAdDelegate alloc] init];
        }
    }
    
    return __sharedMyIAdDelegate;
}

#pragma mark -- Interstitial
- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd{
    if (_myAds && _myAds->getBannerService() == MyAdsBannerService::ADMOB) {
        [[MyIAd sharedMyIAd] removeInterstitial];
    }
}

- (void) interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error {
    // nothing
}

- (void) interstitialAdActionDidFinish:(ADInterstitialAd *)interstitialAd {
    if (_myAds && _myAds->getBannerService() == MyAdsBannerService::ADMOB) {
        [[MyIAd sharedMyIAd] removeInterstitial];
    }
}

- (void) myiad_interstitialAdDidCloseWithSender:(id)sender{
    if (_myAds && _myAds->getBannerService() == MyAdsBannerService::ADMOB) {
        [[MyIAd sharedMyIAd] removeInterstitial];
    }
}

#pragma mark -- Banner
- (void)bannerViewDidLoadAd:(ADBannerView *)banner{
    if (_myAds && _myAds->getBannerService() == MyAdsBannerService::IAD) {
        _myAds->hideAdMobBannerView();
    }
}

@end

#pragma mark
// MARK: MyAdMobDelegate
@implementation MyAdMobDelegate
@synthesize myAds = _myAds;

+ (MyAdMobDelegate *) sharedMyAdMobDelegate{
    if (__sharedMyAdMobDelegate == nil) {
        @synchronized(self) {
            __sharedMyAdMobDelegate = [[MyAdMobDelegate alloc] init];
        }
    }
    
    return __sharedMyAdMobDelegate;
}

- (void)interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd{
    // chưa biết code gì vào đây?
}

- (void)interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error{
    // nothing
}

@end

MYADS_NAMESPACE_BEGIN

#pragma mark
// MARK: MyAds
MyAds * MyAds::getInstance(){
    if (__sharedMyAds == nullptr) {
        __sharedMyAds = new MyAds();
        __sharedMyAds->init();
    }
    
    return __sharedMyAds;
}

bool MyAds::init(){
    srand((unsigned)time(NULL));
    
    _bannerService = MyAdsBannerService::NONE;
    _interstitialService = MyAdsInterstitialService::NONE;
    
    // delegates
    [MyAdMobDelegate sharedMyAdMobDelegate].myAds = this;
    [MyIAdDelegate sharedMyIAdDelegate].myAds = this;
    
    // AdMob
    [MyAdMob sharedMyAdMob].delegate = [MyAdMobDelegate sharedMyAdMobDelegate];
    [MyAdMob sharedMyAdMob].bannerPosition = MYADS_BANNER_POSITION;
    
    // iAd
    [MyIAd sharedMyIAd].delegate = [MyIAdDelegate sharedMyIAdDelegate];
    [MyIAd sharedMyIAd].bannerPosition = MYADS_BANNER_POSITION;
    
    // không gọi prepare iAb và AdMob ở đây vì có thể gặp phải trường hợp show AdMob banner mà không click được!!!
    
    return true;
}

#pragma mark -- General
void MyAds::showBannerView(){
    /**
     - Vì iAd không có hiệu lực ở một số quốc gia nên nếu show iAd banner
     thì cùng lúc cũng show thêm cả AdMob banner, khi nào bannerViewDidLoadAd
     của iAd được gọi thì tắt AdMob banner đi.
     */
    
    if (MYADS_RANDOM_0_1() < MYADS_RATIO_AD_MOB_BANNER) {
        _bannerService = MyAdsBannerService::ADMOB;
        this->showAdMobBannerView();
        this->hideIAdBannerView();
        
    } else {
        _bannerService = MyAdsBannerService::IAD;
        this->showIAdBannerView();
        
        if ([MyIAd sharedMyIAd].bannerView.bannerLoaded == NO) {
            this->showAdMobBannerView();
        } else {
            this->hideAdMobBannerView();
        }
    }
}

void MyAds::hideBannerView(){
    this->hideAdMobBannerView();
    this->hideIAdBannerView();
}

void MyAds::removeBannerView(){
    this->removeAdMobBannerView();
    this->removeIAdBannerView();
}

void MyAds::showInterstitialView(){
    if (MYADS_RANDOM_0_1() < MYADS_RATIO_AD_MOB_INTERSTITIAL) {
        _interstitialService = MyAdsInterstitialService::ADMOB;
        this->showAdMobInterstitialView();
    } else {
        _interstitialService = MyAdsInterstitialService::IAD;
        this->showIAdInterstitialView();
    }
}

void MyAds::hideInterstitialView(){
    this->hideAdMobInterstitialView();
    this->hideIAdInterstitialView();
}

void MyAds::removeInterstitial(){
    this->removeAdMobInterstitialView();
    this->removeIAdInterstitialView();
}

#pragma mark -- iAd
void MyAds::showIAdBannerView(){
    [[MyIAd sharedMyIAd] showBannerView];
}

void MyAds::hideIAdBannerView(){
    [[MyIAd sharedMyIAd] hideBannerView];
}

void MyAds::removeIAdBannerView(){
    [[MyIAd sharedMyIAd] removeBannerView];
}

void MyAds::showIAdInterstitialView(){
    [[MyIAd sharedMyIAd] showInterstitialView];
}

void MyAds::hideIAdInterstitialView(){
    [[MyIAd sharedMyIAd] hideInterstitialView];
}

void MyAds::removeIAdInterstitialView(){
    [[MyIAd sharedMyIAd] removeInterstitial];
}

#pragma mark -- AdMob
void MyAds::showAdMobBannerView(){
    [[MyAdMob sharedMyAdMob] showBannerView];
}

void MyAds::hideAdMobBannerView(){
    [[MyAdMob sharedMyAdMob] hideBannerView];
}

void MyAds::removeAdMobBannerView(){
    [[MyAdMob sharedMyAdMob] removeBannerView];
}

void MyAds::showAdMobInterstitialView(){
    [[MyAdMob sharedMyAdMob] showInterstitialView];
}

void MyAds::hideAdMobInterstitialView(){
    [[MyAdMob sharedMyAdMob] hideInterstitialView];
}

void MyAds::removeAdMobInterstitialView(){
    [[MyAdMob sharedMyAdMob] removeInterstitial];
}

MYADS_NAMESPACE_END
