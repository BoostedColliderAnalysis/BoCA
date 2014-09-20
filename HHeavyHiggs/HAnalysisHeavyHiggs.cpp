# include "HAnalysisHeavyHiggs.hh"

HAnalysisHeavyHiggs::HAnalysisHeavyHiggs()
{

    Print(0, "Constructor");

    ProjectName = "HeavyHiggs5";

    EventNumberMax = 10000;

    ClonesArrays = new HClonesArraySnowmass();
    
    Event = new HEventDelphes();

    Cut = 1;

}

// TString HFileBase::BasePath = "~/Projects/HeavyHiggs/Mass5/";

void HAnalysisHeavyHiggs::SetFileVector()
{

    Print(0, "Fill Analysis Vector", AnalysisName);

    FileVector.push_back(new HFileFolder("Background"));
    FileVector.push_back(new HFileFolder("400GeV"));
//     FileVector.push_back(new HFileFolder("500GeV"));
//     FileVector.push_back(new HFileFolder("600GeV"));
//     FileVector.push_back(new HFileFolder("700GeV"));
//     FileVector.push_back(new HFileFolder("800GeV"));
//     FileVector.push_back(new HFileFolder("900GeV"));
    FileVector.push_back(new HFileFolder("1000GeV"));
    
    FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass5/";

//     FileVector.push_back(new HFileDelphes("pp-bbtt-4f", "background"));

    Print(0, "Files prepared", FileVector.size());

}

void HAnalysisHeavyHiggs::NewFile()
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

void HAnalysisHeavyHiggs::CloseFile()
{
    Print(0, "Close File");

    Print(0, "EventCounter", EventCounter);
    Print(0, "JetCounter", JetCounter);
    Print(0, "DeltaEtaCounter", DeltaEtaCounter);
    Print(0, "BMassCounter", BMassCounter);
    Print(0, "Jet2Counter", Jet2Counter);
    Print(0, "TMassCounter", TMassCounter);

}



bool HAnalysisHeavyHiggs::Analysis()
{

    Print(1, "Analysis", AnalysisName);

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    //     Event->GetLeptons();

    //     vector<PseudoJet> LeptonVector = Event->Leptons->LeptonJetVector;

    //     int LeptonSum = LeptonVector.size();
    //     if (LeptonSum < 1 ) return 0;

    ++EventCounter;

    Event->GetJets();



    vector<PseudoJet> BJets = Event->Jets->BottomJetVector;
    int BJetSum = BJets.size();
    HeavyHiggs->BTag = BJetSum;
    Print(3, "B Jets", BJetSum);



    vector<PseudoJet> TopJets = Event->GetTops();
    Print(3, "Top Jets", TopJets.size());

    vector<PseudoJet> JetVector = Event->Jets->JetVector;
    int JetSum = JetVector.size();
    HeavyHiggs->JetNumber = JetSum;
    Print(2,"JetSum",JetSum);
    if (JetSum > 1) {

        ++JetCounter;

        sort(JetVector.begin(), JetVector.end(), SortJetByEta());

        PseudoJet FrontJet = JetVector.front();
        double FrontPt = FrontJet.pt();
        double FrontEta = FrontJet.eta();

        PseudoJet BackJet = JetVector.back();
        double BackEta = BackJet.eta();
        double BackPt = BackJet.pt();

        PseudoJet CombinedJet = FrontJet + BackJet;
        double CombinedMass = CombinedJet.m();
        double CombinedEta = FrontEta - BackEta;

        if (Cut && CombinedEta < 3) return 0;
        ++DeltaEtaCounter;

        if (Cut && CombinedMass < 200) return 0;
        ++BMassCounter;


//         HeavyHiggs->MaxPt = FrontPt;
//         HeavyHiggs->MinPt = BackPt;
        HeavyHiggs->DeltaEta = CombinedEta;
        HeavyHiggs->BMass = CombinedMass;


        if (JetSum > 3) {
            
            ++Jet2Counter;



//             PseudoJet SecondFrontJet = JetVector.at(1);
//             float SecondFrontPt = SecondFrontJet.perp();
//             float SecondFrontEta = SecondFrontJet.eta();
// 
//             int Counter = 1;
//             while (FrontPt < SecondFrontPt && SecondFrontEta > 0 && Counter < JetSum-1) {
// 
//                 iter_swap(JetVector.begin(), JetVector.begin() + Counter);
// 
//                 ++Counter;
//                 
//                 Print(3,"Counter",Counter);
//                 Print(3,"SecondBackPt",SecondFrontPt);
//                 Print(3,"SecondFrontEta",SecondFrontEta);
// 
//                 SecondFrontJet = JetVector.at(Counter);
//                 SecondFrontPt = SecondFrontJet.perp();
//                 SecondFrontEta = SecondFrontJet.eta();
// 
//             }
// 
//             PseudoJet SecondBackJet = JetVector.at(JetSum - 1);
//             float SecondBackPt = SecondBackJet.perp();
//             float SecondBackEta = SecondBackJet.eta();
// 
//             Counter = 1;
//             while (BackPt < SecondBackPt && SecondBackEta < 0 && Counter < JetSum-1) {
// 
//                 iter_swap(JetVector.begin(), JetVector.begin() + Counter);
// 
//                 ++Counter;
// 
//                 SecondBackJet = JetVector.at(JetSum - Counter);
//                 SecondBackPt = SecondBackJet.perp();
//                 SecondBackEta = SecondBackJet.eta();
// 
//             }
// 
//             
//             FrontJet = JetVector.front();
//             FrontEta = FrontJet.eta();
//             
//             BackJet = JetVector.back();
//             BackEta = BackJet.eta();
//             
//             CombinedJet = FrontJet + BackJet;
//             CombinedMass = CombinedJet.m();
//             CombinedEta = FrontEta - BackEta;
//             
//             
//             HeavyHiggs->DeltaEta2 = CombinedEta;
//             HeavyHiggs->BMass2 = CombinedMass;
            

            JetVector.erase(JetVector.begin());
            JetVector.erase(JetVector.end());

            PseudoJet NegJet;
            PseudoJet PosJet;

            for (int JetNumber = 0; JetNumber < JetSum; ++JetNumber) {

                PseudoJet Jet = JetVector[JetNumber];

                if (Jet.eta() < 0) {

                    NegJet += Jet;

                } else if (Jet.eta() > 0) {

                    PosJet += Jet;

                } else {

                    cout << "perpinticular jet" << endl;

                }


            }

            PseudoJet RestJet = NegJet + PosJet;
            double TMass = RestJet.m();
            if (Cut && TMass < 400) return 0;
            ++TMassCounter;

            HeavyHiggs->TMass = TMass;

            double Phi1 = NegJet.phi_std();
            double Phi2 = PosJet.phi_std();

            double DeltaPhi = fabs(GetDeltaPhi(Phi2, Phi1));

            HeavyHiggs->DeltaPhi = DeltaPhi;

        }


        return 1;

    }

    return 0;

}
