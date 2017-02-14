//
//  MyAdMob.h
//
//
//  Created by Hieu Nguyen Trung on 2/15/15.
//
//

#import <Foundation/Foundation.h>
#import <GoogleMobileAds/GoogleMobileAds.h>
#import "../MyAdDefines.h"
#import "AppController.h"
#import "RootViewController.h"

@interface MyAdMob : NSObject <GADBannerViewDelegate, GADInterstitialDelegate> {
    GADBannerView               *_bannerView;
    GADInterstitial             *_interstitial;
    
    kMyAdsBannerPosition        _bannerPosition;
    BOOL                        _bannerViewShowed;
    BOOL                        _interstitialShowed;
    
    id<GADBannerViewDelegate,
    GADInterstitialDelegate>    _delegate;
}
@property(nonatomic, readonly) GADBannerView *bannerView;
@property(nonatomic, readonly) GADInterstitial *interstitial;
@property(nonatomic, readonly) BOOL interstitialShowed;
@property(nonatomic, readonly) BOOL bannerViewShowed;
@property(nonatomic, readwrite) kMyAdsBannerPosition bannerPosition;
@property(nonatomic, assign) id<GADBannerViewDelegate, GADInterstitialDelegate> delegate;

+ (MyAdMob *) sharedMyAdMob;
+ (AppController *) appController;

#pragma mark Banner
- (void) prepareBannerView;
- (void) showBannerView;
- (void) hideBannerView;
- (void) removeBannerView;

#pragma mark Interstitial
- (void) prepareInterstitialView;
- (void) showInterstitialView;
- (void) hideInterstitialView;
- (void) removeInterstitial;

@end
