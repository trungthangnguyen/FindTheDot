//
//  Utils.cpp
//  FindTheDot
//
//  Created by Hieu Nguyen Trung on 5/18/15.
//
//

#include "Utils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#include "../__platforms/ios/Utils-apple.h"
#endif

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
// ...
#endif

MYCOMPONENTS_UTILS_NAMESPACE_BEGIN

#pragma mark
// MARK: COLOR
Color3B lightenColor(Color3B color, GLubyte factor){
    float p = ((float)factor) / 255.0f;
    Color3B wColor = Color3B(255, 255, 255);
    
    return Color3B((1.0f - p)*wColor.r + p*color.r, (1.0f - p)*wColor.g + p*color.g, (1.0f - p)*wColor.b + p*color.b);
}

Color3B darkenColor(Color3B color, GLubyte factor){
    float p = ((float)factor) / 255.0f;
    Color3B wColor = Color3B(0, 0, 0);
    
    return Color3B((1.0f - p)*wColor.r + p*color.r, (1.0f - p)*wColor.g + p*color.g, (1.0f - p)*wColor.b + p*color.b);
}

#pragma mark
// MARK: STRING
#pragma mark - trimming
void str_trim1(std::string& str){
    std::string::size_type pos1 = str.find_first_not_of(' ');
    std::string::size_type pos2 = str.find_last_not_of(' ');
    
    str = str.substr(pos1 == std::string::npos ? 0 : pos1,
                     pos2 == std::string::npos ? str.length() - 1 : pos2 - pos1 + 1);
}

void str_trim2(std::string& str){       /* faster than trim1 method */
    std::string::size_type pos = str.find_last_not_of(' ');
    
    if(pos != std::string::npos) {
        str.erase(pos + 1);
        pos = str.find_first_not_of(' ');
        
        if(pos != std::string::npos){
            str.erase(0, pos);
        }
    } else {
        str.erase(str.begin(), str.end());
    }
}

std::string& str_trim3(std::string& str){   /* C++ v11 */
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](char& ch)->bool { return !isspace(ch); }));
    str.erase(find_if(str.rbegin(), str.rend(), [](char& ch)->bool { return !isspace(ch); }).base(), str.end());
    
    return str;
}

#pragma mark - to upper/lower
std::string str_toUpper(const char *str){
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    
    return s;
}

std::string str_toLower(const char *str){
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    return s;
}

std::string str_toUpper(std::string& str){
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    
    return s;
}

std::string str_toLower(std::string& str){
    std::string s = str;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    
    return s;
}

#pragma mark
// MARK: CAPTURE SCREEN
void onCaptureScreen(const std::function<void(Image*)>& afterCaptured)
{
    auto glView = Director::getInstance()->getOpenGLView();
    auto frameSize = glView->getFrameSize();
    
    int width = static_cast<int>(frameSize.width);
    int height = static_cast<int>(frameSize.height);
    
    Image *image = new Image();
    image->autorelease();
    
    do
    {
        std::shared_ptr<GLubyte> buffer(new GLubyte[width * height * 4], [](GLubyte* p){ CC_SAFE_DELETE_ARRAY(p); });
        if (!buffer)
        {
            break;
        }
        
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.get());
        
        std::shared_ptr<GLubyte> flippedBuffer(new GLubyte[width * height * 4], [](GLubyte* p) { CC_SAFE_DELETE_ARRAY(p); });
        if (!flippedBuffer)
        {
            break;
        }
        
        for (int row = 0; row < height; ++row)
        {
            memcpy(flippedBuffer.get() + (height - row - 1) * width * 4, buffer.get() + row * width * 4, width * 4);
        }
        
        if (image) {
            image->initWithRawData(flippedBuffer.get(), width * height * 4, width, height, 8);
        }
    }while(0);
    
    if (afterCaptured)
    {
        afterCaptured(image);
    }
}

void captureScreen(const std::function<void(Image *image)>& afterCaptured)
{
    static CustomCommand captureScreenCommand;
    captureScreenCommand.init(std::numeric_limits<float>::max());
    captureScreenCommand.func = std::bind(onCaptureScreen, afterCaptured);
    Director::getInstance()->getRenderer()->addCommand(&captureScreenCommand);
}

#pragma mark
// MARK: ...
void openStore(const char *storeId){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UtilsApple::openStore(storeId);
#endif
}

void openDeveloper(const char *devId){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UtilsApple::openDeveloper(devId);
#endif
}

void openGameCenter(const char *leaderBoardId){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UtilsApple::openGameCenter(leaderBoardId);
#endif
}

void showAlertView(int tag, const char *title, const char *message, const char *cancelButtonTitle, const char *otherButtonTitle){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UtilsApple::showAlertView(tag, title, message, cancelButtonTitle, otherButtonTitle);
#endif
}

void displayActivityWithText(const char *text, const char *image, const char *url){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    UtilsApple::displayActivityWithText(text, image, url);
#endif
}

MYCOMPONENTS_UTILS_NAMESPACE_END
