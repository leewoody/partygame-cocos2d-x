#include "LoginScene.h"
#include "StartScene.h"
#include "CXmlStream.h"

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
	CCSize editBoxSize = CCSizeMake(mysize.width /5, 60);


    CCSprite* spBackground_01 = CCSprite::create("bg_b.png");
    spBackground_01->setAnchorPoint(ccp(0, 0));
    spBackground_01->setPosition(ccp(origin.x, origin.y));
    //spBackground_01->setScale(1);
    //spBackground_01->setVisible(false);
    this->addChild(spBackground_01, 0);
    
    /*
    CCSprite* stateBar = CCSprite::create("StateBar.png");
    //stateBar->setAnchorPoint(ccp(0.5,0));
    stateBar->setVisible(true);
    CCPoint STATE_BAR_POSITION = ccp(visibleSize.width / 2 + origin.x, visibleSize.height - stateBar->getContentSize().height / 2);
    stateBar->setPosition(STATE_BAR_POSITION);
    //stateBar->setScale(1.5f);
    //stateBar->setTextureRect(CCRectMake(0,0,300,200));
    this->addChild(stateBar, 1);
     */

    //用户名editBoxName
	editBoxName = EditBox::create(editBoxSize, Scale9Sprite::create("green_edit.png"));
    editBoxName->setAnchorPoint(ccp(0,1));
    editBoxName->setPosition(ccp(200, 750));

	//editBoxName->setPosition( ccp(mysize.width/2, mysize.height*3/4) );
	this->addChild(editBoxName);

	//属性设置
	editBoxName->setFontName("fonts/Paint Boy.ttf");
	editBoxName->setFontSize(20);
	editBoxName->setFontColor(ccRED);
	editBoxName->setPlaceHolder("Name:");
	editBoxName->setPlaceholderFontColor(ccWHITE);
	editBoxName->setMaxLength(30);

	//模式类型设置
    editBoxName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    editBoxName->setInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS);
    editBoxName->setReturnType(EditBox::KeyboardReturnType::DEFAULT);

	//委托代理对象this
	editBoxName->setDelegate(this);


//密码editBoxPassword
	editBoxPassword = EditBox::create(editBoxSize, Scale9Sprite::create("orange_edit.png"));
    editBoxPassword->setAnchorPoint(ccp(0,1));
    editBoxPassword->setPosition(ccp(200, 650));

    //editBoxPassword->setPosition( midPos );
	this->addChild(editBoxPassword);

	//属性设置
	editBoxPassword->setFont("fonts/Marker Felt.ttf", 30);
	editBoxPassword->setFontColor(ccGREEN);
	editBoxPassword->setPlaceHolder("Password:");
	editBoxPassword->setMaxLength(30);

	//模式设置
    editBoxPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    editBoxPassword->setReturnType(EditBox::KeyboardReturnType::DONE);

	//委托代理对象this
	editBoxPassword->setDelegate(this);
	

    /*
//邮箱editBoxEmail
	EditBox* editBoxEmail = EditBox::create(editBoxSize, Scale9Sprite::create("yellow_edit.png"));
    editBoxEmail->setAnchorPoint(ccp(0,1));
    editBoxEmail->setPosition(ccp(600, 300));

    //editBoxEmail->setPosition( ccp(mysize.width/2, mysize.height/4) );
	this->addChild(editBoxEmail);

	//属性设置
	editBoxEmail->setFont("fonts/Marker Felt.ttf", 30);
	editBoxEmail->setPlaceHolder("Email:");

	//模式类型设置
    editBoxEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
    editBoxEmail->setReturnType(EditBox::KeyboardReturnType::SEND);

	//委托代理对象this
	editBoxEmail->setDelegate(this);

     */
    
    CCLOG("into create Login exitItem");
    auto exitItem = MenuItemImage::create("CloseNormal.png", "CloseNormal.png", CC_CALLBACK_1(Login::menuCallback, this));
    exitMenu = Menu::create(exitItem, NULL);
    exitMenu->setPosition(visibleSize.width - exitItem->getContentSize().width / 2 - 13, visibleSize.height - exitItem->getContentSize().height / 2 - 1);
    exitMenu->setVisible(true);
    this->addChild(exitMenu, 2);
    
    CCLOG("into create Login exitItem");
    auto confirmItem = MenuItemImage::create("confirm.png", "confirm.png", CC_CALLBACK_1(::Login::menuCallback, this));
    confirmItem->setScale(0.5);
    confirmMenu = Menu::create(confirmItem, NULL);
    //confirmMenu->setPosition(visibleSize.width - confirmItem->getContentSize().width/2+50, confirmItem->getContentSize().height / 2 - 36);
    confirmMenu->setAnchorPoint(ccp(0,1));
    confirmMenu->setPosition(ccp(600, 600));

    confirmMenu->setVisible(true);
    this->addChild(confirmMenu, 2);

    //********************************** initialize the question label **********************************
    questionLabel = CCLabelTTF::create(CXmlStream::GetStringByKeyFromFile("question_tips.xml","question_01"), "Arial", 32);
    questionLabel->setAnchorPoint(ccp(0,1));
    questionLabel->setPosition(ccp(70, 500));
    questionLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    questionLabel->setDimensions(CCSize(300, 300));
    questionLabel->setColor(ccc3(0, 0, 0));
    this->addChild(questionLabel, 2);
    
    //********************************** initialize the question label **********************************
    questionLabe2 = CCLabelTTF::create(CXmlStream::GetStringByKeyFromFile("question_tips.xml","question_02"), "Arial", 20);
    questionLabe2->setAnchorPoint(ccp(0,1));
    questionLabe2->setPosition(ccp(450, 500));
    questionLabe2->setHorizontalAlignment(TextHAlignment::LEFT);
    questionLabe2->setDimensions(CCSize(750, 500));
    questionLabe2->setColor(ccc3(0, 0, 0));
    this->addChild(questionLabe2, 2);
    
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
    const char *str = editBox->getText();
    
	CCLog("editBox %p DidEnd !:%s", editBox, str);
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
        mode = static_cast<int>(CCRANDOM_0_1() * 2);//the answer`s mode
        //CCString* xmlName = CCString::createWithFormat("question%d.xml", (int)(mode+1));

        CCString* xmlName = CCString::createWithFormat("question_bonus.xml", (int)(mode+1));

        questionIndex = static_cast<int>(CCRANDOM_0_1() * 3+1);//the question index, which color of the card is the righr answer
        CCString* question_sr = CCString::createWithFormat("bonus_%02d",questionIndex);//define the qustion key string to get qustion string

        MessageBox("call httpclient and Login to get the points.","Alert");
        questionLabel->setString(CXmlStream::GetStringByKeyFromFile(xmlName->getCString(), question_sr->getCString()));
        
        const char *str_uid = editBoxName->getText();
        const char *str_pwd = editBoxPassword->getText();
        
        CCLog("editBox :%s, %s", str_uid, str_pwd);

    }
    
}
