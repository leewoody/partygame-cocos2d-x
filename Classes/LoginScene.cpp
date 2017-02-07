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
    
//��ȡ��������ߴ��С
	CCSize mysize = CCDirector::sharedDirector()->getVisibleSize();
//��ȡ���������ԭ��λ��
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
//��Ļ������λ��
	CCPoint midPos = ccp(mysize.width/2, mysize.height/2);

	

//�༭��ߴ��С
	CCSize editBoxSize = CCSizeMake(mysize.width /10, 60);


//�û���editBoxName
	EditBox* editBoxName = EditBox::create(editBoxSize, Scale9Sprite::create("green_edit.png"));
	editBoxName->setPosition( ccp(mysize.width/2, mysize.height*3/4) );
	this->addChild(editBoxName);

	//��������
	editBoxName->setFontName("fonts/Paint Boy.ttf");
	editBoxName->setFontSize(20);
	editBoxName->setFontColor(ccRED);
	editBoxName->setPlaceHolder("Name:");
	editBoxName->setPlaceholderFontColor(ccWHITE);
	editBoxName->setMaxLength(8);

	//ģʽ��������
    editBoxName->setInputMode(EditBox::InputMode::SINGLE_LINE);
    editBoxName->setInputFlag(EditBox::InputFlag::INTIAL_CAPS_ALL_CHARACTERS);
    editBoxName->setReturnType(EditBox::KeyboardReturnType::DEFAULT);

	//ί�д������this
	editBoxName->setDelegate(this);


//����editBoxPassword
	EditBox* editBoxPassword = EditBox::create(editBoxSize, Scale9Sprite::create("orange_edit.png"));
	editBoxPassword->setPosition( midPos );
	this->addChild(editBoxPassword);

	//��������
	editBoxPassword->setFont("fonts/Marker Felt.ttf", 30);
	editBoxPassword->setFontColor(ccGREEN);
	editBoxPassword->setPlaceHolder("Password:");
	editBoxPassword->setMaxLength(6);

	//ģʽ����
    editBoxPassword->setInputFlag(EditBox::InputFlag::PASSWORD);
    editBoxPassword->setReturnType(EditBox::KeyboardReturnType::DONE);

	//ί�д������this
	editBoxPassword->setDelegate(this);
	

//����editBoxEmail
	EditBox* editBoxEmail = EditBox::create(editBoxSize, Scale9Sprite::create("yellow_edit.png"));
	editBoxEmail->setPosition( ccp(mysize.width/2, mysize.height/4) );
	this->addChild(editBoxEmail);

	//��������
	editBoxEmail->setFont("fonts/Marker Felt.ttf", 30);
	editBoxEmail->setPlaceHolder("Email:");

	//ģʽ��������
    editBoxEmail->setInputMode(EditBox::InputMode::EMAIL_ADDRESS);
    editBoxEmail->setReturnType(EditBox::KeyboardReturnType::SEND);

	//ί�д������this
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


//��ʼ�༭
void Login::editBoxEditingDidBegin(EditBox* editBox)
{
	CCLog("editBox %p DidBegin !", editBox);
}

//�����༭
void Login::editBoxEditingDidEnd(EditBox* editBox)
{
	CCLog("editBox %p DidEnd !", editBox);
}

//�༭�����ݸı�
void Login::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
	CCLog("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

//����return����
void Login::editBoxReturn(EditBox* editBox)
{
	CCLog("editBox %p was returned !",editBox);
}


//�رճ���
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
