//
//  Utils-apple.m
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/7/15.
//
//

#include "Utils-apple.h"
#import "RootViewController.h"

void UtilsApple::openStore(const char *storeId){
    NSString *url = [NSString stringWithFormat:@"https://itunes.apple.com/us/app/id%@?mt=8", [NSString stringWithUTF8String:storeId]];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:url]];
}

void UtilsApple::openDeveloper(const char *devId){
    // devId của LittleFire Studio là 555328464
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:[NSString stringWithFormat:@"itms://itunes.apple.com/us/developer/littlefire-studio/id%s", devId]]];
}

void UtilsApple::openGameCenter(const char *leaderBoardId){
    GKGameCenterViewController *gameCenterViewController = [[[GKGameCenterViewController alloc] init] autorelease];
    
    if (gameCenterViewController) {
        RootViewController *rootViewController = (RootViewController *)[UIApplication sharedApplication].keyWindow.rootViewController;
        
        if (leaderBoardId) {
            gameCenterViewController.leaderboardCategory = [NSString stringWithFormat:@"%s", leaderBoardId];
        }
        
        gameCenterViewController.leaderboardTimeScope = GKLeaderboardTimeScopeAllTime;
        gameCenterViewController.gameCenterDelegate = rootViewController;
        
        [rootViewController presentViewController:gameCenterViewController animated:YES completion:nil];
    }
}

void UtilsApple::showAlertView(int tag, const char *title, const char *message, const char *cancelButtonTitle, const char *otherButtonTitle){
    NSString *titleStr = nil;
    if (title) {
        titleStr = [NSString stringWithUTF8String:title];
    }
    
    NSString *messageStr = nil;
    if (message) {
        messageStr = [NSString stringWithUTF8String:message];
    }
    
    NSString *cancelButtonTitleStr = nil;
    if (cancelButtonTitle) {
        cancelButtonTitleStr = [NSString stringWithUTF8String:cancelButtonTitle];
    }
    
    NSString *otherButtonTitleStr = nil;
    if (otherButtonTitle) {
        otherButtonTitleStr = [NSString stringWithUTF8String:otherButtonTitle];
    }
    
    // alertView
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:titleStr
                                                        message:messageStr
                                                       delegate:[UIApplication sharedApplication].keyWindow.rootViewController
                                              cancelButtonTitle:cancelButtonTitleStr
                                              otherButtonTitles:otherButtonTitleStr, nil];
    [alertView setTag:tag];
    [alertView show];
    [alertView release];
}

void UtilsApple::displayActivityWithText(const char *text, const char *image, const char *url){
    RootViewController *rootViewController = (RootViewController *)[UIApplication sharedApplication].keyWindow.rootViewController;
    
    NSArray *activityItems = [NSArray arrayWithObjects:[NSString stringWithFormat:@"%s", text], [UIImage imageNamed:[NSString stringWithFormat:@"%s", image]], [NSURL URLWithString:[NSString stringWithFormat:@"%s", url]], nil];
//    NSArray *activityTypes = [NSArray arrayWithObjects:nil];
//    NSArray *activityTypes = [NSArray array];
    
    UIActivityViewController *activityVC = [[UIActivityViewController alloc] initWithActivityItems:activityItems applicationActivities:nil];
//    activityVC.excludedActivityTypes = activityTypes;
    [rootViewController presentViewController:activityVC animated:YES completion:nil];
    
    if ([activityVC respondsToSelector:@selector(popoverPresentationController)]){
        // iOS 8+
        UIPopoverPresentationController *presentationController = [activityVC popoverPresentationController];
        presentationController.sourceView = rootViewController.view;
    }
    
    [activityVC release];
}
