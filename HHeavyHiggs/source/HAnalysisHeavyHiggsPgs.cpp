# include "HAnalysisHeavyHiggsPgs.hh"

// hheavyhiggs::HAnalysisHeavyHiggsPgs::HAnalysisHeavyHiggsPgs()
// {
//
//     Print(kNotification, "Constructor");
//
// }

std::vector<hanalysis::RootFile*> hheavyhiggs::HAnalysisHeavyHiggsPgs::GetFiles(const std::string &StudyName)
{

    Print(kNotification, "Fill Analysis Vector",StudyName);

    std::vector<hanalysis::RootFile*> Files;

    Files.emplace_back(new hanalysis::RootFile("Signal_5f"));
    Files.emplace_back(new hanalysis::RootFile("5f_10k_Pt20"));

//     FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    Files.front()->SetBasePath("~/Dropbox/Projects/HeavyHiggs/Simulation/");
    Files.front()->set_file_suffix("_PGS.root");
    Files.front()->set_tree_name("LHCO");

    Print(kNotification, "Files prepared", Files.size());

    return Files;

}

void hheavyhiggs::HAnalysisHeavyHiggsPgs::NewBranches(ExRootTreeWriter *TreeWriter)
{

    Print(kNotification, "New File");


    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HBranchHeavyHiggs::Class());


    eventCounter = 0;
    DeltaRapCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void hheavyhiggs::HAnalysisHeavyHiggsPgs::CloseFile()
{
    Print(kNotification, "Close File");

//     if (Cut) {

        Print(kNotification, "eventCounter", eventCounter);
        Print(kNotification, "JetCounter", JetCounter);
        Print(kNotification, "DeltaRapCounter", DeltaRapCounter);
        Print(kNotification, "BMassCounter", BMassCounter);
        Print(kNotification, "Jet2Counter", Jet2Counter);
        Print(kNotification, "TMassCounter", TMassCounter);

//     }

}


int hheavyhiggs::HAnalysisHeavyHiggsPgs::Analysis(hanalysis::Event &event, const std::string &StudyName)
{

    Print(kInformation, "Analysis",StudyName);

//     event.GetJets();

    Jets BJets = event.Hadrons().GetBottomJets();

    Print(kInformation, "BJet Sum", BJets.size());

//     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
//
//         Print(kInformation, "BJet Pt", BJets[BJetNumber].pt());
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
//     BJets.erase(std::remove_if(BJets.begin(), BJets.end(), [](fastjet::PseudoJet Jet) {
//         return Jet.pt() > 1000000;
//     }), BJets.end());
//     BJets.erase(std::remove_if(BJets.begin(), BJets.end(), [](fastjet::PseudoJet Jet) {
//         return Jet.pt() < 1;
//     }), BJets.end());
//
//     Print(kInformation, "BJet Sum", BJets.size());
//
//     for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {
//
//         Print(kInformation, "BJet Pt", BJets[BJetNumber].pt());
//
//     }



    if (BJets.size() > 1) {

        for (unsigned BJetNumber = 0; BJetNumber < BJets.size(); ++BJetNumber) {

            Print(kInformation, "BJetNumber", BJetNumber);

            for (unsigned BJetNumber2 = 0; BJetNumber2 < BJetNumber; ++BJetNumber2) {

                Print(kInformation, "BJetNumber2", BJetNumber2);

                fastjet::PseudoJet FrontJet, BackJet;

                if (BJets[BJetNumber].rap() > BJets[BJetNumber2].rap()) {

                    FrontJet = BJets[BJetNumber];
                    BackJet = BJets[BJetNumber2];

                } else if (BJets[BJetNumber].rap() < BJets[BJetNumber2].rap()) {

                    FrontJet = BJets[BJetNumber2];
                    BackJet = BJets[BJetNumber];

                } else {

                    Print(kNotification, "Comparison broken");

                }

                float FrontPt = FrontJet.pt();
                float FrontRap = FrontJet.rap();
                float FrontPhi = FrontJet.phi_std();
                Print(kInformation, "FrontPt", FrontPt);
                Print(kInformation, "FrontRap", FrontRap);
                Print(kInformation, "FrontPhi", FrontPhi);

                float BackRap = BackJet.rap();
                float BackPt = BackJet.pt();
                float BackPhi = BackJet.phi_std();

                Print(kInformation, "BackPt", BackPt);
                Print(kInformation, "BackRap", BackRap);
                Print(kInformation, "BackPhi", BackPhi);

                float InvMass = (FrontJet + BackJet).m();
                float DeltaRap = FrontRap - BackRap;

                Print(kInformation, "InvMass", InvMass);
                Print(kInformation, "DeltaRap", DeltaRap);

                float DeltaPhi = GetDeltaPhi(FrontPhi, BackPhi);

                HBranchHeavyHiggs *HeavyHiggs = static_cast<HBranchHeavyHiggs *>(HeavyHiggsBranch->NewEntry());

                HeavyHiggs->BottomRap1 = FrontRap;
                HeavyHiggs->BottomRap2 = BackRap;
                HeavyHiggs->BottomDeltaRap = DeltaRap;

                HeavyHiggs->BottomPhi1 = FrontPhi;
                HeavyHiggs->BottomPhi2 = BackPhi;
                HeavyHiggs->BottomDeltaPhi = DeltaPhi;

                HeavyHiggs->BottomPt1 = FrontPt;
                HeavyHiggs->BottomPt2 = BackPt;
                HeavyHiggs->BottomInvMass = InvMass;

                HeavyHiggs->BTag = BJets.size();
                HeavyHiggs->JetNumber = event.Hadrons().GetJets().size();

            }

        }

        return 1;

    } else {

        Print(kInformation, "Just 1 B Jet");

    }

    return 0;

}
