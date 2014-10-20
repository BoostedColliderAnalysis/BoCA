# include "HAnalysisJetProperties.hh"

HAnalysisJetProperties::HAnalysisJetProperties()
{

    Print(1, "Constructor");

    ProjectName = "Discriminator";

    LeptonEventCounter = 0;

    EventNumberMax = 10000;
    
//     DebugLevel = 5;

}

vector<string> HAnalysisJetProperties::GetStudyNameVector()
{

    vector<string> StudyNameVector = {"Higgs","Top"};

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
//     LeptonBranch = TreeWriter->NewBranch("Leptons", HLeptonBranch::Class());
    JetPropertiesBranch = TreeWriter->NewBranch("Candidates", HJetPropertiesBranch::Class());

}

void HAnalysisJetProperties::CloseFile()
{
    Print(1, "Close File");

}



class HHeavyHiggsJetTag : public HJetTag
{

    int GetBranchId(int, int) const;

};


int HHeavyHiggsJetTag::GetBranchId(const int ParticleId, int BranchId) const
{

    Print(2, "Get Mother Id");

    if (InitialState.find(abs(ParticleId)) != end(InitialState) && HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)) {
        BranchId = IsrId;
    } else if (abs(ParticleId) == BottomId && (abs(BranchId) != TopId && abs(BranchId) != HeavyHiggsId)) {
        BranchId = ParticleId;
    } else if (abs(ParticleId) == TopId && abs(BranchId) != HeavyHiggsId) {
        BranchId = ParticleId;
    } else if (abs(ParticleId) == HeavyHiggsId) {
        BranchId = ParticleId;
    }

    Print(4, "Mother Id", BranchId);


    return BranchId;

}


bool HAnalysisJetProperties::Analysis()
{

    Print(1, "Analysis");

    Event->GetParticles();
//     Event->GetLeptons();

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

    const HHeavyHiggsJetTag *const HeavyHiggsJetTag = new HHeavyHiggsJetTag;

    Event->GetTaggedEFlow(HeavyHiggsJetTag);

    float PtSum;


    for (const auto & EFlowJet : Event->Jets->EFlowJets) {
        PtSum += EFlowJet.pt();
    }

    Print(3, "New Event");

//     for (unsigned ConstNumber = 0; ConstNumber < Event->Jets->EFlowJetVector.size(); ++ConstNumber) {
//
//
//         Print(0,"Index",Event->Jets->EFlowJetVector[ConstNumber].user_index());
//
//         PtSum += Event->Jets->EFlowJetVector[ConstNumber].pt();
//
//     }

    vector<int> IdVector;
//     if (StudyName == "Bottom")vector<int> IdVector = { BottomId,-BottomId};
    if (StudyName == "Top") IdVector = { TopId,-TopId};
//     if (StudyName == "Higgs") vector<int> IdVector = {HeavyHiggsId};
    if (StudyName == "Higgs") IdVector = {CpvHiggsId};

    for (const auto & Id : IdVector) {

        vector<PseudoJet> EFlowJetVector;
        std::copy_if(Event->Jets->EFlowJets.begin(), Event->Jets->EFlowJets.end(), std::back_inserter(EFlowJetVector),
        [Id](const PseudoJet & EFlowJet) {

            if (EFlowJet.user_index() == Id) return 1;
            if (EFlowJet.has_user_info()) {

                if (EFlowJet.user_info<HJetInfo>().HasParticle(Id)) return 1;

            }

            return 0;

        });

        if (EFlowJetVector.size() == 0) {

            Print(1, "NoEflow", Id);

            return 0;

        }

        const PseudoJet CandidateJet = fastjet::join(EFlowJetVector);

        vector<float> DistanceVector;

        for (const auto & EFlowJet : EFlowJetVector) {

            DistanceVector.push_back(CandidateJet.delta_R(EFlowJet));

        }


        std::nth_element(DistanceVector.begin(), DistanceVector.begin() + DistanceVector.size() / 2, DistanceVector.end());

//     Print(0, "Median", DistanceVector[DistanceVector.size() * 0.68]);

        float RMax = 0;
        for (const auto & EFlowJet : EFlowJetVector) {

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



        for (const auto & EFlowJet : EFlowJetVector) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Eta = EFlowJet.eta() - CandidateJet.eta();
            Constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJet.pt();
            Constituent->Id = EFlowJet.user_index();

        }
    }

    return 1;

}



