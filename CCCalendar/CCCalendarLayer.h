//
//  CCCalendarLayer.h
//  CCCalendarTest
//
//  Created by Monky on 16/11/14.
//  Copyright © 2016年 Bird01. All rights reserved.
//

#ifndef __CCCalendarTest__CCCalendarLayer__
#define __CCCalendarTest__CCCalendarLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCCalendar.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCCalendarLayer: public Layer {
public:
    CCCalendarLayer();
    ~CCCalendarLayer();
    
    CREATE_FUNC(CCCalendarLayer)
    virtual bool init();
    
    CC_SYNTHESIZE_RETAIN(ControlButton*, m_pLeftButton, LeftButton);
    CC_SYNTHESIZE_RETAIN(ControlButton*, m_pRightButton, RightButton);
    CC_SYNTHESIZE_RETAIN(CCCalendar*, m_pCalendar, Calendar);
    
    // a selector callback
    void leftButtonClicked(Ref* pSender);
    void rightButtonClicked(Ref* pSender);
    
protected:
    CC_SYNTHESIZE(unsigned int, p_uCurrentYear, CurrentYear);
    CC_SYNTHESIZE(unsigned int, p_uCurrentMonth, CurrentMonth);
};

#endif /* defined(__CCCalendarTest__CCCalendarLayer__) */
