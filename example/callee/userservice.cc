#include<iostream>
#include<string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
using namespace std;
class UserService : public fixbug::UserServiceRpc
{
public:
    bool Login(string name, string pwd)
    {
        cout << "login"<< endl;
        cout << "name:"<<name<<"pwd:"<<pwd<<endl;
        return true;
    }

    bool Register(uint32_t id, string name, string pwd)
    {
        cout << "register!"<< endl;
        cout<< id<<" "<<name<< " "<<pwd<<endl;
        return true;
    }
    void Login(::google::protobuf::RpcController* controller,
    const ::fixbug::LoginRequest* request,
    ::fixbug::LoginResponse* response,
    ::google::protobuf::Closure* done)
    {
        string name = request->name();
        string pwd = request->pwd();

        bool login_result = Login(name,pwd);

        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("none error");
        response->set_success(login_result);

        done->Run();
    }
    void Register(::google::protobuf::RpcController* controller,
    const ::fixbug::RegisterRequest* request,
    ::fixbug::RegisterResponse* response,
    ::google::protobuf::Closure* done)
    {
        uint32_t id = request->id();
        string name = request->name();
        string pwd = request->pwd();

        bool ret = Register(id, name, pwd);

        response->mutable_result()->set_errcode(0);
        response->mutable_result()->set_errmsg("");
        response->set_success(ret);

        done->Run();
    }
};

int main(int argc, char **argv)
{
    // 框架初始化操作
    MprpcApplication::Init(argc, argv);

    RpcProvider provider;
    provider.NotifyService(new UserService());


    provider.Run();

    return 0;
}