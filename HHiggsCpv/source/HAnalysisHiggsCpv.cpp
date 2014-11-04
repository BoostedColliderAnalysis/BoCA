# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    JetTag = new hhiggscpv::HJetTag();

    SubStructure = new hanalysis::HSubStructure();

//     DebugLevel = 3;

}

hhiggscpv::HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

    delete JetTag;

    delete SubStructure;

}

vector<string> hhiggscpv::HAnalysis::GetStudyNames() const
{

    return  {"JetPair"};

}

vector<hanalysis::HFile *> hhiggscpv::HAnalysis::GetFiles(const string StudyName) const
{
    Print(1, "Set File Vector", StudyName);

    vector<hanalysis::HFile *> Files;

    hanalysis::hdelphes::HFile *Background = new hanalysis::hdelphes::HFile("pp-bbtt-bblvlv", "background");
    Background->Crosssection = 3.215; // pb
    Background->Error = 0.012; // pb
    Files.push_back(Background);

    hanalysis::hdelphes::HFile *Even = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->Crosssection = 0.02079; // pb
    Even->Error = 0.000078; // pb
//     Even->TagString="tag_2";
    Files.push_back(Even);

    hanalysis::hdelphes::HFile *Mix = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->Crosssection = 0.01172; // pb
    Mix->Error = 0.000045; // pb
//     Mix->TagString="tag_2";
    Files.push_back(Mix);

    hanalysis::hdelphes::HFile *Odd = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->Crosssection = 0.008951; // pb
    Odd->Error = 0.000035; // pb
//     Odd->TagString="tag_2";
    Files.push_back(Odd);

//     hanalysis::hdelphes::HFile *Signal = new hanalysis::hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.push_back(Signal);

    Print(1, "Files prepared");

    return Files;

}


void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(1, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());

}


int hhiggscpv::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(3, "HCPVHiggs: Get Branch Id", ParticleId, BranchId);

    if (
        RadiationParticles.find(abs(ParticleId)) != end(RadiationParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    } else if (
        HeavyParticles.find(abs(ParticleId)) != end(HeavyParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    }

    Print(3, "HCPVHiggs: Branch Id", BranchId);

    return BranchId;

}

class HJetPair
{

public:

    PseudoJet Jet1;
    PseudoJet Jet2;
    float InvMass() const {
        return (Jet1 + Jet2).m();
    };
    float HiggsDistance() const {
        return abs(InvMass() - 125.);
    };

};

struct SortByInvMass {

    inline bool operator()(const HJetPair *JetPair1,
                           const HJetPair *JetPair2) {

        return (JetPair1->HiggsDistance() < JetPair2->HiggsDistance());

    }

};

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const string StudyName)
{

    Print(2, "Analysis", StudyName);

    Event->GetJets();


    vector<PseudoJet> Jets = Event->GetJetsM()->Jets;

    vector<HJetPair *> JetPairs;
    for (auto Jet1 = Jets.begin(), end = Jets.end(); Jet1 != end; ++Jet1) {
        for (auto Jet2 = std::next(Jet1); Jet2 != end; ++Jet2) {

            HJetPair *JetPair = new HJetPair;
            JetPair->Jet1 = (*Jet1);
            JetPair->Jet2 = (*Jet2);
            JetPairs.push_back(JetPair);
//             std::cout << "[" << (*Jet1).m() << ", " << (*Jet2).m() << "] -> " << (*Jet1+*Jet2).m() << "\n";
        }
    }

    sort(JetPairs.begin(), JetPairs.end(), SortByInvMass());

    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->ScalarHt = Event->GetJetsM()->GetScalarHt();

    if (JetPairs.size() > 0) {
        Candidate->InvMass1 = JetPairs.at(0)->InvMass();
        if (JetPairs.size() > 1) {
            Candidate->InvMass2 = JetPairs.at(1)->InvMass();
            if (JetPairs.size() > 2) {
                Candidate->InvMass3 = JetPairs.at(2)->InvMass();
                if (JetPairs.size() > 3) {
                    Candidate->InvMass4 = JetPairs.at(3)->InvMass();
                    if (JetPairs.size() > 4) {
                        Candidate->InvMass5 = JetPairs.at(4)->InvMass();
                    }
                }
            }
        }

        return 1;
    }

    return 0;

}
