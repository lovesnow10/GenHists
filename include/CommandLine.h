#ifndef COMMANDLINE_H_
#define COMMANDLINE_H_

#include "ReaderBase.h"

class CommandLine : public ReaderBase
{
public:
    static CommandLine *instance(int argc, char** argv);
    static CommandLine *instance() {return m_instance;}

 private:
    CommandLine(int argc, char** argv);
    CommandLine(const CommandLine&);
    ~CommandLine();

    CommandLine &operator=(const CommandLine &);

    bool initialize();

    static CommandLine *m_instance;
    int m_argc;
    char **m_argv;
};

#endif //COMMANDLINE_H_
