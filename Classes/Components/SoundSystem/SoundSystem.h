//
//  SoundSystem.h
//
//
//  Created by Hieu Nguyen Trung on 4/28/15.
//
//

#include <stdio.h>

enum {
    kSoundSystemInvalid = -9999,
};

class SoundSystem {
protected:
    bool    _isEffectsOn;
    bool    _isBackgroundMusicOn;
    
    void init();
    void synthesizeEffects();
    void synthesizeBackgroundMusic();
    
public:
    static SoundSystem * getInstance();
    
    bool getIsEffectsOn() {return _isEffectsOn;};
    bool getIsBackgroundMusicOn() {return _isBackgroundMusicOn;};
    
#pragma mark
// MARK: Effects
    void turnOnEffects();
    void turnOffEffects();
    unsigned int playEffect(const char* filePath, bool loop = false, float pitch = 1.0f, float pan = 0.0f, float gain = 1.0f);
    
    void pauseEffect(unsigned int soundId);
    void pauseAllEffects();
    void resumeEffect(unsigned int soundId);
    void resumeAllEffects();
    void stopEffect(unsigned int soundId);
    void stopAllEffects();
    void preloadEffect(const char* filePath);
    void unloadEffect(const char* filePath);
    
    float getEffectsVolume();
    void setEffectsVolume(float volume);
    
#pragma mark
// MARK: Background music
    void turnOnBackgroundMusic();
    void turnOffBackgroundMusic();
    
    void preloadBackgroundMusic(const char* filePath);
    void playBackgroundMusic(const char* filePath, bool loop = false);
    void stopBackgroundMusic(bool releaseData = false);
    void pauseBackgroundMusic();
    void resumeBackgroundMusic();
    void rewindBackgroundMusic();
    
    bool willPlayBackgroundMusic();
    bool isBackgroundMusicPlaying();
    float getBackgroundMusicVolume();
    void setBackgroundMusicVolume(float volume);
};
