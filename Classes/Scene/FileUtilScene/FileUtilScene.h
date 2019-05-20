#ifndef PROJ_ANDROID_FILEUTILSCENE_H
#define PROJ_ANDROID_FILEUTILSCENE_H
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::ui;

class FileUtilScene : Scene{
public :
    CREATE_FUNC(FileUtilScene);
    static Scene * createScene();
    virtual bool init() override ;
    virtual void saveFile();
    virtual void readFile();
};

#endif //PROJ_ANDROID_FILEUTILSCENE_H
