#pragma once
#include "google/protobuf/service.h"
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
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
    muduo::net::EventLoop m_eventLoop;

    struct ServiceInfo
    {
        google::protobuf::Service* m_service;
        unordered_map<string, const google::protobuf::MethodDescriptor*> m_methondMap;

    };
    unordered_map<string, ServiceInfo> m_serviceMap;
    void OnConnection(const muduo::net::TcpConnectionPtr&);
    void OnMessage(const muduo::net::TcpConnectionPtr&, muduo::net::Buffer*, muduo::Timestamp);
    void SendRpcResponse(const muduo::net::TcpConnectionPtr&, google::protobuf::Message*);
};