//
// Created by 123 on 2019/5/16.
//

#ifndef PROJ_ANDROID_ACTIONSCENE_H
#define PROJ_ANDROID_ACTIONSCENE_H
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;

class ActionScene : Scene{
public :
    CREATE_FUNC(ActionScene);
    static Scene * createScene();
    virtual bool init() override ;
    virtual void removeAction();
    virtual void removeAllAction();
    virtual void removeEaseElastic();
    virtual void progressToRadial();
    virtual void progressToHorizontal();
    virtual void scale();
    virtual void scaleCallback();
    virtual void customSchedule();
};

class StopAction : public ActionManager{
public:
    CREATE_FUNC(StopAction);
    void stopAction();
    static Scene * createScene();
    virtual bool init() ;
};


#endif //PROJ_ANDROID_ACTIONSCENE_H
