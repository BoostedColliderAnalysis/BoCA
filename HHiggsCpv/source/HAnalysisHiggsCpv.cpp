# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    JetTag = new hhiggscpv::HJetTag();

    SubStructure = new hanalysis::HSubStructure();

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
    Background->SetCrosssection(3.215); // pb
    Background->SetError(0.012); // pb
    Files.push_back(Background);

    hanalysis::hdelphes::HFile *Even = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->SetCrosssection(30.02079); // pb
    Even->SetError(0.000078); // pb
//     Even->TagString="tag_2";
    Files.push_back(Even);

    hanalysis::hdelphes::HFile *Mix = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->SetCrosssection(30.01172); // pb
    Mix->SetError(0.000045); // pb
//     Mix->TagString="tag_2";
    Files.push_back(Mix);

    hanalysis::hdelphes::HFile *Odd = new hanalysis::hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(30.008951); // pb
    Odd->SetError(0.000035); // pb
//     Odd->TagString="tag_2";
    Files.push_back(Odd);

    hanalysis::hdelphes::HFile *Test = new hanalysis::hdelphes::HFile("pp-hjj-bbjj");
    Files.push_back(Test);

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

    Print(3, "Get Branch Id", ParticleId, BranchId);

    if (
        RadiationParticles.find(abs(ParticleId)) != end(RadiationParticles) &&
        IntermediateParticles.find(abs(BranchId)) == end(IntermediateParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
      BranchId = IsrId;
    } else if (
      IntermediateParticles.find(abs(ParticleId)) != end(IntermediateParticles) &&
      HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
      BranchId = ParticleId;
    } else if (
        HeavyParticles.find(abs(ParticleId)) != end(HeavyParticles) &&
        HeavyParticles.find(abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    }

    Print(3, "Branch Id", BranchId);

    return BranchId;

}



struct SortByInvMass {

    inline bool operator()(const hanalysis::HSuperStructure &JetPair1,
                           const hanalysis::HSuperStructure &JetPair2) {

        return (JetPair1.HiggsDistance() < JetPair2.HiggsDistance());

    }

};

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const string StudyName)
{

    Print(2, "Analysis", StudyName);

//     Event->GetStructuredJets();

//     vector<PseudoJet> Jets = Event->GetJetsM()->Jets;

    vector<PseudoJet> Jets = Event->GetJets()->GetStructuredJets();



    vector<hanalysis::HSuperStructure> JetPairs;
    for (unsigned JetNumber1 = 0; JetNumber1 < Jets.size(); ++JetNumber1) {
        for (unsigned JetNumber2 = JetNumber1 + 1; JetNumber2 < Jets.size() ; ++JetNumber2) {
            hanalysis::HSuperStructure JetPair;
            JetPair.Jet1 = Jets[JetNumber1];
            JetPair.Jet2 = Jets[JetNumber2];
            JetPair.Number1 = JetNumber1;
            JetPair.Number2 = JetNumber2;
            JetPairs.push_back(JetPair);
        }
    }

    Print(2, "Got pairs", JetPairs.size());

    sort(JetPairs.begin(), JetPairs.end(), SortByInvMass());

    if (JetPairs.size() == 0) return 0;

    hanalysis::HSuperStructure FirstPair = JetPairs.front();
    JetPairs.erase(JetPairs.begin());
    Print(2, "Pair1", FirstPair.Number1, FirstPair.Number2, FirstPair.InvMass());

    hanalysis::HSuperStructure SecondPair;
    for (unsigned i = 0; i < JetPairs.size(); ++i) {

        if (FirstPair.Number1 == JetPairs.at(i).Number1 || FirstPair.Number1 == JetPairs.at(i).Number2 || FirstPair.Number2 == JetPairs.at(i).Number1 || FirstPair.Number2 == JetPairs.at(i).Number2) continue;
        SecondPair = JetPairs.at(i);
        Print(2, "Pair2", SecondPair.Number1, SecondPair.Number2, SecondPair.InvMass());
        JetPairs.erase(JetPairs.begin() + i);
        break;
    }

    hanalysis::HSuperStructure ThirdPair;
    for (unsigned i = 0; i < JetPairs.size(); ++i) {
        if (FirstPair.Number1 == JetPairs.at(i).Number1 || FirstPair.Number1 == JetPairs.at(i).Number2 || FirstPair.Number2 == JetPairs.at(i).Number1 || FirstPair.Number2 == JetPairs.at(i).Number2 || SecondPair.Number1 == JetPairs.at(i).Number1 || SecondPair.Number1 == JetPairs.at(i).Number2 || SecondPair.Number2 == JetPairs.at(i).Number1 || SecondPair.Number2 == JetPairs.at(i).Number2) continue;
        ThirdPair = JetPairs.at(i);
        Print(2, "Pair3", ThirdPair.Number1, ThirdPair.Number2, ThirdPair.InvMass());
        JetPairs.erase(JetPairs.begin() + i);
        break;
    }

    hanalysis::HSuperStructure FourthPair;
    for (unsigned i = 0; i < JetPairs.size(); ++i) {
        if (FirstPair.Number1 == JetPairs.at(i).Number1 || FirstPair.Number1 == JetPairs.at(i).Number2 || FirstPair.Number2 == JetPairs.at(i).Number1 || FirstPair.Number2 == JetPairs.at(i).Number2 || SecondPair.Number1 == JetPairs.at(i).Number1 || SecondPair.Number1 == JetPairs.at(i).Number2 || SecondPair.Number2 == JetPairs.at(i).Number1 || SecondPair.Number2 == JetPairs.at(i).Number2 || ThirdPair.Number1 == JetPairs.at(i).Number1 || ThirdPair.Number1 == JetPairs.at(i).Number2 || ThirdPair.Number2 == JetPairs.at(i).Number1 || ThirdPair.Number2 == JetPairs.at(i).Number2) continue;
        FourthPair = JetPairs.at(i);
        Print(2, "Pair4", FourthPair.Number1, FourthPair.Number2, FourthPair.InvMass());
        JetPairs.erase(JetPairs.begin() + i);
        break;
    }

    Print(2, "Got first 4 pairs");


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->ScalarHt = Event->GetJets()->GetScalarHt();

    if (FirstPair.Number1 != -1) {
        Candidate->InvMass1 = FirstPair.InvMass();
        if (FirstPair.Jet1.has_constituents())  Candidate->Pull11 = FirstPair.GetPullAngle1();
        if (FirstPair.Jet2.has_constituents())    Candidate->Pull12 = FirstPair.GetPullAngle2();

        if (SecondPair.Number1 != -1) {
            Candidate->InvMass2 = SecondPair.InvMass();
            if (SecondPair.Jet1.has_constituents()) Candidate->Pull21 = SecondPair.GetPullAngle1();
            if (SecondPair.Jet2.has_constituents()) Candidate->Pull22 = SecondPair.GetPullAngle2();

            if (ThirdPair.Number1 != -1) {
                Candidate->InvMass3 = ThirdPair.InvMass();
                if (ThirdPair.Jet1.has_constituents()) Candidate->Pull31 = ThirdPair.GetPullAngle1();
                if (ThirdPair.Jet2.has_constituents()) Candidate->Pull32 = ThirdPair.GetPullAngle2();

                if (FourthPair.Number1 != -1) {
                    Candidate->InvMass4 = FourthPair.InvMass();
                    if (FourthPair.Jet1.has_constituents()) Candidate->Pull41 = FourthPair.GetPullAngle1();
                    if (FourthPair.Jet2.has_constituents()) Candidate->Pull42 = FourthPair.GetPullAngle2();

                }

            }

        }

        return 1;
    }

    return 0;

}
