# include "HAnalysisHeavyHiggsDelphes.hh"

hheavyhiggs::HAnalysisHeavyHiggsDelphes::HAnalysisHeavyHiggsDelphes()
{

    Print(1, "Constructor");

}

std::vector<std::string> hheavyhiggs::HAnalysisHeavyHiggsDelphes::GetStudyNameVector()
{

//     std::vector<std::string> StudyNameVector = {"Signal", "Background", "Test"};
    std::vector<std::string> StudyNameVector = {"Signal"};


    return StudyNameVector;

}

std::vector<hanalysis::HFile*> hheavyhiggs::HAnalysisHeavyHiggsDelphes::GetFiles(const std::string &StudyName) const
{

    Print(1, "Fill Analysis Vector", StudyName);

    std::vector<hanalysis::HFile*> Files;

    Files.push_back(new hanalysis::HFile("BG_ttbb"));
    Files.push_back(new hanalysis::HFile("hcpbb_ttbb"));

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
//     FileVector.front()->BasePath = "~/Dropbox/Projects/HeavyHiggs/Simulation/";
    Files.front()->SetFileSuffix(".root");
    Files.front()->SetSnowMass(true);

//     FileVector.push_back(new HFile("pp-bbtt-4f", "background"));

    Print(1, "Files prepared");

    return Files;

}

void hheavyhiggs::HAnalysisHeavyHiggsDelphes::NewBranches(ExRootTreeWriter *TreeWriter)
{

    Print(1, "New File");

    HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());

    EventCounter = 0;
    DeltaEtaCounter = 0;
    BMassCounter = 0;
    TMassCounter = 0;
    JetCounter = 0;
    Jet2Counter = 0;

}

void hheavyhiggs::HAnalysisHeavyHiggsDelphes::CloseFile()
{
    Print(1, "Close File");

//     if (Cut) {

        Print(1, "EventCounter", EventCounter);
        Print(1, "JetCounter", JetCounter);
        Print(1, "DeltaEtaCounter", DeltaEtaCounter);
        Print(1, "BMassCounter", BMassCounter);
        Print(1, "Jet2Counter", Jet2Counter);
        Print(1, "TMassCounter", TMassCounter);

//     }

}

bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Analysis(hanalysis::HEvent *Event, const std::string &StudyName)
{

    Print(2, "Analysis");

    bool Success = 0;

//     Event->GetLeptonsM()->GetLeptons();

    if (StudyName == "Signal") Success = Signal(Event);
    if (StudyName == "Background") Success = Background(Event);
    if (StudyName == "Test")  Success = Test(Event);

    return Success;

}

class hheavyhiggs::HHeavyHiggsJetTag : public hanalysis::HJetTag {

    int GetBranchId(int, int);

};

int hheavyhiggs::HHeavyHiggsJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(2, "Get Mother Id");

    if (RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)) {
        BranchId = IsrId;
    } else if (std::abs(ParticleId) == BottomId && (std::abs(BranchId) != TopId && std::abs(BranchId) != CpvHiggsId)) {
        BranchId = ParticleId;
    } else if (std::abs(ParticleId) == TopId || std::abs(ParticleId) == CpvHiggsId) {
        BranchId = ParticleId;
    }

    Print(4, "Mother Id", BranchId);


    return BranchId;

}

// bool HAnalysisHeavyHiggsDelphes::JetIsBottom(const PseudoJet &Jet)
// {
//
//     return std::abs(Jet.user_index()) == BottomId;
//
// }


bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Signal(hanalysis::HEvent* Event)
{

    Print(2, "Signal");

    HHeavyHiggsJetTag * const HeavyHiggsJetTag = new HHeavyHiggsJetTag;
//     Event->GetTaggedJets(HeavyHiggsJetTag);

    HJets JetVector = Event->GetJets()->GetTaggedJets(HeavyHiggsJetTag);

    HJets BottomJetVector;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (std::abs(JetVector[JetNumber].user_index()) == BottomId) BottomJetVector.push_back(JetVector[JetNumber]);

    }

    if (BottomJetVector.size() < 2)  return 0;

    Print(0,"Signal Bottom",BottomJetVector.size());

    std::sort(BottomJetVector.begin(), BottomJetVector.end(), SortJetByEta());

    PseudoJet FrontJet = BottomJetVector.front();
    PseudoJet BackJet = BottomJetVector.back();

    FillBranch(Event,FrontJet, BackJet);

    return 1;

}


bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Background(hanalysis::HEvent* Event)
{

    Print(2, "Background");

    HHeavyHiggsJetTag * const HeavyHiggsJetTag = new HHeavyHiggsJetTag;
//     Event->GetTaggedJets(HeavyHiggsJetTag);

    HJets JetVector = Event->GetJets()->GetTaggedJets(HeavyHiggsJetTag);

    if (JetVector.size()<1) return 0;

    HJets TopJetVector, BottomJetVector;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (std::abs(JetVector[JetNumber].user_index()) == BottomId) BottomJetVector.push_back(JetVector[JetNumber]);
        if (std::abs(JetVector[JetNumber].user_index()) == TopId) TopJetVector.push_back(JetVector[JetNumber]);

    }

    bool Success = 0;

    if (TopJetVector.size() > 1) {

        Success = 1;

        for (unsigned TopJetNumber = 0; TopJetNumber < TopJetVector.size(); ++TopJetNumber) {

            for (unsigned SecondTopJetNumber = 0; SecondTopJetNumber < TopJetNumber; ++SecondTopJetNumber) {

                PseudoJet FrontJet, BackJet;

                if (TopJetVector[TopJetNumber].rap() > TopJetVector[SecondTopJetNumber].rap()) {

                    FrontJet = TopJetVector[TopJetNumber];
                    BackJet = TopJetVector[SecondTopJetNumber];

                } else {

                    FrontJet = TopJetVector[SecondTopJetNumber];
                    BackJet = TopJetVector[TopJetNumber];

                }

                FillBranch(Event,FrontJet, BackJet);

            }

        }

    }

    if (TopJetVector.size() > 0 && BottomJetVector.size() > 0) {

        Success = 1;

        for (unsigned TopJetNumber = 0; TopJetNumber < TopJetVector.size(); ++TopJetNumber) {

            for (unsigned BottomJetNumber = 0; BottomJetNumber < BottomJetVector.size(); ++BottomJetNumber) {

                PseudoJet FrontJet, BackJet;

                if (TopJetVector[TopJetNumber].rap() > TopJetVector[BottomJetNumber].rap()) {

                    FrontJet = TopJetVector[TopJetNumber];
                    BackJet = BottomJetVector[BottomJetNumber];

                } else {

                    FrontJet = BottomJetVector[BottomJetNumber];
                    BackJet = TopJetVector[TopJetNumber];

                }

                FillBranch(Event,FrontJet, BackJet);

            }

        }

    }

    return Success;

}

bool hheavyhiggs::HAnalysisHeavyHiggsDelphes::Test(hanalysis::HEvent* Event)
{

    Print(2, "Test");

//     Event->GetJets();

    HJets BottomJetVector = Event->GetJets()->GetBottomJets();

    if (BottomJetVector.size() < 2) return 0;

    PseudoJet FrontJet, BackJet;

    for (unsigned BottomJetNumber = 0; BottomJetNumber < BottomJetVector.size(); ++BottomJetNumber) {

        for (unsigned SecondBottomJetNumber = 0; SecondBottomJetNumber < BottomJetNumber; ++SecondBottomJetNumber) {

            if (BottomJetVector[BottomJetNumber].rap() > BottomJetVector[SecondBottomJetNumber].rap()) {

                FrontJet = BottomJetVector[BottomJetNumber];
                BackJet = BottomJetVector[SecondBottomJetNumber];

            } else {

                FrontJet = BottomJetVector[SecondBottomJetNumber];
                BackJet = BottomJetVector[BottomJetNumber];

            }

            FillBranch(Event,FrontJet, BackJet);

        }

    }

    return 1;

}

void hheavyhiggs::HAnalysisHeavyHiggsDelphes::FillBranch(hanalysis::HEvent* Event,PseudoJet FrontJet, PseudoJet BackJet)
{

    float FrontPt = FrontJet.pt();
    float FrontEta = FrontJet.rap();
    float FrontPhi = FrontJet.phi_std();

    float BackEta = BackJet.rap();
    float BackPt = BackJet.pt();
    float BackPhi = BackJet.phi_std();

    float InvMass = (FrontJet + BackJet).m();
    float DeltaEta = FrontEta - BackEta;
    float SumEta = FrontEta + BackEta;
    float DeltaPhi = FrontJet.delta_phi_to(BackJet);
    float SumPhi = FrontPhi + BackPhi; // FIXME constrain this
    float DeltaPt = FrontPt - BackPt;

    float Isolation = std::min(Leptons(Event,FrontJet), Leptons(Event,BackJet));

    HHeavyHiggsBranch *HeavyHiggs = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());

    HeavyHiggs->BottomEta1 = FrontEta;
    HeavyHiggs->BottomEta2 = BackEta;
    HeavyHiggs->BottomDeltaEta = DeltaEta;
    HeavyHiggs->BottomSumEta = SumEta;

    HeavyHiggs->BottomPhi1 = FrontPhi;
    HeavyHiggs->BottomPhi2 = BackPhi;
    HeavyHiggs->BottomDeltaPhi = DeltaPhi;
    HeavyHiggs->BottomSumPhi = SumPhi;

    HeavyHiggs->BottomPt1 = FrontPt;
    HeavyHiggs->BottomPt2 = BackPt;
    HeavyHiggs->BottomInvMass = InvMass;
    HeavyHiggs->BottomDeltaPt = DeltaPt;

    HeavyHiggs->BTag = Event->GetJets()->GetBottomJets().size();
    HeavyHiggs->JetNumber = Event->GetJets()->GetJets().size();
    HeavyHiggs->Isolation = Isolation;

}


float hheavyhiggs::HAnalysisHeavyHiggsDelphes::Leptons(hanalysis::HEvent* Event,PseudoJet Jet)
{

    float Isolation;

    HJets LeptonVector = Event->GetLeptons()->GetLeptonJets();

    for (unsigned LeptonNumber = 0; LeptonNumber < LeptonVector.size(); ++LeptonNumber) {

        Isolation = Jet.delta_R(LeptonVector[LeptonNumber]);

    }

    return Isolation;

}



