//
//  CCCalendarLayer.cpp
//  CCCalendarTest
//
//  Created by Monky on 16/11/14.
//  Copyright © 2016年 Bird01. All rights reserved.
//

#include "CCCalendarLayer.h"
#include "CCCalendar.h"

CCCalendarLayer::CCCalendarLayer()
:m_pLeftButton(NULL)
,m_pRightButton(NULL)
,p_uCurrentYear(0)
,p_uCurrentMonth(0)
,m_pCalendar(NULL)
{
    
}

CCCalendarLayer::~CCCalendarLayer()
{
    CC_SAFE_RELEASE_NULL(m_pLeftButton);
    CC_SAFE_RELEASE_NULL(m_pRightButton);
    CC_SAFE_RELEASE_NULL(m_pCalendar);
}

bool CCCalendarLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    MenuItemImage *pLeftButton = MenuItemImage::create(
                                                          "left_arrow.png",
                                                          "",
                                                          this,
                                                          menu_selector(CCCalendarLayer::leftButtonClicked));
    
    MenuItemImage *pRightButton = MenuItemImage::create(
                                                          "right_arrow.png",
                                                          "",
                                                          this,
                                                          menu_selector(CCCalendarLayer::rightButtonClicked));
    
    pLeftButton->setPosition(Vec2((visibleSize.width/2048)*180, (visibleSize.width/2048)*900));
    pRightButton->setPosition(Vec2((visibleSize.width/2048)*930, (visibleSize.width/2048)*900));
    Menu* pMenu = Menu::create(pLeftButton, NULL);
    Menu* pMenu2 = Menu::create(pRightButton, NULL);
    pMenu->setPosition( CCPointZero );
    pMenu2->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
    this->addChild(pMenu2, 1);
    
    this->setCalendar(CCCalendar::create());
    this->addChild(this->getCalendar());
    
    this->setCurrentYear(this->getCalendar()->getYear());
    this->setCurrentMonth(this->getCalendar()->getMonth());
    //日期
    auto dateLabel = Label::createWithTTF(convertInt(this->getCurrentYear())+"年"+convertInt(this->getCurrentMonth()+1)+"月","Fonts/RTWSYueGoTrial-Regular.otf", (visibleSize.width/2048)*40.0);
    dateLabel->setPosition(Vec2(550,900));
    dateLabel->setTag(10600);
    dateLabel->setTextColor(Color4B::BLACK);
    this->addChild(dateLabel);
    return true;
}

void CCCalendarLayer::leftButtonClicked(cocos2d::Ref *pSender)
{
    this->removeChild(this->getCalendar(), true);
    if (this->getCurrentMonth() == 0)
    {
        this->setCurrentYear(this->getCurrentYear() - 1);
        this->setCurrentMonth(11);
    }
    else
    {
        this->setCurrentMonth(this->getCurrentMonth() - 1);
    }
//    CCLOG("++++++++++%d", this->getCurrentMonth());
    auto dateLabel = (Label*)this->getChildByTag(10600);
    dateLabel->setString(convertInt(this->getCurrentYear())+"年"+convertInt(this->getCurrentMonth()+1)+"月");
    this->setCalendar(CCCalendar::create(this->getCurrentYear(), this->getCurrentMonth()));
    this->addChild(this->getCalendar());
}

void CCCalendarLayer::rightButtonClicked(cocos2d::Ref *pSender)
{
    this->removeChild(this->getCalendar(), true);
    if (this->getCurrentMonth() == 11)
    {
        this->setCurrentYear(this->getCurrentYear() + 1);
        this->setCurrentMonth(0);
    }
    else
    {
        this->setCurrentMonth(this->getCurrentMonth() + 1);
    }
    auto dateLabel = (Label*)this->getChildByTag(10600);
    dateLabel->setString(convertInt(this->getCurrentYear())+"年"+convertInt(this->getCurrentMonth()+1)+"月");
//    CCLOG("---------%d", this->getCurrentMonth());
    this->setCalendar(CCCalendar::create(this->getCurrentYear(), this->getCurrentMonth()));
    this->addChild(this->getCalendar());
}
