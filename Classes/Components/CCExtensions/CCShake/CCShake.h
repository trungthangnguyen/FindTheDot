//
//  CCShake.h
//  Math100
//
//  Created by Hieu Nguyen Trung on 5/28/14.
//
//

#ifndef __Math100__CCShake__
#define __Math100__CCShake__

#include <iostream>
#include "cocos2d.h"

NS_CC_BEGIN

// Code by Francois Guibert
// Contact: www.frozax.com - http://twitter.com/frozax - www.facebook.com/frozax
class CC_DLL Shake : public ActionInterval
{
public:
    Shake();
    
    // Create the action with a time and a strength (same in x and y)
    static Shake* createWithDuration(float d, float strength );
    
    // Create the action with a time and strengths (different in x and y)
    static Shake* createWithDuration(float d, float strength_x, float strength_y );
    
    bool initWithDuration(float d, float strength_x, float strength_y );
    
    virtual void startWithTarget(Node *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
    virtual Shake* reverse() const;
    virtual Shake* clone() const;
    
protected:
    float _initial_x, _initial_y;
    float _strength_x, _strength_y;
    float _duration;
};

NS_CC_END

#endif /* defined(__Math100__CCShake__) */
