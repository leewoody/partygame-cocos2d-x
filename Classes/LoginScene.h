#ifndef __Login_SCENE_H__
#define __Login_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

#include "cocos-ext.h"
using namespace cocos2d::extension;

class Login : public cocos2d::CCLayer,EditBoxDelegate
{
public:
    virtual bool init();  
    static cocos2d::CCScene* scene();
    static cocos2d::Scene* createScene();

    void menuCallback(CCObject* pSender);
    CREATE_FUNC(Login);
	
    Size visibleSize;
    
    //question label
    cocos2d::CCLabelTTF* questionLabel;

    CCMenu* exitMenu;
    CCMenu* confirmMenu;
    
	virtual void editBoxEditingDidBegin(EditBox* editBox); //��ʼ�༭
	virtual void editBoxEditingDidEnd(EditBox* editBox); //�����༭
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text); //�༭�����ָı�
	virtual void editBoxReturn(EditBox* editBox); //����return��Ļص�����
};

#endif // __Login_SCENE_H__
