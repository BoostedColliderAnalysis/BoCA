# include "HAnalysisDiscriminator.hh"
# include "Predicate.hh"

// hcpvhiggs::HAnalysis::HAnalysis()
// {
//
//     Print(kNotification, "Constructor");
//
//     //jet_tag = new analysis::JetTag();
//
//     sub_structure = new analysis::SubStructure();
//
// //     DebugLevel = 3;
//
// }

hcpvhiggs::HAnalysis::~HAnalysis()
{

    Print(kNotification, "Destructor");

    //delete jet_tag;

    delete sub_structure;

}

analysis::Strings hcpvhiggs::HAnalysis::GetStudyNames() const
{

    return  {"Higgs", "Top", "Jet", "Test"};
//     return {"Higgs", "Top"};

}

std::vector<analysis::File *> hcpvhiggs::HAnalysis::GetFiles(const std::string &Name)
{
    Print(kNotification, "Set File Vector", Name);

    std::vector<analysis::File *> NewFiles;

    if (Name != "Higgs") {

      analysis::File *Background = new analysis::File("pp-bbtt-bblvlv", "background");
        Background->set_crosssection(3.215); // pb
        Background->set_crosssection_error(0.012); // pb
        NewFiles.emplace_back(Background);

//         HFile *Background2 = new HFile("pp-bbtt-bblvlv-HIGGS", "background");
//         Background2->Crosssection = 1.243; // pb
//         Background2->Error = 0.1309; // pb
//         Files.emplace_back(Background2);

    }

    analysis::File *Even = new analysis::File("pp-x0tt-bblvlv", "even");
    Even->set_crosssection(0.02079); // pb
    Even->set_crosssection_error(0.000078); // pb
//     Even->TagString="tag_2";
    NewFiles.emplace_back(Even);

    analysis::File *Mix = new analysis::File("pp-x0tt-bblvlv", "mix");
    Mix->set_crosssection(0.01172); // pb
    Mix->set_crosssection_error(0.000045); // pb
//     Mix->TagString="tag_2";
    NewFiles.emplace_back(Mix);

    analysis::File *Odd = new analysis::File("pp-x0tt-bblvlv", "odd");
    Odd->set_crosssection(0.008951); // pb
    Odd->set_crosssection_error(0.000035); // pb
//     Odd->TagString="tag_2";
    NewFiles.emplace_back(Odd);

//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.emplace_back(Signal);

    Print(kNotification, "Files prepared");

    return NewFiles;

}


void hcpvhiggs::HAnalysis::NewBranches(exroot::TreeWriter *NewTreeWriter)
{
    Print(kNotification, "New File");

    CandidateBranch = NewTreeWriter->NewBranch("Candidate", HCandidateBranch::Class());
    LeptonBranch = NewTreeWriter->NewBranch("Lepton", HLeptonBranch::Class());
    constituentBranch = NewTreeWriter->NewBranch("constituent", analysis::ParticleBranch::Class());

}


// int hcpvhiggs::JetTag::GetBranchId(const int particle_id, int BranchId)
// {
//
// //     if (HeavyParticles.find(std::abs(BranchId)) != end(HeavyParticles)) DebugLevel =4;
//
// //     Print(kError, "we are here", particle_id, BranchId);
//     Print(kDebug, "HCPVHiggs: Get Branch Id", particle_id, BranchId);
//
//
//
// //     for(auto HeavyParticle : HeavyParticles) {
// //         Print(kError,"HeavyParticle",HeavyParticle);
// //     }
//
//
//     if (
//         RadiationParticles.find(std::abs(particle_id)) != end(RadiationParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = IsrId;
//     } else if (
//         HeavyParticles.find(std::abs(particle_id)) != end(HeavyParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
//     ) {
//         BranchId = particle_id;
//     }
//
//     Print(kDebug, "HCPVHiggs: Branch Id", BranchId);
// //     DebugLevel =1;
//     return BranchId;
//
// }

int hcpvhiggs::HAnalysis::RunAnalysis(analysis::Event &event, const std::string &Study)
{

    Print(kInformation, "Analysis", Study);

    const analysis::Jets Leptons = GetLeptonJets(event);

    if (Leptons.size() < 2) {

        Print(kNotification, "Not enough Leptons", Leptons.size());
        return 0;

    }

    ++LeptoneventCounter;

    // Higgs stuff

    /*    for(auto HeavyParticle : jet_tag.HeavyParticles) {
            Print(kError,"HeavyParticle",HeavyParticle);
        }  */

    const analysis::Jets CandidateJets{};// = event.GetCandidates(jet_tag);

    if (CandidateJets.empty()) {

        Print(kError, "No Candidates", CandidateJets.size());

        return 0;

    } else Print(kInformation, "Number of Candidates", CandidateJets.size());

    int CandidateCounter = 0;
    bool HasCandidate = 0;
//     bool HiggsCounter = 0;

    for (const auto & CandidateJet : CandidateJets) {

        Print(kDebug, "Candidate", CandidateJet.user_index());

        if (Study == "Higgs") {

            if (CandidateCounter > 0) {

                Print(kInformation, "Number of Higgs", CandidateCounter);
                break;

            }

            if (CandidateJet.user_index() != CpvHiggsId && CandidateJet.user_index() != HiggsId) {

                Print(kDebug, "Not a Higgs");
                continue;

            }

            ++CandidateCounter;

            Print(kDebug, "Higgs", CandidateCounter);

        }

        if (Study == "Top") {

            if (CandidateCounter > 0) {

                Print(kInformation, "Number of Higgs", CandidateCounter);
                break;

            }

            if (std::abs(CandidateJet.user_index()) != TopId) {

                Print(kDebug, "Not a Top");
                continue;

            }

            if (CandidateCounter > 1) Print(kInformation, "Number of Tops", CandidateCounter);

            ++CandidateCounter;

            Print(kDebug, "Top", CandidateCounter);

        }

        if (Study == "Jet") {

            if (CandidateJet.user_index() == CpvHiggsId || CandidateJet.user_index() == HiggsId) {

//                 HiggsCounter = 1;
                Print(kDebug, "First Higgs is not a light Jet", CandidateJet.user_index());
                continue;

            }

            if (std::abs(CandidateJet.user_index()) == TopId) {

                Print(kDebug, "Top is not a light jet", CandidateJet.user_index());
                continue;

            }

            if (CandidateCounter > 2) Print(kNotification, "Number light jets", CandidateCounter);
            ++CandidateCounter;
            Print(kInformation, "Jet", CandidateCounter);

        }

        if (CandidateJet == 0 || CandidateJet.m() <= 0 || CandidateJet.pt() <= 0) {

            Print(kError, "Illeagal Candidate", CandidateJet.m());
            continue;

        }

//         if (CandidateJet.user_info<analysis::JetInfo>().MaximalFraction() < .9) break;

        Print(kInformation, "Tag", CandidateJet.user_info<analysis::JetInfo>().MaximalId(), CandidateJet.user_info<analysis::JetInfo>().MaximalFraction(), CandidateJet.m());

//         Jets constituents = CandidateJet.constituents();
//         sort(constituents.begin(), constituents.end(), SortJetByPt());
//         int Counter = 0;
//         for (const auto & constituent : constituents) {
//             ++Counter;
//             Print(kError, "Const", constituent.user_index(), constituent.pt());
//             if (Counter > 9) break;
//         }


        HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

        Candidate->Mass = CandidateJet.m();
        Candidate->Pt = CandidateJet.pt();
        Candidate->Rap = CandidateJet.rap();
        Candidate->Phi = CandidateJet.phi_std();

        Print(kInformation, "Candidate Mass", CandidateJet.m());

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

        sub_structure->NewEvent();
        if (!sub_structure->GetSubJets(CandidateJet)) {

            Print(kError, "No SubJets");

            return 0;

        }

        Candidate->ScalarHt = event.Hadrons().ScalarHt();

        Candidate->SubJetsDeltaR = sub_structure->GetSubJetsDeltaR();
        Candidate->Asymmetry = sub_structure->GetAsymmetry();
        Candidate->DeltaR = sub_structure->GetDeltaR();
        Candidate->DiPolarity = sub_structure->GetDiPolarity(CandidateJet);

        Candidate->SubJet1Mass = sub_structure->GetSubJet1Mass();
        Candidate->SubJet1Pt = sub_structure->GetSubJet1Pt();
        Candidate->SubJet1DeltaR = sub_structure->GetSubJet1DeltaR();

        Candidate->SubJet2Mass = sub_structure->GetSubJet2Mass();
        Candidate->SubJet2Pt = sub_structure->GetSubJet2Pt();
        Candidate->SubJet2DeltaR = sub_structure->GetSubJet2DeltaR();

        sub_structure->GetIsolation(CandidateJet, Leptons);

        Candidate->IsolationRap = sub_structure->GetIsolationRap();
        Candidate->IsolationPhi = sub_structure->GetIsolationPhi();
        Candidate->IsolationPt = sub_structure->GetIsolationPt();
        Candidate->IsolationDeltaR = sub_structure->GetIsolationDeltaR();
        Candidate->IsolationAngle = sub_structure->GetIsolationAngle();

        Print(kDebug, "Isolation", Candidate->IsolationDeltaR);

        analysis::Vectors constituentVectors = sub_structure->Getconstituents(CandidateJet);

        for (const auto & constituentVector : constituentVectors) {
          analysis::ParticleBranch *constituent = static_cast<analysis::ParticleBranch *>(constituentBranch->NewEntry());
            constituent->Rap = constituentVector.Rapidity();
            constituent->Phi = constituentVector.Phi();
            constituent->Pt = constituentVector.Pt();
        }

        Candidate->ConstRap = sub_structure->GetconstituentRap();
        Candidate->ConstPhi = sub_structure->GetconstituentPhi();
        Candidate->ConstDeltaR = sub_structure->GetconstituentDeltaR();
        Candidate->ConstAngle = sub_structure->GetconstituentAngle();

//         CandidateJet.user_info<JetInfo>().PrintAllInfos(kDetailed);
//         Print(kNotification, "Tag", CandidateJet.user_info<JetInfo>().MaximalId(), CandidateJet.user_info<JetInfo>().MaximalFraction(), CandidateJet.m());

        HasCandidate = 1;
    }

    if (HasCandidate) return 1;

    Print(kInformation, "No Candidates found");

    return 0;

}


analysis::Jets hcpvhiggs::HAnalysis::GetLeptonJets(analysis::Event &event)
{

// Lepton Stuff
    std::vector<float> LeptonRap, LeptonPhi;

//     event.GetLeptons();
//     Jets LeptonJets = event->Lepton->LeptonJets;
//     Jets AntiLeptonJets = event->Lepton->AntiLeptonJets;

//     event.GetParticlesM()->GetParticles();
    analysis::Jets LeptonJets ;//= event.Partons().GetLeptonJets();//TODO fix this
    analysis::Jets AntiLeptonJets;// = event.Partons().GetAntiLeptonJets();//TODO fix this

    LeptonJets = analysis::SortedByPt(LeptonJets);
//     std::sort(LeptonJets.begin(), LeptonJets.end(), analysis::SortJetByPt());
    AntiLeptonJets = analysis::SortedByPt(AntiLeptonJets);
//     std::sort(AntiLeptonJets.begin(), AntiLeptonJets.end(), analysis::SortJetByPt());

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


