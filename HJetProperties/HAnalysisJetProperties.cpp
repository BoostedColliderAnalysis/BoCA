# include "HAnalysisJetProperties.hh"
# include "fastjet/tools/MassDropTagger.hh"
# include "Predicate.hh"

// hjetproperties::HAnalysis::HAnalysis()
// {
//
//     Print(kNotification, "Constructor");
//
//     //jet_tag = new analysis::JetTag();
//
//     sub_structure = new analysis::SubStructure();
//
//     //     DebugLevel = 4;
//
// }


analysis::Strings hjetproperties::HAnalysis::GetStudyNames() const
{

    //     return {"Higgs", "Top", "Isr"};
    return {"Higgs", "Top", "ATop", "Isr"};
    //     return {"Top"};

}

std::vector< analysis::File* > hjetproperties::HAnalysis::GetFiles(const std::string &StudyName)
{

    Print(kNotification, "Set File Vector");

    std::vector<analysis::File*> Files;
    if (StudyName != "Higgs") {

      analysis::File *Background = new analysis::File("pp-bbtt-bblvlv", "background");
        Background->set_crosssection(3.215); // pb
        Background->set_crosssection_error(0.012); // pb
        Files.emplace_back(Background);

    }

    analysis::File *Even = new analysis::File("pp-x0tt-bblvlv", "even");
    Even->set_crosssection(0.02079); // pb
    Even->set_crosssection_error(0.000078); // pb
    Files.emplace_back(Even);

    analysis::File *Mix = new analysis::File("pp-x0tt-bblvlv", "mix");
    Mix->set_crosssection(0.01172); // pb
    Mix->set_crosssection_error(0.000045); // pb
    Files.emplace_back(Mix);

    analysis::File *Odd = new analysis::File("pp-x0tt-bblvlv", "odd");
    Odd->set_crosssection(0.008951); // pb
    Odd->set_crosssection_error(0.000035); // pb
    Files.emplace_back(Odd);

    Print(kNotification, "Files prepared");

    return Files;
}


void hjetproperties::HAnalysis::NewBranches(exroot::TreeWriter *TreeWriter)
{
    Print(kNotification, "New File");

    particle_branch = TreeWriter->NewBranch("Particle", HCandidateBranch::Class());
    ParticleconstituentBranch = TreeWriter->NewBranch("PartConst", ConstituentBranch::Class());

    TrimmedBranch = TreeWriter->NewBranch("Trimmed", HCandidateBranch::Class());
    TrimmedconstituentBranch = TreeWriter->NewBranch("TrimmedConst", ConstituentBranch::Class());

    CAFatJetBranch = TreeWriter->NewBranch("CAFatJet", HCandidateBranch::Class());
    CAFatJetconstituentBranch = TreeWriter->NewBranch("CAFJCOnst", ConstituentBranch::Class());

    CAMassDropBranch = TreeWriter->NewBranch("CAMassDrop", HCandidateBranch::Class());
    CAMassDropconstituentBranch = TreeWriter->NewBranch("CAMDConst", ConstituentBranch::Class());

    CAPrunerBranch = TreeWriter->NewBranch("CAPruner", HCandidateBranch::Class());
    CAPrunerconstituentBranch = TreeWriter->NewBranch("CAPConst", ConstituentBranch::Class());

    CASJTBranch = TreeWriter->NewBranch("CASJT", HCandidateBranch::Class());
    CASJTconstituentBranch = TreeWriter->NewBranch("CASJTConst", ConstituentBranch::Class());

    AktFatJetBranch = TreeWriter->NewBranch("AktFatJet", HCandidateBranch::Class());
    AktFatJetconstituentBranch = TreeWriter->NewBranch("AktFJConst", ConstituentBranch::Class());

    AktMassDropBranch = TreeWriter->NewBranch("AktMassDrop", HCandidateBranch::Class());
    AktMassDropconstituentBranch = TreeWriter->NewBranch("AktMDConst", ConstituentBranch::Class());

    AktPrunerBranch = TreeWriter->NewBranch("AktPruner", HCandidateBranch::Class());
    AktPrunerconstituentBranch = TreeWriter->NewBranch("AktPConst", ConstituentBranch::Class());

    constituentBranch = TreeWriter->NewBranch("constituent", ConstituentBranch::Class());
    eventBranch = TreeWriter->NewBranch("event", analysis::EventBranch::Class());
    LeptonBranch = TreeWriter->NewBranch("Lepton", HLeptonBranch::Class());

}

void hjetproperties::HAnalysis::CloseFile()
{
    Print(kNotification, "Close File");

}

// int hjetproperties::JetTag::GetBranchId(const int particle_id, int BranchId)
// {
//
//     Print(kDebug, "Branch Id", particle_id);
//
//     if (particle_id == -BranchId) {
//
//         Print(kDetailed, "ID CONFILICT", particle_id, BranchId);
//
//     }
//
//     if (
//         RadiationParticles.find(std::abs(particle_id)) != end(RadiationParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = IsrId;
//     } else if (
//         HeavyParticles.find(std::abs(particle_id)) != end(HeavyParticles)
//         && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = particle_id;
//     }
//
//     Print(kDebug, "Branch Id", BranchId);
//
//     return BranchId;
//
// }


int hjetproperties::HAnalysis::Analysis(analysis::Event &event, const std::string &StudyName)
{

    Print(kDebug, "Analysis");

    const analysis::Jets LeptonJets = Leptons(event);

    if (LeptonJets.size() < 2) {

        Print(kInformation, "Not enough Leptons", LeptonJets.size());
        return 0;

    }

//     event.GetTaggedEFlow(jet_tag);
    //
    //     float eventPt = 0;
    //     for (const auto & EFlowJet : event->Jets->EFlowJets) {
    //
    //         eventPt += EFlowJet.pt();
    //
    //     }

    analysis::EventBranch *eventB = static_cast<analysis::EventBranch *>(eventBranch->NewEntry());
    eventB->ScalarPtSum = 1. / event.Hadrons().ScalarHt();

    std::vector<int> Ids;
    //     if (StudyName == "Top") Ids = { TopId, -TopId};
    if (StudyName == "Top") Ids = { TopId};
    if (StudyName == "ATop") Ids = { -TopId};
    if (StudyName == "Higgs") Ids = {CpvHiggsId};
        if (StudyName == "Isr") Ids = {IsrId};

    for (const auto & Id : Ids) {

      analysis::Jets EFlowJets;
        std::copy_if(event.Hadrons().Jets().begin(), event.Hadrons().Jets().end(), std::back_inserter(EFlowJets),
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

        if (EFlowJets.empty()) {

            Print(kError, "NoEflow", Id);
            continue;

        }
        Print(kInformation, "Eflowsize", EFlowJets.size());

        const fastjet::PseudoJet CandidateJet = fastjet::join(EFlowJets);

        std::map<float, fastjet::PseudoJet> JetMap;
        for (const auto & EFlowJet : EFlowJets) {

            JetMap.insert(std::pair<float, fastjet::PseudoJet>(CandidateJet.delta_R(EFlowJet), EFlowJet));

        }


        if (JetMap.empty()) {

            Print(kError, "No JetMap", Id);
            continue;

        }

        std::map<float, fastjet::PseudoJet>::iterator JetPair = JetMap.end();
        --JetPair;
        const float MaxRadius = (*JetPair).first;
        Print(kInformation, "MaxRadius", MaxRadius);

        FillTree(particle_branch, ParticleconstituentBranch, CandidateJet, LeptonJets, MaxRadius);


        float CandidatePt = 0;
        for (const auto & EFlowJet : EFlowJets) {

            CandidatePt += EFlowJet.pt();

        }
        Print(kInformation, "Max Pt", CandidatePt);

        analysis::Jets TrimmedJets;
        float SigmaPt = 0;
        float SigmaRadius = 0;
        JetPair = JetMap.begin();
        float TwoSigma = 0.9545;

        do {

            SigmaRadius = (*JetPair).first;
            TrimmedJets.emplace_back(JetPair->second);
            SigmaPt += (*JetPair).second.pt();

            Print(kInformation, "EFlow", SigmaRadius, SigmaPt);

            ++JetPair;

        }   while (SigmaPt <= (TwoSigma * CandidatePt) && JetPair != JetMap.end());



        Print(kInformation, "Radius", SigmaRadius);
        Print(kInformation, "mini size", TrimmedJets.size());
        if (TrimmedJets.empty()) {

            Print(kError, "No Trimmed Eflow", Id);
            continue;

        }

        const fastjet::PseudoJet MiniCandidateJet = fastjet::join(TrimmedJets);

        FillTree(TrimmedBranch, TrimmedconstituentBranch, MiniCandidateJet, LeptonJets, SigmaRadius);

        fastjet::JetDefinition CAJetDefinition(fastjet::cambridge_algorithm, MaxRadius);
        fastjet::ClusterSequence CAClusterSequence(EFlowJets, CAJetDefinition);
        analysis::Jets CAInclusiveJets = CAClusterSequence.inclusive_jets();
        Print(kDebug, "InclusiveJets Number", CAInclusiveJets.size());

//         std::sort(CAInclusiveJets.begin(), CAInclusiveJets.end(), analysis::SortJetByMass());
        CAInclusiveJets = analysis::SortedByMass(CAInclusiveJets);

        for (const auto & CAInclusiveJet : CAInclusiveJets) {

            if (CAInclusiveJet == 0) continue;

            //             if (!FillTree(CAFatJetBranch, CAFatJetconstituentBranch, CAInclusiveJet, LeptonJets)) return 0;
            FillTree(CAFatJetBranch, CAFatJetconstituentBranch, CAInclusiveJet, LeptonJets);

            fastjet::MassDropTagger CAMassDropTagger(0.67, 0.09);
            fastjet::PseudoJet CAMDJet = CAMassDropTagger(CAInclusiveJet);
            //             if (!FillTree(CAMassDropBranch, CAMassDropconstituentBranch, CAMDJet, LeptonJets)) return 0;
            FillTree(CAMassDropBranch, CAMassDropconstituentBranch, CAMDJet, LeptonJets);

            fastjet::Pruner CAPruner(fastjet::cambridge_algorithm, CAInclusiveJet.m() / CAInclusiveJet.pt(), 0.1);
            fastjet::PseudoJet CAPJet = CAPruner(CAInclusiveJet);
            //             if (!FillTree(CAPrunerBranch, CAPrunerconstituentBranch, CAPJet, LeptonJets)) return 0;
            FillTree(CAPrunerBranch, CAPrunerconstituentBranch, CAPJet, LeptonJets);

            fastjet::CASubJetTagger CASJT;
            fastjet::PseudoJet CAJSTJet = CASJT.result(CAInclusiveJet);
            //             if (!FillTree(CASJTBranch, CASJTconstituentBranch, CAJSTJet, LeptonJets)) return 0;
            FillTree(CASJTBranch, CASJTconstituentBranch, CAJSTJet, LeptonJets);

            break;

        }

        fastjet::JetDefinition AktJetDefinition(fastjet::antikt_algorithm, MaxRadius);
        fastjet::ClusterSequence AktClusterSequence(EFlowJets, AktJetDefinition);
        analysis::Jets AktInclusiveJets = AktClusterSequence.inclusive_jets(0);
        Print(kDebug, "InclusiveJets Number", AktInclusiveJets.size());

//         std::sort(AktInclusiveJets.begin(), AktInclusiveJets.end(), analysis::SortJetByMass());
        AktInclusiveJets = analysis::SortedByMass(AktInclusiveJets);
        for (const auto & AktInclusiveJet : AktInclusiveJets) {

            //             if (!FillTree(AktFatJetBranch, AktFatJetconstituentBranch, AktInclusiveJet, LeptonJets)) return 0;
            FillTree(AktFatJetBranch, AktFatJetconstituentBranch, AktInclusiveJet, LeptonJets);

            fastjet::MassDropTagger MDT(0.67, 0.09);
            fastjet::PseudoJet AktMDJet = MDT(AktInclusiveJet);
            //             if (!FillTree(AktMassDropBranch, AktMassDropconstituentBranch, AktMDJet, LeptonJets)) return 0;
            FillTree(AktMassDropBranch, AktMassDropconstituentBranch, AktMDJet, LeptonJets);

            fastjet::Pruner AktPruner(fastjet::cambridge_algorithm, AktInclusiveJet.m() / AktInclusiveJet.pt(), 0.15);
            fastjet::PseudoJet AktPJet = AktPruner(AktInclusiveJet);
            //             if (!FillTree(AktPrunerBranch, AktPrunerconstituentBranch, AktPJet, LeptonJets)) return 0;
            FillTree(AktPrunerBranch, AktPrunerconstituentBranch, AktPJet, LeptonJets);

            break;

        }

        for (const auto & EFlowJet : EFlowJets) {

            ConstituentBranch *constituent = static_cast<ConstituentBranch *>(constituentBranch->NewEntry());
            constituent->Rap = EFlowJet.rap() - CandidateJet.rap();
            constituent->Phi = EFlowJet.delta_phi_to(CandidateJet);
            constituent->Pt = EFlowJet.pt();
            constituent->Id = EFlowJet.user_index();

        }

    }

    return 1;

}

bool hjetproperties::HAnalysis::FillTree(exroot::TreeBranch *const TreeBranch, exroot::TreeBranch * const constituentTreeBranch, const fastjet::PseudoJet &CandidateJet, const analysis::Jets &LeptonJets, const float DeltaR)
{


    Print(kDebug, "Fill Tree", DeltaR);

    if (CandidateJet != 0 && CandidateJet.m() > 0 && DeltaR > 0) {

        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(TreeBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Rap = CandidateJet.rap();
        Candidate->Phi = CandidateJet.phi_std();
        Candidate->DeltaR = DeltaR;

        Print(kDebug, "Candidate Mass", CandidateJet.m());

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

        sub_structure.NewEvent();
        if (!sub_structure.GetSubJets(CandidateJet)) return 0;

        Candidate->SubJetsDeltaR = sub_structure.GetSubJetsDeltaR();
        Candidate->Asymmetry = sub_structure.GetAsymmetry();
        Candidate->DiPolarity = sub_structure.GetDiPolarity(CandidateJet);

        Candidate->SubJet1Mass = sub_structure.GetSubJet1Mass();
        Candidate->SubJet1Pt = sub_structure.GetSubJet1Pt();
        Candidate->SubJet1DeltaR = sub_structure.GetSubJet1DeltaR();

        Candidate->SubJet2Mass = sub_structure.GetSubJet2Mass();
        Candidate->SubJet2Pt = sub_structure.GetSubJet2Pt();
        Candidate->SubJet2DeltaR = sub_structure.GetSubJet2DeltaR();

        if (!sub_structure.GetIsolation(CandidateJet, LeptonJets)) return 0;

        Candidate->IsolationRap = sub_structure.GetIsolationRap();
        Candidate->IsolationPhi = sub_structure.GetIsolationPhi();
        Candidate->IsolationPt = sub_structure.GetIsolationPt();
        Candidate->IsolationDeltaR = sub_structure.GetIsolationDeltaR();
        Candidate->IsolationAngle = sub_structure.GetIsolationAngle();

        Print(kDebug, "Isolation", Candidate->IsolationDeltaR);

//         if (!sub_structure.Getconstituents(CandidateJet, constituentTreeBranch)) return 0;

        analysis::Vectors constituentVectors = sub_structure.Getconstituents(CandidateJet);

        for (const auto & constituentVector : constituentVectors) {
          analysis::ParticleBranch *constituent = static_cast<analysis::ParticleBranch *>(constituentTreeBranch->NewEntry());
          constituent->Rap = constituentVector.Rapidity();
          constituent->Phi = constituentVector.Phi();
          constituent->Pt = constituentVector.Pt();
        }

        Candidate->ConstRap = sub_structure.GetconstituentRap();
        Candidate->ConstPhi = sub_structure.GetconstituentPhi();
        Candidate->ConstDeltaR = sub_structure.GetconstituentDeltaR();
        Candidate->ConstAngle = sub_structure.GetconstituentAngle();

        Print(kDebug, "Pull", Candidate->ConstDeltaR);

        return 1;

    }

    return 0;

}

bool hjetproperties::HAnalysis::FillTree(exroot::TreeBranch * const TreeBranch, exroot::TreeBranch * const constituentTreeBranch, const fastjet::PseudoJet &Jet, const analysis::Jets &LeptonJets)
{

    return FillTree(TreeBranch, constituentTreeBranch, Jet, LeptonJets, GetDeltaR(Jet));

}

float hjetproperties::HAnalysis::GetDeltaR(const fastjet::PseudoJet &Jet)
{

    Print(kDebug, "DeltaR");

    float DeltaR = 0;

    if (Jet.has_constituents()) {

        for (const auto & constituent : Jet.constituents()) {

            const float ConstDistance = Jet.delta_R(constituent);

            if (ConstDistance > DeltaR) DeltaR = ConstDistance;

        }

    }

    return DeltaR;

}

analysis::Jets hjetproperties::HAnalysis::Leptons(analysis::Event &event)
{

    // Lepton Stuff
    std::vector<float> LeptonRap, LeptonPhi;

    //     event.GetLeptons();

    //     Jets LeptonJets = event->Lepton->LeptonJets;
    //     Jets AntiLeptonJets = event->Lepton->AntiLeptonJets;

//     event.GetParticlesM()->GetParticles();
    analysis::Jets LeptonJets;// = event.Partons().GetLeptonJets();//TODO fix this
    analysis::Jets AntiLeptonJets;// = event.Partons().GetAntiLeptonJets();//TODO fix this

//     std::sort(LeptonJets.begin(), LeptonJets.end(), analysis::SortJetByPt());
    LeptonJets = analysis::SortedByPt(LeptonJets);
//     std::sort(AntiLeptonJets.begin(), AntiLeptonJets.end(), analysis::SortJetByPt());
    AntiLeptonJets = analysis::SortedByPt(AntiLeptonJets);

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

        LeptonRap.emplace_back(LeptonJet.rap());
        LeptonPhi.emplace_back(LeptonJet.phi_std());

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

        LeptonRap.emplace_back(AntiLeptonJet.rap());
        LeptonPhi.emplace_back(AntiLeptonJet.phi_std());

    }

    LeptonJets.insert(LeptonJets.end(), AntiLeptonJets.begin(), AntiLeptonJets.end());

    Print(kInformation, "Number of Leptons", LeptonJets.size());

    return LeptonJets;

}

