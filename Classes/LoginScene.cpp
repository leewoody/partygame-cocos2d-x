#include "LoginScene.h"
#include "StartScene.h"
#include "CXmlStream.h"

#include "HTTPManager.h"
#include "json/rapidjson.h"
#include "json/document.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
//cocos2d/cocos/2d/platform/android/jni/JniHelper.cpp
#include "../cocos2d/cocos/2d/platform/android/jni/JniHelper.h" //这里的路径要根据你工程的实际情况进行更改
#include <android/log.h>

#if 1
#define  LOG_TAG    "JniHelper"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...)
#endif

#endif

USING_NS_CC;

std::string Service_Key="fd%@$rw15902!";
std::string SERVICEUrl = "https://cloudicweb.nhi.gov.tw/nhiapp/";
std::string SERVICE_LoginCheck2 = SERVICEUrl + "service/app_accountlogin.ashx";

std::string HealthPassbookSignUpUrl = "https://med.nhi.gov.tw/ihke2000/IHKE2000S01.aspx";
std::string HealthDataUrl1          = "https://med.nhi.gov.tw/IHKE8000/IHKE8109s01.aspx";
std::string HealthDataUrl2          = "https://med.nhi.gov.tw/IHKE8000/IHKE8202S01.aspx";

std::string sKey_PARAM = "ServiceKey";
std::string acc_PARAM = "Account";
std::string pass_PARAM = "PassPort";
std::string act_PARAM = "ActId";
std::string device_PARAM = "DeviceID";
std::string token_PARAM = "Token";

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
    questionLabel = CCLabelTTF::create(CXmlStream::GetStringByKeyFromFile("question_tips.xml","question_01"), "fonts/Paint Boy.ttf", 32);
    questionLabel->setAnchorPoint(ccp(0,1));
    questionLabel->setPosition(ccp(70, 500));
    questionLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    questionLabel->setDimensions(CCSize(300, 300));
    questionLabel->setColor(ccc3(0, 0, 0));
    this->addChild(questionLabel, 2);

    //********************************** initialize the question label **********************************
    questionLabe2 = CCLabelTTF::create(CXmlStream::GetStringByKeyFromFile("question_tips.xml","question_02"), "fonts/Paint Boy.ttf", 20);
    questionLabe2->setAnchorPoint(ccp(0,1));
    questionLabe2->setPosition(ccp(450, 500));
    questionLabe2->setHorizontalAlignment(TextHAlignment::LEFT);
    questionLabe2->setDimensions(CCSize(750, 500));
    questionLabe2->setColor(ccc3(0, 0, 0));
    this->addChild(questionLabe2, 2);

    //********************************** initialize the tip label **********************************
    tipLabel = CCLabelTTF::create("Tips", "fonts/Paint Boy.ttf", 22);
    tipLabel->setAnchorPoint(ccp(0,1));
    tipLabel->setPosition(ccp(680, 750));
    tipLabel->setHorizontalAlignment(TextHAlignment::LEFT);
    tipLabel->setDimensions(CCSize(500, 500));
    tipLabel->setColor(ccc3(100, 100, 100));
    this->addChild(tipLabel, 2);

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
        tipLabel->setString("Tips: Login...");
        
        mode = static_cast<int>(CCRANDOM_0_1() * 2);//the answer`s mode
        //CCString* xmlName = CCString::createWithFormat("question%d.xml", (int)(mode+1));

        CCString* xmlName = CCString::createWithFormat("question_bonus.xml");

        questionIndex = static_cast<int>(CCRANDOM_0_1() * 3+1);//the question index, which color of the card is the righr answer
        CCString* question_sr = CCString::createWithFormat("bonus_%02d",questionIndex);//define the qustion key string to get qustion string

        //MessageBox("call httpclient and Login to get the points.","Alert");
        questionLabel->setString(CXmlStream::GetStringByKeyFromFile(xmlName->getCString(), question_sr->getCString()));

        LoginProcess();
        
    }

}

void Login::LoginProcess()
{
    
    const char *str_uid = editBoxName->getText();
    const char *str_pwd = editBoxPassword->getText();
    
    int uid_len=strlen(str_uid);
    int pwd_len=strlen(str_pwd);
    if(uid_len == 0 || pwd_len == 0)
    {
        tipLabel->setString("Tips: Please enter the UID/PWD...");
        return;
        
    }
    
    CCString* uuid=CCString::createWithFormat("F5NKCY010699,cad244603e0368ea");
    //做应用时很多时候都得获取到每个设备的机器码
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    jobject jobj;
    //getStaticMethodInfo方法是调用静态类的，也可以不用调用静态类的getMethodInfo
    bool b = JniHelper::getStaticMethodInfo(minfo,
                                            "org.cocos2dx.cpp.AppActivity", //类路径
                                            "getUUID", //静态方法名
                                            "()Ljava/lang/String;");//括号里的是参数，后面的是返回值。
    log("CC_PLATFORM_ANDROIDCC_PLATFORM_ANDROIDCC_PLATFORM_ANDROIDCC_PLATFORM_ANDROIDCC_PLATFORM_ANDROID");
    if(b)
    {
        std::string ret;
        //std::string uuid;
        
        jstring jret = (jstring)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        ret = JniHelper::jstring2string(jret);
        minfo.env->DeleteLocalRef(jret);
        minfo.env->DeleteLocalRef(minfo.classID);
        
        uuid=CCString::createWithFormat("%s", ret.c_str());
        
    }
    else
    {
        log("JniHelper::getMethodInfo error...");
    }
#endif
    strUUID=uuid->getCString();
    CCString* postData=CCString::createWithFormat("%s=%s&%s=%s&%s=%s&%s=%s&%s=", sKey_PARAM.c_str(), Service_Key.c_str(), acc_PARAM.c_str(), str_uid, pass_PARAM.c_str(), str_pwd, act_PARAM.c_str(), uuid->getCString(), device_PARAM.c_str());
    
    //const char* postData = "ServiceKey=fd%@$rw15902!&Account=d121146818&PassPort=d121146818&ActId=F5NKCY010699,cad244603e0368ea&DeviceID=";
    
    log("postData:%s", postData->getCString() );
    
    auto httpManager = new HTTPManager();
    httpManager->retain();
    httpManager->setHttpDelegate(this);
    httpManager->sendPostRequest(SERVICE_LoginCheck2, "login", postData->getCString() );
}

void Login::onHttpManagerRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (strcmp(response->getHttpRequest()->getTag(), "login") == 0)
    {
        CCLOG("Get success");
        
        writeFileFromRequest(response,"qwe.json");
        std::vector<char>* buffer = response->getResponseData();
        std::string res;
        res.insert(res.begin(), buffer->begin(), buffer->end());
        
        tipLabel->setString(res);
        ProcessToken(res);
        
    }
    if (strcmp(response->getHttpRequest()->getTag(), "session") == 0)
    {
        CCLOG("Get success");
        
        writeFileFromRequest(response,"session.html");
        std::vector<char>* buffer = response->getResponseData();
        std::string res;
        res.insert(res.begin(), buffer->begin(), buffer->end());
        
        tipLabel->setString(res);
        DataProcess(strToken,strUUID);
        
    }
    if (strcmp(response->getHttpRequest()->getTag(), "HealthDataUrl1") == 0)
    {
        CCLOG("HealthDataUrl1 Get success");
        
        writeFileFromRequest(response,"HealthDataUrl1.html");
        std::vector<char>* buffer = response->getResponseData();
        std::string res;
        res.insert(res.begin(), buffer->begin(), buffer->end());
        
        //tipLabel->setString(res);
        DataProcess2(strToken,strUUID);
        
    }
    if (strcmp(response->getHttpRequest()->getTag(), "HealthDataUrl2") == 0)
    {
        CCLOG("HealthDataUrl2 Get success");
        
        writeFileFromRequest(response,"HealthDataUrl2.html");
        std::vector<char>* buffer = response->getResponseData();
        std::string res;
        res.insert(res.begin(), buffer->begin(), buffer->end());
        
        //tipLabel->setString(res);
        //DataProcess(strToken,strUUID);
        
    }
}

void Login::writeFileFromRequest(cocos2d::network::HttpResponse *response,std::string filename)
{
    //http header
    std::vector<char>* buffer0 = response->getResponseHeader();
    std::string path0= FileUtils::getInstance()->getWritablePath();
    std::string fullPath0 =  path0 + filename + ".header";
    FILE* fp0 = fopen(fullPath0.c_str(), "wb");

    log("header writeFileFromRequest %s",fullPath0.c_str());

    std::string resHeader;
    resHeader.insert(resHeader.begin(), buffer0->begin(), buffer0->end());
    log("\nHttp Test,dump header:\n%s\n", resHeader.c_str());
    
    unsigned char bf0;
    for (unsigned int i  = 0; i < buffer0->size(); i++) {

        bf0 = buffer0->at(i);
        //printf("%c", bf0);
        fwrite(&bf0, 1, 1, fp0);

    }
    fclose(fp0);

    std::vector<char>* buffer = response->getResponseData();
    std::string path= FileUtils::getInstance()->getWritablePath();
    std::string fullPath =  path + filename;
    FILE* fp = fopen(fullPath.c_str(), "wb");


    log("data writeFileFromRequest %s",fullPath.c_str());
    
    std::string resData;
    resData.insert(resData.begin(), buffer->begin(), buffer->end());
    log("\nHttp Test,dump data:\n%s\n", resData.c_str());
    
    unsigned char bf;
    for (unsigned int i  = 0; i < buffer->size(); i++) {

        bf = buffer->at(i);
        //printf("%c", bf);
        fwrite(&bf, 1, 1, fp);

    }
    fclose(fp);

}

/*
 {"IsProcessOK":true,"ReturnCode":"0000","Message":"正確","Token":"428E01x18276s0421C22621Z360f0i024W58Hd2j2J9B72m3a","Account":null,"InsType":null}
*/

void Login::ProcessToken(std::string strResult)
{
    //std::string str = "{\"hello\" : \"word\"}";
    //CCLOG("%s\n", strResult.c_str());
    rapidjson::Document d;
    d.Parse<0>(strResult.c_str());
    if (d.HasParseError())  //打印解析错误
    {
        CCLOG("GetParseError %s\n",d.GetParseError());
    }
    
    if (d.IsObject() && d.HasMember("IsProcessOK") && d.HasMember("ReturnCode")) {
        
        CCLOG("%d, %s\n", d["IsProcessOK"].GetBool(), d["ReturnCode"].GetString() );//打印获取hello的值
        std::string strReturnCode =d["ReturnCode"].GetString();
        if(strReturnCode == "0000")
        {
            CCLOG("Token: %s\n", d["Token"].GetString());//打印获取hello的值
            strToken=d["Token"].GetString();
            SessionProcess(strToken,strUUID);
        }
        
    }
}

void Login::SessionProcess(std::string sToken, std::string sActId)
{
    CCString* postData=CCString::createWithFormat("%s=%s&%s=%s", token_PARAM.c_str(), sToken.c_str(), act_PARAM.c_str(), sActId.c_str());
    
    //const char* postData = "ServiceKey=fd%@$rw15902!&Account=d121146818&PassPort=d121146818&ActId=F5NKCY010699,cad244603e0368ea&DeviceID=";
    
    log("SessionProcess postData:%s", postData->getCString() );
    
    auto httpManager = new HTTPManager();
    httpManager->retain();
    httpManager->setHttpDelegate(this);
    httpManager->sendPostRequest(HealthPassbookSignUpUrl, "session", postData->getCString() );

    
}

void Login::DataProcess(std::string sToken, std::string sActId)
{
    CCString* postData=CCString::createWithFormat("%s=%s&%s=%s", token_PARAM.c_str(), sToken.c_str(), act_PARAM.c_str(), sActId.c_str());
    
    //const char* postData = "ServiceKey=fd%@$rw15902!&Account=d121146818&PassPort=d121146818&ActId=F5NKCY010699,cad244603e0368ea&DeviceID=";
    
    log("DataProcess postData:%s", postData->getCString() );
    
    auto httpManager = new HTTPManager();
    httpManager->retain();
    httpManager->setHttpDelegate(this);
    httpManager->sendPostRequest(HealthDataUrl1, "HealthDataUrl1", postData->getCString() );
    
    
}

void Login::DataProcess2(std::string sToken, std::string sActId)
{
    CCString* postData=CCString::createWithFormat("%s=%s&%s=%s", token_PARAM.c_str(), sToken.c_str(), act_PARAM.c_str(), sActId.c_str());
    
    //const char* postData = "ServiceKey=fd%@$rw15902!&Account=d121146818&PassPort=d121146818&ActId=F5NKCY010699,cad244603e0368ea&DeviceID=";
    
    log("DataProcess2 postData:%s", postData->getCString() );
    
    auto httpManager = new HTTPManager();
    httpManager->retain();
    httpManager->setHttpDelegate(this);
    httpManager->sendPostRequest(HealthDataUrl2, "HealthDataUrl2", postData->getCString() );
    
    
}
