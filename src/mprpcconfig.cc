#include "mprpcconfig.h"
#include <iostream>
#include <string>
#include "logger.h"
void MprpcConfig::LoadConfigFile(const char* config_file)
{
    FILE* pf = fopen(config_file, "r");
    if(nullptr == pf)
    {
        LOG_ERROR("%s is not exist!", config_file);
        exit(EXIT_FAILURE);
    }

    while(!feof(pf))
    {
        char buf[512] = {0};
        fgets(buf, 512, pf);

        string src_buf(buf);

        // 去除字符串两端的空格和换行符
        Trim(src_buf);

        // 跳过注释行和空行
        if(src_buf[0] == '#' || src_buf.empty())
        {
            continue;
        }

        // 解析key=value
        int idx = src_buf.find('=');
        if(idx == -1)
        {
            continue;
        }

        string key = src_buf.substr(0, idx);
        string value = src_buf.substr(idx+1, src_buf.size()-idx);

        // 去除key两端的空格
        Trim(key);

        // 去除value两端的空格
        Trim(value);

        m_configMap.insert({key, value});
    }
    fclose(pf);
}
string MprpcConfig::Load(const string& key)
{
    auto it = m_configMap.find(key);
    if(it == m_configMap.end())
    {
        return "";
    }
    return it->second;
}

void MprpcConfig::Trim(string &src_buf)
{
    // 去除字符串左端的空格和换行符
    int idx = src_buf.find_first_not_of(" \t\n\r");
    if(idx != -1)
    {
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    else
    {
        src_buf = "";
        return;
    }

    // 去除字符串右端的空格和换行符
    idx = src_buf.find_last_not_of(" \t\n\r");
    if(idx != -1)
    {
        src_buf = src_buf.substr(0, idx+1);
    }
}