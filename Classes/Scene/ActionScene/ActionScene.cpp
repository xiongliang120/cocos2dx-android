#include "ActionScene.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include <android/log.h>

#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, __FILE__, __VA_ARGS__)
#else
#define LOGI(...) ;
#endif

 Scene * ActionScene::createScene(){
    Scene* scene = ActionScene::create();
     return scene;
}

bool ActionScene::init(){
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
//                removeAction();
//                removeAllAction();
//                removeEaseElastic();
//                progressToHorizontal();
//                scale();
//                customSchedule();
                  scaleCallback();
                break;
            default:
                break;
        }
    });
    return true;
}


void ActionScene::removeAction() {
    auto l = Label::createWithTTF("Should not crash", "fonts/arial.ttf", 16.0f);
    addChild(l);
    l->setPosition(VisibleRect::center().x, VisibleRect::top().y - 75);

    auto pMove = MoveBy::create(2, Vec2(200, 0));
//    auto pCallback = CallFunc::create(CC_CALLBACK_0(StopAction::stopAction,this));
    auto pSequence = Sequence::create(pMove, NULL, nullptr);
    pSequence->setTag(101);

    auto pChild = Sprite::create("1.png");
    pChild->setPosition( VisibleRect::center() );

    addChild(pChild, 1, 101);
    pChild->runAction(pSequence);
}

void ActionScene::removeAllAction() {
    auto l = Label::createWithTTF("Should stop scale & move after 4 seconds but keep rotate", "fonts/arial.ttf", 16.0f);
    addChild(l);
    l->setPosition( Vec2(VisibleRect::center().x-50, VisibleRect::top().y - 75) );

    auto pMove1 = MoveBy::create(2, Vec2(60, 0));
    auto pMove2 = MoveBy::create(2, Vec2(-60, 0));
    auto pSequenceMove = Sequence::createWithTwoActions(pMove1, pMove2);
    auto pRepeatMove = RepeatForever::create(pSequenceMove);
    pRepeatMove->setTag(102);

    auto pScale1 = ScaleBy::create(2, 1.5f);
    auto pScale2 = ScaleBy::create(2, 1.0f/1.5f);
    auto pSequenceScale = Sequence::createWithTwoActions(pScale1, pScale2);
    auto pRepeatScale = RepeatForever::create(pSequenceScale);
    pRepeatScale->setTag(102);

    auto pRotate = RotateBy::create(2, 360);
    auto pRepeatRotate = RepeatForever::create(pRotate);

    auto pChild = Sprite::create("1.png");
    pChild->setPosition( VisibleRect::center() );

    addChild(pChild, 1, 103);
    pChild->runAction(pRepeatMove);
    pChild->runAction(pRepeatScale);
    pChild->runAction(pRepeatRotate);
}


void ActionScene::removeEaseElastic(){
    auto pChild = Sprite::create("1.png");
    pChild->setPosition( VisibleRect::center() );
    addChild(pChild, 1, 103);

    auto move = MoveBy::create(3, Vec2(VisibleRect::right().x-130, 0));
    auto move_back = move->reverse();

    auto move_ease_in = EaseElasticIn::create(move->clone() );
    auto move_ease_in_back = move_ease_in->reverse();

    auto move_ease_out = EaseElasticOut::create(move->clone() );
    auto move_ease_out_back = move_ease_out->reverse();

    auto delay = DelayTime::create(0.25f);

    auto seq1 = Sequence::create(move, delay, move_back, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_in, delay->clone(), move_ease_in_back, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_out, delay->clone(), move_ease_out_back, delay->clone(), nullptr);

    pChild->runAction( RepeatForever::create(seq2));
//    pChild->runAction( RepeatForever::create(seq2));
//    pChild->runAction( RepeatForever::create(seq3));
}

void ActionScene::progressToRadial(){
    auto s = Director::getInstance()->getWinSize();

    auto to1 = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0, 0));
    auto to2 = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0, 0));

    auto left = ProgressTimer::create(Sprite::create("grossinis_sister1.png"));
    left->setType( ProgressTimer::Type::RADIAL );
    addChild(left);
    left->setPosition(100, s.height/2);
    left->runAction( RepeatForever::create(to1));

    auto right = ProgressTimer::create(Sprite::create("grossinis_sister2.png"));
    right->setType(ProgressTimer::Type::RADIAL);
    // Makes the ridial CCW
    right->setReverseDirection(true);
    addChild(right);
    right->setPosition(s.width/2, s.height/2);
    right->runAction( RepeatForever::create(to2));
}

void ActionScene::progressToHorizontal(){
    auto s = Director::getInstance()->getWinSize();

    auto to1 = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0, 0));
    auto to2 = Sequence::createWithTwoActions(ProgressTo::create(2, 100), ProgressTo::create(0, 0));

    auto left = ProgressTimer::create(Sprite::create("weapon_back_icon.png"));
    left->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the left since the midpoint is 0 for the x
    left->setMidpoint(Vec2(0,0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left->setBarChangeRate(Vec2(1, 0));
    addChild(left);
    left->setPosition(100, s.height/2);
    left->runAction( RepeatForever::create(to1));

    auto right = ProgressTimer::create(Sprite::create("grossinis_sister2.png"));
    right->setType(ProgressTimer::Type::BAR);
    //    Setup for a bar starting from the left since the midpoint is 1 for the x
    right->setMidpoint(Vec2(1, 0));
    //    Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right->setBarChangeRate(Vec2(1, 0));
    addChild(right);
    right->setPosition(s.width/2, s.height/2);
    right->runAction( RepeatForever::create(to2));
}

void ActionScene::scale(){
    auto pChild = Sprite::create("1.png");
    pChild->setPosition( VisibleRect::center() );
    addChild(pChild, 1, 103);

    auto actionTo1 = ScaleTo::create(2.0f, 0.5f);
    auto actionTo2 = ScaleTo::create(2.0f, 1.0f);

    auto actionBy = ScaleBy::create(2.0f, 1.0f, 10.0f);
    auto actionBy2 = ScaleBy::create(2.0f, 5.0f, 1.0f);

    auto pSequenceMove = Sequence::createWithTwoActions(actionTo1, actionTo2);
    auto pRepeatMove = RepeatForever::create(pSequenceMove);

    pChild->runAction(pRepeatMove);
    //pChild->runAction( Sequence::create(actionBy, actionBy->reverse(), nullptr));
   // pChild->runAction( Sequence::create(actionBy2, actionBy2->reverse(), nullptr));
}

/**
 * 设置动画的回调
 */
void ActionScene::scaleCallback() {
    auto pChild = Sprite::create("1.png");
    pChild->setPosition( VisibleRect::center() );
    addChild(pChild, 1, 103);

    auto actionTo1 = ScaleTo::create(2.0f, 0.5f);
    auto pCallback = CallFunc::create(CC_CALLBACK_0(ActionScene::customSchedule,this));
    auto pSequence = Sequence::create(actionTo1, pCallback, nullptr);
    pChild->runAction(pSequence);
}


void ActionScene::customSchedule(){
    for (int i = 0; i < 10; ++i) {  //循环执行延期函数会只执行一次
        this->scheduleOnce([this](float dt) {
            LOGI("延期2.0执行");
        }, 0.2f, "delay scale");
    }
}

