#include <iostream>

#include "mprpcapplication.h"
#include "friend.pb.h"


int main(int argc, char** argv)
{
    MprpcApplication::Init(argc, argv);

    fixbug::FriendServiceRpc_Stub stub(new MprpcChannel());

    fixbug::GetFriendListRequest request;
    request.set_userid(1000);

    fixbug::GetFriendListResponse response;

    MprpcController controller;
    stub.GetFriendList(&controller, &request, &response, nullptr);

    if(controller.Failed())
    {
        cout<< controller.ErrorText()<< endl;
    }
    else
    {
    if(response.result().errcode() == 0)
    {
        cout<< "rpc GetFriendList response success"<< endl;
        int size = response.friends_size();
        for(int i=0; i<size; i++)
        {
            cout << "index: "<< (i+1) << " name: "<< response.friends(i) << endl;
        }
    }
    else
    {
        cout<< "rpc GetFriendList response error" << response.result().errmsg() << endl;
    }
    }

    return 0;
}