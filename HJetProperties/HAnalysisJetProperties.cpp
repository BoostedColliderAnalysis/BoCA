# include "HAnalysisJetProperties.hh"

HAnalysisJetProperties::HAnalysisJetProperties()
{

    Print(1, "Constructor");

    ProjectName = "Discriminator";

    LeptonEventCounter = 0;

    EventNumberMax = 10000;

}

vector<string> HAnalysisJetProperties::GetStudyNameVector()
{

    vector<string> StudyNameVector = {"Constituents"};

    return StudyNameVector;

}

void HAnalysisJetProperties::SetFileVector()
{

    Print(1, "Set File Vector", StudyName);


//     FileVector.push_back(new HFileFolder("BG_ttbb"));
    FileVector.push_back(new HFileFolder("h2bb_ttbb"));

    FileVector.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
    FileVector.front()->FileSuffix = ".root";
//     FileVector.front()->Snowmass = 1;

    int AnalysisSum = FileVector.size();
    Print(1, "Files prepared", AnalysisSum);

}


void HAnalysisJetProperties::NewFile()
{
    Print(1, "New File");

    ConstituentBranch = TreeWriter->NewBranch("Constituent", HConstituentBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Leptons", HLeptonBranch::Class());
    JetPropertiesBranch = TreeWriter->NewBranch("Candidates", HJetPropertiesBranch::Class());

}

void HAnalysisJetProperties::CloseFile()
{
    Print(1, "Close File");

}



bool HAnalysisJetProperties::Analysis()
{

    Print(3, "Analysis");

    Event->GetLeptons();

//     vector<PseudoJet> LeptonJetVector = Event->Lepton->GetLeptonJetVector();
//
// //     if (LeptonJetVector.size() < 2) return 0;
//
//     sort(LeptonJetVector.begin(), LeptonJetVector.end(), SortJetByPt());
//
// //     for (unsigned LeptonNumber = 0; LeptonNumber < LeptonJetVector.size(); ++LeptonNumber) {
// //
// //         HLeptonBranch *Lepton= static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
// //         Lepton->Eta = LeptonJetVector[LeptonNumber].eta();
// //         Lepton->Phi = LeptonJetVector[LeptonNumber].phi();
// //         Lepton->Pt = LeptonJetVector[LeptonNumber].pt();
// //
// //     }
//
//     HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
//     Lepton->Pt = 1. / (LeptonJetVector[0].pt() - LeptonJetVector[1].pt());
//     Lepton->Mass = 1. / (LeptonJetVector[0].pt() + LeptonJetVector[1].pt());

    Event->GetTaggedEFlow();

    float PtSum;


    for (auto& EFlowJet: Event->Jets->EFlowJetVector) {
        PtSum += EFlowJet.pt();
    }

    Print(0, "New Event");

//     for (unsigned ConstNumber = 0; ConstNumber < Event->Jets->EFlowJetVector.size(); ++ConstNumber) {
//
//
//         Print(0,"Index",Event->Jets->EFlowJetVector[ConstNumber].user_index());
//
//         PtSum += Event->Jets->EFlowJetVector[ConstNumber].pt();
//
//     }

//     int Id = CpvHiggsId;
    vector<int> IdVector = { -BottomId};
//     vector<int> IdVector = {HeavyHiggsId};

    for (auto& Id : IdVector) {

        vector<PseudoJet> EFlowJetVector;
        std::copy_if(Event->Jets->EFlowJetVector.begin(), Event->Jets->EFlowJetVector.end(), std::back_inserter(EFlowJetVector),
        [Id](const PseudoJet& EFlowJet) {

            return EFlowJet.user_index() == Id;

        });

        if (EFlowJetVector.size() == 0) {

            Print(0, "NoEflow", Id);

            return 0;

        }

        const PseudoJet CandidateJet = fastjet::join(EFlowJetVector);

        vector<float> DistanceVector;

        for (auto& EFlowJet : EFlowJetVector) {

            DistanceVector.push_back(CandidateJet.delta_R(EFlowJet));

        }


        std::nth_element(DistanceVector.begin(), DistanceVector.begin() + DistanceVector.size() / 2, DistanceVector.end());

//     Print(0, "Median", DistanceVector[DistanceVector.size() * 0.68]);

        float RMax = 0;
        for (auto& EFlowJet : EFlowJetVector) {

            float DeltaR = CandidateJet.delta_R(EFlowJet);
            if (DeltaR > RMax) RMax = DeltaR;

        }

//     Print(0, "RMax", RMax);

        HJetPropertiesBranch *Jet = static_cast<HJetPropertiesBranch *>(JetPropertiesBranch->NewEntry());

//         Print(-1,"size",DistanceVector.size());

        Jet->Mass = CandidateJet.m();
        Jet->Pt = CandidateJet.pt();
        Jet->Eta = CandidateJet.eta();
        Jet->Phi = CandidateJet.phi_std();
        Jet->Radius = DistanceVector[int(DistanceVector.size() * 0.68)];
        Jet->JetPtSum = 1. / PtSum;
//         Jet->PtSum= 1. / (PtSum + LeptonJetVector[0].pt() + LeptonJetVector[1].pt());



        for (auto& EFlowJet : EFlowJetVector) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Eta = EFlowJet.eta() - CandidateJet.eta();
            Constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJet.pt();
            Constituent->Id = EFlowJet.user_index();

        }
    }

    return 1;

}
