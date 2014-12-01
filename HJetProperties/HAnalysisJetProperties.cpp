# include "HAnalysisJetProperties.hh"

hjetproperties::HAnalysis::HAnalysis()
{

    Print(HNotification, "Constructor");

    JetTag = new hanalysis::HJetTag();

    SubStructure = new hdelphes::HSubStructure();

    //     DebugLevel = 4;

}


hjetproperties::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    delete JetTag;

    delete SubStructure;

}

HStrings hjetproperties::HAnalysis::GetStudyNames() const
{

    //     return {"Higgs", "Top", "Isr"};
    return {"Higgs", "Top", "ATop", "Isr"};
    //     return {"Top"};

}

std::vector< hanalysis::HFile* > hjetproperties::HAnalysis::GetFiles(const std::string &StudyName)
{

    Print(HNotification, "Set File Vector");

    std::vector<hanalysis::HFile*> Files;
    if (StudyName != "Higgs") {

        hdelphes::HFile *Background = new hdelphes::HFile("pp-bbtt-bblvlv", "background");
        Background->SetCrosssection(3.215); // pb
        Background->SetError(0.012); // pb
        Files.push_back(Background);

    }

    hdelphes::HFile *Even = new hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->SetCrosssection(0.02079); // pb
    Even->SetError(0.000078); // pb
    Files.push_back(Even);

    hdelphes::HFile *Mix = new hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->SetCrosssection(0.01172); // pb
    Mix->SetError(0.000045); // pb
    Files.push_back(Mix);

    hdelphes::HFile *Odd = new hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(0.008951); // pb
    Odd->SetError(0.000035); // pb
    Files.push_back(Odd);

    Print(HNotification, "Files prepared");

    return Files;
}


void hjetproperties::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(HNotification, "New File");

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

void hjetproperties::HAnalysis::CloseFile()
{
    Print(HNotification, "Close File");

}

// int hjetproperties::HJetTag::GetBranchId(const int ParticleId, int BranchId)
// {
// 
//     Print(HDebug, "Get Branch Id", ParticleId);
// 
//     if (ParticleId == -BranchId) {
// 
//         Print(HDetailed, "ID CONFILICT", ParticleId, BranchId);
// 
//     }
// 
//     if (
//         RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = IsrId;
//     } else if (
//         HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles)
//         && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = ParticleId;
//     }
// 
//     Print(HDebug, "Branch Id", BranchId);
// 
//     return BranchId;
// 
// }


bool hjetproperties::HAnalysis::Analysis(hanalysis::HEvent *Event, const std::string &StudyName)
{

    Print(HDebug, "Analysis");

    const HJets LeptonJets = Leptons(Event);

    if (LeptonJets.size() < 2) {

        Print(HInformation, "Not enough Leptons", LeptonJets.size());
        return 0;

    }

//     Event->GetTaggedEFlow(JetTag);
    //
    //     float EventPt = 0;
    //     for (const auto & EFlowJet : Event->Jets->EFlowJets) {
    //
    //         EventPt += EFlowJet.pt();
    //
    //     }

    HEventBranch *EventB = static_cast<HEventBranch *>(EventBranch->NewEntry());
    EventB->ScalarPtSum = 1. / Event->GetJets()->GetScalarHt();

    std::vector<int> Ids;
    //     if (StudyName == "Top") Ids = { TopId, -TopId};
    if (StudyName == "Top") Ids = { TopId};
    if (StudyName == "ATop") Ids = { -TopId};
    if (StudyName == "Higgs") Ids = {CpvHiggsId};
        if (StudyName == "Isr") Ids = {IsrId};

    for (const auto & Id : Ids) {

        HJets EFlowJets;
        std::copy_if(Event->GetJets()->GetTaggedEFlowJets(JetTag).begin(), Event->GetJets()->GetTaggedEFlowJets().end(), std::back_inserter(EFlowJets),
                     [Id](const fastjet::PseudoJet & EFlowJet) {

                         if (EFlowJet.user_index() == Id) return 1;

                     if (
                         EFlowJet.user_index() != 5000000 &&
                         std::abs(EFlowJet.user_index()) != 6 &&
                         EFlowJet.user_index() != 86
                     )
                         std::cout << "EFlowId " << EFlowJet.user_index() << std::endl;
                         return 0;

                     });

        if (EFlowJets.size() == 0) {

            Print(HError, "NoEflow", Id);
            continue;

        }
        Print(HInformation, "Eflowsize", EFlowJets.size());

        const fastjet::PseudoJet CandidateJet = fastjet::join(EFlowJets);

        std::map<float, fastjet::PseudoJet> JetMap;
        for (const auto & EFlowJet : EFlowJets) {

            JetMap.insert(std::pair<float, fastjet::PseudoJet>(CandidateJet.delta_R(EFlowJet), EFlowJet));

        }


        if (JetMap.size() == 0) {

            Print(HError, "No JetMap", Id);
            continue;

        }

        std::map<float, fastjet::PseudoJet>::iterator JetPair = JetMap.end();
        --JetPair;
        const float MaxRadius = (*JetPair).first;
        Print(HInformation, "MaxRadius", MaxRadius);

        FillTree(ParticleBranch, ParticleConstituentBranch, CandidateJet, LeptonJets, MaxRadius);


        float CandidatePt = 0;
        for (const auto & EFlowJet : EFlowJets) {

            CandidatePt += EFlowJet.pt();

        }
        Print(HInformation, "Max Pt", CandidatePt);

        HJets TrimmedJets;
        float SigmaPt = 0;
        float SigmaRadius = 0;
        JetPair = JetMap.begin();
        do {

            SigmaRadius = (*JetPair).first;
            TrimmedJets.push_back(JetPair->second);
            SigmaPt += (*JetPair).second.pt();

            Print(HInformation, "EFlow", SigmaRadius, SigmaPt);

            ++JetPair;

        }   while (SigmaPt <= (TwoSigma * CandidatePt) && JetPair != JetMap.end());



        Print(HInformation, "Radius", SigmaRadius);
        Print(HInformation, "mini size", TrimmedJets.size());
        if (TrimmedJets.size() == 0) {

            Print(HError, "No Trimmed Eflow", Id);
            continue;

        }

        const fastjet::PseudoJet MiniCandidateJet = fastjet::join(TrimmedJets);

        FillTree(TrimmedBranch, TrimmedConstituentBranch, MiniCandidateJet, LeptonJets, SigmaRadius);

        fastjet::JetDefinition CAJetDefinition(fastjet::cambridge_algorithm, MaxRadius);
        fastjet::ClusterSequence CAClusterSequence(EFlowJets, CAJetDefinition);
        HJets CAInclusiveJets = CAClusterSequence.inclusive_jets();
        Print(HDebug, "InclusiveJets Number", CAInclusiveJets.size());

        std::sort(CAInclusiveJets.begin(), CAInclusiveJets.end(), SortJetByMass());

        for (const auto & CAInclusiveJet : CAInclusiveJets) {

            if (CAInclusiveJet == 0) continue;

            //             if (!FillTree(CAFatJetBranch, CAFatJetConstituentBranch, CAInclusiveJet, LeptonJets)) return 0;
            FillTree(CAFatJetBranch, CAFatJetConstituentBranch, CAInclusiveJet, LeptonJets);

            fastjet::MassDropTagger CAMassDropTagger(0.67, 0.09);
            fastjet::PseudoJet CAMDJet = CAMassDropTagger(CAInclusiveJet);
            //             if (!FillTree(CAMassDropBranch, CAMassDropConstituentBranch, CAMDJet, LeptonJets)) return 0;
            FillTree(CAMassDropBranch, CAMassDropConstituentBranch, CAMDJet, LeptonJets);

            fastjet::Pruner CAPruner(fastjet::cambridge_algorithm, CAInclusiveJet.m() / CAInclusiveJet.pt(), 0.1);
            fastjet::PseudoJet CAPJet = CAPruner(CAInclusiveJet);
            //             if (!FillTree(CAPrunerBranch, CAPrunerConstituentBranch, CAPJet, LeptonJets)) return 0;
            FillTree(CAPrunerBranch, CAPrunerConstituentBranch, CAPJet, LeptonJets);

            fastjet::CASubJetTagger CASJT;
            fastjet::PseudoJet CAJSTJet = CASJT.result(CAInclusiveJet);
            //             if (!FillTree(CASJTBranch, CASJTConstituentBranch, CAJSTJet, LeptonJets)) return 0;
            FillTree(CASJTBranch, CASJTConstituentBranch, CAJSTJet, LeptonJets);

            break;

        }

        fastjet::JetDefinition AktJetDefinition(fastjet::antikt_algorithm, MaxRadius);
        fastjet::ClusterSequence AktClusterSequence(EFlowJets, AktJetDefinition);
        HJets AktInclusiveJets = AktClusterSequence.inclusive_jets(0);
        Print(HDebug, "InclusiveJets Number", AktInclusiveJets.size());

        std::sort(AktInclusiveJets.begin(), AktInclusiveJets.end(), SortJetByMass());
        for (const auto & AktInclusiveJet : AktInclusiveJets) {

            //             if (!FillTree(AktFatJetBranch, AktFatJetConstituentBranch, AktInclusiveJet, LeptonJets)) return 0;
            FillTree(AktFatJetBranch, AktFatJetConstituentBranch, AktInclusiveJet, LeptonJets);

            fastjet::MassDropTagger MDT(0.67, 0.09);
            fastjet::PseudoJet AktMDJet = MDT(AktInclusiveJet);
            //             if (!FillTree(AktMassDropBranch, AktMassDropConstituentBranch, AktMDJet, LeptonJets)) return 0;
            FillTree(AktMassDropBranch, AktMassDropConstituentBranch, AktMDJet, LeptonJets);

            fastjet::Pruner AktPruner(fastjet::cambridge_algorithm, AktInclusiveJet.m() / AktInclusiveJet.pt(), 0.15);
            fastjet::PseudoJet AktPJet = AktPruner(AktInclusiveJet);
            //             if (!FillTree(AktPrunerBranch, AktPrunerConstituentBranch, AktPJet, LeptonJets)) return 0;
            FillTree(AktPrunerBranch, AktPrunerConstituentBranch, AktPJet, LeptonJets);

            break;

        }

        for (const auto & EFlowJet : EFlowJets) {

            HConstituentBranch *Constituent = static_cast<HConstituentBranch *>(ConstituentBranch->NewEntry());
            Constituent->Rap = EFlowJet.rap() - CandidateJet.rap();
            Constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            Constituent->Pt = EFlowJet.pt();
            Constituent->Id = EFlowJet.user_index();

        }

    }

    return 1;

}

bool hjetproperties::HAnalysis::FillTree(ExRootTreeBranch *const TreeBranch, ExRootTreeBranch * const ConstituentTreeBranch, const fastjet::PseudoJet &CandidateJet, const HJets &LeptonJets, const float DeltaR)
{


    Print(HDebug, "Fill Tree", DeltaR);

    if (CandidateJet != 0 && CandidateJet.m() > 0 && DeltaR > 0) {

        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(TreeBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Rap = CandidateJet.rap();
        Candidate->Phi = CandidateJet.phi_std();
        Candidate->DeltaR = DeltaR;

        Print(HDebug, "Candidate Mass", CandidateJet.m());

        // Tagging

        int UserIndex = std::abs(CandidateJet.user_index());

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

        Candidate->IsolationRap = SubStructure->GetIsolationRap();
        Candidate->IsolationPhi = SubStructure->GetIsolationPhi();
        Candidate->IsolationPt = SubStructure->GetIsolationPt();
        Candidate->IsolationDeltaR = SubStructure->GetIsolationDeltaR();
        Candidate->IsolationAngle = SubStructure->GetIsolationAngle();

        Print(HDebug, "Isolation", Candidate->IsolationDeltaR);

//         if (!SubStructure->GetConstituents(CandidateJet, ConstituentTreeBranch)) return 0;

        HVectors ConstituentVectors = SubStructure->GetConstituents(CandidateJet);

        for (const auto & ConstituentVector : ConstituentVectors) {
          HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentTreeBranch->NewEntry());
          Constituent->Rap = ConstituentVector.Rapidity();
          Constituent->Phi = ConstituentVector.Phi();
          Constituent->Pt = ConstituentVector.Pt();
        }

        Candidate->ConstRap = SubStructure->GetConstituentRap();
        Candidate->ConstPhi = SubStructure->GetConstituentPhi();
        Candidate->ConstDeltaR = SubStructure->GetConstituentDeltaR();
        Candidate->ConstAngle = SubStructure->GetConstituentAngle();

        Print(HDebug, "Pull", Candidate->ConstDeltaR);

        return 1;

    }

    return 0;

}

bool hjetproperties::HAnalysis::FillTree(ExRootTreeBranch * const TreeBranch, ExRootTreeBranch * const ConstituentTreeBranch, const fastjet::PseudoJet &Jet, const HJets &LeptonJets)
{

    return FillTree(TreeBranch, ConstituentTreeBranch, Jet, LeptonJets, GetDeltaR(Jet));

}

float hjetproperties::HAnalysis::GetDeltaR(const fastjet::PseudoJet &Jet)
{

    Print(HDebug, "Get DeltaR");

    float DeltaR = 0;

    if (Jet.has_constituents()) {

        for (const auto & Constituent : Jet.constituents()) {

            const float ConstDistance = Jet.delta_R(Constituent);

            if (ConstDistance > DeltaR) DeltaR = ConstDistance;

        }

    }

    return DeltaR;

}

HJets hjetproperties::HAnalysis::Leptons(hanalysis::HEvent* Event)
{

    // Lepton Stuff
    std::vector<float> LeptonRap, LeptonPhi;

    //     Event->GetLeptons();

    //     HJets LeptonJets = Event->Lepton->LeptonJets;
    //     HJets AntiLeptonJets = Event->Lepton->AntiLeptonJets;

//     Event->GetParticlesM()->GetParticles();
    HJets LeptonJets = Event->GetParticles()->GetLeptonJets();
    HJets AntiLeptonJets = Event->GetParticles()->GetAntiLeptonJets();

    std::sort(LeptonJets.begin(), LeptonJets.end(), SortJetByPt());
    std::sort(AntiLeptonJets.begin(), AntiLeptonJets.end(), SortJetByPt());

    bool HardestLepton = 1;
    for (const auto & LeptonJet : LeptonJets) {

        if (HardestLepton) {

            HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());

            Lepton->Pt = LeptonJet.pt();
            Lepton->Rap = LeptonJet.rap();
            Lepton->Phi = LeptonJet.phi_std();
            Lepton->Charge = -1;
            Lepton->Mass = LeptonJet.m();
        }
        HardestLepton = 0;

        LeptonRap.push_back(LeptonJet.rap());
        LeptonPhi.push_back(LeptonJet.phi_std());

    }

    HardestLepton = 1;
    for (const auto & AntiLeptonJet : AntiLeptonJets) {

        if (HardestLepton) {

            HLeptonBranch *Lepton = static_cast<HLeptonBranch *>(LeptonBranch->NewEntry());

            Lepton->Pt = AntiLeptonJet.pt();
            Lepton->Rap = AntiLeptonJet.rap();
            Lepton->Phi = AntiLeptonJet.phi_std();
            Lepton->Charge = 1;
            Lepton->Mass = AntiLeptonJet.m();

        }
        HardestLepton = 0;

        LeptonRap.push_back(AntiLeptonJet.rap());
        LeptonPhi.push_back(AntiLeptonJet.phi_std());

    }

    LeptonJets.insert(LeptonJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());

    Print(HInformation, "Number of Leptons", LeptonJets.size());

    return LeptonJets;

}

