//
//  CCCalendarDayCell.cpp
//  CCCalendarTest
//
//  Created by Monky on 16/11/14.
//  Copyright © 2016年 Bird01. All rights reserved.
//

#include "CCCalendarDayCell.h"

CCCalendarDayCell::CCCalendarDayCell()
:m_uYear(0)
,m_uMonth(0)
,m_uDay(0)
{
    
}

CCCalendarDayCell::~CCCalendarDayCell()
{
    
}

CCCalendarDayCell *CCCalendarDayCell::create(unsigned int year, unsigned int month, unsigned int day)
{
    CCCalendarDayCell *cell = CCCalendarDayCell::create();
    cell->setYear(year);
    cell->setMonth(month);
    cell->setDay(day);
    return cell;
}

bool CCCalendarDayCell::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
//    ccColor4B color = ccc4(0xFF, 0xFF, 0xFF, 0x7A);
//    CCLayerColor *layer = CCLayerColor::create(color, 30, 30);
//    this->addChild(layer);
    this->setContentSize(CCSize(50, 50));
    return true;
}

void CCCalendarDayCell::onEnter()
{
    auto pbutton = cocos2d::ui::Button::create("","","",cocos2d::ui::Widget::TextureResType::PLIST);
    pbutton->setTitleText(convertInt(this->getDay()).c_str());
    pbutton->setTitleFontName("Fonts/arial.ttf");
    
    pbutton->setTitleFontSize(45);
    //CCLabelTTF* pLabel = CCLabelTTF::create(convertInt(this->getDay()).c_str(), "Thonburi",50);
    pbutton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
    pbutton->addTouchEventListener([=](Ref* pSender,cocos2d::ui::Widget::TouchEventType type){
        if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
            CCLOG("%u-%d",this->getMonth(),this->getDay());
        }
    });

    this->addChild(pbutton);
     Node::onEnter();
}

int CCCalendarDayCell::getWeekDays()
{
    struct tm *fmt = new tm;
    fmt->tm_year = this->getYear() - 1900;
    fmt->tm_mon = this->getMonth();
    fmt->tm_mday = this->getDay();
    fmt->tm_hour = 1;
    fmt->tm_min = 1;
    fmt->tm_sec = 1;
    mktime(fmt);
    int weekday = fmt->tm_wday;
    delete fmt;
    return weekday;
    
}

std::string convertInt(int number)
{
    std::stringstream ss;
    ss << number;
    return ss.str();
}
