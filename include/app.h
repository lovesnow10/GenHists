#ifndef APP_H_
#define APP_H_

#include "AnaTemplate.h"
#include "CommandLine.h"
#include "TreeSkim.h"
#include "tbConfig.h"

class app : public AnaTemplate
{
public:
    app(int argc, char **argv);
    ~app() {};

    bool initialize();
    bool run();
    bool finalize();

private:
    int m_argc;
    char **m_argv;

    CommandLine *cmd;
    tbConfig* m_Config;
    AnaTemplate *m_worker;
};
#endif //APP_H_
