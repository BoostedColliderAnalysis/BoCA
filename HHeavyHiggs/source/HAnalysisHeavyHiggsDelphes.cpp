# include "HAnalysisHeavyHiggsDelphes.hh"

HAnalysisHeavyHiggsDelphes::HAnalysisHeavyHiggsDelphes()
{

    Print(1, "Constructor");

}

vector<string> HAnalysisHeavyHiggsDelphes::GetStudyNameVector()
{

//     vector<string> StudyNameVector = {"Signal", "Background", "Test"};
    vector<string> StudyNameVector = {"Signal"};


    return StudyNameVector;

}

vector<HFile*> HAnalysisHeavyHiggsDelphes::GetFiles(const string StudyName) const
{

    Print(1, "Fill Analysis Vector", StudyName);

    vector<HFile*> Files;

    Files.push_back(new HFileFolder("BG_ttbb"));
    Files.push_back(new HFileFolder("hcpbb_ttbb"));

    Files.front()->BasePath = "~/Projects/HeavyHiggs/Mass/";
//     FileVector.front()->BasePath = "~/Dropbox/Projects/HeavyHiggs/Simulation/";
    Files.front()->FileSuffix = ".root";
    Files.front()->Snowmass = 1;

//     FileVector.push_back(new HFileDelphes("pp-bbtt-4f", "background"));

    Print(1, "Files prepared");

    return Files;

}

void HAnalysisHeavyHiggsDelphes::NewBranches(ExRootTreeWriter *TreeWriter)
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

void HAnalysisHeavyHiggsDelphes::CloseFile()
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

bool HAnalysisHeavyHiggsDelphes::Analysis(HEvent *Event, const string StudyName)
{

    Print(2, "Analysis");

    bool Success = 0;

    Event->GetLeptons();

    if (StudyName == "Signal") Success = Signal(Event);
    if (StudyName == "Background") Success = Background(Event);
    if (StudyName == "Test")  Success = Test(Event);

    return Success;

}

class HHeavyHiggsJetTag : public HJetTag {

    int GetBranchId(int, int);

};

int HHeavyHiggsJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(2, "Get Mother Id");

    if (InitialState.find(abs(ParticleId)) != end(InitialState) && HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)) {
        BranchId = IsrId;
    } else if (abs(ParticleId) == BottomId && (abs(BranchId) != TopId && abs(BranchId) != CpvHiggsId)) {
        BranchId = ParticleId;
    } else if (abs(ParticleId) == TopId || abs(ParticleId) == CpvHiggsId) {
        BranchId = ParticleId;
    }

    Print(4, "Mother Id", BranchId);


    return BranchId;

}

// bool HAnalysisHeavyHiggsDelphes::JetIsBottom(const PseudoJet &Jet)
// {
//
//     return abs(Jet.user_index()) == BottomId;
//
// }


bool HAnalysisHeavyHiggsDelphes::Signal(HEvent* Event)
{

    Print(2, "Signal");

    const HHeavyHiggsJetTag * const HeavyHiggsJetTag = new HHeavyHiggsJetTag;
    Event->GetTaggedJets(HeavyHiggsJetTag);

    vector<PseudoJet> JetVector = Event->Jets->Jets;

    vector<PseudoJet> BottomJetVector;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (abs(JetVector[JetNumber].user_index()) == BottomId) BottomJetVector.push_back(JetVector[JetNumber]);

    }

    if (BottomJetVector.size() < 2)  return 0;

    Print(0,"Signal Bottom",BottomJetVector.size());

    sort(BottomJetVector.begin(), BottomJetVector.end(), SortJetByEta());

    PseudoJet FrontJet = BottomJetVector.front();
    PseudoJet BackJet = BottomJetVector.back();

    FillBranch(Event,FrontJet, BackJet);

    return 1;

}


bool HAnalysisHeavyHiggsDelphes::Background(HEvent* Event)
{

    Print(2, "Background");

    const HHeavyHiggsJetTag * const HeavyHiggsJetTag = new HHeavyHiggsJetTag;
    Event->GetTaggedJets(HeavyHiggsJetTag);

    vector<PseudoJet> JetVector = Event->Jets->Jets;

    if (JetVector.size()<1) return 0;

    vector<PseudoJet> TopJetVector, BottomJetVector;

    for (unsigned JetNumber = 0; JetNumber < JetVector.size(); ++JetNumber) {

        if (abs(JetVector[JetNumber].user_index()) == BottomId) BottomJetVector.push_back(JetVector[JetNumber]);
        if (abs(JetVector[JetNumber].user_index()) == TopId) TopJetVector.push_back(JetVector[JetNumber]);

    }

    bool Success = 0;

    if (TopJetVector.size() > 1) {

        Success = 1;

        for (unsigned TopJetNumber = 0; TopJetNumber < TopJetVector.size(); ++TopJetNumber) {

            for (unsigned SecondTopJetNumber = 0; SecondTopJetNumber < TopJetNumber; ++SecondTopJetNumber) {

                PseudoJet FrontJet, BackJet;

                if (TopJetVector[TopJetNumber].eta() > TopJetVector[SecondTopJetNumber].eta()) {

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

                if (TopJetVector[TopJetNumber].eta() > TopJetVector[BottomJetNumber].eta()) {

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

bool HAnalysisHeavyHiggsDelphes::Test(HEvent* Event)
{

    Print(2, "Test");

    Event->GetJets();

    vector<PseudoJet> BottomJetVector = Event->Jets->BottomJets;

    if (BottomJetVector.size() < 2) return 0;

    PseudoJet FrontJet, BackJet;

    for (unsigned BottomJetNumber = 0; BottomJetNumber < BottomJetVector.size(); ++BottomJetNumber) {

        for (unsigned SecondBottomJetNumber = 0; SecondBottomJetNumber < BottomJetNumber; ++SecondBottomJetNumber) {

            if (BottomJetVector[BottomJetNumber].eta() > BottomJetVector[SecondBottomJetNumber].eta()) {

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
void HAnalysisHeavyHiggsDelphes::FillBranch(HEvent* Event,PseudoJet FrontJet, PseudoJet BackJet)
{

    float FrontPt = FrontJet.pt();
    float FrontEta = FrontJet.eta();
    float FrontPhi = FrontJet.phi_std();

    float BackEta = BackJet.eta();
    float BackPt = BackJet.pt();
    float BackPhi = BackJet.phi_std();

    float InvMass = (FrontJet + BackJet).m();
    float DeltaEta = FrontEta - BackEta;
    float SumEta = FrontEta + BackEta;
    float DeltaPhi = FrontJet.delta_phi_to(BackJet);
    float SumPhi = FrontPhi + BackPhi; // FIXME constrain this
    float DeltaPt = FrontPt - BackPt;

    float Isolation = min(Leptons(Event,FrontJet), Leptons(Event,BackJet));

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

    HeavyHiggs->BTag = Event->Jets->BottomJets.size();
    HeavyHiggs->JetNumber = Event->Jets->Jets.size();
    HeavyHiggs->Isolation = Isolation;

}


float HAnalysisHeavyHiggsDelphes::Leptons(HEvent* Event,PseudoJet Jet)
{

    float Isolation;

    vector<PseudoJet> LeptonVector = Event->Lepton->GetLeptonJets();

    for (unsigned LeptonNumber = 0; LeptonNumber < LeptonVector.size(); ++LeptonNumber) {

        Isolation = Jet.delta_R(LeptonVector[LeptonNumber]);

    }

    return Isolation;

}



