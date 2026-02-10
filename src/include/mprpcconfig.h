#pragma once
#include <unordered_map>
#include <string>
using namespace std;
class MprpcConfig
{
public:
    void LoadConfigFile(const char* config_file);
    string Load(const string& key);
    void Trim(string &src_buf);

private:
    unordered_map<string, string> m_configMap; 
};