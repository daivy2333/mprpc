#include <iostream>

#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"
int main(int argc, char** argv)
{
    MprpcApplication::Init(argc, argv);

    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());

    fixbug::LoginRequest request;
    request.set_name("daivy");
    request.set_pwd("123456");

    fixbug::LoginResponse response;

    stub.Login(nullptr, &request, &response, nullptr);

    if(response.result().errcode() == 0)
    {
        cout<< "rpc login response success:" << response.success() << endl;
    }
    else
    {
        cout<< "rpc login response error" << response.result().errmsg() << endl;
    }


    fixbug::RegisterRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("6666");
    fixbug::RegisterResponse rsp;

    stub.Register(nullptr, &req, &rsp, nullptr);
    if(rsp.result().errcode() == 0)
    {
        cout<< "rpc rege response success:" << response.success() << endl;
    }
    else
    {
        cout<< "rpc regee response error" << response.result().errmsg() << endl;
    }

    return 0;
}