//
//  time.h
//  GlewTest
//
//  Created by 施铭 on 16/10/31.
//  Copyright © 2016年 施铭. All rights reserved.
//

#ifndef TIME_H
#define TIME_H

//游戏时间类
class Time
{
private:
    Time();
    
public:
    static float getCurrentTime();
    
    static Time* getInstance();
    
private:
    static Time* mTime;
};

#endif
