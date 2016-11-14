//
//  CCCalendar.h
//  CCCalendarTest
//
//  Created by Monky on 16/11/14.
//  Copyright © 2016年 Bird01. All rights reserved.
//

#ifndef __CCCalendarTest__CCCalendar__
#define __CCCalendarTest__CCCalendar__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCCalendarDayCell.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CCCalendar: public Layer {
public:
    CCCalendar();
    ~CCCalendar();
    
    static CCCalendar* create(unsigned int year, unsigned int month);
    CREATE_FUNC(CCCalendar);
    virtual bool init();
    
    CC_SYNTHESIZE_RETAIN(CCArray*, m_pGridCellList, Grids);
    CC_SYNTHESIZE(unsigned int, m_uYear, Year);
    CC_SYNTHESIZE(unsigned int, m_uMonth, Month);
    //间距
    CC_SYNTHESIZE(float, m_fGapX, GapX);
    CC_SYNTHESIZE(float, m_fGapY, GapY);
    
    void addAGridCell(CCCalendarDayCell *gridCell);
    int getColumnCount();
    int getRowCount();
    CCPoint getLastAvilableCellPosition();
    
    int getMonthDays();
    
protected:
    unsigned int m_uFirstDayOfTheWeekThisMonth;
};

#endif /* defined(__CCCalendarTest__CCCalendar__) */
