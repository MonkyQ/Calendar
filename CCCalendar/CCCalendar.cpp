//
//  CCCalendar.cpp
//  CCCalendarTest
//
//  Created by Monky on 16/11/14.
//  Copyright © 2016年 Bird01. All rights reserved.
//

#include "CCCalendar.h"

CCCalendar::CCCalendar()
:m_pGridCellList(NULL)
,m_fGapX(0)
,m_fGapY(0)
,m_uYear(0)
,m_uMonth(0)
{
    
}

CCCalendar::~CCCalendar()
{
    CC_SAFE_RELEASE_NULL(m_pGridCellList);
}

CCCalendar *CCCalendar::create(unsigned int year, unsigned int month)
{
    CCCalendar *pRet = new CCCalendar();
    pRet->setYear(year);
    pRet->setMonth(month);
    if (pRet && pRet->init()) 
    { 
        pRet->autorelease(); 
        return pRet; 
    } 
    else 
    { 
        delete pRet; 
        pRet = NULL; 
        return NULL; 
    } 
}

bool CCCalendar::init()
{
    if (!Layer::init())
    {
        return false;
    }

    this->setGrids(CCArray::create());
    
    this->setGapX(50);
    this->setGapY(50);
    
    if (m_uYear == 0 && m_uMonth == 0)
    {
        time_t now;
        struct tm *fmt;
        time(&now);
        fmt = localtime(&now);
        this->setYear(fmt->tm_year + 1900);
        this->setMonth(fmt->tm_mon);
    }
    
    struct tm *fmt = new tm;
    fmt->tm_year = this->getYear() - 1900;
    fmt->tm_mon = this->getMonth();
    fmt->tm_mday = 1;
    fmt->tm_hour = 1;
    fmt->tm_min = 1;
    fmt->tm_sec = 1;
    mktime(fmt);
    m_uFirstDayOfTheWeekThisMonth = fmt->tm_wday;
    delete fmt;
    
    for (int i = 1; i <= getMonthDays(); i ++)
    {
        CCCalendarDayCell *cell = CCCalendarDayCell::create(this->getYear(), this->getMonth(), i);
        this->addAGridCell(cell);
    }
    
    return true;
}

void CCCalendar::addAGridCell(CCCalendarDayCell *gridCell)
{
    if (this->getGrids()->count() <= 0)
    {
        gridCell->setPosition(Vec2(m_fGapX*4.5 + (m_fGapX + gridCell->getContentSize().width) * m_uFirstDayOfTheWeekThisMonth
                                  , this->getContentSize().height - (gridCell->getContentSize().height +  m_fGapY)*8));
    }
    else
    {
        gridCell->setPosition(getLastAvilableCellPosition());
    }
    
    this->getGrids()->addObject(gridCell);
    this->addChild(gridCell);
}

int CCCalendar::getColumnCount()
{
//    float oneGridWidth = ((CCCalendarDayCell*)this->getGrids()->objectAtIndex(0))->getContentSize().width;
//    oneGridWidth += this->getGapX();
//    return this->getContentSize().width / oneGridWidth;
    return 7;
}

int CCCalendar::getRowCount()
{
//    float oneGridHeight = ((CCCalendarDayCell*)this->getGrids()->objectAtIndex(0))->getContentSize().height;
//    oneGridHeight += this->getGapY();
//    return this->getContentSize().height / oneGridHeight;
    return 5;
}

CCPoint CCCalendar::getLastAvilableCellPosition()
{
    CCCalendarDayCell *lastCell = (CCCalendarDayCell*)this->getGrids()->objectAtIndex(this->getGrids()->count() - 1);
    
    if (lastCell->getWeekDays() == 6)
    {
        return Vec2 (m_fGapX*4.5, lastCell->getPosition().y - m_fGapY - lastCell->getContentSize().height);
    }
    else
    {
        return Vec2 (m_fGapX + lastCell->getPosition().x + lastCell->getContentSize().width, lastCell->getPosition().y);
    }
}

int CCCalendar::getMonthDays()
{
    switch (this->getMonth()) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            return 31;
            break;
        case 1:
        {
            if ((this->getYear() % 4 == 0 && this->getYear() % 100 != 0)|| this->getYear() % 400 == 0)
            {
                return 29;
            }
            else
            {
                return 28;
            }
            break;
        }
        case 3:
        case 5:
        case 8:
        case 10:
            return 30;
            break;
        default:
            return 0;
            break;
    }
}
