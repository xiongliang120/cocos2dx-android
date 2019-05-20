//
// Created by 123 on 2019/5/17.
//

#ifndef PROJ_ANDROID_TABCONTROLSCENE_H
#define PROJ_ANDROID_TABCONTROLSCENE_H

#include "cocos2d.h"


class TabControlScene : cocos2d::Scene{
public :
    CREATE_FUNC(TabControlScene)
    static cocos2d::Scene * createScene();
    virtual bool init() override ;
};

#endif //PROJ_ANDROID_TABCONTROLSCENE_H
