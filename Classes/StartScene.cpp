#include "StartScene.h"
#include "DragScene.h"
#include "VisionScene.h"
#include "LoginScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

Scene* StartScene::createScene()
{
    auto scene=Scene::create();
    auto layer=StartScene::create();
    scene->addChild(layer);
    //scene->autorelease();
    return scene;
}
bool StartScene::init()
{
    if(!Layer::init())
    {
        return false;
    }
     visibleSize=Director::getInstance()->getVisibleSize();
    Point origin=Director::getInstance()->getVisibleOrigin();
    
    //CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("bg_start.wav", true);
    
    
    CCSprite* spBackground_01 = CCSprite::create("bg_cover_1.png");
    spBackground_01->setAnchorPoint(ccp(0, 0));
    spBackground_01->setPosition(ccp(origin.x, origin.y));
    //spBackground_01->setScale(1);
    //spBackground_01->setVisible(false);
    this->addChild(spBackground_01, 0);
    
    auto game_center_item = MenuItemImage::create("game_a_item.png", "game_a_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
    game_center_menu = Menu::create(game_center_item, NULL);
    game_center_item->setAnchorPoint(ccp(0, 0));
    game_center_menu->setPosition(200,200);
    this->addChild(game_center_menu, 2);
    
    auto game_a_item = MenuItemImage::create("game_a_item.png", "game_a_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
    game_a_menu = Menu::create(game_a_item, NULL);
    game_a_item->setAnchorPoint(ccp(0, 0));
    game_a_menu->setPosition(81,478);
    this->addChild(game_a_menu, 2);
    
    auto game_b_item = MenuItemImage::create("game_b_item.png", "game_b_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
    game_b_menu = Menu::create(game_b_item, NULL);
    game_b_item->setAnchorPoint(ccp(0, 0));
    game_b_menu->setPosition(662,478);
    game_b_menu->setVisible(true);
    this->addChild(game_b_menu, 2);
    
    auto game_c_item = MenuItemImage::create("game_c_item.png", "game_c_item.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
    game_c_menu = Menu::create(game_c_item, NULL);
    game_c_item->setAnchorPoint(ccp(0, 0));
    game_c_menu->setPosition(112,114);
    game_c_menu->setVisible(true);
    this->addChild(game_c_menu, 2);
    
    auto game_start_item = MenuItemImage::create("game_start_item.png", "game_start_item.png", CC_CALLBACK_1(StartScene::menuCallBack,this));
    game_start_menu = Menu::create(game_start_item, NULL);
    //game_start_item->setAnchorPoint(ccp(0, 0));
    game_start_menu->setPosition(506,432);
    this->addChild(game_start_menu, 2);
    
    CCLOG("into create VisionScene gameInfoItem");
    auto gameInfoItem = MenuItemImage::create("layout-04.png", "layout-04.png", CC_CALLBACK_1(StartScene::menuCallBack, this));
    gameInfoMenu = Menu::create(gameInfoItem, NULL);
    gameInfoMenu->setPosition(3*visibleSize.width / 2, 3*visibleSize.height / 2);
    //gameInfoMenu->setVisible(false);
    this->addChild(gameInfoMenu, 5);
    
    return true;
}
void StartScene::menuCallBack(cocos2d::Ref* pSender)
{
    CCNode* node = (CCNode*)pSender;
    if (node->getParent() == game_b_menu){
        //CCScene* scene = HelloWorld::createScene();
        //CCDirector::sharedDirector()->replaceScene(scene);
        //CCTransitionScene* transition = CCTransitionProgressRadialCCW::create(1.5f, HelloWorld::createScene());//������ת
        //CCTransitionScene* transition = CCTransitionProgressHorizontal::create(1.2f, HelloWorld::createScene());//ˮƽ������
        //CCTransitionScene* transition = CCTransitionProgressInOut::create(1.2f, HelloWorld::createScene());//���ﵽ����չ
        //    //��͸��
        //CCTransitionScene* transition = CCTransitionCrossFade::create(4.5f, HelloWorld::createScene());
        //��ҳ
        //CCTransitionScene* transition = CCTransitionPageTurn::create(0.5f, HelloWorld::createScene(), false);
        //����
        //CCTransitionScene* transition = CCTransitionJumpZoom::create(2.0f, HelloWorld::createScene());
        //��������
        //CCTransitionScene* transition = CCTransitionFadeTR::create(3.5f, HelloWorld::createScene());
        //�����۵�
        //CCTransitionScene* transition = CCTransitionFadeUp::create(1.2f, HelloWorld::createScene());
        //���������ʧ
        //CCTransitionScene* transition = CCTransitionTurnOffTiles::create(1.2f, HelloWorld::createScene());
        //���л����л�
        //CCTransitionScene* transition = CCTransitionSplitRows::create(1.2f, HelloWorld::createScene());
        //����
        //CCTransitionScene* transition = CCTransitionSplitCols::create(1.2f, HelloWorld::createScene());
        //��ɫ����
        //CCTransitionScene* transition = CCTransitionFade::create(12.f, HelloWorld::createScene(), ccc3(120, 25, 100));
        //X�ᷴת�л�����
        //CCTransitionScene* transition = CCTransitionFlipX::create(1.2f, HelloWorld::createScene());
        //Y��
        //CCTransitionScene* transition = CCTransitionFlipY::create(1.2f, HelloWorld::createScene());
        //��ת�ǵķ�ת�л�ֱ����
        CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, HelloWorld::createScene());
        //CCTransitionScene* transition = CCTransitionZoomFlipX::create(1.2f, HelloWorld::createScene());
        //���Ž���
        //CCTransitionScene* transition = CCTransitionShrinkGrow::create(1.2f, HelloWorld::createScene());
        //��ת����
        //CCTransitionScene* transition = CCTransitionRotoZoom::create(1.2f, HelloWorld::createScene());
        CCDirector::sharedDirector()->replaceScene(transition);
    }
    if (node->getParent() == game_start_menu)
    {
        CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, Login::createScene());
        CCDirector::sharedDirector()->replaceScene(transition);
        
        /*
        //gameInfoMenu->setVisible(true);
        auto action = JumpTo::create(1,Point(visibleSize.width/2,visibleSize.height/2),50,5);
        gameInfoMenu->runAction(action);
        
        CCLOG("enter helpMenu Click");
        gameInfoMenu->isVisible() ? log("gameInfoMenu visible:true") : log("gameInfoMenu visible:false");
        node->getParent()->setVisible(false);
         */
        
    }
    if (node->getParent() == gameInfoMenu)
    {
        auto action1 = JumpTo::create(1, Point(3*visibleSize.width / 2, 3*visibleSize.height / 2), 50, 5);
        auto action = Sequence::create(action1, CallFuncN::create(CC_CALLBACK_1(StartScene::menuCallBack, this)), NULL);
        gameInfoMenu->runAction(action);
        CCLOG("enter gameInfoMenu click");
        game_start_menu->setVisible(true);
        
    }
    if (node->getParent() == game_center_menu)
    {
        CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, VisionScene::createScene());
        CCDirector::sharedDirector()->replaceScene(transition);
    }
    if (node->getParent() == game_a_menu)
    {
        CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, VisionScene::createScene());
        CCDirector::sharedDirector()->replaceScene(transition);
    }
    if (node->getParent() == game_c_menu)
    {
        CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, DragScene::createScene());
        CCDirector::sharedDirector()->replaceScene(transition);
    }
}
