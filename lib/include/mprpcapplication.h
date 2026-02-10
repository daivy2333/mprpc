#pragma once
#include "mprpcconfig.h"
#include "mprpccontroller.h"
#include "mprpcchannel.h"
// mprpc的初始化类 负责初始化的

class MprpcApplication
{
public:
    static void Init(int argc, char **argv);
    static MprpcApplication& GetInstance();
    static MprpcConfig& Getconfig();
private:
    static MprpcConfig m_config;
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
};