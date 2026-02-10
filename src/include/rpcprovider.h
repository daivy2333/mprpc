#pragma once
#include "google/protobuf/service.h"
#include "TcpServer.h"
#include "Eventloop.h"
#include "InetAddress.h"
#include "TcpConnection.h"
#include<functional>
#include <google/protobuf/descriptor.h>
#include<unordered_map>
using namespace std;
class RpcProvider
{
public:
    void NotifyService(google::protobuf::Service *service); // rpc方法接口

    void Run(); // 启动服务，开始rpc远程网络调用
private:
    EventLoop m_eventLoop;

    struct ServiceInfo
    {
        google::protobuf::Service* m_service;
        unordered_map<string, const google::protobuf::MethodDescriptor*> m_methondMap;

    };
    unordered_map<string, ServiceInfo> m_serviceMap;
    void OnConnection(const TcpConnectionPtr&);
    void OnMessage(const TcpConnectionPtr&, Buffer*, Timestamp);
    void SendRpcResponse(const TcpConnectionPtr&, google::protobuf::Message*);
};