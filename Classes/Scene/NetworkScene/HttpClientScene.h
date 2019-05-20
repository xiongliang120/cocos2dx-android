#ifndef PROJ_ANDROID_HTTPCLIENTSCENE_H
#define PROJ_ANDROID_HTTPCLIENTSCENE_H

#include "cocos2d.h"
#include "network/HttpClient.h"
using namespace cocos2d::network;


class HttpClientScene : cocos2d::Scene{
public :
    CREATE_FUNC(HttpClientScene)
    static cocos2d::Scene * createScene();
    virtual bool init() override ;
    virtual void onHttpRequestCompleted(HttpClient * sender, HttpResponse *response);
    virtual void post();
    virtual void get();
};

#endif //PROJ_ANDROID_HTTPCLIENTSCENE_H
