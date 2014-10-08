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


    HFileDelphes *Even = new HFileDelphes("pp-x0tt-bblvlv", "even");
    Even->Crosssection = 0.02079; // pb
    Even->Error = 0.000078; // pb
    FileVector.push_back(Even);

    int AnalysisSum = FileVector.size();
    Print(1, "Files prepared", AnalysisSum);

}


void HAnalysisJetProperties::NewFile()
{
    Print(1, "New File");

    ConstituentBranch = TreeWriter->NewBranch("Constituent", HConstituentBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Leptons", HLeptonBranch::Class());
    CandidateBranch = TreeWriter->NewBranch("Candidates", HCandidateBranch::Class());

}

void HAnalysisJetProperties::CloseFile()
{
    Print(1, "Close File");

}



bool HAnalysisJetProperties::Analysis()
{

    Event->GetLeptons();

    vector<PseudoJet> LeptonJetVector = Event->Lepton->GetLeptonJetVector();


    if (LeptonJetVector.size() < 2) return 0;
    sort(LeptonJetVector.begin(),LeptonJetVector.end(),SortJetByPt());

//     for (unsigned LeptonNumber = 0; LeptonNumber < LeptonJetVector.size(); ++LeptonNumber) {
//
//         HLeptonBranch *Lepton= static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
//         Lepton->Eta = LeptonJetVector[LeptonNumber].eta();
//         Lepton->Phi = LeptonJetVector[LeptonNumber].phi();
//         Lepton->Pt = LeptonJetVector[LeptonNumber].pt();
//
//     }

    HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
    Lepton->Pt = 1. / (LeptonJetVector[0].pt() - LeptonJetVector[1].pt());
    Lepton->Mass = 1. / (LeptonJetVector[0].pt() + LeptonJetVector[1].pt());

    Event->GetTaggedEFlow();

    float PtSum;

    for (unsigned ConstNumber = 0; ConstNumber < Event->Jets->EFlowJetVector.size(); ++ConstNumber) {

        PtSum += Event->Jets->EFlowJetVector[ConstNumber].pt();

    }

//     int Id = CpvHiggsId;
    vector<int> IdVector = {-BottomId,BottomId};

    for (unsigned IdNumber=0; IdNumber<IdVector.size(); ++IdNumber) {

        vector<PseudoJet> EFlowJetVector;
        int Id = IdVector[IdNumber];
        std::copy_if(Event->Jets->EFlowJetVector.begin(), Event->Jets->EFlowJetVector.end(), std::back_inserter(EFlowJetVector),
        [Id](PseudoJet const & EFlowJet) {
            return EFlowJet.user_index() == Id;
        });

        const PseudoJet CandidateJet = fastjet::join(EFlowJetVector);

        vector<float> DistanceVector;

        for (unsigned ConstNumber = 0; ConstNumber < EFlowJetVector.size(); ++ConstNumber) {

            DistanceVector.push_back(CandidateJet.delta_R(EFlowJetVector[ConstNumber]));

        }


        std::nth_element(DistanceVector.begin(), DistanceVector.begin() + DistanceVector.size() / 2, DistanceVector.end());

//     Print(0, "Median", DistanceVector[DistanceVector.size() * 0.68]);

        float RMax = 0;
        for (unsigned EFlowNumber = 0; EFlowNumber < EFlowJetVector.size(); ++EFlowNumber) {

            float DeltaR = CandidateJet.delta_R(EFlowJetVector[EFlowNumber]);
            if (DeltaR > RMax) RMax = DeltaR;

        }

//     Print(0, "RMax", RMax);

        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Eta = CandidateJet.eta();
        Candidate->Phi = CandidateJet.phi_std();
        Candidate->Area = DistanceVector[DistanceVector.size() * 0.68];
        Candidate->IsolationPt = 1. / PtSum;
        Candidate->SubJet1Pt = 1./(PtSum + LeptonJetVector[0].pt() + LeptonJetVector[1].pt());



        for (unsigned EFlowNumber = 0; EFlowNumber < EFlowJetVector.size(); ++EFlowNumber) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Eta = EFlowJetVector[EFlowNumber].eta() - CandidateJet.eta();
            Constituent->Phi = EFlowJetVector[EFlowNumber].delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJetVector[EFlowNumber].pt();
            Constituent->Id = EFlowJetVector[EFlowNumber].user_index();

        }
    }

    return 1;

}
