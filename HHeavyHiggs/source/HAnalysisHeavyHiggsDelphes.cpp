# include "HAnalysisHeavyHiggsDelphes.hh"

HAnalysisHeavyHiggsDelphes::HAnalysisHeavyHiggsDelphes()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggs";

    EventNumberMax = 10000;

    Cut = 1;

}

vector<string> HAnalysisHeavyHiggsDelphes::GetStudyNameVector()
{

    vector<string> StudyNameVector = {"Signal", "Background", "Test"};

    return StudyNameVector;

}

void HAnalysisHeavyHiggsDelphes::SetFileVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);


//     if (AnalysisName != "Signal") {

    FileVector.push_back(new HFileFolder("5k_Pt20"));

//     }

    FileVector.push_back(new HFileFolder("Signal_5f"));
//     FileVector.push_back(new HFileFolder("500GeV"));
//     FileVector.push_back(new HFileFolder("600GeV"));
//     FileVector.push_back(new HFileFolder("700GeV"));
//     FileVector.push_back(new HFileFolder("800GeV"));
//     FileVector.push_back(new HFileFolder("900GeV"));
//     FileVector.push_back(new HFileFolder("1000GeV"));

//     FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    FileVector.front()->BasePath = "~/Dropbox/Projects/HeavyHiggs/Simulation/";
    FileVector.front()->FileSuffix = "_Delphes.root";
    FileVector.front()->Snowmass = 1;

//     FileVector.push_back(new HFileDelphes("pp-bbtt-4f", "background"));

    Print(0, "Files prepared", FileVector.size());

}

void HAnalysisHeavyHiggsDelphes::NewFile()
{

    Print(0, "New File");

    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());

    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void HAnalysisHeavyHiggsDelphes::CloseFile()
{
    Print(0, "Close File");

    if (Cut) {

        Print(0, "EventCounter", EventCounter);
        Print(0, "JetCounter", JetCounter);
        Print(0, "DeltaEtaCounter", DeltaEtaCounter);
        Print(0, "BMassCounter", BMassCounter);
        Print(0, "Jet2Counter", Jet2Counter);
        Print(0, "TMassCounter", TMassCounter);

    }

}


bool HAnalysisHeavyHiggsDelphes::Analysis()
{

    Print(1, "Analysis", AnalysisName);
    bool Success;

    if (StudyName == "Signal") Success = Signal();
    if (StudyName == "Background") Success = Background();
    if (StudyName == "Test")  Success = Test();

    return Success;

}

bool HAnalysisHeavyHiggsDelphes::Test()
{

    Print(1, "BTag");

    Event->GetJets();
    Event->GetLeptons();

    vector<PseudoJet> BJets = Event->Jets->BottomJetVector;
    vector<PseudoJet> LeptonJet = Event->Lepton->LeptonJetVector;

    if (BJets.size() > 1) {

        for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {

            for (unsigned BJetNumber2 = 0; BJetNumber2 < BJetNumber; ++BJetNumber2) {

                PseudoJet FrontJet, BackJet;

                if (BJets[BJetNumber].eta() > BJets[BJetNumber2].eta()) {

                    FrontJet = BJets[BJetNumber];
                    BackJet = BJets[BJetNumber2];

                } else {

                    FrontJet = BJets[BJetNumber2];
                    BackJet = BJets[BJetNumber];

                }

                FillBranch(FrontJet,BackJet);

            }

        }

        return 1;

    }

    return 0;

}
bool HAnalysisHeavyHiggsDelphes::Background()
{

    Print(1, "Truth Level");

    Event->GetTaggedJets();
    Event->GetLeptons();

    vector<PseudoJet> BJets = Event->Jets->BottomJetVector;
    vector<PseudoJet> JetVector = Event->Jets->JetVector;

    if (JetVector.size() < 2) return 0;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (JetVector[JetNumber].user_index() == BottomId) JetVector.erase(JetVector. begin() + JetNumber);

    }

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if(JetVector[JetNumber].user_index() == BottomId) Print(-1,"ERROR");

    }

    for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {

        for (unsigned BJetNumber2 = 0; BJetNumber2 < BJetNumber; ++BJetNumber2) {

            PseudoJet FrontJet, BackJet;

            if (BJets[BJetNumber].eta() > BJets[BJetNumber2].eta()) {

                FrontJet = BJets[BJetNumber];
                BackJet = BJets[BJetNumber2];

            } else {

                FrontJet = BJets[BJetNumber2];
                BackJet = BJets[BJetNumber];

            }

            FillBranch(FrontJet,BackJet);

        }

    }

    return 1;

}

bool HAnalysisHeavyHiggsDelphes::Signal()
{

    Print(1, "Truth Level");


    Event->GetTaggedJets();
    Event->GetLeptons();

    vector<PseudoJet> BJets = Event->Jets->BottomJetVector;

    vector<PseudoJet> JetVector = Event->Jets->JetVector;

//     vector<PseudoJet> TopVector;
    vector<PseudoJet> BottomVector;

    if (JetVector.size() < 4) return 0;


    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (JetVector[JetNumber].user_index() == BottomId) BottomVector.push_back(JetVector[JetNumber]);
//         if (JetVector[JetNumber].user_index() == TopId) TopVector.push_back(JetVector[JetNumber]);

    }

    if (BottomVector.size() > 1) {

        sort(BottomVector.begin(), BottomVector.end(), SortJetByEta());


        PseudoJet FrontJet = BottomVector.front();
        PseudoJet BackJet = BottomVector.back();

        FillBranch(FrontJet,BackJet);


    } else {

        return 0;

    }

//     if (TopVector.size() > 1) {
//
//         sort(TopVector.begin(), TopVector.end(), SortJetByEta());
//
//         PseudoJet FrontJet = TopVector.front();
//         float FrontPt = FrontJet.pt();
//         float FrontEta = FrontJet.eta();
//         float FrontPhi = FrontJet.phi();
//
//         PseudoJet BackJet = TopVector.back();
//         float BackEta = BackJet.eta();
//         float BackPt = BackJet.pt();
//         float BackPhi = BackJet.phi();
//
//         float InvMass = (FrontJet + BackJet).m();
//         float DeltaEta = FrontEta - BackEta;
//         float DeltaPhi = GetDeltaPhi(FrontPhi, BackPhi);
//
//         HeavyHiggs->TopEta1 = FrontEta;
//         HeavyHiggs->TopEta2 = BackEta;
//         HeavyHiggs->TopDeltaEta = DeltaEta;
//
//         HeavyHiggs->TopPhi1 = FrontPhi;
//         HeavyHiggs->TopPhi2 = BackPhi;
//         HeavyHiggs->TopDeltaPhi = DeltaPhi;
//
//         HeavyHiggs->TopPt1 = FrontPt;
//         HeavyHiggs->TopPt2 = BackPt;
//         HeavyHiggs->TopInvMass = InvMass;
//
//     } else {
//
//         return 0;
//
//     }

    return 1;

}

void HAnalysisHeavyHiggsDelphes::FillBranch(PseudoJet FrontJet, PseudoJet BackJet) {

    float FrontPt = FrontJet.pt();
    float FrontEta = FrontJet.eta();
    float FrontPhi = FrontJet.phi_std();

    float BackEta = BackJet.eta();
    float BackPt = BackJet.pt();
    float BackPhi = BackJet.phi_std();

    float InvMass = (FrontJet + BackJet).m();
    float DeltaEta = FrontEta - BackEta;
    float SumEta = FrontEta + BackEta;
    float DeltaPhi = GetDeltaPhi(FrontPhi, BackPhi);
    float SumPhi = FrontPhi + BackPhi; // FIXME constrain this
    float DeltaPt = FrontPt - BackPt;

    float Isolation = min(Leptons(FrontJet),Leptons(BackJet));

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    HeavyHiggs->BottomEta1 = FrontEta;
    HeavyHiggs->BottomEta2 = BackEta;
    HeavyHiggs->BottomDeltaEta = DeltaEta;
    HeavyHiggs->BottomSumEta = SumEta;

    HeavyHiggs->BottomPhi1 = FrontPhi;
    HeavyHiggs->BottomPhi2 = BackPhi;
    HeavyHiggs->BottomDeltaPhi = DeltaPhi;
    HeavyHiggs->BottomSumPhi = SumPhi;

    HeavyHiggs->BottomPt1 = FrontPt;
    HeavyHiggs->BottomPt2 = BackPt;
    HeavyHiggs->BottomInvMass = InvMass;
    HeavyHiggs->BottomDeltaPt = DeltaPt;

    HeavyHiggs->BTag = Event->Jets->BottomJetVector.size();
    HeavyHiggs->JetNumber = Event->Jets->JetVector.size();
    HeavyHiggs->Isolation = Isolation;

}


float HAnalysisHeavyHiggsDelphes::Leptons(PseudoJet Jet) {

    float Isolation;

    vector<PseudoJet> LeptonVector = Event->Lepton->GetLeptonJetVector();

    for (unsigned LeptonNumber = 0; LeptonNumber<LeptonVector.size(); ++LeptonNumber) {

        Isolation = Jet.delta_R(LeptonVector[LeptonNumber]);

    }

    return Isolation;

}


// bool HAnalysisHeavyHiggsDelphes::Analysis()
// {
//
//     Print(1, "Analysis", AnalysisName);
//
//     HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());
//
//     //     Event->GetLeptons();
//
//     //     vector<PseudoJet> LeptonVector = Event->Leptons->LeptonJetVector;
//
//     //     int LeptonSum = LeptonVector.size();
//     //     if (LeptonSum < 1 ) return 0;
//
//     ++EventCounter;
//
//     Event->GetTaggedJets();
//
//
//
//
// //     vector<PseudoJet> BJets = Event->Jets->BottomJetVector;
// //     int BJetSum = BJets.size();
// //     HeavyHiggs->BTag = BJetSum;
// //     Print(3, "B Jets", BJetSum);
//
//
//
// //     vector<PseudoJet> TopJets = Event->GetTops();
// //     Print(3, "Top Jets", TopJets.size());
//
//     vector<PseudoJet> JetVector = Event->Jets->JetVector;
//     int JetSum = JetVector.size();
//     HeavyHiggs->JetNumber = JetSum;
//     Print(2,"JetSum",JetSum);
//
//     if (JetSum > 1) {
//
//         ++JetCounter;
//
//         sort(JetVector.begin(), JetVector.end(), SortJetByEta());
//
//         PseudoJet FrontJet = JetVector.front();
//         float FrontPt = FrontJet.pt();
//         float FrontEta = FrontJet.eta();
//
//         PseudoJet BackJet = JetVector.back();
//         float BackEta = BackJet.eta();
//         float BackPt = BackJet.pt();
//
//         PseudoJet CombinedJet = FrontJet + BackJet;
//         float CombinedMass = CombinedJet.m();
//         float CombinedEta = FrontEta - BackEta;
//
//         if (Cut && CombinedEta < 3) return 0;
//         ++DeltaEtaCounter;
//
//         if (Cut && CombinedMass < 200) return 0;
//         ++BMassCounter;
//
//
// //         HeavyHiggs->MaxPt = FrontPt;
// //         HeavyHiggs->MinPt = BackPt;
//         HeavyHiggs->DeltaEta = CombinedEta;
//         HeavyHiggs->BMass = CombinedMass;
//
//
//         if (JetSum > 3) {
//
//             ++Jet2Counter;
//
//
//
// //             PseudoJet SecondFrontJet = JetVector.at(1);
// //             float SecondFrontPt = SecondFrontJet.perp();
// //             float SecondFrontEta = SecondFrontJet.eta();
// //
// //             int Counter = 1;
// //             while (FrontPt < SecondFrontPt && SecondFrontEta > 0 && Counter < JetSum-1) {
// //
// //                 iter_swap(JetVector.begin(), JetVector.begin() + Counter);
// //
// //                 ++Counter;
// //
// //                 Print(3,"Counter",Counter);
// //                 Print(3,"SecondBackPt",SecondFrontPt);
// //                 Print(3,"SecondFrontEta",SecondFrontEta);
// //
// //                 SecondFrontJet = JetVector.at(Counter);
// //                 SecondFrontPt = SecondFrontJet.perp();
// //                 SecondFrontEta = SecondFrontJet.eta();
// //
// //             }
// //
// //             PseudoJet SecondBackJet = JetVector.at(JetSum - 1);
// //             float SecondBackPt = SecondBackJet.perp();
// //             float SecondBackEta = SecondBackJet.eta();
// //
// //             Counter = 1;
// //             while (BackPt < SecondBackPt && SecondBackEta < 0 && Counter < JetSum-1) {
// //
// //                 iter_swap(JetVector.begin(), JetVector.begin() + Counter);
// //
// //                 ++Counter;
// //
// //                 SecondBackJet = JetVector.at(JetSum - Counter);
// //                 SecondBackPt = SecondBackJet.perp();
// //                 SecondBackEta = SecondBackJet.eta();
// //
// //             }
// //
// //
// //             FrontJet = JetVector.front();
// //             FrontEta = FrontJet.eta();
// //
// //             BackJet = JetVector.back();
// //             BackEta = BackJet.eta();
// //
// //             CombinedJet = FrontJet + BackJet;
// //             CombinedMass = CombinedJet.m();
// //             CombinedEta = FrontEta - BackEta;
// //
// //
// //             HeavyHiggs->DeltaEta2 = CombinedEta;
// //             HeavyHiggs->BMass2 = CombinedMass;
//
//
//             JetVector.erase(JetVector.begin());
//             JetVector.erase(JetVector.end());
//
//             PseudoJet NegJet;
//             PseudoJet PosJet;
//
//             for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {
//
//                 PseudoJet Jet = JetVector[JetNumber];
//
//                 if (Jet.eta() < 0) {
//
//                     NegJet += Jet;
//
//                 } else if (Jet.eta() > 0) {
//
//                     PosJet += Jet;
//
//                 } else {
//
//                     cout << "perpinticular jet" << endl;
//
//                 }
//
//
//             }
//
//             PseudoJet RestJet = NegJet + PosJet;
//             float TMass = RestJet.m();
//             if (Cut && TMass < 400) return 0;
//             ++TMassCounter;
//
//             HeavyHiggs->TMass = TMass;
//
//             float Phi1 = NegJet.phi_std();
//             float Phi2 = PosJet.phi_std();
//
//             float DeltaPhi = fabs(GetDeltaPhi(Phi2, Phi1));
//
//             HeavyHiggs->DeltaPhi = DeltaPhi;
//
//
//
//         }
//
//
//         return 1;
//
//     }
//
//     return 0;
//
// }
