//
//  MyGameCenter.h
//
//
//  Created by Hieu Nguyen Trung on 11/16/15.
//
//

#include "../__config/MyComponentConfig.h"

MYCOMPONENTS_NAMESPACE_BEGIN

class MyGameCenter {
    
public:
    static bool isGameCenterAvailable();
    static void authenticateLocalUser();
    static void reportScoreForCategory(long score, const char *category);
    static void reloadHighScoresForCategory(const char *category);
    static void submitAchievementWithPercentComplete(const char *identifier, double percentComplete);
    static void resetAchievements();
    static void mapPlayerIDtoPlayer(const char *playerID);
};

MYCOMPONENTS_NAMESPACE_END
