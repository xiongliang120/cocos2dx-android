#include "FileUtilScene.h"
#include "ui/CocosGUI.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, __FILE__, __VA_ARGS__)
#else
#define LOGI(...) ;
#endif

Scene * FileUtilScene::createScene(){
   Scene* scene = FileUtilScene::create();
    return scene;
}

bool FileUtilScene::init(){
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
//                saveFile();
                 readFile();
                break;
            default:
                break;
        }
    });

    return true;
}

void FileUtilScene::saveFile(){
    ValueVector array;
    ValueMap mapInArray;
    mapInArray["string1"] = "string in dictInArray key 0";
    mapInArray["string2"] = "string in dictInArray key 1";
    array.push_back(Value(mapInArray));

    array.push_back(Value("string in array"));

    ValueVector arrayInArray;
    arrayInArray.push_back(Value("string 0 in arrayInArray"));
    arrayInArray.push_back(Value("string 1 in arrayInArray"));
    array.push_back(Value(arrayInArray));

    //add boolean to the plist
    auto booleanObject = Value(true);
    array.push_back(booleanObject);

    //add integer to the plist
    auto intObject = Value(1024);
    array.push_back(intObject);

    //add float to the plist
    auto floatObject = Value(1024.1024f);
    array.push_back(floatObject);

    //add double to the plist
    auto doubleObject = Value(1024.123);
    array.push_back(doubleObject);


    // end with /
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = writablePath + "testWriteValueVector.plist";
    if (FileUtils::getInstance()->writeValueVectorToFile(array, fullPath.c_str()))
    {
        LOGI("see the plist file at %s", fullPath.c_str());
    }
    else
    {
        LOGI("write plist file failed");
    }
}

void FileUtilScene::readFile(){
    std::string writablePath = FileUtils::getInstance()->getWritablePath();
    std::string fullPath = writablePath + "testWriteValueVector.plist";
    ValueVector readArray = FileUtils::getInstance()->getValueVectorFromFile(fullPath.c_str());
    std::string readDataStr = "read data:\n";
    // read value map data
    ValueMap readMapInArray = readArray.at(0).asValueMap();
    readDataStr += "  mapValue:[\"string1\"][" + readMapInArray["string1"].asString() + "]\n";
    readDataStr += "  mapValue:[\"string2\"][" + readMapInArray["string2"].asString() + "]\n";

    // read string data
    readDataStr += "  stringValue:" + readArray.at(1).asString() + "\n";

    // read value vector data
    ValueVector readVectorInArray = readArray.at(2).asValueVector();
    readDataStr += "  vectorValue:[1]" + readVectorInArray.at(0).asString() + "\n";
    readDataStr += "  vectorValue:[2]" + readVectorInArray.at(1).asString() + "\n";

    // read bool data
    readDataStr += "  boolValue:" + StringUtils::format("%d", readArray.at(3).asBool()) + "\n";

    // read int data
    readDataStr += "  intValue:" + StringUtils::format("%d", readArray.at(4).asInt()) + "\n";

    // read float data
    readDataStr += "  floatValue:" + StringUtils::format("%f", readArray.at(5).asFloat()) + "\n";

    // read double data
    readDataStr += "  doubleValue:" + StringUtils::format("%f", readArray.at(6).asDouble()) + "\n";
    LOGI("%s",readDataStr.data());
}


