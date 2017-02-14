//
//  Utils.h
//
//
//  Created by Hieu Nguyen Trung
//
//

#include "cocos2d.h"
#include "../__config/MyComponentConfig.h"

#define MYCOMPONENTS_UTILS_NAMESPACE        MYCOMPONENTS_NAMESPACE::Utils
#define MYCOMPONENTS_UTILS_NAMESPACE_BEGIN  MYCOMPONENTS_NAMESPACE_BEGIN namespace Utils {
#define MYCOMPONENTS_UTILS_NAMESPACE_END    }}
#define USING_NS_MYCOMPONENTS_UTILS         using namespace MYCOMPONENTS_UTILS_NAMESPACE

USING_NS_CC;

MYCOMPONENTS_UTILS_NAMESPACE_BEGIN

#pragma mark
// MARK: COLOR
Color3B lightenColor(Color3B color, GLubyte factor);    /* factor càng lớn thì càng gần với màu gốc, càng nhỏ thì càng gần với màu trắng */
Color3B darkenColor(Color3B color, GLubyte factor);     /* factor càng lớn thì càng gần với màu gốc, càng nhỏ thì càng gần với màu đen */

#pragma mark
// MARK: STRING
#pragma mark - trimming
void str_trim1(std::string& str);
void str_trim2(std::string& str);
std::string& str_trim3(std::string& str);

#pragma mark - to upper/lower
std::string str_toUpper(const char *str);
std::string str_toLower(const char *str);
std::string str_toUpper(std::string& str);
std::string str_toLower(std::string& str);

#pragma mark
// MARK: CAPTURE SCREEN
void captureScreen(const std::function<void(Image *image)>& afterCaptured);

#pragma mark
// MARK: ...
void openStore(const char *storeId);
void openDeveloper(const char *devId);
void openGameCenter(const char *leaderBoardId);
void showAlertView(int tag, const char *title, const char *message, const char *cancelButtonTitle, const char *otherButtonTitle);
void displayActivityWithText(const char *text, const char *image, const char *url);

MYCOMPONENTS_UTILS_NAMESPACE_END
