#ifndef ANATEMPLATE_H_
#define ANATEMPLATE_H_
#include "tbConfig.h"
#include <vector>
#include <map>
#include <string>
#include "CommandLine.h"

class AnaTemplate
{
public:
    AnaTemplate() {};
    virtual ~AnaTemplate() = default;

    virtual bool initialize() = 0;
    virtual bool run() = 0;
    virtual bool finalize() = 0;
};

#endif //ANATEMPLATE_H_
