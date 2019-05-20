//
// Created by 123 on 2019/5/15.
//

#ifndef PROJ_ANDROID_JNISCENE_H
#define PROJ_ANDROID_JNISCENE_H
#include "cocos2d.h"
USING_NS_CC;

class JniScene : Scene{
public:
    static cocos2d::Scene * createScene();
    virtual bool init() override ;
    CREATE_FUNC(JniScene);
};


#endif //PROJ_ANDROID_JNISCENE_H
