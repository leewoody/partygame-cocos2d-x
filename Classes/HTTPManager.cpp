//
//  HTTPManager.cpp
//  ht_mobile_cpp
//
//  Created by 杜甲 on 14-6-12.
//
//

#include "HTTPManager.h"
#include <iostream>


//#include "../UnZip/DJZipArchive.h"
#define HTTPHeader "http://www.epicc.com.cn/QrDmzBastionNB/BastionServlet"

HTTPManager::HTTPManager()
{
}
HTTPManager::~HTTPManager()
{
}
void HTTPManager::sendGetRequest(std::string url,std::string requestTag)
{
    HttpRequest* request = new HttpRequest();//使用HttpRequest无参的构造函数，提供了一个很好的默认设置
    request->setRequestType(cocos2d::network::HttpRequest::Type::GET);//设置连接方式，常用GET和POST
    request->setUrl(url.c_str());//设置连接地址
    //设置回调，在onHttpRequestCompleted中读取数据
    //request->setResponseCallback(CC_CALLBACK_2(HTTPManager::onHttpRequestCompleted, this));
    request->setResponseCallback(this, httpresponse_selector(HTTPManager::onHttpRequestCompleted));

    request->setTag(requestTag.c_str());//设置Tag
    network::HttpClient::getInstance()->enableCookies(NULL);
    network::HttpClient::getInstance()->send(request);//添加到HttpClient任务队列
    request->release();//释放连接
}

void HTTPManager::getFormData(std::string parameter)
{
    HttpRequest* request = new HttpRequest();
    request->setUrl(HTTPHeader);
    request->setRequestType(HttpRequest::Type::POST);

    //request->setResponseCallback(CC_CALLBACK_2(HTTPManager::onHttpRequestCompleted, this));
    request->setResponseCallback(this, httpresponse_selector(HTTPManager::onHttpRequestCompleted));


    //write the post data
    const char* postData = StringUtils::format("parameter=%s",parameter.c_str()).c_str();
    log("postData = %s",postData);
    request->setRequestData(postData, strlen(postData));
    request->setTag("getFormData");
    log("url = %s",request->getUrl());

    HttpClient::getInstance()->send(request);
    request->release();
}

void HTTPManager::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
    if (!response) {
        return;
    }


    if (0 != strlen(response->getHttpRequest()->getTag())) {
        log("%s compeled",response->getHttpRequest()->getTag());
    }



    long statusCode = response->getResponseCode();

    char statusString[64] = {};

    sprintf(statusString, "HTTP Status Code:%ld , tag = %s",statusCode,response->getHttpRequest()->getTag());
    log("response code:%s",statusString);


    if (!response->isSucceed()) {
        log("response failed");
        log("error buffer:%s",response->getErrorBuffer());
        return;
    }


    if (_httpManagerDelegate) {
        _httpManagerDelegate->onHttpManagerRequestCompleted(sender, response);
    }



    const char* resTag = response->getHttpRequest()->getTag();
}

void HTTPManager::writeFileFromRequest(cocos2d::network::HttpResponse *response,std::string filename)
{

    std::vector<char>* buffer = response->getResponseData();
    printf("Http Test,dump data:");
    std::string path= FileUtils::getInstance()->getWritablePath();
    std::string fullPath =  path + filename;
    FILE* fp = fopen(fullPath.c_str(), "wb");


    log("将文件写入本地 %s",fullPath.c_str());



    unsigned char bf;
    for (unsigned int i  = 0; i < buffer->size(); i++) {

        bf = buffer->at(i);
        fwrite(&bf, 1, 1, fp);

    }
    fclose(fp);

}

void HTTPManager::addHttpListener(ccHttpManagerCallback &callback)
{
    _eventCallback = callback;

}


