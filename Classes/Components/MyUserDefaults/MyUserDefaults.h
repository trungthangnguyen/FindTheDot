//
//  MyUserDefaults.h
//
//
//  Created by Hieu Nguyen Trung on 4/29/15.
//
//

#include "../__config/MyComponentConfig.h"
#include "../Utils/Utils.h"
#include "../Utils/Rijndael.h"
#include <iostream>

MYCOMPONENTS_NAMESPACE_BEGIN

class MyUserDefaults {
    CRijndael *_rijndael;
    
    ~MyUserDefaults();
    
    bool init();
    
    std::string stringWithZeroPadding(const std::string &str);
    std::string encryptedString(const std::string &str);
    std::string decryptedString(const std::string &str);
    
public:
    static MyUserDefaults * getInstance();
    
    void flush();
    
    bool        getBoolForKey(const char* pKey, bool defaultValue = false);
    int         getIntegerForKey(const char* pKey, int defaultValue = 0);
    long        getLongForKey(const char* pKey, long defaultValue = 0);
    float       getFloatForKey(const char* pKey, float defaultValue = 0);
    double      getDoubleForKey(const char* pKey, double defaultValue = 0);
    std::string getStringForKey(const char* pKey, const std::string & defaultValue = "");
    
    void setBoolForKey(const char* pKey, bool value);
    void setIntegerForKey(const char* pKey, int value);
    void setLongForKey(const char* pKey, long value);
    void setFloatForKey(const char* pKey, float value);
    void setDoubleForKey(const char* pKey, double value);
    void setStringForKey(const char* pKey, const std::string & value);
};

MYCOMPONENTS_NAMESPACE_END




