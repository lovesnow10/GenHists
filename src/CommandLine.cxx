#include "CommandLine.h"

CommandLine* CommandLine::m_instance = 0;

CommandLine::CommandLine(int argc, char** argv) : m_argc(argc), m_argv(argv) {}
CommandLine::~CommandLine() {};

CommandLine* CommandLine::instance(int argc, char** argv)
{
    if (m_instance == 0)
    {
        m_instance = new CommandLine(argc, argv);
        if (!m_instance->initialize())
        {
            std::cerr<<"Cannot initialize CommandLine!!"<<std::endl;
            delete m_instance;
            m_instance = 0;
        }
    }
    return m_instance;
}

bool CommandLine::initialize()
{
    int iarg;
    std::string tmpstr;
    std::string flagName;
    std::vector<std::string> flagValues;
    bool foundFlag;

    flagName = "exename";
    tmpstr = m_argv[0];
    flagValues.push_back(tmpstr);
    m_SettingMap.insert(std::make_pair(flagName, flagValues));
    flagName.clear();
    flagValues.clear();

    for (iarg = 1; iarg < m_argc; ++iarg)
    {
        tmpstr = m_argv[iarg];
        foundFlag = false;

        if (tmpstr.length() > 1 && tmpstr[0] == '-')
        {
            if (std::isalpha(tmpstr[1])) foundFlag = true;
            if (tmpstr.length() > 2 && tmpstr[1] == '-' && std::isalpha(tmpstr[2])) foundFlag = true;
        }
        if (foundFlag)
        {
            if (flagName.length() > 0)
            {
                if (m_SettingMap.find(flagName) != m_SettingMap.end())
                {
                    std::cerr<< "Warning:: Ignoring duplicate flag: "<< flagName<< std::endl;
                }
                else
                {
                    m_SettingMap.insert(std::make_pair(flagName, flagValues));
                }
                flagName.clear();
                flagValues.clear();
            }
            flagName = tmpstr;
        }
        else if (flagName.length() > 0)
        {
            flagValues.push_back(tmpstr);
        }
        else
        {
            std::cerr<<" Warning:: Arguments must come after a flag. Ignoring: " << tmpstr << std::endl;
        }
    }
    if (flagName.length() > 0)
    {
        if (m_SettingMap.find(flagName) != m_SettingMap.end())
        {
            std::cerr<<"Warning:: Ignoring duplicate flag: " << flagName << std::endl;
        }
        else
        {
            m_SettingMap.insert(std::make_pair(flagName, flagValues));
        }
    }
    return true;
}
