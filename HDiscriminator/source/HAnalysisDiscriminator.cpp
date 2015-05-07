# include "HAnalysisDiscriminator.hh"

// hcpvhiggs::HAnalysis::HAnalysis()
// {
//
//     Print(HNotification, "Constructor");
//
//     //JetTag = new hanalysis::HJetTag();
//
//     SubStructure = new hanalysis::HSubStructure();
//
// //     DebugLevel = 3;
//
// }

hcpvhiggs::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    //delete JetTag;

    delete SubStructure;

}

Strings hcpvhiggs::HAnalysis::GetStudyNames() const
{

    return  {"Higgs", "Top", "Jet", "Test"};
//     return {"Higgs", "Top"};

}

std::vector<hanalysis::RootFile *> hcpvhiggs::HAnalysis::GetFiles(const std::string &Name)
{
    Print(HNotification, "Set File Vector", Name);

    std::vector<hanalysis::RootFile *> NewFiles;

    if (Name != "Higgs") {

      hanalysis::hdelphes::HFile *Background = new hanalysis::hdelphes::HFile("pp-bbtt-bblvlv", "background");
        Background->set_crosssection(3.215); // pb
        Background->set_crosssection_error(0.012); // pb
        NewFiles.emplace_back(Background);

//         HFile *Background2 = new HFile("pp-bbtt-bblvlv-HIGGS", "background");
//         Background2->Crosssection = 1.243; // pb
//         Background2->Error = 0.1309; // pb
//         Files.emplace_back(Background2);

    }

    hanalysis::hdelphes::HFile *Even = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->set_crosssection(0.02079); // pb
    Even->set_crosssection_error(0.000078); // pb
//     Even->TagString="tag_2";
    NewFiles.emplace_back(Even);

    hanalysis::hdelphes::HFile *Mix = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->set_crosssection(0.01172); // pb
    Mix->set_crosssection_error(0.000045); // pb
//     Mix->TagString="tag_2";
    NewFiles.emplace_back(Mix);

    hanalysis::hdelphes::HFile *Odd = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->set_crosssection(0.008951); // pb
    Odd->set_crosssection_error(0.000035); // pb
//     Odd->TagString="tag_2";
    NewFiles.emplace_back(Odd);

//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.emplace_back(Signal);

    Print(HNotification, "Files prepared");

    return NewFiles;

}


void hcpvhiggs::HAnalysis::NewBranches(ExRootTreeWriter *NewTreeWriter)
{
    Print(HNotification, "New File");

    CandidateBranch = NewTreeWriter->NewBranch("Candidate", HCandidateBranch::Class());
    LeptonBranch = NewTreeWriter->NewBranch("Lepton", HLeptonBranch::Class());
    ConstituentBranch = NewTreeWriter->NewBranch("Constituent", HParticleBranch::Class());

}


// int hcpvhiggs::HJetTag::GetBranchId(const int ParticleId, int BranchId)
// {
//
// //     if (HeavyParticles.find(std::abs(BranchId)) != end(HeavyParticles)) DebugLevel =4;
//
// //     Print(HError, "we are here", ParticleId, BranchId);
//     Print(HDebug, "HCPVHiggs: Get Branch Id", ParticleId, BranchId);
//
//
//
// //     for(auto HeavyParticle : HeavyParticles) {
// //         Print(HError,"HeavyParticle",HeavyParticle);
// //     }
//
//
//     if (
//         RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = IsrId;
//     } else if (
//         HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = ParticleId;
//     }
//
//     Print(HDebug, "HCPVHiggs: Branch Id", BranchId);
// //     DebugLevel =1;
//     return BranchId;
//
// }

int hcpvhiggs::HAnalysis::Analysis(hanalysis::HEvent &Event, const std::string &Study)
{

    Print(HInformation, "Analysis", Study);

    const HJets Leptons = GetLeptonJets(Event);

    if (Leptons.size() < 2) {

        Print(HNotification, "Not enough Leptons", Leptons.size());
        return 0;

    }

    ++LeptonEventCounter;

    // Higgs stuff

    /*    for(auto HeavyParticle : JetTag.HeavyParticles) {
            Print(HError,"HeavyParticle",HeavyParticle);
        }  */

    const HJets CandidateJets = Event.GetCandidates(JetTag);

    if (CandidateJets.empty()) {

        Print(HError, "No Candidates", CandidateJets.size());

        return 0;

    } else Print(HInformation, "Number of Candidates", CandidateJets.size());

    int CandidateCounter = 0;
    bool HasCandidate = 0;
//     bool HiggsCounter = 0;

    for (const auto & CandidateJet : CandidateJets) {

        Print(HDebug, "Candidate", CandidateJet.user_index());

        if (Study == "Higgs") {

            if (CandidateCounter > 0) {

                Print(HInformation, "Number of Higgs", CandidateCounter);
                break;

            }

            if (CandidateJet.user_index() != CpvHiggsId && CandidateJet.user_index() != HiggsId) {

                Print(HDebug, "Not a Higgs");
                continue;

            }

            ++CandidateCounter;

            Print(HDebug, "Higgs", CandidateCounter);

        }

        if (Study == "Top") {

            if (CandidateCounter > 0) {

                Print(HInformation, "Number of Higgs", CandidateCounter);
                break;

            }

            if (std::abs(CandidateJet.user_index()) != TopId) {

                Print(HDebug, "Not a Top");
                continue;

            }

            if (CandidateCounter > 1) Print(HInformation, "Number of Tops", CandidateCounter);

            ++CandidateCounter;

            Print(HDebug, "Top", CandidateCounter);

        }

        if (Study == "Jet") {

            if (CandidateJet.user_index() == CpvHiggsId || CandidateJet.user_index() == HiggsId) {

//                 HiggsCounter = 1;
                Print(HDebug, "First Higgs is not a light Jet", CandidateJet.user_index());
                continue;

            }

            if (std::abs(CandidateJet.user_index()) == TopId) {

                Print(HDebug, "Top is not a light jet", CandidateJet.user_index());
                continue;

            }

            if (CandidateCounter > 2) Print(HNotification, "Number light jets", CandidateCounter);
            ++CandidateCounter;
            Print(HInformation, "Jet", CandidateCounter);

        }

        if (CandidateJet == 0 || CandidateJet.m() <= 0 || CandidateJet.pt() <= 0) {

            Print(HError, "Illeagal Candidate", CandidateJet.m());
            continue;

        }

//         if (CandidateJet.user_info<hanalysis::HJetInfo>().MaximalFraction() < .9) break;

        Print(HInformation, "Tag", CandidateJet.user_info<hanalysis::HJetInfo>().MaximalId(), CandidateJet.user_info<hanalysis::HJetInfo>().MaximalFraction(), CandidateJet.m());

//         HJets Constituents = CandidateJet.constituents();
//         sort(Constituents.begin(), Constituents.end(), SortJetByPt());
//         int Counter = 0;
//         for (const auto & Constituent : Constituents) {
//             ++Counter;
//             Print(HError, "Const", Constituent.user_index(), Constituent.pt());
//             if (Counter > 9) break;
//         }


        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Rap = CandidateJet.rap();
        Candidate->Phi = CandidateJet.phi_std();

        Print(HInformation, "Candidate Mass", CandidateJet.m());

        // Tagging

        int UserIndex = std::abs(CandidateJet.user_index());

        if (UserIndex == CpvHiggsId || UserIndex == HiggsId) {

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
        if (!SubStructure->GetSubJets(CandidateJet)) {

            Print(HError, "No SubJets");

            return 0;

        }

        Candidate->ScalarHt = Event.GetJets()->GetScalarHt();

        Candidate->SubJetsDeltaR = SubStructure->GetSubJetsDeltaR();
        Candidate->Asymmetry = SubStructure->GetAsymmetry();
        Candidate->DeltaR = SubStructure->GetDeltaR();
        Candidate->DiPolarity = SubStructure->GetDiPolarity(CandidateJet);

        Candidate->SubJet1Mass = SubStructure->GetSubJet1Mass();
        Candidate->SubJet1Pt = SubStructure->GetSubJet1Pt();
        Candidate->SubJet1DeltaR = SubStructure->GetSubJet1DeltaR();

        Candidate->SubJet2Mass = SubStructure->GetSubJet2Mass();
        Candidate->SubJet2Pt = SubStructure->GetSubJet2Pt();
        Candidate->SubJet2DeltaR = SubStructure->GetSubJet2DeltaR();

        SubStructure->GetIsolation(CandidateJet, Leptons);

        Candidate->IsolationRap = SubStructure->GetIsolationRap();
        Candidate->IsolationPhi = SubStructure->GetIsolationPhi();
        Candidate->IsolationPt = SubStructure->GetIsolationPt();
        Candidate->IsolationDeltaR = SubStructure->GetIsolationDeltaR();
        Candidate->IsolationAngle = SubStructure->GetIsolationAngle();

        Print(HDebug, "Isolation", Candidate->IsolationDeltaR);

        HVectors ConstituentVectors = SubStructure->GetConstituents(CandidateJet);

        for (const auto & ConstituentVector : ConstituentVectors) {
            HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
            Constituent->Rap = ConstituentVector.Rapidity();
            Constituent->Phi = ConstituentVector.Phi();
            Constituent->Pt = ConstituentVector.Pt();
        }

        Candidate->ConstRap = SubStructure->GetConstituentRap();
        Candidate->ConstPhi = SubStructure->GetConstituentPhi();
        Candidate->ConstDeltaR = SubStructure->GetConstituentDeltaR();
        Candidate->ConstAngle = SubStructure->GetConstituentAngle();

//         CandidateJet.user_info<HJetInfo>().PrintAllInfos(HDetailed);
//         Print(HNotification, "Tag", CandidateJet.user_info<HJetInfo>().MaximalId(), CandidateJet.user_info<HJetInfo>().MaximalFraction(), CandidateJet.m());

        HasCandidate = 1;
    }

    if (HasCandidate) return 1;

    Print(HInformation, "No Candidates found");

    return 0;

}


HJets hcpvhiggs::HAnalysis::GetLeptonJets(hanalysis::HEvent &Event)
{

// Lepton Stuff
    std::vector<float> LeptonRap, LeptonPhi;

//     Event.GetLeptons();
//     HJets LeptonJets = Event->Lepton->LeptonJets;
//     HJets AntiLeptonJets = Event->Lepton->AntiLeptonJets;

//     Event.GetParticlesM()->GetParticles();
    HJets LeptonJets = Event.GetParticles()->GetLeptonJets();
    HJets AntiLeptonJets = Event.GetParticles()->GetAntiLeptonJets();

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

    Print(HInformation, "Number of Leptons", LeptonJets.size());

    return LeptonJets;

}


