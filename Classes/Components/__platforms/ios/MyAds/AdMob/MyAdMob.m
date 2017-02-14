//
//  MyAdMob.m
//
//
//  Created by Hieu Nguyen Trung on 2/15/15.
//
//

#import "MyAdMob.h"

static MyAdMob *__sharedMyAdMob = nil;

@implementation MyAdMob
@synthesize bannerView = _bannerView;
@synthesize interstitial = _interstitial;
@synthesize interstitialShowed = _interstitialShowed;
@synthesize bannerViewShowed = _bannerViewShowed;
@synthesize bannerPosition = _bannerPosition;
@synthesize delegate = _delegate;

#pragma mark Initialize
+ (MyAdMob *) sharedMyAdMob{
    if (__sharedMyAdMob == nil) {
        @synchronized(self) {
            __sharedMyAdMob = [[MyAdMob alloc] init];
        }
    }
    
    return __sharedMyAdMob;
}

+ (AppController *) appController{
    return (AppController *)[[UIApplication sharedApplication] delegate];
}

#pragma mark BannerView
- (GADAdSize) getBannerSize:(UIDeviceOrientation)orientation{
    if (UIDeviceOrientationIsLandscape(orientation)) {  // Landscape
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            return MYADMOB_BANNER_SIZE_IPHONE;
        } else {
            return MYADMOB_BANNER_SIZE_IPAD;
        }
    } else {                                            // Portrait
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            return MYADMOB_BANNER_SIZE_IPHONE;
        } else {
            return MYADMOB_BANNER_SIZE_IPAD;
        }
    }
}

- (GADAdSize) getBannerSize{
    return [self getBannerSize:[UIDevice currentDevice].orientation];
}

/**
 Gốc toạ độ (0, 0) nằm ở mép trái, bên trên của màn hình
    (0, 0) ----> x
    |
    |
    |
    V
    y
 */

- (CGRect) getBannerFrame{
    RootViewController *viewController = [MyAdMob appController].viewController;
    GADAdSize gadSize = [self getBannerSize];
    
    if (_bannerPosition == kMyAdsBannerPositionTop) {
        return CGRectMake(viewController.view.frame.size.width/2 - gadSize.size.width/2,
                          0,
                          gadSize.size.width,
                          gadSize.size.height);
    } else if (_bannerPosition == kMyAdsBannerPositionBottom) {
        return CGRectMake(viewController.view.frame.size.width/2 - gadSize.size.width/2,
                          viewController.view.frame.size.height - gadSize.size.height,
                          gadSize.size.width,
                          gadSize.size.height);
    }
    
    return CGRectZero;
}

- (CGRect) getBannerFrameOutside{
    RootViewController *viewController = [MyAdMob appController].viewController;
    GADAdSize gadSize = [self getBannerSize];
    
    if (_bannerPosition == kMyAdsBannerPositionTop) {
        return CGRectMake(viewController.view.frame.size.width/2 + gadSize.size.width/2,
                          -gadSize.size.height,
                          gadSize.size.width,
                          gadSize.size.height);
    } else if (_bannerPosition == kMyAdsBannerPositionBottom) {
        return CGRectMake(viewController.view.frame.size.width/2 + gadSize.size.width/2,
                          viewController.view.frame.size.height + gadSize.size.height,
                          gadSize.size.width,
                          gadSize.size.height);
    }
    
    return CGRectZero;
}

- (void) createAndLoadBannerView{
    if (_bannerView == nil) {
        RootViewController *viewController = [MyAdMob appController].viewController;
        
        _bannerView = [[GADBannerView alloc] initWithFrame:[self getBannerFrameOutside]];
        _bannerView.delegate = self;
        _bannerView.adUnitID = MYADMOB_AD_UNIT_ID_BANNER;
        _bannerView.rootViewController = viewController;
        [viewController.view addSubview:_bannerView];
        
        GADRequest *request = [GADRequest request];
        request.testDevices = MYADMOB_TEST_DEVICES_ARRAY;
        [_bannerView loadRequest:request];
    }
}

- (void) removeBannerView{
    if (_bannerView) {
        [_bannerView removeFromSuperview];
        [_bannerView release];
        _bannerView = nil;
    }
}

- (void) fixupBannerView{
    if (_bannerView) {
        if (_bannerViewShowed) {
            [_bannerView setFrame:[self getBannerFrame]];
        } else {
            [_bannerView setFrame:[self getBannerFrameOutside]];
        }
    }
}

- (void) prepareBannerView{
    [self removeBannerView];
    [self createAndLoadBannerView];
}

- (void) showBannerView{
    _bannerViewShowed = YES;
    
    if (_bannerView) {
        [self fixupBannerView];
    } else {
        [self prepareBannerView];
    }
}

- (void) hideBannerView{
    if (_bannerViewShowed) {
        _bannerViewShowed = NO;
        [self prepareBannerView];
    }
}

#pragma mark GADBannerViewDelegate
- (void)adViewDidReceiveAd:(GADBannerView *)view{
    [self fixupBannerView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(adViewDidReceiveAd:)]) {
        [_delegate adViewDidReceiveAd:view];
    }
}

- (void)adView:(GADBannerView *)view didFailToReceiveAdWithError:(GADRequestError *)error{
    [self prepareBannerView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(adView:didFailToReceiveAdWithError:)]) {
        [_delegate adView:view didFailToReceiveAdWithError:error];
    }
}

- (void)adViewWillLeaveApplication:(GADBannerView *)adView{
    [self prepareBannerView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(adViewWillLeaveApplication:)]) {
        [_delegate adViewWillLeaveApplication:adView];
    }
}

#pragma mark Interstitial Ad
- (void ) createAndLoadInterstitial{
    if (_interstitial == nil) {
        _interstitial = [[GADInterstitial alloc] initWithAdUnitID:MYADMOB_AD_UNIT_ID_INTERSTITIAL];
        _interstitial.delegate = self;
        
        GADRequest *request = [GADRequest request];
        request.testDevices = MYADMOB_TEST_DEVICES_ARRAY;
        [_interstitial loadRequest:request];
    }
}

- (void) presentInterstitial{
    if (_interstitialShowed && _interstitial && _interstitial.isReady) {
        [_interstitial presentFromRootViewController:[MyAdMob appController].viewController];
    }
}

- (void) removeInterstitial{
    if (_interstitial) {
        if (_interstitial.hasBeenUsed) {
            [[MyAdMob appController].viewController dismissViewControllerAnimated:YES completion:NULL];
        }
        
        [_interstitial release];
        _interstitial = nil;
    }
}

- (void) prepareInterstitialView{
    [self removeInterstitial];
    [self createAndLoadInterstitial];
}

- (void) showInterstitialView{
    _interstitialShowed = YES;
    
    if (_interstitial && _interstitial.isReady) {
        [self presentInterstitial];
    } else {
        [self prepareInterstitialView];
    }
}

- (void) hideInterstitialView{
    if (_interstitialShowed) {
        _interstitialShowed = NO;
        [self prepareInterstitialView];
    }
}

#pragma mark GADInterstitialDelegate
- (void) interstitialDidReceiveAd:(GADInterstitial *)ad{
    [self presentInterstitial];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialDidReceiveAd:)]) {
        [_delegate interstitialDidReceiveAd:ad];
    }
}

- (void) interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error{
    [self prepareInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitial:didFailToReceiveAdWithError:)]) {
        [_delegate interstitial:ad didFailToReceiveAdWithError:error];
    }
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad{
    [self hideInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialDidDismissScreen:)]) {
        [_delegate interstitialDidDismissScreen:ad];
    }
}

- (void)interstitialWillLeaveApplication:(GADInterstitial *)ad{
    [self hideInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialWillLeaveApplication:)]) {
        [_delegate interstitialWillLeaveApplication:ad];
    }
}

#pragma mark dealoc
- (void) dealloc{
    [super dealloc];
    
    [self removeBannerView];
    [self removeInterstitial];
}

@end
