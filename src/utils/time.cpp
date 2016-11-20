//
//  time.cpp
//  GlewTest
//
//  Created by 施铭 on 16/10/31.
//  Copyright © 2016年 施铭. All rights reserved.
//

#include <stdio.h>
#include "time.h"
#include <GLFW/glfw3.h>

Time* Time::mTime = NULL;

Time::Time()
{
    
}

float Time::getCurrentTime()
{
    return glfwGetTime();
}

Time* Time::getInstance()
{
    if(!mTime)
    {
        mTime = new Time();
    }
    return mTime;
}