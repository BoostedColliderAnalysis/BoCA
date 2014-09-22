# include "HMvaHeavyHiggs.hh"

HMvaHeavyHiggs::HMvaHeavyHiggs()
{

    Print(0 , "Constructor");

    AnalysisName = "HeavyHiggs";

    SignalVector = {"Signal"};

    BackgroundVector = {"Background"};

    TestName = "Test";

    SignalTreeVector = {"even", "mix", "odd"};

    BackgroundTreeVector = {"background", "even", "mix", "odd"};

    TestTreeVector = {"background","even", "mix", "odd"};

    CandidateBranchName = "Candidate";

    LeptonBranchName = "Lepton";

    WeightBranchName = "Info";

    SignalEfficiency = 0.5;

    Luminosity = 3000; // fb

    Latex = 1;

    Candidate = new HCandidateBranch();

    DefineVariables();

    Cut = "Candidate.SubJet1Pt>0&&Candidate.SubJet2Pt>0&&Candidate.IsolationPt>0";

}

HMvaHeavyHiggs::~HMvaHeavyHiggs()
{

    Print(0 , "Constructor");

}

void HMvaHeavyHiggs::DefineVariables()
{

    Print(0 , "Define Variables");

    ObservableVector.push_back(NewObservable(&Candidate->Mass, "Candidate.Mass", "Mass", "GeV"));
    ObservableVector.push_back(NewObservable(&Candidate->Pt, "Candidate.Pt","Pt", "GeV"));
    ObservableVector.push_back(NewObservable(&Candidate->Eta, "Candidate.Eta", "Eta"));
    ObservableVector.push_back(NewObservable(&Candidate->Phi, "Candidate.Phi", "Phi"));

    ObservableVector.push_back(NewObservable(&Candidate->SubJetsDeltaR, "Candidate.SubJetsDeltaR", "SubJet DeltaR"));

    ObservableVector.push_back(NewObservable(&Candidate->SubJet1Mass, "Candidate.SubJet1Mass","SubJet1 Mass", "GeV"));
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

    if (Debug > 0) cout << "Variables defined" << endl;

}
