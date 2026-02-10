#include "rpcprovider.h"
#include "mprpcapplication.h"
#include "rpcheader.pb.h"
#include "logger.h"
#include "zookeeperutil.h"
void RpcProvider::NotifyService(google::protobuf::Service *service)
{
    ServiceInfo service_info;
    //获取描述信息
    const google::protobuf::ServiceDescriptor* pserviceDesc = service->GetDescriptor();

    string service_name = pserviceDesc->name();
    int methodCnt = pserviceDesc->method_count(); 
    LOG_INFO("%s", service_name.c_str());
    for(int i=0; i<methodCnt; i++)
    {
        const google::protobuf::MethodDescriptor* pmethodDesc = pserviceDesc->method(i);
        string method_name = pmethodDesc->name();
        LOG_INFO("%s", method_name.c_str());
        service_info.m_methondMap.insert({method_name, pmethodDesc});
    }
    service_info.m_service = service;
    m_serviceMap.insert({service_name, service_info});
}

void RpcProvider::Run()
{
    string ip = MprpcApplication::GetInstance().Getconfig().Load("rpcserverip");

    uint16_t port = atoi(MprpcApplication::GetInstance().Getconfig().Load("rpcserverport").c_str());
    
    // InetAddress address(ip, port);
    InetAddress address(port, ip);
    TcpServer server(&m_eventLoop, address);

    server.setConnectionCallback(bind(&RpcProvider::OnConnection, this, placeholders::_1));
    server.setMessageCallback(bind(&RpcProvider::OnMessage, this, placeholders::_1,
    placeholders::_2, placeholders::_3));
    server.setThreadNum(4);
    LOG_INFO("start: %s port: %d", ip.c_str(), port);

    ZkClient zkCli;
    zkCli.Start();
    for(auto& sp: m_serviceMap)
    {
        string service_path = "/"+sp.first;
        zkCli.Create(service_path.c_str(), nullptr, 0);
        for(auto& mp: sp.second.m_methondMap)
        {
            string method_path = service_path+"/"+mp.first;
            char method_path_data[128] = {0};
            sprintf(method_path_data,"%s:%d", ip.c_str(), port);
            zkCli.Create(method_path.c_str(), method_path_data, strlen(method_path_data), ZOO_EPHEMERAL);
        }
    }
    server.start();
    m_eventLoop.loop();
}

/**
 * 处理RPC连接的回调函数
 * 当有新的连接建立或连接断开时被调用
 * @param conn TCP连接的智能指针，包含连接的相关信息
 */
void RpcProvider::OnConnection(const TcpConnectionPtr& conn)
{
    // 检查连接状态是否为已连接
    if(!conn->connected())
    {
        // 如果连接已断开，则关闭连接
        conn->shutdown();
    }
}


void RpcProvider::OnMessage(const TcpConnectionPtr& conn, Buffer* buffer, Timestamp)
{
    string recv_buf = buffer->retrieveAllAsString();

    uint32_t header_size = 0;
    recv_buf.copy((char*)&header_size, 4, 0);

    string rpc_header_str = recv_buf.substr(4, header_size);
    mprpc::RpcHeader rpcHeader;

    string service_name;
    string method_name;
    uint32_t args_size;
    if(rpcHeader.ParseFromString(rpc_header_str))
    {
        service_name = rpcHeader.service_name();
        method_name = rpcHeader.method_name();
        args_size = rpcHeader.args_size();
    }
    else
    {
        LOG_ERROR("rpc_header_str:%s parse error!", rpc_header_str.c_str());
        return;
    }
    string args_str = recv_buf.substr(4+header_size,args_size);

/*
    cout<<"+++++++++++++++" << endl;
    cout<<header_size<<"header_size"<<endl;
    cout<<rpc_header_str<<"rpc_header_str"<<endl;
    cout<<service_name<<"service_name"<<endl;
    cout<<method_name<<"method_name"<<endl;
    cout<<args_str<<"args_str"<<endl;
    cout<<"+++++++++++++++" << endl;
*/
    auto it = m_serviceMap.find(service_name);
    if(it == m_serviceMap.end())
    {
        LOG_ERROR("%s do not have", service_name.c_str());
        return;
    }
    auto mit = it->second.m_methondMap.find(method_name);

    if(mit == it->second.m_methondMap.end())
    {
        LOG_ERROR("method dont have");
        return;
    }


    google::protobuf::Service* service = it->second.m_service;
    const google::protobuf::MethodDescriptor* method = mit->second;

    google::protobuf::Message* request = service->GetRequestPrototype(method).New();
    if(!request->ParseFromString(args_str))
    {
        LOG_ERROR("request parse error: %s", args_str.c_str());
        return;
    }
    google::protobuf::Message* response = service->GetResponsePrototype(method).New();

    google::protobuf::Closure* done = google::protobuf::NewCallback<RpcProvider, const TcpConnectionPtr&, google::protobuf::Message*>
    (this, &RpcProvider::SendRpcResponse, conn, response);


    service->CallMethod(method, nullptr, request, response, done);
}

void RpcProvider::SendRpcResponse(const TcpConnectionPtr& conn, google::protobuf::Message* response)
{
    string response_str;
    if(response->SerializeToString(&response_str))
    {
        conn->send(response_str);
        conn->shutdown();
    }
    else
    {
        LOG_ERROR("Serialize error");
    }

    conn->shutdown();
}