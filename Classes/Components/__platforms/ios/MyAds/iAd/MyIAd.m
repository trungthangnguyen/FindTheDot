//
//  MyIAd.m
//
//
//  Created by Hieu Nguyen Trung on 2/15/15.
//
//

#import "MyIAd.h"

static MyIAd *__sharedMyIAd = nil;

@implementation MyIAd
@synthesize bannerView = _bannerView;
@synthesize interstitial = _interstitial;
@synthesize bannerViewShowed = _bannerViewShowed;
@synthesize interstitialShowed = _interstitialShowed;
@synthesize bannerPosition = _bannerPosition;
@synthesize delegate = _delegate;

#pragma mark
// MARK: Initialize
+ (MyIAd *) sharedMyIAd{
    if (__sharedMyIAd == nil) {
        @synchronized(self) {
            __sharedMyIAd = [[MyIAd alloc] init];
        }
    }
    
    return __sharedMyIAd;
}

+ (AppController *) appController{
    return (AppController *)[[UIApplication sharedApplication] delegate];
}

#pragma mark
// MARK: BannerView
- (int) getBannerHeight:(UIDeviceOrientation)orientation{
    if (UIDeviceOrientationIsLandscape(orientation)) {  // Landscape
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            return 32;
        } else {
            return 66;
        }
    } else {                                            // Portrait
        if (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone) {
            return 50;
        } else {
            return 66;
        }
    }
}

- (int) getBannerHeight{
    return [self getBannerHeight:[UIDevice currentDevice].orientation];
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
    if (_bannerView) {
        CGRect frame = [_bannerView frame];
        
        if (_bannerPosition == kMyAdsBannerPositionTop) {
            return CGRectMake(0, 0, frame.size.width, frame.size.height);
        } else if (_bannerPosition == kMyAdsBannerPositionBottom) {
            RootViewController *viewController = [MyIAd appController].viewController;
            return CGRectMake(0, viewController.view.frame.size.height - [self getBannerHeight], frame.size.width, frame.size.height);
        }
    }
    
    return CGRectZero;
}

- (CGRect) getBannerFrameOutside{
    if (_bannerView) {
        CGRect frame = [_bannerView frame];
        
        if (_bannerPosition == kMyAdsBannerPositionTop) {
            return CGRectMake(0, -[self getBannerHeight], frame.size.width, frame.size.height);
        } else if (_bannerPosition == kMyAdsBannerPositionBottom) {
            RootViewController *viewController = [MyIAd appController].viewController;
            return CGRectMake(0, viewController.view.frame.size.height, frame.size.width, frame.size.height);
        }
    }
    
    return CGRectZero;
}

- (void) createBannerView{
    if (_bannerView == nil) {
        _bannerView = [[ADBannerView alloc] initWithFrame:CGRectZero];
        [_bannerView setAutoresizingMask:UIViewAutoresizingFlexibleHeight];
        [_bannerView setFrame:[self getBannerFrameOutside]];
        [_bannerView setDelegate:self];
        [[MyIAd appController].viewController.view addSubview:_bannerView];
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
        [_bannerView setAutoresizingMask:UIViewAutoresizingFlexibleHeight];
        
        [UIView beginAnimations:@"fixupIAdBannerView" context:nil];
        
        if (_bannerViewShowed && _bannerView.bannerLoaded) {
            [_bannerView setFrame:[self getBannerFrame]];
        } else {
            [_bannerView setFrame:[self getBannerFrameOutside]];
        }
        
        [UIView commitAnimations];
    }
}

- (void) prepareBannerView{
    [self removeBannerView];
    [self createBannerView];
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

#pragma mark ADBannerViewDelegate
- (void) bannerViewDidLoadAd:(ADBannerView *)banner {
    [self fixupBannerView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(bannerViewDidLoadAd:)]) {
        [_delegate bannerViewDidLoadAd:banner];
    }
}

- (void) bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error{
    [self prepareBannerView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(bannerView:didFailToReceiveAdWithError:)]) {
        [_delegate bannerView:banner didFailToReceiveAdWithError:error];
    }
}

- (void) bannerViewActionDidFinish:(ADBannerView *)banner{
    [self prepareBannerView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(bannerViewActionDidFinish:)]) {
        [_delegate bannerViewActionDidFinish:banner];
    }
}

#pragma mark
// MARK: Interstitial Ad
- (void) createInterstitial {
    if (_interstitial == nil) {
        _interstitial = [[ADInterstitialAd alloc] init];
        [_interstitial setDelegate:self];
        
//        if ([RootViewController versionNumber] >= 7) {
        if ([[UIDevice currentDevice].systemVersion floatValue] >= 7.0f) {
            [MyIAd appController].viewController.interstitialPresentationPolicy = ADInterstitialPresentationPolicyManual;
        }
        
        // interstitialView
        RootViewController *viewController = (RootViewController *)[MyIAd appController].viewController;
        _interstitialView = [[UIView alloc] initWithFrame:viewController.view.bounds];
        [viewController.view addSubview:_interstitialView];
    }
}

- (void) removeInterstitial {
    if (_interstitialView) {
        [_interstitialView removeFromSuperview];
        [_interstitialView release];
        _interstitialView = nil;
    }
    
    if (_interstitial) {
        [_interstitial release];
        _interstitial = nil;
    }
}

- (void) prepareInterstitialView{
    [self removeInterstitial];
    [self createInterstitial];
}

- (void) showInterstitialView{
    _interstitialShowed = YES;
    
    if (_interstitial) {
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

- (void) presentInterstitial{
    if (_interstitialShowed && _interstitial && _interstitial.loaded) {
        [_interstitial presentInView:_interstitialView];
        
        // close button
        UIButton* button = [UIButton buttonWithType:UIButtonTypeCustom];
        button.backgroundColor = [UIColor clearColor];
        button.frame = CGRectMake(8, 8, 32, 32);
        [button addTarget:self action:@selector(closeAd:) forControlEvents:UIControlEventTouchDown];
        [button setBackgroundImage:[UIImage imageNamed:@"myiad_button_close.png"] forState:UIControlStateNormal];
        [_interstitialView addSubview:button];
        
        [UIView beginAnimations:@"animateAdBannerOn" context:nil];
        [UIView setAnimationDuration:1];
        [_interstitialView setAlpha:1];
        [UIView commitAnimations];
    }
}

- (void) closeAd:(id) sender {
#if KEEP_CURRENT_INTERSTITIAL
    [UIView beginAnimations:@"animateAdBannerOff" context:nil];
    [UIView setAnimationDuration:1];
    [_interstitialView setAlpha:0];
    [UIView commitAnimations];
#else
    [self hideInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(myiad_interstitialAdDidCloseWithSender:)]) {
        [_delegate myiad_interstitialAdDidCloseWithSender:sender];
    }
#endif
}

#pragma mark ADInterstitialAdDelegate
- (void) interstitialAdDidLoad:(ADInterstitialAd *) interstitialAd {
    [self presentInterstitial];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialAdDidLoad:)]) {
        [_delegate interstitialAdDidLoad:interstitialAd];
    }
}

- (void) interstitialAd:(ADInterstitialAd *)interstitialAd didFailWithError:(NSError *)error {
    [self prepareInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialAd:didFailWithError:)]) {
        [_delegate interstitialAd:interstitialAd didFailWithError:error];
    }
}

- (void) interstitialAdDidUnload:(ADInterstitialAd *)interstitialAd {
    [self hideInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialAdDidUnload:)]) {
        [_delegate interstitialAdDidUnload:interstitialAd];
    }
}

- (void) interstitialAdActionDidFinish:(ADInterstitialAd *)interstitialAd {
    [self hideInterstitialView];
    
    if (_delegate && [_delegate respondsToSelector:@selector(interstitialAdActionDidFinish:)]) {
        [_delegate interstitialAdActionDidFinish:interstitialAd];
    }
}

#pragma mark
// MARK: dealloc
- (void) dealloc{
    [super dealloc];
    
    [self removeBannerView];
    [self removeInterstitial];
}

@end
