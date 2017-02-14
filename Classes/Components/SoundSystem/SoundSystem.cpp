//
//  SoundSystem.cpp
//
//
//  Created by Hieu Nguyen Trung on 4/28/15.
//
//

#include "SoundSystem.h"
#include "cocos2d.h"
//#include "../../../cocos2d/cocos/audio/include/SimpleAudioEngine.h"
#include <cocos/audio/include/SimpleAudioEngine.h>

USING_NS_CC;
using namespace CocosDenshion;

#define SOUNDSYSTEM_KEY_EFFECTS     "soundsystem_key_effects"
#define SOUNDSYSTEM_KEY_BACKGROUND  "soundsystem_key_background"

static SoundSystem *__sharedSoundSystem = nullptr;

#pragma mark Initialize
SoundSystem * SoundSystem::getInstance(){
    if (__sharedSoundSystem == nullptr) {
        __sharedSoundSystem = new SoundSystem();
        __sharedSoundSystem->init();
    }
    
    return __sharedSoundSystem;
}

void SoundSystem::init(){
    UserDefault *userDefault = UserDefault::getInstance();
    
    _isEffectsOn = userDefault->getBoolForKey(SOUNDSYSTEM_KEY_EFFECTS, true);
    _isBackgroundMusicOn = userDefault->getBoolForKey(SOUNDSYSTEM_KEY_BACKGROUND, true);
}

void SoundSystem::synthesizeEffects(){
    UserDefault::getInstance()->setBoolForKey(SOUNDSYSTEM_KEY_EFFECTS, _isEffectsOn);
    UserDefault::getInstance()->flush();
}

void SoundSystem::synthesizeBackgroundMusic(){
    UserDefault::getInstance()->setBoolForKey(SOUNDSYSTEM_KEY_BACKGROUND, _isBackgroundMusicOn);
    UserDefault::getInstance()->flush();
}

#pragma mark Sound Effects
void SoundSystem::turnOnEffects(){
    if (_isEffectsOn == false) {
        _isEffectsOn = true;
        this->synthesizeEffects();
    }
}

void SoundSystem::turnOffEffects(){
    if (_isEffectsOn) {
        _isEffectsOn = false;
        this->synthesizeEffects();
    }
}

unsigned int SoundSystem::playEffect(const char* filePath, bool loop, float pitch, float pan, float gain){
    if (_isEffectsOn) {
        return SimpleAudioEngine::getInstance()->playEffect(filePath, loop, pitch, pan, gain);
    }
    
    return kSoundSystemInvalid;
}

void SoundSystem::pauseEffect(unsigned int soundId){
    SimpleAudioEngine::getInstance()->pauseEffect(soundId);
}

void SoundSystem::pauseAllEffects(){
    SimpleAudioEngine::getInstance()->pauseAllEffects();
}

void SoundSystem::resumeEffect(unsigned int soundId){
    SimpleAudioEngine::getInstance()->resumeEffect(soundId);
}

void SoundSystem::resumeAllEffects(){
    SimpleAudioEngine::getInstance()->resumeAllEffects();
}

void SoundSystem::stopEffect(unsigned int soundId){
    SimpleAudioEngine::getInstance()->stopEffect(soundId);
}

void SoundSystem::stopAllEffects(){
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundSystem::preloadEffect(const char* filePath){
    SimpleAudioEngine::getInstance()->preloadEffect(filePath);
}

void SoundSystem::unloadEffect(const char* filePath){
    SimpleAudioEngine::getInstance()->unloadEffect(filePath);
}

float SoundSystem::getEffectsVolume(){
    return SimpleAudioEngine::getInstance()->getEffectsVolume();
}

void SoundSystem::setEffectsVolume(float volume){
    SimpleAudioEngine::getInstance()->setEffectsVolume(volume);
}

#pragma mark Background music
void SoundSystem::turnOnBackgroundMusic(){
    if (_isBackgroundMusicOn == false) {
        _isBackgroundMusicOn = true;
        this->synthesizeBackgroundMusic();
        
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}

void SoundSystem::turnOffBackgroundMusic(){
    if (_isBackgroundMusicOn) {
        _isBackgroundMusicOn = false;
        this->synthesizeBackgroundMusic();
        
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
}

void SoundSystem::preloadBackgroundMusic(const char* filePath){
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(filePath);
}

void SoundSystem::playBackgroundMusic(const char* pszFilePath, bool bLoop){
    if (_isBackgroundMusicOn) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic(pszFilePath, bLoop);
    }
}

void SoundSystem::stopBackgroundMusic(bool releaseData){
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(releaseData);
}

void SoundSystem::pauseBackgroundMusic(){
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void SoundSystem::resumeBackgroundMusic(){
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void SoundSystem::rewindBackgroundMusic(){
    SimpleAudioEngine::getInstance()->rewindBackgroundMusic();
}

bool SoundSystem::willPlayBackgroundMusic(){
    return SimpleAudioEngine::getInstance()->willPlayBackgroundMusic();
}

bool SoundSystem::isBackgroundMusicPlaying(){
    return SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
}

float SoundSystem::getBackgroundMusicVolume(){
    return SimpleAudioEngine::getInstance()->getBackgroundMusicVolume();
}

void SoundSystem::setBackgroundMusicVolume(float volume){
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume);
}
