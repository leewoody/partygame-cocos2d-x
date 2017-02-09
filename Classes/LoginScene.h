#ifndef __Login_SCENE_H__
#define __Login_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;

#include "HTTPManager.h"

class Login : public cocos2d::CCLayer,EditBoxDelegate,public HTTPManagerDelegate
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    static cocos2d::Scene* createScene();

    void menuCallback(CCObject* pSender);
    CREATE_FUNC(Login);
	
    EditBox* editBoxName;
    EditBox* editBoxPassword;

    Size visibleSize;
    CCString* uid;
    CCString* pwd;


    int questionIndex = 1;//the questionIdex means the qustion`s index,normally is which color of the card is the answer

    int mode = 0;//0 represent disorder,1 represent order

    //question label
    cocos2d::CCLabelTTF* questionLabel;
    cocos2d::CCLabelTTF* questionLabe2;
    cocos2d::CCLabelTTF* tipLabel;
    
    CCMenu* exitMenu;
    CCMenu* confirmMenu;
    
	virtual void editBoxEditingDidBegin(EditBox* editBox); //开始编辑
	virtual void editBoxEditingDidEnd(EditBox* editBox); //结束编辑
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text); //编辑框文字改变
	virtual void editBoxReturn(EditBox* editBox); //触发return后的回调函数
    
    virtual void onHttpManagerRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) ;
    
private:
    
    void writeFileFromRequest(cocos2d::network::HttpResponse *response,std::string filename);
    void LoginProcess();

};

#endif // __Login_SCENE_H__
