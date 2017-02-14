//
//  Utils-apple.h
//  CanYouTap100
//
//  Created by Hieu Nguyen Trung on 11/7/15.
//
//

class UtilsApple {
    
public:
    static void openStore(const char *storeId);
    static void openDeveloper(const char *devId);
    static void openGameCenter(const char *leaderBoardId = nullptr);
    static void showAlertView(int tag, const char *title, const char *message, const char *cancelButtonTitle, const char *otherButtonTitle);
    static void displayActivityWithText(const char *text, const char *image, const char *url);
};
