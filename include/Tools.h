#ifndef TOOLS_H_
#define TOOLS_H_
#include "TMatrixDSym.h"
#include "TMatrixDSymEigen.h"
#include "TSystemDirectory.h"
#include "TList.h"
#include "TLorentzVector.h"
#include "TString.h"
#include "TVector3.h"
#include <vector>
#include <map>
#include <iostream>
#include <cmath>
namespace Tools
{
    enum class SampleType {data, signal, ttbar, singletop, zjets, wjets, dibosons};
    float mT(TLorentzVector a, TLorentzVector b);
    std::vector<TString> FindFiles(TString dirname);
    std::vector<TString> FindSamplesInDir(TString dirname, Tools::SampleType _type);
    float* CalculateThrust(const std::vector<TVector3> mom);
    float CalculateSphericity(const std::vector<TVector3> mom);
    void CalcJoakimVars(std::vector<TLorentzVector> lmom, std::vector<TLorentzVector> jmom, std::vector<TLorentzVector> bmom, TLorentzVector met, std::map<TString, float> &vars);
}
#endif //TOOLS_H_