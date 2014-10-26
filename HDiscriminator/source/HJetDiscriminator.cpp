# include "HJetDiscriminator.hh"

HiggsCPV::HJetDiscriminator::HJetDiscriminator()
{

    Print(1, "Constructor");

    JetTag = new HiggsCPV::HJetTag();

    SubStructure = new Analysis::HSubStructure();

//     DebugLevel = 4;

}


HiggsCPV::HJetDiscriminator::~HJetDiscriminator()
{

    Print(1, "Destructor");

    delete JetTag;

    delete SubStructure;

}

vector<string> HiggsCPV::HJetDiscriminator::GetStudyNames() const
{

//     return {"Higgs", "Top", "Isr"};
    return {"Higgs", "Top", "ATop"};
//     return {"Top"};

}

vector< Analysis::HFile* > HiggsCPV::HJetDiscriminator::GetFiles(const string StudyName) const
{

    Print(1, "Set File Vector");

    vector<Analysis::HFile*> Files;
    if (StudyName != "Higgs") {

      Analysis::HDelphes::HFile *Background = new Analysis::HDelphes::HFile("pp-bbtt-bblvlv", "background");
        Background->Crosssection = 3.215; // pb
        Background->Error = 0.012; // pb
        Files.push_back(Background);

    }

    Analysis::HDelphes::HFile *Even = new Analysis::HDelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->Crosssection = 0.02079; // pb
    Even->Error = 0.000078; // pb
    Files.push_back(Even);

    Analysis::HDelphes::HFile *Mix = new Analysis::HDelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->Crosssection = 0.01172; // pb
    Mix->Error = 0.000045; // pb
    Files.push_back(Mix);

    Analysis::HDelphes::HFile *Odd = new Analysis::HDelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->Crosssection = 0.008951; // pb
    Odd->Error = 0.000035; // pb
    Files.push_back(Odd);

    Print(1, "Files prepared");

    return Files;
}


void HiggsCPV::HJetDiscriminator::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(1, "New File");

    ParticleBranch = TreeWriter->NewBranch("Particle", HCandidateBranch::Class());
    ParticleConstituentBranch = TreeWriter->NewBranch("PartConst", HConstituentBranch::Class());

    TrimmedBranch = TreeWriter->NewBranch("Trimmed", HCandidateBranch::Class());
    TrimmedConstituentBranch = TreeWriter->NewBranch("TrimmedConst", HConstituentBranch::Class());

    CAFatJetBranch = TreeWriter->NewBranch("CAFatJet", HCandidateBranch::Class());
    CAFatJetConstituentBranch = TreeWriter->NewBranch("CAFJCOnst", HConstituentBranch::Class());

    CAMassDropBranch = TreeWriter->NewBranch("CAMassDrop", HCandidateBranch::Class());
    CAMassDropConstituentBranch = TreeWriter->NewBranch("CAMDConst", HConstituentBranch::Class());

    CAPrunerBranch = TreeWriter->NewBranch("CAPruner", HCandidateBranch::Class());
    CAPrunerConstituentBranch = TreeWriter->NewBranch("CAPConst", HConstituentBranch::Class());

    CASJTBranch = TreeWriter->NewBranch("CASJT", HCandidateBranch::Class());
    CASJTConstituentBranch = TreeWriter->NewBranch("CASJTConst", HConstituentBranch::Class());

    AktFatJetBranch = TreeWriter->NewBranch("AktFatJet", HCandidateBranch::Class());
    AktFatJetConstituentBranch = TreeWriter->NewBranch("AktFJConst", HConstituentBranch::Class());

    AktMassDropBranch = TreeWriter->NewBranch("AktMassDrop", HCandidateBranch::Class());
    AktMassDropConstituentBranch = TreeWriter->NewBranch("AktMDConst", HConstituentBranch::Class());

    AktPrunerBranch = TreeWriter->NewBranch("AktPruner", HCandidateBranch::Class());
    AktPrunerConstituentBranch = TreeWriter->NewBranch("AktPConst", HConstituentBranch::Class());

    ConstituentBranch = TreeWriter->NewBranch("Constituent", HConstituentBranch::Class());
    EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Lepton", HLeptonBranch::Class());

}

void HiggsCPV::HJetDiscriminator::CloseFile()
{
    Print(1, "Close File");

}

int HiggsCPV::HJetTag::GetBranchId(const int ParticleId, int BranchId) const
{

    Print(3, "Get Branch Id", ParticleId);

    if (ParticleId == -BranchId) {

        Print(4, "ID CONFILICT", ParticleId, BranchId);

    }

    if (
        RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) &&
        HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    } else if (
        HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles)
        && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    }

    Print(3, "Branch Id", BranchId);

    return BranchId;

}


bool HiggsCPV::HJetDiscriminator::Analysis(Analysis::HEvent* Event,string StudyName)
{

    Print(3, "Analysis");

    const vector<PseudoJet> LeptonJets = Leptons(Event);

    if (LeptonJets.size() < 2) {

        Print(2, "Not enough Leptons", LeptonJets.size());
        return 0;

    }

    Event->GetTaggedEFlow(JetTag);
//
//     float EventPt = 0;
//     for (const auto & EFlowJet : Event->Jets->EFlowJets) {
//
//         EventPt += EFlowJet.pt();
//
//     }

    HEventBranch *EventB = static_cast<HEventBranch *>(EventBranch->NewEntry());
    EventB->ScalarPtSum = 1. / Event->Jets->GetScalarHt();

    vector<int> Ids;
    //     if (StudyName == "Top") Ids = { TopId, -TopId};
    if (StudyName == "Top") Ids = { TopId};
    if (StudyName == "ATop") Ids = { -TopId};
    if (StudyName == "Higgs") Ids = {CpvHiggsId};
    //     if (StudyName == "Isr") Ids = {IsrId};

    for (const auto & Id : Ids) {

        vector<PseudoJet> EFlowJets;
        std::copy_if(Event->Jets->EFlowJets.begin(), Event->Jets->EFlowJets.end(), std::back_inserter(EFlowJets),
        [Id](const PseudoJet & EFlowJet) {

            if (EFlowJet.user_index() == Id) return 1;

            if (
                EFlowJet.user_index() != 5000000 &&
                abs(EFlowJet.user_index()) != 6 &&
                EFlowJet.user_index() != 10
            )
                cout << "EFlowId " << EFlowJet.user_index() << endl;
            return 0;

        });

        if (EFlowJets.size() == 0) {

            Print(0, "NoEflow", Id);
            continue;

        }
        Print(2, "Eflowsize", EFlowJets.size());

        const PseudoJet CandidateJet = fastjet::join(EFlowJets);

        std::map<float, PseudoJet> JetMap;
        for (const auto & EFlowJet : EFlowJets) {

            JetMap.insert(std::pair<float, PseudoJet>(CandidateJet.delta_R(EFlowJet), EFlowJet));

        }


        if (JetMap.size() == 0) {

            Print(0, "No JetMap", Id);
            continue;

        }

        std::map<float, PseudoJet>::iterator JetPair = JetMap.end();
        --JetPair;
        const float MaxRadius = (*JetPair).first;
        Print(2, "MaxRadius", MaxRadius);

        FillTree(ParticleBranch, ParticleConstituentBranch, CandidateJet, LeptonJets, MaxRadius);


        float CandidatePt = 0;
        for (const auto & EFlowJet : EFlowJets) {

            CandidatePt += EFlowJet.pt();

        }
        Print(2, "Max Pt", CandidatePt);

        vector<PseudoJet> TrimmedJets;
        float SigmaPt = 0;
        float SigmaRadius = 0;
        JetPair = JetMap.begin();
        do {

            SigmaRadius = (*JetPair).first;
            TrimmedJets.push_back(JetPair->second);
            SigmaPt += (*JetPair).second.pt();

            Print(2, "EFlow", SigmaRadius, SigmaPt);

            ++JetPair;

        }   while (SigmaPt <= (TwoSigma * CandidatePt) && JetPair != JetMap.end());



        Print(2, "Radius", SigmaRadius);
        Print(2, "mini size", TrimmedJets.size());
        if (TrimmedJets.size() == 0) {

            Print(0, "No Trimmed Eflow", Id);
            continue;

        }

        const PseudoJet MiniCandidateJet = fastjet::join(TrimmedJets);

        FillTree(TrimmedBranch, TrimmedConstituentBranch, MiniCandidateJet, LeptonJets, SigmaRadius);

        JetDefinition CAJetDefinition(cambridge_algorithm, MaxRadius);
        ClusterSequence CAClusterSequence(EFlowJets, CAJetDefinition);
        vector<PseudoJet> CAInclusiveJets = CAClusterSequence.inclusive_jets();
        Print(3, "InclusiveJets Number", CAInclusiveJets.size());

        sort(CAInclusiveJets.begin(), CAInclusiveJets.end(), SortJetByMass());

        for (const auto & CAInclusiveJet : CAInclusiveJets) {

            if (CAInclusiveJet == 0) continue;

//             if (!FillTree(CAFatJetBranch, CAFatJetConstituentBranch, CAInclusiveJet, LeptonJets)) return 0;
            FillTree(CAFatJetBranch, CAFatJetConstituentBranch, CAInclusiveJet, LeptonJets);

            fastjet::MassDropTagger CAMassDropTagger(0.67, 0.09);
            PseudoJet CAMDJet = CAMassDropTagger(CAInclusiveJet);
//             if (!FillTree(CAMassDropBranch, CAMassDropConstituentBranch, CAMDJet, LeptonJets)) return 0;
            FillTree(CAMassDropBranch, CAMassDropConstituentBranch, CAMDJet, LeptonJets);

            fastjet::Pruner CAPruner(fastjet::cambridge_algorithm, CAInclusiveJet.m() / CAInclusiveJet.pt(), 0.1);
            PseudoJet CAPJet = CAPruner(CAInclusiveJet);
//             if (!FillTree(CAPrunerBranch, CAPrunerConstituentBranch, CAPJet, LeptonJets)) return 0;
            FillTree(CAPrunerBranch, CAPrunerConstituentBranch, CAPJet, LeptonJets);

            fastjet::CASubJetTagger CASJT;
            PseudoJet CAJSTJet = CASJT.result(CAInclusiveJet);
//             if (!FillTree(CASJTBranch, CASJTConstituentBranch, CAJSTJet, LeptonJets)) return 0;
            FillTree(CASJTBranch, CASJTConstituentBranch, CAJSTJet, LeptonJets);

            break;

        }

        JetDefinition AktJetDefinition(antikt_algorithm, MaxRadius);
        ClusterSequence AktClusterSequence(EFlowJets, AktJetDefinition);
        vector<PseudoJet> AktInclusiveJets = AktClusterSequence.inclusive_jets(0);
        Print(3, "InclusiveJets Number", AktInclusiveJets.size());

        sort(AktInclusiveJets.begin(), AktInclusiveJets.end(), SortJetByMass());
        for (const auto & AktInclusiveJet : AktInclusiveJets) {

//             if (!FillTree(AktFatJetBranch, AktFatJetConstituentBranch, AktInclusiveJet, LeptonJets)) return 0;
            FillTree(AktFatJetBranch, AktFatJetConstituentBranch, AktInclusiveJet, LeptonJets);

            fastjet::MassDropTagger MDT(0.67, 0.09);
            PseudoJet AktMDJet = MDT(AktInclusiveJet);
//             if (!FillTree(AktMassDropBranch, AktMassDropConstituentBranch, AktMDJet, LeptonJets)) return 0;
            FillTree(AktMassDropBranch, AktMassDropConstituentBranch, AktMDJet, LeptonJets);

            fastjet::Pruner AktPruner(fastjet::cambridge_algorithm, AktInclusiveJet.m() / AktInclusiveJet.pt(), 0.15);
            PseudoJet AktPJet = AktPruner(AktInclusiveJet);
//             if (!FillTree(AktPrunerBranch, AktPrunerConstituentBranch, AktPJet, LeptonJets)) return 0;
            FillTree(AktPrunerBranch, AktPrunerConstituentBranch, AktPJet, LeptonJets);

            break;

        }

        for (const auto & EFlowJet : EFlowJets) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Eta = EFlowJet.eta() - CandidateJet.eta();
            Constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJet.pt();
            Constituent->Id = EFlowJet.user_index();

        }

    }

    return 1;

}

bool HiggsCPV::HJetDiscriminator::FillTree(ExRootTreeBranch *const TreeBranch, ExRootTreeBranch * const ConstituentTreeBranch, const PseudoJet &CandidateJet, const vector<PseudoJet> &LeptonJets, const float DeltaR)
{


    Print(3, "Fill Tree", DeltaR);

    if (CandidateJet != 0 && CandidateJet.m() > 0 && DeltaR > 0) {

        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(TreeBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Eta = CandidateJet.eta();
        Candidate->Phi = CandidateJet.phi_std();
        Candidate->DeltaR = DeltaR;

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
        Candidate->Asymmetry = SubStructure->GetAsymmetry();
        Candidate->DiPolarity = SubStructure->GetDiPolarity(CandidateJet);

        Candidate->SubJet1Mass = SubStructure->GetSubJet1Mass();
        Candidate->SubJet1Pt = SubStructure->GetSubJet1Pt();
        Candidate->SubJet1DeltaR = SubStructure->GetSubJet1DeltaR();

        Candidate->SubJet2Mass = SubStructure->GetSubJet2Mass();
        Candidate->SubJet2Pt = SubStructure->GetSubJet2Pt();
        Candidate->SubJet2DeltaR = SubStructure->GetSubJet2DeltaR();

        if (!SubStructure->GetIsolation(CandidateJet, LeptonJets)) return 0;

        Candidate->IsolationEta = SubStructure->GetIsolationEta();
        Candidate->IsolationPhi = SubStructure->GetIsolationPhi();
        Candidate->IsolationPt = SubStructure->GetIsolationPt();
        Candidate->IsolationDeltaR = SubStructure->GetIsolationDeltaR();
        Candidate->IsolationAngle = SubStructure->GetIsolationAngle();

        Print(3, "Isolation", Candidate->IsolationDeltaR);

        if (!SubStructure->GetConstituents(CandidateJet, ConstituentTreeBranch)) return 0;

        Candidate->ConstEta = SubStructure->GetConstituentEta();
        Candidate->ConstPhi = SubStructure->GetConstituentPhi();
        Candidate->ConstDeltaR = SubStructure->GetConstituentDeltaR();
        Candidate->ConstAngle = SubStructure->GetConstituentAngle();

        Print(3, "Pull", Candidate->ConstDeltaR);

        return 1;

    }

    return 0;

}

bool HiggsCPV::HJetDiscriminator::FillTree(ExRootTreeBranch * const TreeBranch, ExRootTreeBranch * const ConstituentTreeBranch, const PseudoJet &Jet, const vector<PseudoJet> &LeptonJets)
{

    return FillTree(TreeBranch, ConstituentTreeBranch, Jet, LeptonJets, GetDeltaR(Jet));

}

float HiggsCPV::HJetDiscriminator::GetDeltaR(const PseudoJet &Jet)
{

    Print(3, "Get DeltaR");

    float DeltaR = 0;

    if (Jet.has_constituents()) {

        for (const auto & Constituent : Jet.constituents()) {

            const float ConstDistance = Jet.delta_R(Constituent);

            if (ConstDistance > DeltaR) DeltaR = ConstDistance;

        }

    }

    return DeltaR;

}

vector<PseudoJet> HiggsCPV::HJetDiscriminator::Leptons(Analysis::HEvent* Event)
{

    // Lepton Stuff
    vector<float> LeptonEta, LeptonPhi;

//     Event->GetLeptons();

//     vector<PseudoJet> LeptonJets = Event->Lepton->LeptonJets;
//     vector<PseudoJet> AntiLeptonJets = Event->Lepton->AntiLeptonJets;

    Event->GetParticles();
    vector<PseudoJet> LeptonJets = Event->Particles->GetLeptonJets();
    vector<PseudoJet> AntiLeptonJets = Event->Particles->GetAntiLeptonJets();

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

