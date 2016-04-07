#include "GenHistRun.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

bool GenHistRun::initialize()
{
    //set up category and channel
    category.push_back("2jex2bex");
    category.push_back("3jex2bex");
    category.push_back("4jin2bex");

    channel.push_back("ee");
    channel.push_back("mumu");
    channel.push_back("emu");

    //set up variable vector and bins
    if (!m_Config->HasKey("--Variables"))
    {
        cout<<"Please give variables!"<<endl;
        exit(1);
    }
    ifstream in_var((*m_Config)["--Variables"].c_str());
    string line;
    while (getline(in_var, line))
    {
        line = line.replace(line.find("\n"), 1, "");
        stringstream ss(line);
        string varname, nbins, xlow, xup;
        ss>>varname>>nbins>>xlow>>xup;
        variables.push_back(varname);
        varBins[varname]["NBINS"] = atof(nbins);
        varBins[varname]["XLOW"] = atof(xlow);
        varBins[varname]["XUP"] = atof(xup);
    }
    in_var.close();

    //set up inputFileMap
    if(!m_Config->HasKey("--inputFiles"))
    {
        std::cout<<"Please supply input files!"<<std::endl;
        exit(1);
    }
    ifstream in_file((*m_Config)["--inputFiles"].c_str());
    while(getline(in_file, line))
    {
        if (line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        string bkg, bkg_path;
        ss>>bkg>>bkg_path;
        inputFileMap[bkg] = new DataSets(bkg_path);
    }
    in_file.close();

    //set up outputFile and XSHelper
    m_XS = new XSHelper();
    m_outFile = NULL;
    if (m_Config->HasKey("--outName"))
    {
        m_outFile = TFile::Open((*m_Config)["--outName"].c_str(), "RECREATE");
    }
    else
    {
        cout<<"No outName specified, using 'output.root'"<<endl;
        m_outFile = TFile::Open("output.root", "RECREATE");
    }

    BookHistograms();
    return true;
}

bool GenHistRun::run()
{
    for (auto )
}

void GenHistRun::BookHistograms()
{
}