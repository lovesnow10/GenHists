#include "app.h"
#include <vector>
#include <string>

app::app(int argc, char **argv)
{
    m_argc = argc;
    m_argv = argv;
}

bool app::initialize()
{
    cmd = CommandLine::instance(m_argc, m_argv);
    m_Config = new tbConfig();
    std::vector<std::string> flags = cmd->GetKeys();
    for (auto it : flags)
    {
        cmd->GetValue(it, (*m_Config)[it]);
    }
    m_Config->DeleteConfig("exename");

    m_worker = new TreeSkim(m_Config);
    if (!m_worker->initialize())
    {
        std::cerr<<"Cannot Initial worker!!"<<std::endl;
        exit(1);
    }
    return true;
}

bool app::run()
{
    m_worker->run();
    return true;
}

bool app::finalize()
{
    m_worker->finalize();
    std::cout<<"All works have been done!"<<std::endl;
    return true;
}
