#include "ReaderBase.h"

std::vector<std::string> ReaderBase::GetKeys() const
{
    std::vector<std::string> keys;
    for (auto m_pair : m_SettingMap)
    {
        keys.push_back(m_pair.first);
    }
    return keys;
}

bool ReaderBase::HasKey(const std::string &key) const
{
    return m_SettingMap.find(key) != m_SettingMap.end();
}
bool ReaderBase::GetValue(const std::string &key, std::vector<std::string> &value) const
{
    std::map<std::string, std::vector<std::string>>::const_iterator iterator = m_SettingMap.find(key);
    value.clear();
    if (iterator == m_SettingMap.end()) return false;
    if (iterator->second.size() == 0) return false;
    value = iterator->second;
    return true;
}

bool ReaderBase::GetValue(const std::string &key, std::string &value) const
{
    std::map<std::string, std::vector<std::string>>::const_iterator iterator = m_SettingMap.find(key);
    value.clear();
    if (iterator == m_SettingMap.end()) return false;
    if (iterator->second.size() == 0) return false;
    value = iterator->second.at(0);
    return true;
}

std::vector<std::string>& ReaderBase::operator[](const std::string key)
{
//    std::map<std::string, std::vector<std::string>>::const_iterator iterator = m_SettingMap.find(key);
//    if (iterator == m_SettingMap.end()) return NULL;
    return m_SettingMap.at(key);
}

const std::vector<std::string>& ReaderBase::operator[](const std::string key) const
{
    //std::map<std::string, std::vector<std::string>>::const_iterator iterator = m_SettingMap.find(key);
//    if (iterator == m_SettingMap.end()) return NULL;
    return m_SettingMap.at(key);
}

ReaderBase::~ReaderBase()
{
//    delete m_SettingMap;
}

