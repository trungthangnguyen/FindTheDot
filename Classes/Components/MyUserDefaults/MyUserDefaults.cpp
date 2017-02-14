//
//  MyUserDefaults.cpp
//
//
//  Created by Hieu Nguyen Trung on 4/29/15.
//
//

#include "MyUserDefaults.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_MYCOMPONENTS_UTILS;

MYCOMPONENTS_NAMESPACE_BEGIN

#define MYUSERDEFAULTS_KEY          "hieunt88vn12345"
#define MYUSERDEFAULTS_LENGTH       16
#define MYUSERDEFAULTS_BLOCKSIZE    16

#pragma mark Hex & Char
//Function to convert unsigned char to string of length 2
void Char2Hex(unsigned char ch, char* szHex)
{
    unsigned char byte[2];
    byte[0] = ch/16;
    byte[1] = ch%16;
    for(int i=0; i<2; i++)
    {
        if(byte[i] >= 0 && byte[i] <= 9)
            szHex[i] = '0' + byte[i];
        else
            szHex[i] = 'A' + byte[i] - 10;
    }
    szHex[2] = 0;
}

//Function to convert string of length 2 to unsigned char
void Hex2Char(char const* szHex, unsigned char& rch)
{
    rch = 0;
    for(int i=0; i<2; i++)
    {
        if(*(szHex + i) >='0' && *(szHex + i) <= '9')
            rch = (rch << 4) + (*(szHex + i) - '0');
        else if(*(szHex + i) >='A' && *(szHex + i) <= 'F')
            rch = (rch << 4) + (*(szHex + i) - 'A' + 10);
        else
            break;
    }
}

//Function to convert string of unsigned chars to string of chars
void CharStr2HexStr(unsigned char const* pucCharStr, char* pszHexStr, int iSize)
{
    int i;
    char szHex[3];
    pszHexStr[0] = 0;
    for(i=0; i<iSize; i++)
    {
        Char2Hex(pucCharStr[i], szHex);
        strcat(pszHexStr, szHex);
    }
}

//Function to convert string of chars to string of unsigned chars
void HexStr2CharStr(char const* pszHexStr, unsigned char* pucCharStr, int iSize)
{
    int i;
    unsigned char ch;
    for(i=0; i<iSize; i++)
    {
        Hex2Char(pszHexStr+2*i, ch);
        pucCharStr[i] = ch;
    }
}

#pragma mark Initialize & Utils
static MyUserDefaults *__sharedMyUserDefaults = nullptr;

MyUserDefaults::~MyUserDefaults(){
    delete _rijndael;
}

MyUserDefaults * MyUserDefaults::getInstance(){
    if (__sharedMyUserDefaults == nullptr) {
        __sharedMyUserDefaults = new MyUserDefaults();
        __sharedMyUserDefaults->init();
    }
    
    return __sharedMyUserDefaults;
}

bool MyUserDefaults::init(){
    _rijndael = new CRijndael();
    _rijndael->MakeKey(MYUSERDEFAULTS_KEY, CRijndael::sm_chain0, MYUSERDEFAULTS_LENGTH, MYUSERDEFAULTS_BLOCKSIZE);
    
//    cout << "--------" << endl;
//    CCLOG("string: %s", this->getStringForKey("string").c_str());
//    this->setStringForKey("string", "   hieu nguyen trung   ");
//    CCLOG("string: %s", this->getStringForKey("string").c_str());
//    
//    cout << "--------" << endl;
//    CCLOG("bool: %d", this->getBoolForKey("bool"));
//    this->setBoolForKey("bool", 1);
//    CCLOG("bool: %d", this->getBoolForKey("bool"));
//    
//    cout << "--------" << endl;
//    CCLOG("int: %d", this->getIntegerForKey("int"));
//    this->setIntegerForKey("int", 7788);
//    CCLOG("int: %d", this->getIntegerForKey("int"));
//    
//    cout << "--------" << endl;
//    CCLOG("long: %ld", this->getLongForKey("long"));
//    this->setLongForKey("long", 123456789);
//    CCLOG("long: %ld", this->getLongForKey("long"));
//    
//    cout << "--------" << endl;
//    CCLOG("float: %f", this->getFloatForKey("float"));
//    this->setFloatForKey("float", 5.123789f);
//    CCLOG("float: %f", this->getFloatForKey("float"));
//    
//    cout << "--------" << endl;
//    CCLOG("double: %lf", this->getDoubleForKey("double"));
//    this->setDoubleForKey("double", 987654.123456);
//    CCLOG("double: %lf", this->getDoubleForKey("double"));
    
    return true;
}

void MyUserDefaults::flush(){
    UserDefault::getInstance()->flush();
}

std::string MyUserDefaults::stringWithZeroPadding(const std::string &str){
    const unsigned long size = str.size();
    std::string sss = str;
    int mod = size%MYUSERDEFAULTS_BLOCKSIZE;
    
    if (mod != 0) {
        std::string blanks(MYUSERDEFAULTS_BLOCKSIZE - mod, ' ');
        sss.append(blanks);
    }
    
    return sss;
}

std::string MyUserDefaults::encryptedString(const std::string &str){
    // insert zero padding for multiple block string
    std::string in = this->stringWithZeroPadding(str);
    
    // create encrypted string
    const long size = in.size();
    char result[size + 1];
    memset(result, 0, size + 1);
    
    // encrypt
    _rijndael->Encrypt(in.c_str(), result, size, CRijndael::ECB);
    
    // hex string (use to save data)
    char hex[size*2 + 1];
    memset(hex, 0, size*2 + 1);
    CharStr2HexStr((unsigned char*)result, hex, (int)size);
    
    return hex;
}

std::string MyUserDefaults::decryptedString(const std::string &str){
    const long size = str.size();
    
    char enStr[size/2 + 1];
    memset(enStr, 0, size/2 + 1);
    HexStr2CharStr(str.c_str(), (unsigned char *)enStr, (int)size/2);
    
    char result[size/2 +1];
    memset(result, 0, size/2 + 1);
    _rijndael->Decrypt(enStr, result, size/2);
    
    // trim string and return
    std::string sss = result;
    
    return str_trim3(sss);
}

#pragma mark GET methods
bool MyUserDefaults::getBoolForKey(const char* pKey, bool defaultValue){
    std::string str = this->getStringForKey(pKey);
    
    if (std::strcmp(str.c_str(), "") == 0) {
        return defaultValue;
    }
    
    return std::atoi(str.c_str());
}

int MyUserDefaults::getIntegerForKey(const char* pKey, int defaultValue){
    std::string str = this->getStringForKey(pKey);
    
    if (std::strcmp(str.c_str(), "") == 0) {
        return defaultValue;
    }
    
    return std::atoi(str.c_str());
}

long MyUserDefaults::getLongForKey(const char* pKey, long defaultValue){
    std::string str = this->getStringForKey(pKey);
    
    if (std::strcmp(str.c_str(), "") == 0) {
        return defaultValue;
    }
    
    return std::atol(str.c_str());
}

float MyUserDefaults::getFloatForKey(const char* pKey, float defaultValue){
    std::string str = this->getStringForKey(pKey);
    
    if (std::strcmp(str.c_str(), "") == 0) {
        return defaultValue;
    }
    
    return std::atof(str.c_str());
}

double MyUserDefaults::getDoubleForKey(const char* pKey, double defaultValue){
    std::string str = this->getStringForKey(pKey);
    
    if (std::strcmp(str.c_str(), "") == 0) {
        return defaultValue;
    }
    
    return std::atof(str.c_str());
}

std::string MyUserDefaults::getStringForKey(const char *key, const std::string &defaultValue){
    std::string hex = UserDefault::getInstance()->getStringForKey(key, defaultValue);
    
    if (std::strcmp(hex.c_str(), defaultValue.c_str()) == 0) {
        return defaultValue;
    }
    
    return this->decryptedString(hex);
}

#pragma mark SET methods
void MyUserDefaults::setBoolForKey(const char* pKey, bool value){
    UserDefault::getInstance()->setStringForKey(pKey, this->encryptedString(StringUtils::toString(value)));
}

void MyUserDefaults::setIntegerForKey(const char* pKey, int value){
    UserDefault::getInstance()->setStringForKey(pKey, this->encryptedString(StringUtils::toString(value)));
}

void MyUserDefaults::setLongForKey(const char* pKey, long value){
    UserDefault::getInstance()->setStringForKey(pKey, this->encryptedString(StringUtils::toString(value)));
}

void MyUserDefaults::setFloatForKey(const char* pKey, float value){
    UserDefault::getInstance()->setStringForKey(pKey, this->encryptedString(StringUtils::toString(value)));
}

void MyUserDefaults::setDoubleForKey(const char* pKey, double value){
    UserDefault::getInstance()->setStringForKey(pKey, this->encryptedString(StringUtils::toString(value)));
}

void MyUserDefaults::setStringForKey(const char *pKey, const std::string &value){
    std::string str = value;
    str_trim2(str);
    
    if (str.size()) {
        UserDefault::getInstance()->setStringForKey(pKey, this->encryptedString(str));
    }
}

MYCOMPONENTS_NAMESPACE_END
