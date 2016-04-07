#include "Tools.h"

float Tools::mT(TLorentzVector a, TLorentzVector b)
{
    TVector3 pt_a = a.Vect();
    TVector3 pt_b = b.Vect();
    pt_a.SetZ(0);
    pt_b.SetZ(0);
    float mT = (a.M2() + b.M2() + 2*(a.Et()*b.Et() - pt_a.Dot(pt_b)));
    if (mT > 0) mT = sqrt(mT);
    return mT;
}

std::vector<TString> Tools::FindFiles(TString dirname)
{
    TSystemDirectory dir(dirname, dirname);
    TList *files = dir.GetListOfFiles();
    std::vector<TString> root_files;
    if (files)
    {
        TSystemFile *file;
        TString fname;
        TIter next(files);
        while ((file = (TSystemFile*)next()))
        {
            fname = file->GetName();
            if (!file->IsDirectory() && fname.Contains(".root"))
            {
                TString rfile(dirname);
                root_files.push_back(rfile + "/" + fname);
            }
        }
    }
    return root_files;
}

//std::vector<TString> Tools::FindSamplesInDir(TString dirname, Tools::SampleType _type)
//{
//    TSystemDirectory dir(dirname, dirname);
//    TList *files = dir.GetListOfFiles();
//    std::vector<TString> sample_dirs;
//    if (files)
//    {
//        TSystemFile *sample;
//        TString fname;
//        TIter next(files);
//        while ((sample = (TSystemFile*)next()))
//        {
//            fname = file->GetName();
//            if (file->IsDirectory() && fname.Contains(".root"))
//            {
//                TString dsid;
//                int index = fname.Index(".Physics_Main");
//                if (_type == Tools::SampleType::data)
//                {
//                    dsid = fname(index - 8, 8);
//                }
//                else
//                {
//                    dsid = fname(index - 6, 6);
//                }
//                switch (_type)
//                {
//                case Tools::SampleType::data:
//                    if (dsid(0, 2) != '00') continue;
//                    break;
//                case Tools::SampleType::ttbar:
//                    int i_dsid = atoi(dsid.Data());
//                    if (i_dsid != 410000) continue;
//                    break;
//                case Tools::SampleType::singletop:
//                    int i_dsid = atoi(dsid.Data());
//                    if (i_dsid != 410011 && i_dsid != 410012 && i_dsid != 410015 && i_dsid != 410016 ) continue;
//                    break;
//                case Tools::SampleType::signal:
//                    int i_dsid = atoi(dsid.Data());
//                    if (!(i_dsid > 341540 && i_dsid < 341549)) continue;
//                    break;
//                case Tools::SampleType::zjets:
//                    int i_dsid = atoi(dsid.Data());
//                    if (!(i_dsid > 361371 && i_dsid < 361442)) continue;
//                    break;
//                case Tools::SampleType::wjets:
//                    int i_dsid = atoi(dsid.Data());
//                    if (!(i_dsid > 361299 && i_dsid < 361372)) continue;
//                    break;
//                case Tools::SampleType::dibosons:
//                    int i_dsid = atoi(dsid.Data());
//                    if (!(i_dsid > 361062 && i_dsid < 361088)) continue;
//                    break;
//                default:
//                    std::cout<<"Invalid Type!"<<std::endl;
//                    exit(1);
//                }
//                TString rfile(dirname);
//                sample_dirs.push_back(rfile + "/" + fname);
//            }
//        }
//    }
//    return sample_dirs;
//}

float* Tools::CalculateThrust(std::vector<TVector3> mom)
{
    float *thrust;
    thrust = new float [2];
    float MaxT = -9999.0;
    TVector3 axisZ(0, 0, 1);
    TVector3 nT(0, 0, 0);

    for (auto p : mom)
    {
        TVector3 tmp_n(p.Px()/p.Perp(), p.Py()/p.Perp(), p.Pz()/p.Perp());
        float sumPM = 0;
        float sumPD = 0;
        for (auto t : mom)
        {
            sumPD += t.Dot(tmp_n);
            sumPM += t.Perp();
        }
        float tmp_Thrust = sumPD / sumPM;
        if (tmp_Thrust > MaxT)
        {
            MaxT = tmp_Thrust;
            nT = tmp_n;
        }
    }
    thrust[0] = MaxT;
    TVector3 nM = nT.Cross(axisZ);

    float sumPD = 0;
    float sumPM = 0;
    for (auto p : mom)
    {
        sumPD += p.Dot(nM);
        sumPM += p.Perp();
    }
    thrust[1] = sumPD / sumPM;

    return thrust;
}

float Tools::CalculateSphericity(std::vector<TVector3> mom)
{
    TMatrixDSym TensorT(2);

    float Pxx = 0, Pxy = 0, Pyx = 0, Pyy = 0;
    float normal = 0;
    for (auto p : mom)
    {
        Pxx += p.Px() * p.Px();
        Pxy += p.Px() * p.Py();
        Pyx += p.Py() * p.Px();
        Pyy += p.Py() * p.Py();
        normal += p.Perp2();
    }
    TensorT(0, 0) = Pxx / normal;
    TensorT(0, 1) = Pxy / normal;
    TensorT(1, 0) = Pyx / normal;
    TensorT(1, 1) = Pyy / normal;

    TMatrixDSymEigen Eigenvalues(TensorT);
    TVectorD eigenVec = Eigenvalues.GetEigenValues();

    float sphericity = 0;
    sphericity = 2.0 * eigenVec[1] / (eigenVec[0] + eigenVec[1]);

    return sphericity;
}

void Tools::CalcJoakimVars(std::vector<TLorentzVector> lmom, std::vector<TLorentzVector> jmom, std::vector<TLorentzVector> bmom, TLorentzVector met, std::map<TString, float> &vars)
{
    if (jmom.size() < 3)
    {
        vars["ssum_M_j1j2j3"] = -1;
        vars["E_j3l2met"] = -1;
        vars["dM_j3_vs_met"] = -1;
        vars["dPhi_b1met_vs_j1j3l1l2"] = 0;
    }
    else
    {
        vars["ssum_M_j1j2j3"] = jmom.at(0).M() + jmom.at(1).M() + jmom.at(2).M();
        vars["E_j3l2met"] = (jmom.at(2) + lmom.at(1) + met).E();
        vars["dM_j3_vs_met"] = fabs(jmom.at(2).M() - met.M());
        vars["dPhi_b1met_vs_j1j3l1l2"] = (bmom.at(0) + met).DeltaPhi(jmom.at(0) + jmom.at(2) + lmom.at(0) + lmom.at(1));
    }
    vars["ssum_pt_b1b2"] = bmom.at(0).Pt() + bmom.at(1).Pt();
    vars["E_b2l1met"] = (bmom.at(1) + lmom.at(0) + met).E();
    vars["dPhi_b1b2l1l2met_vs_j1"] = (bmom.at(0) + bmom.at(1) + lmom.at(0) + lmom.at(1) + met).DeltaPhi(jmom.at(0));
    vars["dE_b1b2l2met_vs_j2"] = fabs((bmom.at(0) + bmom.at(1) + lmom.at(0) + met).E() - jmom.at(1).E());
    vars["pt_l1l2met"] = (lmom.at(0) + lmom.at(1) + met).Pt();
    vars["pt_b1l1l2"] = (bmom.at(0) + lmom.at(1) + lmom.at(0)).Pt();
    vars["mT_b2l2"] = (bmom.at(1) + lmom.at(1)).Mt();
    vars["mT_j1_vs_l2"] = mT(jmom.at(0), lmom.at(1));

    float min_m_bb = 1e15;
    float min_m_lb = 1e15;
    float max_pt_jj = 0;
    float m_min_dEta_bb = -1;
    float pt_min_dR_bb = -1;
    float m_max_pt_jj = -1;
    float m_max_dPhi_bb = -1;
    float min_dEta_bb = 1e15;
    float min_dR_bb = 1e15;
    float max_dPhi_bb = 0;

    for (unsigned int i = 0; i < jmom.size(); ++i)
    {
        for (unsigned int j = i+1; j < jmom.size(); ++j)
        {
            TLorentzVector jj = jmom.at(i) + jmom.at(j);

            float m = jj.M();
            float pt = jj.Pt();

            if (max_pt_jj < pt)
            {
                max_pt_jj = pt;
                m_max_pt_jj = m;
            }
        }
    }
    for (unsigned int i = 0; i < bmom.size(); ++i)
    {
        for (unsigned int j = i+1; j < bmom.size(); ++j)
        {
            TLorentzVector bb = bmom.at(i) + bmom.at(j);
            float dEta = fabs(bmom.at(i).Eta() - bmom.at(j).Eta());
            float m = bb.M();
            float pt = bb.Pt();
            float dR = bmom.at(i).DeltaR(bmom.at(j));
            float dPhi = bmom.at(i).DeltaPhi(bmom.at(j));

            if (dEta < min_dEta_bb)
            {
                min_dEta_bb = dEta;
                m_min_dEta_bb = m;
            }
            if (dR < min_dR_bb)
            {
                min_dR_bb = dR;
                pt_min_dR_bb = pt;
            }
            if(dPhi > max_dPhi_bb)
            {
                min_dR_bb = dR;
                pt_min_dR_bb = pt;
            }
            if(dPhi > max_dPhi_bb)
            {
                max_dPhi_bb = dPhi;
                m_max_dPhi_bb = m;
            }
            if (m < min_m_bb)
            {
                min_m_bb = m;
            }
        }
        for (auto lep : lmom)
        {
            TLorentzVector lb = bmom.at(i) + lep;

            float m = lb.M();
            if (min_m_lb > m)
            {
                min_m_lb = m;
            }
        }
    }
    vars["min_m_bb"] = min_m_bb;
    vars["min_m_lb"] = min_m_lb;
    vars["max_pt_jj"] = max_pt_jj;
    vars["m_min_dEta_bb"] = m_min_dEta_bb;
    vars["pt_min_dR_bb"] = pt_min_dR_bb;
    vars["m_max_pt_jj"] = m_max_pt_jj;
    vars["m_max_dPhi_bb"] = m_max_dPhi_bb;
    vars["min_dEta_bb"] = min_dEta_bb;
    vars["min_dR_bb"] = min_dR_bb;
    vars["max_dPhi_bb"] = max_dPhi_bb;
}
