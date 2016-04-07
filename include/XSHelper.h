#ifndef XSHELPER_H_
#define XSHELPER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class XSHelper
{
public:
    XSHelper();
    ~XSHelper() {};

    float GetXS (const string key);
    const float GetXS (const string key) const;
private:
    XSHelper(XSHelper &xs) {};
    map<string, float> m_XSMap;
};

#endif //#XSHELPER