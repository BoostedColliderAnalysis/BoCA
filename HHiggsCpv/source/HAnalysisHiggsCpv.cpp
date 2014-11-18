# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

    Print(HNotification, "Constructor");

    JetTag = new hhiggscpv::HJetTag();

    SubStructure = new hdelphes::HSubStructure();

}

hhiggscpv::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    delete JetTag;

    delete SubStructure;

}

std::vector<std::string> hhiggscpv::HAnalysis::GetStudyNames(const std::string &TaggerName) const
{

    if (TaggerName == "BTagger") {
        return {"Bottom","LightJet"};
    }

    if (TaggerName == "Event") {
        return  {"JetPair"};
    }

}

std::vector<hanalysis::HFile *> hhiggscpv::HAnalysis::GetFiles(const std::string &StudyName) const
{
    Print(HNotification, "Set File Vector", StudyName);

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

    Print(HNotification, "Files prepared");

    return Files;

}


void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(HNotification, "New File");

    CandidateBranch = TreeWriter->NewBranch("Candidate", HCandidateBranch::Class());
    ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
    BTaggerBranch = TreeWriter->NewBranch("Constituent", HBTaggerBranch::Class());

}


int hhiggscpv::HJetTag::GetBranchId(const int ParticleId, int BranchId)
{

    Print(HDebug, "Get Branch Id", ParticleId, BranchId);

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

    Print(HDebug, "Branch Id", BranchId);

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

    Print(HInformation, "Analysis", StudyName);
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);

    if (StudyName == "Bottom" || StudyName == "LightJet") {

        if (GetBTag(Event, StudyName)) return 1;

    } else if (StudyName == "JetPairs") {

        if (GetEvent(Event, StudyName)) return 1;

    }

    return 0;

}

bool hhiggscpv::HAnalysis::GetEvent(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    HJets Jets = Event->GetJets()->GetStructuredJets();


    HMvaBTagger *Mva = new HMvaBTagger();

    hhiggscpv::HReader *Reader = new hhiggscpv::HReader(Mva);

    std::map<int, fastjet::PseudoJet> JetsMap;

    for(const auto& Jet : Jets) {

        int Bdt = Reader->GetBdt(Jet);
        std::pair<int,fastjet::PseudoJet> JetPair = std::make_pair(Bdt,Jet);
        JetsMap.add(JetPair);

    }

    delete Reader;

    delete Mva;




    std::sort(Jets.begin(), Jets.end(), SortJetByPt());

    std::vector<hdelphes::HSuperStructure> JetPairs;
    for (unsigned JetPosition1 = 0; JetPosition1 < Jets.size(); ++JetPosition1) {

        if (!(Jets[JetPosition1].has_user_info<hanalysis::HJetInfo>())) continue;
        //         hanalysis::HJetInfo = Jets[JetPosition1].user_info<hanalysis::HJetInfo>();
        if (Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement() <= 0) continue;

        Print(HDebug,"Distance",Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement());
        for (unsigned JetPosition2 = JetPosition1 + 1; JetPosition2 < Jets.size() ; ++JetPosition2) {

            if (!(Jets[JetPosition1].has_user_info<hanalysis::HJetInfo>())) continue;
            if (Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement() <= 0) continue;

            hdelphes::HSuperStructure JetPair(Jets[JetPosition1], Jets[JetPosition2]);
            JetPair.SetPosition1(JetPosition1);
            JetPair.SetPosition2(JetPosition2);
            JetPairs.push_back(JetPair);
        }
    }
    std::sort(JetPairs.begin(), JetPairs.end(), SortByInvMass());

    Print(HInformation, "Got pairs", JetPairs.size());

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


    if (JetPairs.size() <= 1) {
        Print(HInformation, "Number of Jet Pairs", JetPairs.size());
        return 0;
    }



    HCandidateBranch *Candidate = static_cast<HCandidateBranch *>(CandidateBranch->NewEntry());

    Candidate->ScalarHt = Event->GetJets()->GetScalarHt();
    Candidate->JetNumber = Event->GetJets()->GetJets().size();
    Candidate->BottomNumber = Event->GetJets()->GetBottomJets().size();
    Candidate->VertexNumber = Event->GetJets()->GetBottomJets().size();


    if (JetPairs.size() > 0) {
        Print(HInformation, "Pair1", JetPairs.at(0).GetPosition1(), JetPairs.at(0).GetPosition2(), JetPairs.at(0).GetInvariantMass());
        FillCandidate(JetPairs.at(0),&Candidate->InvMass1,&Candidate->DeltaR1,&Candidate->Pull11,&Candidate->Pull12,&Candidate->Vertex11,&Candidate->Vertex12,&Candidate->Mass11,&Candidate->Mass12);
        if (JetPairs.size() > 1) {
            FillCandidate(JetPairs.at(1),&Candidate->InvMass2,&Candidate->DeltaR2,&Candidate->Pull21,&Candidate->Pull22,&Candidate->Vertex21,&Candidate->Vertex22,&Candidate->Mass21,&Candidate->Mass22);
            if (JetPairs.size() > 2) {
                FillCandidate(JetPairs.at(2),&Candidate->InvMass3,&Candidate->DeltaR3,&Candidate->Pull31,&Candidate->Pull32,&Candidate->Vertex31,&Candidate->Vertex32,&Candidate->Mass31,&Candidate->Mass32);
            }

        }

        if(Candidate->Pull31!=-10&&Candidate->Pull32!=-10)return 1;


        //         HVectors ConstituentVectors = FirstPair.GetConstituents();
        //         for (const auto & ConstituentVector : ConstituentVectors) {
        //
        //
        //           if (std::abs(ConstituentVector.Eta()) > LargeNumber) {
        //             Print(HError, "ERROR");
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

}


void hhiggscpv::HAnalysis::FillCandidate(const hdelphes::HSuperStructure &JetPair, float * const InvMass, float * const DeltaR, float * const Pull1, float * const Pull2, float * const Vertex1, float * const Vertex2, float* const Mass1, float * const Mass2) const {

    Print(HInformation,"FillCandidate",JetPair.GetPosition1(),JetPair.GetPosition2());

    *InvMass = JetPair.GetInvariantMass();
    *DeltaR = JetPair.GetDeltaR();
    if (JetPair.GetJet1().has_constituents()) *Pull1 = JetPair.GetPullAngle1();
    if (JetPair.GetJet2().has_constituents()) *Pull2 = JetPair.GetPullAngle2();
    if (JetPair.GetJet1().has_user_info<hanalysis::HJetInfo>()) {
        *Vertex1 = JetPair.GetJet1().user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        *Mass1 = JetPair.GetJet1().user_info<hanalysis::HJetInfo>().GetVertexMass();
    }
    if (JetPair.GetJet2().has_user_info<hanalysis::HJetInfo>()) {
        *Vertex2 = JetPair.GetJet2().user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        *Mass2 = JetPair.GetJet2().user_info<hanalysis::HJetInfo>().GetVertexMass();
    }

}


bool hhiggscpv::HAnalysis::GetBTag(hanalysis::HEvent *const Event, const std::string &StudyName) {

    Print(HInformation, "Analysis", StudyName);

    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    if (StudyName == "Bottom") {

        for (HJets::iterator it = Jets.begin(); it != Jets.end();) {
            Print(HInformation, "Truth Level", (*it).user_info<hanalysis::HJetInfo>().GetMaximalId());
            if (std::abs((*it).user_info<hanalysis::HJetInfo>().GetMaximalId()) != BottomId || (*it).user_info<hanalysis::HJetInfo>().GetMaximalFraction() < .8) {
                it = Jets.erase(it);
            } else {
                ++it;
            }
        }

    } else if (StudyName == "LightJet") {

        for (HJets::iterator it = Jets.begin(); it != Jets.end();) {
            if (std::abs((*it).user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
                it = Jets.erase(it);
            } else {
                ++it;
            }
        }

    }


    if (Jets.size() < 1) {
        Print(HInformation, "Not Jets");
        return 0;
    }
    Print(HInformation, "Number Jets", Jets.size());

    for (const auto & Jet : Jets) {

        HBTaggerBranch *BTagger = static_cast<HBTaggerBranch *>(BTaggerBranch->NewEntry());

        BTagger->JetMass = Jet.m();

        Print(HInformation, "Mass", Jet.m());
        //         if (Jet.has_constituents()) {
        //             BTagger->Pull = SubStructure->GetDiPolarity(Jet);
        //             BTagger->DeltaR = SubStructure->GetDeltaR();
        //         }
        if (Jet.has_user_info<hanalysis::HJetInfo>()) {
            Print(HInformation, "Has Info", BTagger->Vertex = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement());
            BTagger->Vertex = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement();
            BTagger->VertexMass = Jet.user_info<hanalysis::HJetInfo>().GetVertexMass();
            BTagger->VertexNumber = Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber();
        }

        //         HVectors ConstituentVectors = FirstPair.GetConstituents();
        //         for (const auto & ConstituentVector : ConstituentVectors) {
        //
        //           if (std::abs(ConstituentVector.Eta()) > LargeNumber) {
        //             Print(HError, "ERROR");
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

//   return 1;

    return 1;

}

