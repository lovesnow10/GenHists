#ifndef DATASETS_H_
#define DATASETS_H_

#include <iostream>
#include <string>
#include <vector>

class DataSets
{
public:
    DataSets() {};
    DataSets(std::string dname);
    ~DataSets() {};

    const std::vector<std::string>& GetAllFiles() const;
    bool GetOneFile(std::string &s);
private:
    std::vector<std::string> rootfiles;
    unsigned int index;
};

#endif //DATASETS_H_