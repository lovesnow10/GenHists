#ifndef TBCONFIG_H_
#define TBCONFIG_H_
#include <iostream>
#include <string>
#include <vector>
#include <map>

class tbConfig
{
public:
    tbConfig() {};
    ~tbConfig() {};
    std::string *Get(const std::string flag);
    const std::string *Get(const std::string flag) const;
    std::string &operator[] (const std::string flag);
    const std::string &operator[] (const std::string flag) const;
    void printConfig() const;
    std::vector<std::string> GetKeys() const;
    bool HasKey(const std::string key) const;
    void DeleteConfig(const std::string flag);
private:
    std::map<std::string, std::string> m_Config;
};

#endif //TBCONFIG_H_