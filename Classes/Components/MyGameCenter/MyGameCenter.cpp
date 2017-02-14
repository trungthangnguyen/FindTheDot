//
//  MyGameCenter.cpp
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/16/15.
//
//

#include "MyGameCenter.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "../__platforms/ios/MyGameCenter-apple.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// ...
#endif

MYCOMPONENTS_NAMESPACE_BEGIN

bool MyGameCenter::isGameCenterAvailable(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    return MyGameCenterApple::isGameCenterAvailable();
#endif
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    // ...
#endif
    
    return false;
}

void MyGameCenter::authenticateLocalUser(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyGameCenterApple::authenticateLocalUser();
#endif
}

void MyGameCenter::reportScoreForCategory(long score, const char *category){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyGameCenterApple::reportScoreForCategory(score, category);
#endif
}

void MyGameCenter::reloadHighScoresForCategory(const char *category){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyGameCenterApple::reloadHighScoresForCategory(category);
#endif
}

void MyGameCenter::submitAchievementWithPercentComplete(const char *identifier, double percentComplete){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyGameCenterApple::submitAchievementWithPercentComplete(identifier, percentComplete);
#endif
}

void MyGameCenter::resetAchievements(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyGameCenterApple::resetAchievements();
#endif
}

void MyGameCenter::mapPlayerIDtoPlayer(const char *playerID){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    MyGameCenterApple::mapPlayerIDtoPlayer(playerID);
#endif
}

MYCOMPONENTS_NAMESPACE_END
