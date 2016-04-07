#ifndef READERBASE_H_
#define READERBASE_H_

#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

class ReaderBase
{
public:
    ReaderBase(){};
    virtual ~ReaderBase();
    std::vector<std::string> GetKeys() const;
    bool HasKey(const std::string &key) const;
    bool GetValue(const std::string &key, std::vector<std::string> &value) const;
    bool GetValue(const std::string &key, std::string &value) const;
    std::vector<std::string> &operator[](const std::string key);
    const std::vector<std::string> &operator[](const std::string key) const;

protected:
    std::map<std::string, std::vector<std::string>> m_SettingMap;
};

#endif //READERBASE_H
