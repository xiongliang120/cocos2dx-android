//
// Created by 123 on 2019/5/17.
//

#ifndef PROJ_ANDROID_JSONSCENE_H
#define PROJ_ANDROID_JSONSCENE_H

#include "cocos2d.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;


class JsonScene : cocos2d::Scene{
public :
    int career;
    char* careerMatch;
    char* date;


    CREATE_FUNC(JsonScene)
    static cocos2d::Scene * createScene();
    virtual bool init() override ;
    virtual void onHttpRequestCompleted(HttpClient * sender, HttpResponse *response);
    virtual void post();

};
#endif //PROJ_ANDROID_JSONSCENE_H
