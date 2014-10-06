# include "HAnalysisJetProperties.hh"

HAnalysisJetProperties::HAnalysisJetProperties()
{

    Print(0, "Constructor");

    ProjectName = "Discriminator";

    LeptonEventCounter = 0;

//     ClonesArrays = new HClonesArrayDelphes();
//
//     Event = new HEventDelphes();

//     Debug = 3;

    EventNumberMax = 10000;

}

vector<string> HAnalysisJetProperties::GetStudyNameVector()
{

    vector<string> StudyNameVector = {"Constituents"};

    return StudyNameVector;

}

void HAnalysisJetProperties::SetFileVector()
{

    Print(0, "Set File Vector", StudyName);


    HFileDelphes *Even = new HFileDelphes("pp-x0tt-bblvlv", "even");
    Even->Crosssection = 0.02079; // pb
    Even->Error = 0.000078; // pb
    FileVector.push_back(Even);

    int AnalysisSum = FileVector.size();
    Print(0, "Files prepared", AnalysisSum);

}


void HAnalysisJetProperties::NewFile()
{
    Print(0, "New File");

    ConstituentBranch = TreeWriter->NewBranch("Constituent", HConstituentBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Leptons",HLeptonBranch::Class());
    CandidateBranch = TreeWriter->NewBranch("Candidates",HCandidateBranch::Class());

}

void HAnalysisJetProperties::CloseFile()
{
    Print(0, "Close File");

}



bool HAnalysisJetProperties::Analysis()
{

    Event->GetLeptons();
    
    vector<PseudoJet> LeptonJetVector = Event->Lepton->GetLeptonJetVector();
    
    if (LeptonJetVector.size() <2 ) return 0; 
    
//     for (unsigned LeptonNumber = 0; LeptonNumber < LeptonJetVector.size(); ++LeptonNumber) {
//         
//         HLeptonBranch *Lepton= static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
//         Lepton->Eta = LeptonJetVector[LeptonNumber].eta();
//         Lepton->Phi = LeptonJetVector[LeptonNumber].phi();
//         Lepton->Pt = LeptonJetVector[LeptonNumber].pt();
//         
//     }

    HLeptonBranch *Lepton= static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());
    Lepton->Pt = LeptonJetVector[0].pt() - LeptonJetVector[1].pt();
    Lepton->Mass = LeptonJetVector[0].pt() + LeptonJetVector[1].pt();
    
    Event->GetTaggedEFlow();

    vector<PseudoJet> EFlowJetVector = Event->Jets->EFlowJetVector;

    PseudoJet HiggsJet;

    for (unsigned EFlowNumber = 0; EFlowNumber < EFlowJetVector.size(); ++EFlowNumber) {

        if (EFlowJetVector[EFlowNumber].user_index() == CpvHiggsId) {

            HiggsJet = fastjet::join(HiggsJet, EFlowJetVector[EFlowNumber]);

        }

    }
    
    
    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());
    
    Candidate->Mass = HiggsJet.m();
    Candidate->Pt = HiggsJet.pt();
    Candidate->Eta = HiggsJet.eta();
    Candidate->Phi = HiggsJet.phi_std();
   


    for (unsigned EFlowNumber = 0; EFlowNumber < EFlowJetVector.size(); ++EFlowNumber) {

        HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
        Constituent->Eta = EFlowJetVector[EFlowNumber].eta() - HiggsJet.eta();
        Constituent->Phi = EFlowJetVector[EFlowNumber].delta_phi_to(HiggsJet);
        Constituent->Pt = EFlowJetVector[EFlowNumber].pt();
        Constituent->Id = EFlowJetVector[EFlowNumber].user_index();

    }


    return 1;

}
