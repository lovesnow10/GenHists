#include "DataSets.h"
#include <stdio.h>

DataSets::DataSets(std::string dname)
{
    index = 0;
    rootfiles.clear();


    FILE* fp;
    char buf[256] = {0};
    std::string cmd = "ls";
    std::string fullcmd = cmd + " " + dname;
    fp = popen(fullcmd.c_str(), "r");
    if (NULL == fp)
    {
        perror("popen error! Please check path\n");
        exit(1);
    }
    while (fgets(buf, 256, fp) != NULL)
    {
        std::string s = buf;
        s = s.replace(s.find("\n"), 1, "");
        rootfiles.push_back(dname + "/" + s);
    }
    pclose(fp);
    std::cout<<"Datasets Initialed"<<std::endl;
}

const std::vector<std::string>& DataSets::GetAllFiles() const
{
    if (rootfiles.size() == 0)
    {
        std::cout<<"No file found!!"<<std::endl;
        exit(1);
    }
    return rootfiles;
}

bool DataSets::GetOneFile(std::string &s)
{
    if (index < rootfiles.size())
    {
        s = rootfiles.at(index++);
        return true;
    }
    else
    {
        return false;
    }
}
