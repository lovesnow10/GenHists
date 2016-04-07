#ifndef GENHISTRUN_H_
#define GENHISTRUN_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TROOT.h"

#include "AnaTemplate.h"
#include "tbConfig.h"
#include "DataSets.h"
#include "XSHelper.h"

using namespace std;

class GenHistRun : public AnaTemplate
{
public:
    GenHistRun(tbConfig *m_config)
    {
        m_Config = m_config;
    };
    ~GenHistRun() {};

    bool initialize();
    bool run();
    bool finalize();

private:
    GenHistRun(GenHistRun &hr);
    tbConfig *m_Config;
    TFile *m_outFile;
    XSHelper *m_XS;

    void BookHistograms();

    map<string, DataSets*> inputFileMap;
    map<string, vector<TH1F*>> singleHists;
    map<string, TH1F*> combHists;

    vector<string> category;
    vector<string> channel;
    vector<string> variables;
    map<string, map<string, float>> varBins;
};

#endif //GENHISTRUN_H_