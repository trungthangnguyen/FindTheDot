//
//  MyIAd.h
//
//
//  Created by Hieu Nguyen Trung on 2/15/15.
//
//

#import <Foundation/Foundation.h>
#import <iAd/iAd.h>
#import "../MyAdDefines.h"
#import "AppController.h"
#import "RootViewController.h"

@protocol MyIAdDelegate  <NSObject>
@optional
- (void) myiad_interstitialAdDidCloseWithSender:(id)sender;

@end


@interface MyIAd : NSObject <ADBannerViewDelegate, ADInterstitialAdDelegate> {
    ADBannerView                *_bannerView;
    ADInterstitialAd            *_interstitial;
    UIView                      *_interstitialView;
    
    kMyAdsBannerPosition        _bannerPosition;
    BOOL                        _bannerViewShowed;
    BOOL                        _interstitialShowed;
    
    id<MyIAdDelegate,
    ADBannerViewDelegate,
    ADInterstitialAdDelegate>   _delegate;
}
@property(nonatomic, readonly) ADBannerView *bannerView;
@property(nonatomic, readonly) ADInterstitialAd *interstitial;
@property(nonatomic, readonly) BOOL bannerViewShowed;
@property(nonatomic, readonly) BOOL interstitialShowed;
@property(nonatomic, readwrite) kMyAdsBannerPosition bannerPosition;
@property(nonatomic, assign) id<MyIAdDelegate, ADBannerViewDelegate, ADInterstitialAdDelegate> delegate;

+ (MyIAd *) sharedMyIAd;
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
