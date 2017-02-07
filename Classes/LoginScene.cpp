#include "LoginScene.h"
#include "StartScene.h"

USING_NS_CC;


Scene* Login::createScene()
{
    CCLOG("into create VisionScene");
    auto scene=Scene::create();
    auto layer=Login::create();
    scene->addChild(layer);
    //scene->autorelease();
    CCLOG("out create VisionScene");
    return scene;
}

CCScene* Login::scene()
{
    CCScene *scene = CCScene::create();
    Login *layer = Login::create();
    scene->addChild(layer);
    return scene;
}


bool Login::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    visibleSize=Director::getInstance()->getVisibleSize();
    
//获取可视区域尺寸大小
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();
//获取可视区域的原点位置
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//屏幕正中心位置
	CCPoint midPos = ccp(mysize.width/2, mysize.height/2);

	

//编辑框尺寸大小
	CCSize editBoxSize = CCSizeMake(mysize.width /10, 60);


//用户名editBoxName
	EditBox* editBoxName = EditBox::create(editBoxSize, Scale9Sprite::create("green_edit.png"));
	editBoxName->setPosition( ccp(mysize.width/2, mysize.height*3/4) );
	this->addChild(editBoxName);

	//属性设置
	editBoxName->setFontName("fonts/Paint Boy.ttf");
	editBoxName->setFontSize(20);
	editBoxName->setFontColor(ccRED);
	editBoxName->setPlaceHolder("Name:");
	editBoxName->setPlaceholderFontColor(ccWHITE);
	editBoxName->setMaxLength(8);

	//模式类型设置
    editBoxName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    editBoxName->setInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS);
    editBoxName->setReturnType(EditBox::KeyboardReturnType::DEFAULT);

	//委托代理对象this
	editBoxName->setDelegate(this);


//密码editBoxPassword
	EditBox* editBoxPassword = EditBox::create(editBoxSize, Scale9Sprite::create("orange_edit.png"));
	editBoxPassword->setPosition( midPos );
	this->addChild(editBoxPassword);

	//属性设置
	editBoxPassword->setFont("fonts/Marker Felt.ttf", 30);
	editBoxPassword->setFontColor(ccGREEN);
	editBoxPassword->setPlaceHolder("Password:");
	editBoxPassword->setMaxLength(6);

	//模式设置
    editBoxPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    editBoxPassword->setReturnType(EditBox::KeyboardReturnType::DONE);

	//委托代理对象this
	editBoxPassword->setDelegate(this);
	

//邮箱editBoxEmail
	EditBox* editBoxEmail = EditBox::create(editBoxSize, Scale9Sprite::create("yellow_edit.png"));
	editBoxEmail->setPosition( ccp(mysize.width/2, mysize.height/4) );
	this->addChild(editBoxEmail);

	//属性设置
	editBoxEmail->setFont("fonts/Marker Felt.ttf", 30);
	editBoxEmail->setPlaceHolder("Email:");

	//模式类型设置
    editBoxEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
    editBoxEmail->setReturnType(EditBox::KeyboardReturnType::SEND);

	//委托代理对象this
	editBoxEmail->setDelegate(this);

    CCLOG("into create Login exitItem");
    auto exitItem = MenuItemImage::create("game_b_exit.png", "game_b_exit.png", CC_CALLBACK_1(Login::menuCallback, this));
    exitMenu = Menu::create(exitItem, NULL);
    exitMenu->setPosition(visibleSize.width - exitItem->getContentSize().width / 2 - 13, visibleSize.height - exitItem->getContentSize().height / 2 - 1);
    exitMenu->setVisible(true);
    this->addChild(exitMenu, 2);
    
    CCLOG("into create Login exitItem");
    auto confirmItem = MenuItemImage::create("confirm.png", "confirm.png", CC_CALLBACK_1(::Login::menuCallback, this));
    confirmItem->setScale(0.5);
    confirmMenu = Menu::create(confirmItem, NULL);
    confirmMenu->setPosition(visibleSize.width - confirmItem->getContentSize().width/2+50, confirmItem->getContentSize().height / 2 - 36);
    confirmMenu->setVisible(true);
    this->addChild(confirmMenu, 2);

	return true;
}


//开始编辑
void Login::editBoxEditingDidBegin(EditBox* editBox)
{
	CCLog("editBox %p DidBegin !", editBox);
}

//结束编辑
void Login::editBoxEditingDidEnd(EditBox* editBox)
{
	CCLog("editBox %p DidEnd !", editBox);
}

//编辑框内容改变
void Login::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

//触发return返回
void Login::editBoxReturn(EditBox* editBox)
{
	CCLog("editBox %p was returned !",editBox);
}


//关闭程序
void Login::menuCallback(CCObject* pSender)
{
#if 0
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
#endif

    CCNode* node = (CCNode*)pSender;
    
    if (node->getParent() == exitMenu)
    {
        CCScene* scene = StartScene::createScene();
        CCTransitionScene* transition = CCTransitionFlipAngular::create(1.2f, scene);
        CCDirector::sharedDirector()->replaceScene(transition);
        node->getParent()->setVisible(false);
    }
    if (node->getParent() == confirmMenu)
    {
        MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    }
}
