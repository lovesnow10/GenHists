#include "tbConfig.h"
#include <iomanip>

std::string* tbConfig::Get(const std::string flag)
{
    if (m_Config.find(flag) != m_Config.end()) return &m_Config[flag];
    else return NULL;
}

const std::string* tbConfig::Get(const std::string flag) const
{
    if (m_Config.find(flag) != m_Config.end()) return &m_Config.at(flag);
    else return NULL;
}

std::string& tbConfig::operator[] (const std::string flag)
{
    return m_Config[flag];
}

const std::string& tbConfig::operator[] (const std::string flag) const
{
    return m_Config.at(flag);
}

void tbConfig::printConfig() const
{
    size_t nConfig = m_Config.size();
    if (nConfig == 0)
    {
        std::cout<<"|"<<std::setw(60)<<std::setfill('*')<<"|"<<std::endl;
        std::cout<<"|--WARNING: You haven't give any config!"<<std::endl;
        std::cout<<"|"<<std::setw(60)<<std::setfill('*')<<"|"<<std::endl;
        return;
    }
    else
    {
        std::cout<<"|"<<std::setw(60)<<std::setfill('-')<<"|"<<std::endl;
        std::cout<<"|--"<<"Your Input Configs are :"<<std::endl;
        for (auto conf : m_Config)
        {
//            const char *fl = *(conf->first).c_str();
//            const char *vl = *(conf->second).c_str();
            printf("|** %-15s %s \n", conf.first.c_str(), conf.second.c_str());
        }
        std::cout<<"|"<<std::setw(60)<<std::setfill('-')<<"|"<<std::endl;
        return;
    }
}

std::vector<std::string> tbConfig::GetKeys() const
{
    std::vector<std::string> keys;
    for (auto m_pair : m_Config)
    {
        keys.push_back(m_pair.first);
    }
    return keys;
}

bool tbConfig::HasKey(const std::string key) const
{
    return m_Config.find(key) != m_Config.end();
}

void tbConfig::DeleteConfig(const std::string flag)
{
    if (m_Config.find(flag) != m_Config.end()) m_Config.erase(flag);
}