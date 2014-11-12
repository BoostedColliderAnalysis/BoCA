# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

    Print(1, "Constructor");

    JetTag = new hhiggscpv::HJetTag();

    SubStructure = new hdelphes::HSubStructure();

}

hhiggscpv::HAnalysis::~HAnalysis()
{

    Print(1, "Destructor");

    delete JetTag;

    delete SubStructure;

}

std::vector<std::string> hhiggscpv::HAnalysis::GetStudyNames() const
{

    return  {"JetPair"};

}

std::vector<hanalysis::HFile *> hhiggscpv::HAnalysis::GetFiles(const std::string &StudyName) const
{
    Print(1, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile *> Files;

    hdelphes::HFile *Test3 = new hdelphes::HFile("pp-hz-bbvv", "signal");
//     Files.push_back(Test3);
//     return Files;

    hdelphes::HFile *Test4 = new hdelphes::HFile("pp-bbz-bbvv", "background");
//     Files.push_back(Test4);

    hdelphes::HFile *Background = new hdelphes::HFile("pp-bbtt-bblvlv", "background");
    Background->SetCrosssection(3.215); // pb
    Background->SetError(0.012); // pb
    Files.push_back(Background);

    hdelphes::HFile *Even = new hdelphes::HFile("pp-x0tt-bblvlv", "even");
    Even->SetCrosssection(30.02079); // pb
    Even->SetError(0.000078); // pb
//     Even->TagString="tag_2";
    Files.push_back(Even);

    hdelphes::HFile *Mix = new hdelphes::HFile("pp-x0tt-bblvlv", "mix");
    Mix->SetCrosssection(30.01172); // pb
    Mix->SetError(0.000045); // pb
//     Mix->TagString="tag_2";
    Files.push_back(Mix);

    hdelphes::HFile *Odd = new hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(30.008951); // pb
    Odd->SetError(0.000035); // pb
//     Odd->TagString="tag_2";
    Files.push_back(Odd);

    hdelphes::HFile *Test = new hdelphes::HFile("pp-hjj-bbjj");
//     Files.push_back(Test);

    hdelphes::HFile *Test2 = new hdelphes::HFile("pp-bbjj");
//     Files.push_back(Test2);

//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
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
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());

}


int hhiggscpv::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(3, "Get Branch Id", ParticleId, BranchId);

    if (
        HeavyParticles.find(std::abs(ParticleId)) != end(HeavyParticles) && HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = ParticleId;
    } else if (
        IntermediateParticles.find(std::abs(ParticleId)) != end(IntermediateParticles) &&
        IntermediateParticles.find(std::abs(BranchId)) == end(IntermediateParticles)
    ) {
        BranchId = ParticleId;
    } else if (
        RadiationParticles.find(std::abs(ParticleId)) != end(RadiationParticles)
//     &&    IntermediateParticles.find(std::abs(BranchId)) == end(IntermediateParticles) &&
//         HeavyParticles.find(std::abs(BranchId)) == end(HeavyParticles)
    ) {
        BranchId = IsrId;
    }

    Print(3, "Branch Id", BranchId);

    return BranchId;

}



struct SortByInvMass {

    inline bool operator()(const hdelphes::HSuperStructure &JetPair1,
                           const hdelphes::HSuperStructure &JetPair2) {

        return (JetPair1.GetHiggsDeltaM() < JetPair2.GetHiggsDeltaM());

    }

};

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(2, "Analysis", StudyName);
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    HJets Jets = Event->GetJets()->GetStructuredJets();

    std::vector<hdelphes::HSuperStructure> JetPairs;
    for (unsigned JetPosition1 = 0; JetPosition1 < Jets.size(); ++JetPosition1) {

//       Print(0,"1 HiggsJet",Jets[JetPosition1].user_index() );

//         if (Jets[JetPosition1].user_index() != HiggsId && Jets[JetPosition1].user_index() != CpvHiggsId) continue;
//         if (std::abs(Jets[JetPosition1].user_index()) != BottomId) continue;

        for (unsigned JetPosition2 = JetPosition1 + 1; JetPosition2 < Jets.size() ; ++JetPosition2) {

//             if (Jets.at(JetPosition2).user_index() != HiggsId && Jets[JetPosition2].user_index() != CpvHiggsId) continue;
//             if (std::abs(Jets[JetPosition2].user_index()) != BottomId) continue;
//         Print(0,"2 HiggsJet");

            hdelphes::HSuperStructure JetPair;
            JetPair.SetJet1(Jets[JetPosition1]);
            JetPair.SetJet2(Jets[JetPosition2]);
            JetPair.SetPosition1(JetPosition1);
            JetPair.SetPosition2(JetPosition2);
            JetPairs.push_back(JetPair);
        }
    }

    if (JetPairs.size() <= 1) {
        Print(2, "No Jet Pairs");
        return 0;
    }

    Print(2, "Got pairs", JetPairs.size());

    for (std::vector<hdelphes::HSuperStructure>::iterator it = JetPairs.begin(); it != JetPairs.end(); ++it) {
        for (std::vector<hdelphes::HSuperStructure>::iterator it2 = JetPairs.begin(); it2 != JetPairs.end();) {
            if ((*it).IsSamePair(*it2) && it2 > it) {
                it2 = JetPairs.erase(it2);
            } else {
                ++it2;
            }
        }
        if (it == JetPairs.end()) break;
    }


    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->ScalarHt = Event->GetJets()->GetScalarHt();
    Candidate->JetNumber = Event->GetJets()->GetJets().size();
    Candidate->BottomNumber = Event->GetJets()->GetBottomJets().size();


    if (JetPairs.size() > 0) {

        Print(2, "Pair1", JetPairs.at(0).GetPosition1(), JetPairs.at(0).GetPosition2(), JetPairs.at(0).GetInvariantMass());
        Candidate->InvMass1 = JetPairs.at(0).GetInvariantMass();
        Candidate->DeltaR1 = JetPairs.at(0).GetDeltaR();

        if (JetPairs.at(0).GetJet1().has_user_info<hanalysis::HJetInfo>())
            Candidate->Vertex11 = JetPairs.at(0).GetJet1().user_info<hanalysis::HJetInfo>().GetVertex().Vect().Mag();
        if (JetPairs.at(0).GetJet2().has_user_info<hanalysis::HJetInfo>())
            Candidate->Vertex12 = JetPairs.at(0).GetJet2().user_info<hanalysis::HJetInfo>().GetVertex().Vect().Mag();


        if (JetPairs.at(0).GetJet1().has_constituents()) Candidate->Pull11 = JetPairs.at(0).GetPullAngle1();
        if (JetPairs.at(0).GetJet2().has_constituents()) Candidate->Pull12 = JetPairs.at(0).GetPullAngle2();

        if (JetPairs.size() > 2) {

          Candidate->InvMass2 = JetPairs.at(1).GetInvariantMass();
          Candidate->DeltaR2 = JetPairs.at(1).GetDeltaR();
          if (JetPairs.at(1).GetJet1().has_constituents()) Candidate->Pull21 = JetPairs.at(1).GetPullAngle1();
          if (JetPairs.at(1).GetJet2().has_constituents()) Candidate->Pull22 = JetPairs.at(1).GetPullAngle2();


          if (JetPairs.at(1).GetJet1().has_user_info<hanalysis::HJetInfo>())
              Candidate->Vertex21 = JetPairs.at(1).GetJet1().user_info<hanalysis::HJetInfo>().GetVertex().Vect().Mag();
            if (JetPairs.at(1).GetJet2().has_user_info<hanalysis::HJetInfo>())
              Candidate->Vertex22 = JetPairs.at(1).GetJet2().user_info<hanalysis::HJetInfo>().GetVertex().Vect().Mag();

//             if (ThirdPair.GetPosition1() != EmptyPosition) {
//                 Candidate->InvMass3 = ThirdPair.GetInvariantMass();
//                 Candidate->DeltaR3 = ThirdPair.GetDeltaR();
//                 if (ThirdPair.GetJet1().has_constituents()) Candidate->Pull31 = ThirdPair.GetPullAngle1();
//                 if (ThirdPair.GetJet2().has_constituents()) Candidate->Pull32 = ThirdPair.GetPullAngle2();

//                 if (FourthPair.GetPosition1() != EmptyPosition) {
//                     Candidate->InvMass4 = FourthPair.GetInvariantMass();
//                     if (FourthPair.GetJet1().has_constituents()) Candidate->Pull41 = FourthPair.GetPullAngle1();
//                     if (FourthPair.GetJet2().has_constituents()) Candidate->Pull42 = FourthPair.GetPullAngle2();
//
//                 }
//

            return 1;
//             }

        }



//         HVectors ConstituentVectors = FirstPair.GetConstituents();
//         for (const auto & ConstituentVector : ConstituentVectors) {
//
//
//           if (std::abs(ConstituentVector.Eta()) > LargeNumber) {
//             Print(0, "ERROR");
//             continue;
//           }
//
//             HParticleBranch *Constituent = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
//             Constituent->Eta = ConstituentVector.Eta();
//             Constituent->Phi = ConstituentVector.Phi();
//             Constituent->Pt = ConstituentVector.Pt();
//
//         }

    }

    return 0;

}
