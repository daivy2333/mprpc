#pragma once
#include <google/protobuf/service.h>
#include <string>
#include <string>
using namespace std;
class MprpcController: public google::protobuf::RpcController
{
public:
    MprpcController();
    void Reset();
    bool Failed() const;
    string ErrorText() const;
    void SetFailed(const string& reason);

    void StartCancel();
    bool IsCanceled()const;
    void NotifyOnCancel(google::protobuf::Closure* callback);
private:
    bool m_failed;
    string m_errText;
private:
};