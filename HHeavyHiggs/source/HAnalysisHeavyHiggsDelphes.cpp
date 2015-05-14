# include "HAnalysisHeavyHiggsDelphes.hh"

// hheavyhiggs::HAnalysisHeavyHiggsDelphes::HAnalysisHeavyHiggsDelphes()
// {
//
//     Print(kNotification, "Constructor");
//
// }

Strings hheavyhiggs::HAnalysisHeavyHiggsDelphes::GetStudyNameVector()
{

//     Strings StudyNameVector = {"Signal", "Background", "Test"};
    Strings StudyNameVector = {"Signal"};


    return StudyNameVector;

}

std::vector<hanalysis::RootFile*> hheavyhiggs::HAnalysisHeavyHiggsDelphes::GetFiles(const std::string &Study)
{

    Print(kNotification, "Fill Analysis Vector", Study);

    std::vector<hanalysis::RootFile*> NewFiles;

    NewFiles.emplace_back(new hanalysis::RootFile("BG_ttbb"));
    NewFiles.emplace_back(new hanalysis::RootFile("hcpbb_ttbb"));

    NewFiles.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
//     FileVector.front()->BasePath = "~/Dropbox/Projects/HeavyHiggs/Simulation/";
    NewFiles.front()->set_file_suffix(".root");
    NewFiles.front()->set_snow_mass(true);

//     FileVector.emplace_back(new HFile("pp-bbtt-4f", "background");

    Print(kNotification, "Files prepared");

    return NewFiles;

}

void hheavyhiggs::HAnalysisHeavyHiggsDelphes::NewBranches(ExRootTreeWriter *NewTreeWriter)
{

    Print(kNotification, "New File");

    HeavyHiggsBranch = NewTreeWriter->NewBranch("HeavyHiggs", HBranchHeavyHiggs::Class());

    eventCounter = 0;
    DeltaRapCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void hheavyhiggs::HAnalysisHeavyHiggsDelphes::CloseFile()
{
    Print(kNotification, "Close File");

//     if (Cut) {

        Print(kNotification, "eventCounter", eventCounter);
        Print(kNotification, "JetCounter", JetCounter);
        Print(kNotification, "DeltaRapCounter", DeltaRapCounter);
        Print(kNotification, "BMassCounter", BMassCounter);
        Print(kNotification, "Jet2Counter", Jet2Counter);
        Print(kNotification, "TMassCounter", TMassCounter);

//     }

}

int hheavyhiggs::HAnalysisHeavyHiggsDelphes::Analysis(hanalysis::Event &event, const std::string &Name)
{

    Print(kInformation, "Analysis");

    bool Success = 0;

//     event.GetLeptonsM()->GetLeptons();

    if (Name == "Signal") Success = Signal(event);
    if (Name == "Background") Success = Background(event);
    if (Name == "Test")  Success = Test(event);

    return Success;

}

// class hheavyhiggs::HHeavyHiggsJetTag : public hanalysis::HJetTag {
//
//     int GetBranchId(int, int);
//
// };

// int hheavyhiggs::HHeavyHiggsJetTag::GetBranchId(const int ParticleId, int BranchId)
// {
//
//     Print(kInformation, "Get Mother Id");
//
//     if (RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)) {
//         BranchId = IsrId;
//     } else if (std::abs(ParticleId) == BottomId && (std::abs(BranchId) != TopId && std::abs(BranchId) != CpvHiggsId)) {
//         BranchId = ParticleId;
//     } else if (std::abs(ParticleId) == TopId || std::abs(ParticleId) == CpvHiggsId) {
//         BranchId = ParticleId;
//     }
//
//     Print(kDetailed, "Mother Id", BranchId);
//
//
//     return BranchId;
//
// }

// bool HAnalysisHeavyHiggsDelphes::JetIsBottom(const fastjet::PseudoJet &Jet)
// {
//
//     return std::abs(Jet.user_index()) == BottomId;
//
// }


bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Signal(hanalysis::Event &event)
{

    Print(kInformation, "Signal");

    hanalysis::HJetTag  JetTag;
//     event.GetTaggedJets(HeavyHiggsJetTag);

    Jets JetVector = event.Hadrons().GetTaggedJets(JetTag);

    Jets BottomJetVector;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (std::abs(JetVector[JetNumber].user_index()) == BottomId) BottomJetVector.emplace_back(JetVector[JetNumber]);

    }

    if (BottomJetVector.size() < 2)  return 0;

    Print(kError,"Signal Bottom",BottomJetVector.size());

    std::sort(BottomJetVector.begin(), BottomJetVector.end(), SortJetByRap());

    fastjet::PseudoJet FrontJet = BottomJetVector.front();
    fastjet::PseudoJet BackJet = BottomJetVector.back();

    FillBranch(event,FrontJet, BackJet);

    return 1;

}


bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Background(hanalysis::Event &event)
{

    Print(kInformation, "Background");

    hanalysis::HJetTag  HeavyHiggsJetTag;
//     event.GetTaggedJets(HeavyHiggsJetTag);

    Jets JetVector = event.Hadrons().GetTaggedJets(HeavyHiggsJetTag);

    if (JetVector.size()<1) return 0;

    Jets TopJetVector, BottomJetVector;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (std::abs(JetVector[JetNumber].user_index()) == BottomId) BottomJetVector.emplace_back(JetVector[JetNumber]);
        if (std::abs(JetVector[JetNumber].user_index()) == TopId) TopJetVector.emplace_back(JetVector[JetNumber]);

    }

    bool Success = 0;

    if (TopJetVector.size() > 1) {

        Success = 1;

        for (unsigned TopJetNumber = 0; TopJetNumber < TopJetVector.size(); ++TopJetNumber) {

            for (unsigned SecondTopJetNumber = 0; SecondTopJetNumber < TopJetNumber; ++SecondTopJetNumber) {

                fastjet::PseudoJet FrontJet, BackJet;

                if (TopJetVector[TopJetNumber].rap() > TopJetVector[SecondTopJetNumber].rap()) {

                    FrontJet = TopJetVector[TopJetNumber];
                    BackJet = TopJetVector[SecondTopJetNumber];

                } else {

                    FrontJet = TopJetVector[SecondTopJetNumber];
                    BackJet = TopJetVector[TopJetNumber];

                }

                FillBranch(event,FrontJet, BackJet);

            }

        }

    }

    if (TopJetVector.size() > 0 && BottomJetVector.size() > 0) {

        Success = 1;

        for (unsigned TopJetNumber = 0; TopJetNumber < TopJetVector.size(); ++TopJetNumber) {

            for (unsigned BottomJetNumber = 0; BottomJetNumber < BottomJetVector.size(); ++BottomJetNumber) {

                fastjet::PseudoJet FrontJet, BackJet;

                if (TopJetVector[TopJetNumber].rap() > TopJetVector[BottomJetNumber].rap()) {

                    FrontJet = TopJetVector[TopJetNumber];
                    BackJet = BottomJetVector[BottomJetNumber];

                } else {

                    FrontJet = BottomJetVector[BottomJetNumber];
                    BackJet = TopJetVector[TopJetNumber];

                }

                FillBranch(event,FrontJet, BackJet);

            }

        }

    }

    return Success;

}

bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Test(hanalysis::Event &event)
{

    Print(kInformation, "Test");

//     event.GetJets();

    Jets BottomJetVector = event.Hadrons().GetBottomJets();

    if (BottomJetVector.size() < 2) return 0;

    fastjet::PseudoJet FrontJet, BackJet;

    for (unsigned BottomJetNumber = 0; BottomJetNumber < BottomJetVector.size(); ++BottomJetNumber) {

        for (unsigned SecondBottomJetNumber = 0; SecondBottomJetNumber < BottomJetNumber; ++SecondBottomJetNumber) {

            if (BottomJetVector[BottomJetNumber].rap() > BottomJetVector[SecondBottomJetNumber].rap()) {

                FrontJet = BottomJetVector[BottomJetNumber];
                BackJet = BottomJetVector[SecondBottomJetNumber];

            } else {

                FrontJet = BottomJetVector[SecondBottomJetNumber];
                BackJet = BottomJetVector[BottomJetNumber];

            }

            FillBranch(event,FrontJet, BackJet);

        }

    }

    return 1;

}

void hheavyhiggs::HAnalysisHeavyHiggsDelphes::FillBranch(hanalysis::Event &event,fastjet::PseudoJet FrontJet, fastjet::PseudoJet BackJet)
{

    float FrontPt = FrontJet.pt();
    float FrontRap = FrontJet.rap();
    float FrontPhi = FrontJet.phi_std();

    float BackRap = BackJet.rap();
    float BackPt = BackJet.pt();
    float BackPhi = BackJet.phi_std();

    float InvMass = (FrontJet + BackJet).m();
    float DeltaRap = FrontRap - BackRap;
    float SumRap = FrontRap + BackRap;
    float DeltaPhi = FrontJet.delta_phi_to(BackJet);
    float SumPhi = FrontPhi + BackPhi; // FIXME constrain this
    float DeltaPt = FrontPt - BackPt;

    float Isolation = std::min(Leptons(event,FrontJet), Leptons(event,BackJet));

    HBranchHeavyHiggs *HeavyHiggs = static_cast<HBranchHeavyHiggs *>(HeavyHiggsBranch->NewEntry());

    HeavyHiggs->BottomRap1 = FrontRap;
    HeavyHiggs->BottomRap2 = BackRap;
    HeavyHiggs->BottomDeltaRap = DeltaRap;
    HeavyHiggs->BottomSumRap = SumRap;

    HeavyHiggs->BottomPhi1 = FrontPhi;
    HeavyHiggs->BottomPhi2 = BackPhi;
    HeavyHiggs->BottomDeltaPhi = DeltaPhi;
    HeavyHiggs->BottomSumPhi = SumPhi;

    HeavyHiggs->BottomPt1 = FrontPt;
    HeavyHiggs->BottomPt2 = BackPt;
    HeavyHiggs->BottomInvMass = InvMass;
    HeavyHiggs->BottomDeltaPt = DeltaPt;

    HeavyHiggs->BTag = event.Hadrons().GetBottomJets().size();
    HeavyHiggs->JetNumber = event.Hadrons().GetJets().size();
    HeavyHiggs->Isolation = Isolation;

}


float hheavyhiggs::HAnalysisHeavyHiggsDelphes::Leptons(hanalysis::Event &event,fastjet::PseudoJet Jet)
{

    float Isolation;

    Jets LeptonVector = event.Leptons().GetLeptonJets();

    for (unsigned LeptonNumber = 0; LeptonNumber < LeptonVector.size(); ++LeptonNumber) {

        Isolation = Jet.delta_R(LeptonVector[LeptonNumber]);

    }

    return Isolation;

}



