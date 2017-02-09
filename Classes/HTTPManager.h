//
//  HTTPManager.h
//  ht_mobile_cpp
//
//  Created by 杜甲 on 14-6-12.
//
//

#ifndef __ht_mobile_cpp__HTTPManager__
#define __ht_mobile_cpp__HTTPManager__

#include "cocos2d.h"
#include "../cocos2d/extensions/cocos-ext.h"
#include "network/HttpClient.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace network;
class  HTTPManagerDelegate
{
public:
   virtual void onHttpManagerRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) = 0;
};

class HTTPManager:public Ref
{
public:
    HTTPManager();
    ~HTTPManager();
    CC_SYNTHESIZE(HTTPManagerDelegate*, _httpManagerDelegate, HttpDelegate);
    //Http Response Callback
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    void getFormData(std::string parameter);
    void sendGetRequest(std::string url,std::string requestTag);
    void sendPostRequest(std::string url,std::string requestTag,const char* postData);

    //void writeFileFromRequest(cocos2d::network::HttpResponse *response,std::string filename);
    typedef std::function<void(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)> ccHttpManagerCallback;
    void addHttpListener(ccHttpManagerCallback& callback);

private:
    ccHttpManagerCallback _eventCallback;
};


#endif /* defined(__ht_mobile_cpp__HTTPManager__) */
