# include "HAnalysisHeavyHiggsPgs.hh"

HAnalysisHeavyHiggsPgs::HAnalysisHeavyHiggsPgs()
{

    Print(1, "Constructor");

}

vector<Analysis::HFile*> HAnalysisHeavyHiggsPgs::GetFiles(const string StudyName) const
{

    Print(1, "Fill Analysis Vector",StudyName);

    vector<Analysis::HFile*> Files;

    Files.push_back(new Analysis::HFileFolder("Signal_5f"));
    Files.push_back(new Analysis::HFileFolder("5f_10k_Pt20"));

//     FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    Files.front()->BasePath = "~/Dropbox/Projects/HeavyHiggs/Simulation/";
    Files.front()->FileSuffix = "_PGS.root";
    Files.front()->TreeString = "LHCO";

    Print(1, "Files prepared", Files.size());

    return Files;

}

void HAnalysisHeavyHiggsPgs::NewBranches(ExRootTreeWriter *TreeWriter)
{

    Print(1, "New File");


    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());


    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void HAnalysisHeavyHiggsPgs::CloseFile()
{
    Print(1, "Close File");

//     if (Cut) {

        Print(1, "EventCounter", EventCounter);
        Print(1, "JetCounter", JetCounter);
        Print(1, "DeltaEtaCounter", DeltaEtaCounter);
        Print(1, "BMassCounter", BMassCounter);
        Print(1, "Jet2Counter", Jet2Counter);
        Print(1, "TMassCounter", TMassCounter);

//     }

}


bool HAnalysisHeavyHiggsPgs::Analysis(Analysis::HEvent* Event,string StudyName)
{

    Print(2, "Analysis",StudyName);

    Event->GetJets();

    vector<PseudoJet> BJets = Event->Jets->BottomJets;

    Print(2, "BJet Sum", BJets.size());

//     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
//
//         Print(2, "BJet Pt", BJets[BJetNumber].pt());
//
//     }
//
// //     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
// //
// //         if (BJets[BJetNumber].pt() < 1 || BJets[BJetNumber].pt() > 10000) {
// //
// //             BJets.erase(BJets.begin() + BJetNumber);
// //
// //         }
// //     }
//
//     BJets.erase(std::remove_if(BJets.begin(), BJets.end(), [](PseudoJet Jet) {
//         return Jet.pt() > 1000000;
//     }), BJets.end());
//     BJets.erase(std::remove_if(BJets.begin(), BJets.end(), [](PseudoJet Jet) {
//         return Jet.pt() < 1;
//     }), BJets.end());
//
//     Print(2, "BJet Sum", BJets.size());
//
//     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
//
//         Print(2, "BJet Pt", BJets[BJetNumber].pt());
//
//     }



    if (BJets.size() > 1) {

        for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {

            Print(2, "BJetNumber", BJetNumber);

            for (unsigned BJetNumber2 = 0; BJetNumber2 < BJetNumber; ++BJetNumber2) {

                Print(2, "BJetNumber2", BJetNumber2);

                PseudoJet FrontJet, BackJet;

                if (BJets[BJetNumber].eta() > BJets[BJetNumber2].eta()) {

                    FrontJet = BJets[BJetNumber];
                    BackJet = BJets[BJetNumber2];

                } else if (BJets[BJetNumber].eta() < BJets[BJetNumber2].eta()) {

                    FrontJet = BJets[BJetNumber2];
                    BackJet = BJets[BJetNumber];

                } else {

                    Print(1, "Comparison broken");

                }

                float FrontPt = FrontJet.pt();
                float FrontEta = FrontJet.eta();
                float FrontPhi = FrontJet.phi_std();
                Print(2, "FrontPt", FrontPt);
                Print(2, "FrontEta", FrontEta);
                Print(2, "FrontPhi", FrontPhi);

                float BackEta = BackJet.eta();
                float BackPt = BackJet.pt();
                float BackPhi = BackJet.phi_std();

                Print(2, "BackPt", BackPt);
                Print(2, "BackEta", BackEta);
                Print(2, "BackPhi", BackPhi);

                float InvMass = (FrontJet + BackJet).m();
                float DeltaEta = FrontEta - BackEta;

                Print(2, "InvMass", InvMass);
                Print(2, "DeltaEta", DeltaEta);

                float DeltaPhi = GetDeltaPhi(FrontPhi, BackPhi);

                HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

                HeavyHiggs->BottomEta1 = FrontEta;
                HeavyHiggs->BottomEta2 = BackEta;
                HeavyHiggs->BottomDeltaEta = DeltaEta;

                HeavyHiggs->BottomPhi1 = FrontPhi;
                HeavyHiggs->BottomPhi2 = BackPhi;
                HeavyHiggs->BottomDeltaPhi = DeltaPhi;

                HeavyHiggs->BottomPt1 = FrontPt;
                HeavyHiggs->BottomPt2 = BackPt;
                HeavyHiggs->BottomInvMass = InvMass;

                HeavyHiggs->BTag = BJets.size();
                HeavyHiggs->JetNumber = Event->Jets->Jets.size();

            }

        }

        return 1;

    } else {

        Print(2, "Just 1 B Jet");

    }

    return 0;

}
