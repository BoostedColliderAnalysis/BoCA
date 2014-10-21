# include "HAnalysisDiscriminator.hh"

HAnalysisDiscriminator::HAnalysisDiscriminator()
{

    Print(1, "Constructor");

    ProjectName = "Discriminator";

    LeptonEventCounter = 0;

//     DebugLevel = 3;

//     EventNumberMax = 10000;

    DiscriminatorJetTag = new HDiscriminatorJetTag();
    
    SubStructure = new HSubStructure();

}

HAnalysisDiscriminator::~HAnalysisDiscriminator()
{

    Print(1, "Destructor");

    delete DiscriminatorJetTag;
    
    delete SubStructure;

}

vector<string> HAnalysisDiscriminator::GetStudyNames()
{

//     vector<string> StudyNameVector = {"Higgs", "Top", "TwoTop","HiggsTop", "Jet", "Test"};
    vector<string> StudyNameVector = {"Higgs", "Top", "Jet", "Test"};
    //     vector<string> StudyNameVector = {"Top"};

    return StudyNameVector;

}

void HAnalysisDiscriminator::SetFileVector()
{

    Print(1, "Set File Vector", StudyName);

    if (StudyName != "Higgs") {

        HFileDelphes *Background = new HFileDelphes("pp-bbtt-bblvlv", "background");
        Background->Crosssection = 3.215; // pb
        Background->Error = 0.012; // pb
        FileVector.push_back(Background);

    }

    HFileDelphes *Even = new HFileDelphes("pp-x0tt-bblvlv", "even");
    Even->Crosssection = 0.02079; // pb
    Even->Error = 0.000078; // pb
    FileVector.push_back(Even);

    HFileDelphes *Mix = new HFileDelphes("pp-x0tt-bblvlv", "mix");
    Mix->Crosssection = 0.01172; // pb
    Mix->Error = 0.000045; // pb
    FileVector.push_back(Mix);

    HFileDelphes *Odd = new HFileDelphes("pp-x0tt-bblvlv", "odd");
    Odd->Crosssection = 0.008951; // pb
    Odd->Error = 0.000035; // pb
    FileVector.push_back(Odd);

    int AnalysisSum = FileVector.size();
    Print(1, "Files prepared", AnalysisSum);

}


void HAnalysisDiscriminator::NewFile()
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Lepton", HLeptonBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());

    LeptonEventCounter = 0;

}

void HAnalysisDiscriminator::CloseFile()
{
    Print(1, "Close File");

}

int HDiscriminatorJetTag::GetBranchId(const int ParticleId, int BranchId) const
{

    Print(3, "Get Branch Id", ParticleId);

    if (ParticleId == -BranchId) {

        Print(4, "ID CONFILICT", ParticleId, BranchId);

    }

    if (
        RadiationParticles.find(abs(ParticleId)) != end(RadiationParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    } else if (
        HeavyParticles.find(abs(ParticleId)) != end(HeavyParticles)
        && HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    } 
    
    Print(3, "Branch Id", BranchId);

    return BranchId;

}

bool HAnalysisDiscriminator::Analysis()
{

    Print(2, "Analysis", StudyName);

    const vector<PseudoJet> Leptons = GetLeptonJets();

    if (Leptons.size() < 2) {

        Print(2, "Not enough Leptons", Leptons.size());
        return 0;

    }

    ++LeptonEventCounter;

    // Higgs stuff

    const vector<PseudoJet> CandidateJets = Event->GetHiggsTopCandidates(DiscriminatorJetTag);



    if (CandidateJets.size() < 1) {

        Print(2, "No a Candidates", CandidateJets.size());
        return 0;

    } else Print(2, "Number of Candidates", CandidateJets.size());

    int CandidateCounter = 0;
    bool HasCandidate = 0;
    bool HiggsCounter = 0;

    for (const auto & CandidateJet : CandidateJets) {

        Print(3, "Candidate", CandidateJet.user_index());

        if (StudyName == "Higgs") {

            if (CandidateCounter > 0) {

                Print(2, "Number of Higgs", CandidateCounter);
                break;

            }

            if (CandidateJet.user_index() != CpvHiggsId) {

                Print(3, "Not a Higgs");
                continue;

            }

            ++CandidateCounter;

        }

        if (StudyName == "Top") {

            if (abs(CandidateJet.user_index()) != TopId) {

                Print(3, "Not a Top");
                continue;

            }

            if (CandidateCounter > 1) Print(2, "Number of Tops", CandidateCounter);
            ++CandidateCounter;
            Print(3, "Top", CandidateCounter);

        }

        if (StudyName == "Jet") {

            if (CandidateJet.user_index() == CpvHiggsId && HiggsCounter == 0) {

                HiggsCounter = 1;
                Print(3, "Not a light jet");
                continue;

            }

            if (abs(CandidateJet.user_index()) == TopId) {

                Print(3, "Not a light jet");
                continue;

            }

            if (CandidateCounter > 2) Print(1, "Number light jets", CandidateCounter);
            ++CandidateCounter;
            Print(2, "Jet", CandidateCounter);

        }

        if (CandidateJet == 0 || CandidateJet.m() <= 0 || CandidateJet.pt() <= 0) {

            Print(0, "Illeagal Candidate", CandidateJet.m());
            continue;

        }


        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Eta = CandidateJet.eta();
        Candidate->Phi = CandidateJet.phi_std();

        Print(3, "Candidate Mass", CandidateJet.m());

        // Tagging

        int UserIndex = abs(CandidateJet.user_index());

        if (UserIndex == CpvHiggsId) {
            Candidate->HiggsTag = 1;
            Candidate->TopTag = 0;

        } else if (UserIndex == TopId) {

            Candidate->TopTag = 1;
            Candidate->HiggsTag = 0;

        } else {

            Candidate->TopTag = 0;
            Candidate->HiggsTag = 0;

        }

        SubStructure->NewEvent();
        if (!SubStructure->GetSubJets(CandidateJet)) return 0;

        Candidate->SubJetsDeltaR = SubStructure->GetSubJetsDeltaR();
        Candidate->Asymmetry= SubStructure->GetAsymmetry();
        Candidate->DeltaR= SubStructure->GetDeltaR();

        Candidate->SubJet1Mass = SubStructure->GetSubJet1Mass();
        Candidate->SubJet1Pt = SubStructure->GetSubJet1Pt();
        Candidate->SubJet1DeltaR = SubStructure->GetSubJet1DeltaR();
        
        Candidate->SubJet2Mass = SubStructure->GetSubJet2Mass();
        Candidate->SubJet2Pt = SubStructure->GetSubJet2Pt();
        Candidate->SubJet2DeltaR = SubStructure->GetSubJet2DeltaR();
        
        SubStructure->GetIsolation(CandidateJet,Leptons);

        Candidate->IsolationEta = SubStructure->GetIsolationEta();
        Candidate->IsolationPhi = SubStructure->GetIsolationPhi();
        Candidate->IsolationPt = SubStructure->GetIsolationPt();
        Candidate->IsolationDeltaR = SubStructure->GetIsolationDeltaR();
        Candidate->IsolationAngle = SubStructure->GetIsolationAngle();

        Print(3, "Isolation", Candidate->IsolationDeltaR);
        
        if(!SubStructure->GetConstituents(CandidateJet, ConstituentBranch)) return 0;
        
        Candidate->ConstEta = SubStructure->GetConstituentEta();
        Candidate->ConstPhi = SubStructure->GetConstituentPhi();
        Candidate->ConstDeltaR = SubStructure->GetConstituentDeltaR();
        Candidate->ConstAngle = SubStructure->GetConstituentAngle();

        Print(3, "Pull", Candidate->ConstDeltaR);

        HasCandidate = 1;
    }

    if (HasCandidate) return 1;

    Print(2, "No Candidates found");

    return 0;

}


vector<PseudoJet> HAnalysisDiscriminator::GetLeptonJets()
{

// Lepton Stuff
    vector<float> LeptonEta, LeptonPhi;

    Event->GetLeptons();

    vector<PseudoJet> LeptonJets = Event->Lepton->LeptonJets;
    vector<PseudoJet> AntiLeptonJets = Event->Lepton->AntiLeptonJets;

//     vector<TLorentzVector> LeptonVector = Event->Leptons->LeptonLorentzVectorVector;
//     vector<TLorentzVector> AntiLeptonVector = Event->Leptons->AntiLeptonLorentzVectorVector;

//     Event->GetParticles();
//     vector<TLorentzVector> LeptonVector = Event->Particle->LeptonVector();
//     vector<TLorentzVector> AntiLeptonVector = Event->Particle->AntiLeptonVector();

    sort(LeptonJets.begin(), LeptonJets.end(), SortJetByPt());
    sort(AntiLeptonJets.begin(), AntiLeptonJets.end(), SortJetByPt());

    bool HardestLepton = 1;
    for (const auto & LeptonJet : LeptonJets) {

        if (HardestLepton) {

            HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());

            Lepton->Pt = LeptonJet.pt();
            Lepton->Eta = LeptonJet.eta();
            Lepton->Phi = LeptonJet.phi_std();
            Lepton->Charge = -1;
            Lepton->Mass = LeptonJet.m();
        }
        HardestLepton = 0;

        LeptonEta.push_back(LeptonJet.eta());
        LeptonPhi.push_back(LeptonJet.phi_std());

    }

    HardestLepton = 1;
    for (const auto & AntiLeptonJet : AntiLeptonJets) {

        if (HardestLepton) {

            HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());

            Lepton->Pt = AntiLeptonJet.pt();
            Lepton->Eta = AntiLeptonJet.eta();
            Lepton->Phi = AntiLeptonJet.phi_std();
            Lepton->Charge = 1;
            Lepton->Mass = AntiLeptonJet.m();

        }
        HardestLepton = 0;

        LeptonEta.push_back(AntiLeptonJet.eta());
        LeptonPhi.push_back(AntiLeptonJet.phi_std());

    }

    LeptonJets.insert(LeptonJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());

    Print(2, "Number of Leptons", LeptonJets.size());

    return LeptonJets;

}


