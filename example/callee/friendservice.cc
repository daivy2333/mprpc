#include<iostream>
#include<string>
#include "friend.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
#include <vector>
#include "logger.h"
using namespace std;

class FriendService : public fixbug::FriendServiceRpc
{
public:
    vector<string> GetFriendList(uint32_t userid)
    {
        cout<< "get friendlist service "<< userid<< endl;
        vector<string> vec;
        vec.push_back("demon1");
        vec.push_back("kk");
        vec.push_back("dvy");
        return vec;
    }

    void GetFriendList(::google::protobuf::RpcController* controller,
    const ::fixbug::GetFriendListRequest* request,
    ::fixbug::GetFriendListResponse* response,
    ::google::protobuf::Closure* done)
    {
        uint32_t userid = request->userid();
        vector<string> friendsList = GetFriendList(userid);
        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("bam");

        for(string& name : friendsList)
        {
            string* p = response->add_friends();
            *p = name;
        }
        done->Run();
    }
private:
};

int main(int argc, char **argv)
{
    LOG_INFO("first log msg\n");
    LOG_ERROR("%s:%s:%d\n", __FILE__,__FUNCTION__, __LINE__);
    // 框架初始化操作
    MprpcApplication::Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new FriendService());


    provider.Run();

    return 0;
}