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




class HJetPair// : public hanalysis::HObject
{

public:

    float InvMass() const {
        return (Jet1 + Jet2).m();
    };

    float HiggsDistance() const {
        return abs(InvMass() - 125.);
    };

//     float GetPullAngle1() const {
//       return GetPull(Jet1,Jet2);
//     }
//
//     float GetPullAngle2() const {
//       return GetPull(Jet2,Jet1);
//     }

    float GetPullAngle1() const {
        const float Pull = GetPull(Jet1);
        const float Angle = GetAngle1();
//         cout << Pull << "   " << Angle << endl;
        return GetDeltaPhi(Pull, Angle);
        return (Pull - Angle);
    }

    float GetPullAngle2() const {
        const float Pull = GetPull(Jet2);
        const float Angle = GetAngle2();
//         cout << Pull << "   " << Angle << endl;
        return GetDeltaPhi(Pull, Angle);
        return (Pull - Angle);
    }

    PseudoJet Jet1;

    PseudoJet Jet2;

    int Number1 = -1;

    int Number2 = -1;

private:

    float GetDeltaPhi(const float Phi, const float RefPhi) const {

        float const TwoPi = 2 * TMath::Pi();

        float DeltaPhi = Phi - RefPhi;


        while (fabs(DeltaPhi) > TMath::Pi()) {

            if (DeltaPhi < -float(TMath::Pi())) {

                DeltaPhi += TwoPi;

            } else if (DeltaPhi > float(TMath::Pi())) {

                DeltaPhi -= TwoPi;

            } else {

                break;

            }

        }

        return DeltaPhi;

    }

    float GetAngle1()const {
        return (atan2(Jet2.delta_phi_to(Jet1), (Jet1.rap() - Jet2.rap())));
    };

    float GetAngle2()const {
        return (atan2(Jet1.delta_phi_to(Jet2), (Jet2.rap() - Jet1.rap())));
    };


    float GetPull(const PseudoJet &CandidateJet) const {

        float Rap = 0;
        float Phi = 0;

        for (const auto & Constituent : CandidateJet.constituents()) {

            const float PullFactor = Constituent.pt() / CandidateJet.pt() * Constituent.delta_R(CandidateJet);

            const float DeltaY = Constituent.rap() - CandidateJet.rap();
            const float DeltaPhi = CandidateJet.delta_phi_to(Constituent);

            Rap += PullFactor * DeltaY;
            Phi += PullFactor * DeltaPhi;

        }

        return atan2(Phi, Rap);

    };


    float GetPull(const PseudoJet &CandidateJet, const PseudoJet &RefJet) const {

        float Rap = 0;
        float Phi = 0;

        for (const auto & Constituent : CandidateJet.constituents()) {

            const float PullFactor = Constituent.pt() / CandidateJet.pt() * Constituent.delta_R(CandidateJet);

            const float DeltaY = Constituent.rap() - CandidateJet.rap();
            const float DeltaPhi = CandidateJet.delta_phi_to(Constituent);

            Rap += PullFactor * DeltaY;
            Phi += PullFactor * DeltaPhi;

        }

        cout << Rap << "   " << RefJet.rap() << endl;
        cout << Phi << "   " << RefJet.phi_std() << endl;
        cout << endl;

        Rap -= RefJet.rap();
        Phi -= RefJet.phi_std();

        return atan2(Phi, Rap);

    };

};

struct SortByInvMass {

    inline bool operator()(const HJetPair &JetPair1,
                           const HJetPair &JetPair2) {

        return (JetPair1.HiggsDistance() < JetPair2.HiggsDistance());

    }

};

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const string StudyName)
{

    Print(2, "Analysis", StudyName);

    Event->GetStructuredJets();

    vector<PseudoJet> Jets = Event->GetJetsM()->Jets;

    vector<HJetPair> JetPairs;
    for (unsigned JetNumber1 = 0; JetNumber1 < Jets.size(); ++JetNumber1) {
        for (unsigned JetNumber2 = JetNumber1 + 1; JetNumber2 < Jets.size() ; ++JetNumber2) {
            HJetPair JetPair;
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

    HJetPair FirstPair = JetPairs.front();
    JetPairs.erase(JetPairs.begin());
    Print(2, "Pair1", FirstPair.Number1, FirstPair.Number2, FirstPair.InvMass());

    HJetPair SecondPair;
    for (unsigned i = 0; i < JetPairs.size(); ++i) {

        if (FirstPair.Number1 == JetPairs.at(i).Number1 || FirstPair.Number1 == JetPairs.at(i).Number2 || FirstPair.Number2 == JetPairs.at(i).Number1 || FirstPair.Number2 == JetPairs.at(i).Number2) continue;
        SecondPair = JetPairs.at(i);
        Print(2, "Pair2", SecondPair.Number1, SecondPair.Number2, SecondPair.InvMass());
        JetPairs.erase(JetPairs.begin() + i);
        break;
    }

    HJetPair ThirdPair;
    for (unsigned i = 0; i < JetPairs.size(); ++i) {
        if (FirstPair.Number1 == JetPairs.at(i).Number1 || FirstPair.Number1 == JetPairs.at(i).Number2 || FirstPair.Number2 == JetPairs.at(i).Number1 || FirstPair.Number2 == JetPairs.at(i).Number2 || SecondPair.Number1 == JetPairs.at(i).Number1 || SecondPair.Number1 == JetPairs.at(i).Number2 || SecondPair.Number2 == JetPairs.at(i).Number1 || SecondPair.Number2 == JetPairs.at(i).Number2) continue;
        ThirdPair = JetPairs.at(i);
        Print(2, "Pair3", ThirdPair.Number1, ThirdPair.Number2, ThirdPair.InvMass());
        JetPairs.erase(JetPairs.begin() + i);
        break;
    }

    HJetPair FourthPair;
    for (unsigned i = 0; i < JetPairs.size(); ++i) {
        if (FirstPair.Number1 == JetPairs.at(i).Number1 || FirstPair.Number1 == JetPairs.at(i).Number2 || FirstPair.Number2 == JetPairs.at(i).Number1 || FirstPair.Number2 == JetPairs.at(i).Number2 || SecondPair.Number1 == JetPairs.at(i).Number1 || SecondPair.Number1 == JetPairs.at(i).Number2 || SecondPair.Number2 == JetPairs.at(i).Number1 || SecondPair.Number2 == JetPairs.at(i).Number2 || ThirdPair.Number1 == JetPairs.at(i).Number1 || ThirdPair.Number1 == JetPairs.at(i).Number2 || ThirdPair.Number2 == JetPairs.at(i).Number1 || ThirdPair.Number2 == JetPairs.at(i).Number2) continue;
        FourthPair = JetPairs.at(i);
        Print(2, "Pair4", FourthPair.Number1, FourthPair.Number2, FourthPair.InvMass());
        JetPairs.erase(JetPairs.begin() + i);
        break;
    }

    Print(2, "Got first 4 pairs");


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->ScalarHt = Event->GetJetsM()->GetScalarHt();

    if (FirstPair.Number1 != -1) {
        Candidate->InvMass1 = FirstPair.InvMass();
        Candidate->Pull11 = FirstPair.GetPullAngle1();
        Candidate->Pull12 = FirstPair.GetPullAngle2();

        if (SecondPair.Number1 != -1) {
            Candidate->InvMass2 = SecondPair.InvMass();
            Candidate->Pull21 = SecondPair.GetPullAngle1();
            Candidate->Pull22 = SecondPair.GetPullAngle2();

            if (ThirdPair.Number1 != -1) {

                Candidate->InvMass3 = ThirdPair.InvMass();
                Candidate->Pull31 = ThirdPair.GetPullAngle1();
                Candidate->Pull32 = ThirdPair.GetPullAngle2();

                if (FourthPair.Number1 != -1) {
                    Candidate->InvMass4 = FourthPair.InvMass();
                    Candidate->Pull41 = FourthPair.GetPullAngle1();
                    Candidate->Pull42 = FourthPair.GetPullAngle2();
                }

            }
        }

        return 1;
    }

    return 0;

}
