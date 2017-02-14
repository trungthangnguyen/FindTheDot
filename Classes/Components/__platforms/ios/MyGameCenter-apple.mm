//
//  MyGameCenter-apple.m
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/16/15.
//
//

#include "MyGameCenter-apple.h"

#import "GameCenter/GameCenterManager.h"

bool MyGameCenterApple::isGameCenterAvailable(){
    return [GameCenterManager isGameCenterAvailable];
}

void MyGameCenterApple::authenticateLocalUser(){
    if ([GameCenterManager isGameCenterAvailable]) {
        auto gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
        
        if (gameCenterManager) {
            [gameCenterManager authenticateLocalUser];
        }
    }
}

void MyGameCenterApple::reportScoreForCategory(long score, const char *category){
    if ([GameCenterManager isGameCenterAvailable]) {
        auto gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
        
        if (gameCenterManager) {
            [gameCenterManager reportScore:score forCategory:[NSString stringWithFormat:@"%s", category]];
        }
    }
}

void MyGameCenterApple::reloadHighScoresForCategory(const char *category){
    if ([GameCenterManager isGameCenterAvailable]) {
        auto gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
        
        [gameCenterManager reloadHighScoresForCategory:[NSString stringWithFormat:@"%s", category]];
    }
}

void MyGameCenterApple::submitAchievementWithPercentComplete(const char *identifier, double percentComplete){
    if ([GameCenterManager isGameCenterAvailable]) {
        auto gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
        
        [gameCenterManager submitAchievement:[NSString stringWithFormat:@"%s", identifier] percentComplete:percentComplete];
    }
}

void MyGameCenterApple::resetAchievements(){
    if ([GameCenterManager isGameCenterAvailable]) {
        auto gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
        
        [gameCenterManager resetAchievements];
    }
}

void MyGameCenterApple::mapPlayerIDtoPlayer(const char *playerID){
    if ([GameCenterManager isGameCenterAvailable]) {
        auto gameCenterManager = [[[GameCenterManager alloc] init] autorelease];
        
        [gameCenterManager mapPlayerIDtoPlayer:[NSString stringWithFormat:@"%s", playerID]];
    }
}


