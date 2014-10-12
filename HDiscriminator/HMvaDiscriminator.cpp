# include "HMvaDiscriminator.hh"

HMvaDiscriminator::HMvaDiscriminator()
{

    Print(1 , "Constructor");

//     Debug = 1;

    AnalysisName = "Discriminator";

//     SignalVector = {"Higgs","HiggsTop"};
    SignalNameVector = {"Higgs"};

//     BackgroundVector = {"Top", "Jet","TwoTop"};
    BackgroundNameVector = {"Top", "Jet"};
//         BackgroundVector = {"Top"};

    TestName = "Test";

    SignalTreeNameVector = {"even", "mix", "odd"};
//         SignalTreeVector = {"even"};

    BackgroundTreeNameVector = {"background", "even", "mix", "odd"};
//         BackgroundTreeVector = {"even"};

    TestTreeNameVector = {"background","even", "mix", "odd"};
//         TestTreeVector = {"even"};

    CandidateBranchName = "Candidate";

    SpectatorBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    Latex = 1;

    Candidate = new HCandidateBranch();

    DefineVariables();

    Cut = "Candidate.SubJet1Pt>0&&Candidate.SubJet2Pt>0&&Candidate.IsolationPt>0";

}

HMvaDiscriminator::~HMvaDiscriminator()
{

    Print(1 , "Constructor");
    
    delete Candidate;

}

void HMvaDiscriminator::DefineVariables()
{

    Print(1 , "Define Variables");

    ObservableVector.push_back(NewObservable(&Candidate->Mass, "Candidate.Mass", "Mass", "GeV","m_j"));
    ObservableVector.push_back(NewObservable(&Candidate->Pt, "Candidate.Pt","Pt", "GeV","p^T_j"));
    ObservableVector.push_back(NewObservable(&Candidate->Eta, "Candidate.Eta", "Eta","\\eta_j"));
    ObservableVector.push_back(NewObservable(&Candidate->Phi, "Candidate.Phi", "Phi","\\phi_j"));

    ObservableVector.push_back(NewObservable(&Candidate->SubJetsDeltaR, "Candidate.SubJetsDeltaR", "SubJet DeltaR","\\Delta R(j_1,j_2)"));

    ObservableVector.push_back(NewObservable(&Candidate->SubJet1Mass, "Candidate.SubJet1Mass","SubJet1 Mass", "GeV","m_{j_1}"));
    ObservableVector.push_back(NewObservable(&Candidate->SubJet1Pt, "Candidate.SubJet1Pt","SubJet1 Pt", "GeV"));
    ObservableVector.push_back(NewObservable(&Candidate->SubJet1DeltaR,"Candidate.SubJet1DeltaR","SubJet1 DeltaR"));

    ObservableVector.push_back(NewObservable(&Candidate->SubJet2Mass, "Candidate.SubJet2Mass","SubJet2 Mass", "GeV"));
    ObservableVector.push_back(NewObservable(&Candidate->SubJet2Pt, "Candidate.SubJet2Pt","SubJet2 Pt", "GeV"));
    ObservableVector.push_back(NewObservable(&Candidate->SubJet2DeltaR,"Candidate.SubJet2DeltaR","SubJet2 DeltaR"));

//     ObservableVector.push_back(NewObservable(&Candidate->ConstEta, "Candidate.ConstEta", "Const Eta"));
//     ObservableVector.push_back(NewObservable(&Candidate->ConstPhi, "Candidate.ConstPhi", "Const Phi"));
    ObservableVector.push_back(NewObservable(&Candidate->ConstDeltaR, "Candidate.ConstDeltaR","Const DeltaR"));
    ObservableVector.push_back(NewObservable(&Candidate->ConstAngle, "Candidate.ConstAngle","Const Angle"));

//     ObservableVector.push_back(NewObservable(&Candidate->IsolationEta, "Candidate.IsolationEta"));
//     ObservableVector.push_back(NewObservable(&Candidate->IsolationPhi, "Candidate.IsolationPhi"));
    ObservableVector.push_back(NewObservable(&Candidate->IsolationDeltaR, "Candidate.IsolationDeltaR","Isol DeltaR"));
    ObservableVector.push_back(NewObservable(&Candidate->IsolationAngle, "Candidate.IsolationAngle","Isol Angle"));
    ObservableVector.push_back(NewObservable(&Candidate->IsolationPt, "Candidate.IsolationPt","Isol Pt", "GeV"));

    SpectatorVector.push_back(NewObservable(&Candidate->HiggsTag, "Candidate.HiggsTag","Higgs Tag"));
    SpectatorVector.push_back(NewObservable(&Candidate->TopTag, "Candidate.TopTag","Top Tag"));

    Print(1,"Variables defined");

}
