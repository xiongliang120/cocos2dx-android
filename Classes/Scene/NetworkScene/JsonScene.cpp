#include "JsonScene.h"
#include "ui/CocosGUI.h"
#include "thirdparty/json.hpp"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, __FILE__, __VA_ARGS__)
#else
#define LOGI(...) ;
#endif

USING_NS_CC;
using namespace cocos2d::ui;


Scene * JsonScene::createScene(){
    Scene *scene = JsonScene::create();
    return scene;
}

bool JsonScene::init() {
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
                post();
                break;
            default:
                break;
        }
    });
    return true;
}


void JsonScene::post(){
    HttpRequest *request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::POST);
    request->setUrl("http://47.88.58.164:10005/horoscope/today");
    std::vector<std::string> headers;
    headers.push_back("Content-Type: application/json; charset=utf-8");
    request->setHeaders(headers);

    nlohmann::json json;
    json["app"] = "com.horoscopetest.test.ios";
    json["ts"] = "1557479517";
    json["data"]["cid"] = 1;
    json["udid"] = "d36e2bf1e3ee5d5acfd6453932ff4208";
    json["version"] ="2410";
    std::string jsonString = json.dump();
    const char* postData = jsonString.c_str();
    request->setRequestData(postData,strlen(postData));
    request->setResponseCallback(CC_CALLBACK_2(JsonScene::onHttpRequestCompleted,this));
    HttpClient::getInstance()->sendImmediate(request);
    request->release();


}



void JsonScene::onHttpRequestCompleted(HttpClient * sender,HttpResponse *response){
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
        return;
    }

    std::vector<char> *buffer = response->getResponseData();
    std::stringstream oss;
    for (int i = 0; i < buffer->size() ; ++i) {
        oss<< (*buffer)[i];
    }
    std::string temp = oss.str();
    LOGI("print  %s",temp.c_str());
    if(temp.size() >0){
        auto j = nlohmann::json::parse(temp.c_str());
      //  career = j["career"];
//        careerMatch = j["careerMatch"];
//        date = j["date"];
          LOGI("dsfdsfsdf");
       // LOGI("print json parse %d,%s",career);
    }


}



