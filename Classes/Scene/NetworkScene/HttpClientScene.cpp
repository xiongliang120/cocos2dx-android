#include "HttpClientScene.h"
#include "ui/CocosGUI.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, __FILE__, __VA_ARGS__)
#else
#define LOGI(...) ;
#endif
USING_NS_CC;
using namespace cocos2d::ui;

Scene * HttpClientScene::createScene(){
    Scene* scene = HttpClientScene::create();
    return scene;
}

bool HttpClientScene::init(){
    if (!Scene::init()) {
        return false;
    }

    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Size visibleSize = Director::getInstance()->getVisibleSize();

    //添加背景
    auto bg = Sprite::create("bg_0.png");
    bg->setContentSize(visibleSize);
    bg->setPosition(origin.x + visibleSize.width * 0.5, origin.y + visibleSize.height * 0.5);
    this->addChild(bg, 0);

    //添加左上角返回按钮
    Button *backIcon = Button::create("weapon_back_icon.png");
    backIcon->ignoreContentAdaptWithSize(false);
    backIcon->setContentSize(Size(50, 50));
    backIcon->setPosition(Vec2(200, 280));
    this->addChild(backIcon,0);

    backIcon->addTouchEventListener([&](Ref *sender, Widget::TouchEventType type){
        switch (type) {
            case Widget::TouchEventType::BEGAN:
                break;
            case Widget::TouchEventType::ENDED:
                //post();
                get();
                break;
            default:
                break;
        }
    });
    return true;
}

void HttpClientScene::post(){
    LOGI("开始发送Post请求");
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://httpbin.org/post");
    request->setRequestType(HttpRequest::Type::POST);
    request->setResponseCallback(CC_CALLBACK_2(HttpClientScene::onHttpRequestCompleted,this));
    char* postData = "visitor=cocos2d&TestSuite=Extensions Test/NetworkTest";
    request->setRequestData(postData, strlen(postData));
    request->setTag("Post immediate"); //立即发送
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    /*
    request->setTag("Post");  //先添加到任务队列中,到了再发送请求
    HttpClient::getInstance()->send(request);
    */
}


void HttpClientScene::get(){
    LOGI("开始发送Get请求");
    HttpRequest* request = new HttpRequest();
    request->setUrl("http://httpbin.org/ip");
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(HttpClientScene::onHttpRequestCompleted, this));
    request->setTag("Get immediate");
    HttpClient::getInstance()->sendImmediate(request);
    request->release();
    /*
    request->setTag("Get");
    HttpClient::getInstance()->send(request);
    request->release();
    */
}

void HttpClientScene::onHttpRequestCompleted(HttpClient * sender,HttpResponse *response){
    if (!response)
    {
        return;
    }

    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        LOGI("%s completed", response->getHttpRequest()->getTag());
    }

    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    LOGI("HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    LOGI("response code: %ld", statusCode);

    if (!response->isSucceed())
    {
        LOGI("response failed");
        LOGI("error buffer: %s", response->getErrorBuffer());
        return;
    }

    // dump data
    std::vector<char> *buffer = response->getResponseData();
    LOGI("Http Test, dump data: ");
    for (unsigned int i = 0; i < buffer->size(); i++)
    {
        LOGI("%c", (*buffer)[i]);
    }

}


