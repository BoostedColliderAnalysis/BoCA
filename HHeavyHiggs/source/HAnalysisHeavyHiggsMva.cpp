# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{

//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");

    SubStructure = new hdelphes::HSubStructure();
    JetTag = new hanalysis::HJetTag();
    BottomTagger = new hdelphes::HBottomTagger();
    LeptonicTopTagger = new hdelphes::HLeptonicTopTagger();
    HeavyHiggsTagger = new hdelphes::HHeavyHiggsTagger();

}

hheavyhiggs::HAnalysisMva::~HAnalysisMva()
{

    Print(HNotification, "Destructor");

    delete JetTag;
    delete SubStructure;

}

HStrings hheavyhiggs::HAnalysisMva::GetStudyNames(const HTagger Tagger)
{
    Print(HNotification, "Get Study Names", Tagger);

//     Tagger = NewTagger;

    if (Tagger == HBottomTagger) {
        return {"Bottom", "NotBottom"};
    } else if (Tagger == HTopTagger) {
        return  {"Top", "NotTop"};
    } else if (Tagger == HHiggsTagger) {
        return  {"HeavyHiggs", "NotHeavyHiggs"};
    } else if (Tagger == HEventTagger) {
        return  {"Signal", "Background"};
    } else {
        Print(HError, "unexpected TaggerName", Tagger);
        return {};
    }
}

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const std::string &StudyName) const
{
    Print(HNotification, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile *> Files;

//     hdelphes::HFile *Test3 = new hdelphes::HFile("pp-hz-bbvv", "signal");
//     Files.push_back(Test3);
//     return Files;

    if (StudyName != "Higgs" && StudyName != "Signal") {

//     hdelphes::HFile *Test4 = new hdelphes::HFile("pp-bbz-bbvv", "background");
        //     Files.push_back(Test4);

//     hdelphes::HFile *Test2 = new hdelphes::HFile("pp-bbjj");
        //     Files.push_back(Test2);


        hdelphes::HFile *Background = new hdelphes::HFile("pp-bbtt-bblvlv", "background");
        Background->SetCrosssection(3.215); // pb
        Background->SetError(0.012); // pb
        Files.push_back(Background);

    }

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

//     hdelphes::HFile *Test = new hdelphes::HFile("pp-hjj-bbjj");
//     Files.push_back(Test);
//     hdelphes::HFile *Signal = new hdelphes::HFile("pp-htt-bblvlv", "signal");
//     Signal->Crosssection = 0.01419; // pb
//     Signal->Error = 0.000067; // pb
// //     Odd->TagString="tag_2";
//     Files.push_back(Signal);

    Print(HNotification, "Files prepared");

    return Files;

}


void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    if (Tagger == HBottomTagger) {
        BottomBranch = TreeWriter->NewBranch("Bottom", HBottomBranch::Class());
    } else if (Tagger == HTopTagger) {
        TopBranch = TreeWriter->NewBranch("Top", HLeptonicTopBranch::Class());
    } else if (Tagger == HHiggsTagger) {
        HiggsBranch = TreeWriter->NewBranch("Higgs", HHiggsBranch::Class());
    } else if (Tagger == HEventTagger) {
        EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    }
//     } else {
//         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger)
{

    Print(HInformation, "Analysis", StudyName);

    if (Tagger == HBottomTagger) {
        if (GetBottomTag(Event, StudyName)) return 1;
    } else if (Tagger == HTopTagger) {
        if (GetTopTag(Event, StudyName)) return 1;
    } else if (Tagger == HHiggsTagger) {
        if (GetHeavyHiggsTag(Event, StudyName)) return 1;
    } else if (Tagger == HEventTagger) {
        if (GetSignalTag(Event, StudyName)) return 1;
    } else {
        Print(HError, "unknown Tagger", Tagger);
    }

    return 0;

}


bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HDebug, "Get Bottom Tag", StudyName);

    HState State;
    if (StudyName == "Bottom") State = HSignal;
    if (StudyName == "NotBottom") State = HBackground;

    std::vector<HBottomBranch *> Bottoms = BottomTagger->GetBottomTag(Event, State);

    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HInformation, "Get Tops", StudyName);

    HState State;
    if (StudyName == "Top") State = HSignal;
    if (StudyName == "NotTop") State = HBackground;

    std::vector<HLeptonicTopBranch *> Tops = LeptonicTopTagger->GetTopTag(Event, State, BottomTagger);

    for (const auto & Top : Tops) {
        HLeptonicTopBranch *TopTagger = static_cast<HLeptonicTopBranch *>(TopBranch->NewEntry());
        *TopTagger = *Top;
    }


    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Higgs Tag", StudyName);

    HState State;
    if (StudyName == "Higgs") State = HSignal;
    if (StudyName == "NotHiggs") State = HBackground;

    std::vector<HMvaHeavyHiggsBranch *> Higgses = HeavyHiggsTagger->GetHeavyHiggsTag(Event, State, BottomTagger, LeptonicTopTagger);

    for (const auto & Higgs : Higgses) {
      HMvaHeavyHiggsBranch *HiggsTagger = static_cast<HMvaHeavyHiggsBranch *>(HiggsBranch->NewEntry());
      *HiggsTagger = *Higgs;
    }

    return 1;

}


struct SortHeavyHiggsEvents {
    inline bool operator()(const HHeavyHiggsEvent &Event1, const HHeavyHiggsEvent &Event2) {
        return (Event1.GetBdt() > Event2.GetBdt());
    }
};

bool hheavyhiggs::HAnalysisMva::GetSignalTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Event", StudyName);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;

    HJets Jets = Event->GetJets()->GetStructuredJets();
    if (Jets.size() < 4) return 0;

    for (auto & Jet : Jets) {
        const float Bdt = BottomTagger->GetBottomBdt(Jet);
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        JetInfo->SetBTag(Bdt);
        Jet.set_user_info(JetInfo);
    }

    std::vector<HHeavyHiggsEvent> HeavyHiggsEvents;
    for (HJets::iterator Lepton1 = Leptons.begin(); Lepton1 != Leptons.end(); ++Lepton1) {
        for (HJets::iterator Lepton2 = Lepton1 + 1; Lepton2 != Leptons.end(); ++Lepton2) {
            const HJets EventLeptons {
                (*Lepton1), (*Lepton2)
            };
            for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
                for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
                    for (HJets::iterator Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                        for (HJets::iterator Jet4 = Jet3 + 1; Jet4 != Jets.end(); ++Jet4) {
                            const HJets EventJets = {(*Jet1), (*Jet2), (*Jet3), (*Jet4)};
                            std::vector<HHeavyHiggsEvents> NewHeavyHiggsEvents = GetHHeavyHiggsEvents(EventJets, EventLeptons);
                            HeavyHiggsEvents.insert(HeavyHiggsEvents.end(), NewHeavyHiggsEvents.begin(), NewHeavyHiggsEvents.end());
                        }
                    }
                }
            }
        }
    }

    std::sort(HeavyHiggsEvents.begin(), HeavyHiggsEvents.end(), SortHeavyHiggsEvents());



    HEventBranch *EventTagger = static_cast<HEventBranch *>(EventBranch->NewEntry());

    EventTagger->ScalarHt = Event->GetJets()->GetScalarHt();
    EventTagger->JetNumber = Event->GetJets()->GetJets().size();
    EventTagger->BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventTagger->LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
    EventTagger->HeavyParticleTag = HeavyHiggsEvents.front().GetBdt();
    if (StudyName == "Signal") {
        EventTagger->Signal = 1;
    } else {
        EventTagger->Signal = 0;
    }

    return 1;

}

std::vector<HHeavyHiggsEvent > hheavyhiggs::HAnalysisMva::GetHHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons)
{

    std::vector<HHeavyHiggsEvent> HeavyHiggsEvents;

    hdelphes::HSuperStructure HiggsPair01 = hdelphes::HSuperStructure(Jets[0], Jets[1]);
    HiggsPair01.Tag = HeavyHiggsTagger->GetHeavyHiggsBdt(HiggsPair01);
    hdelphes::HSuperStructure HiggsPair02 = hdelphes::HSuperStructure(Jets[0], Jets[2]);
    HiggsPair02.Tag = HeavyHiggsTagger->GetHeavyHiggsBdt(HiggsPair02);
    hdelphes::HSuperStructure HiggsPair03 = hdelphes::HSuperStructure(Jets[0], Jets[3]);
    HiggsPair03.Tag = HeavyHiggsTagger->GetHeavyHiggsBdt(HiggsPair03);
    hdelphes::HSuperStructure HiggsPair12 = hdelphes::HSuperStructure(Jets[1], Jets[2]);
    HiggsPair12.Tag = HeavyHiggsTagger->GetHeavyHiggsBdt(HiggsPair12);
    hdelphes::HSuperStructure HiggsPair13 = hdelphes::HSuperStructure(Jets[1], Jets[3]);
    HiggsPair13.Tag = HeavyHiggsTagger->GetHeavyHiggsBdt(HiggsPair13);
    hdelphes::HSuperStructure HiggsPair23 = hdelphes::HSuperStructure(Jets[2], Jets[3]);
    HiggsPair23.Tag = HeavyHiggsTagger->GetHeavyHiggsBdt(HiggsPair23);

    hdelphes::HSuperStructure Top0 = hdelphes::HSuperStructure(Jets[0], Leptons[0]);
    Top0.Tag = LeptonicTopTagger->GetTopBdt(Top0);
    hdelphes::HSuperStructure Top1 = hdelphes::HSuperStructure(Jets[1], Leptons[0]);
    Top1.Tag = LeptonicTopTagger->GetTopBdt(Top1);
    hdelphes::HSuperStructure Top2 = hdelphes::HSuperStructure(Jets[2], Leptons[0]);
    Top2.Tag = LeptonicTopTagger->GetTopBdt(Top2);
    hdelphes::HSuperStructure Top3 = hdelphes::HSuperStructure(Jets[3], Leptons[0]);
    Top3.Tag = LeptonicTopTagger->GetTopBdt(Top3);

    hdelphes::HSuperStructure AntiTop0 = hdelphes::HSuperStructure(Jets[0], Leptons[1]);
    AntiTop0.Tag = LeptonicTopTagger->GetTopBdt(AntiTop0);
    hdelphes::HSuperStructure AntiTop1 = hdelphes::HSuperStructure(Jets[1], Leptons[1]);
    AntiTop1.Tag = LeptonicTopTagger->GetTopBdt(AntiTop1);
    hdelphes::HSuperStructure AntiTop2 = hdelphes::HSuperStructure(Jets[2], Leptons[1]);
    AntiTop2.Tag = LeptonicTopTagger->GetTopBdt(AntiTop2);
    hdelphes::HSuperStructure AntiTop3 = hdelphes::HSuperStructure(Jets[3], Leptons[1]);
    AntiTop3.Tag = LeptonicTopTagger->GetTopBdt(AntiTop3);


    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair01, Top2, AntiTop3));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair01, Top3, AntiTop2));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair02, Top1, AntiTop3));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair02, Top3, AntiTop1));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair03, Top1, AntiTop2));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair03, Top2, AntiTop1));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair12, Top0, AntiTop3));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair12, Top3, AntiTop0));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair13, Top0, AntiTop2));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair13, Top2, AntiTop0));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair23, Top0, AntiTop1));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HiggsPair23, Top1, AntiTop0));

    return HeavyHiggsEvents;

}





//     if (JetPairs.size() > 0) {
//         Print(HInformation, "Pair1", JetPairs.at(0).GetPosition1(), JetPairs.at(0).GetPosition2(), JetPairs.at(0).GetInvariantMass());
//         FillCandidate(JetPairs.at(0), &Candidate->InvMass1, &Candidate->DeltaR1, &Candidate->Pull1, &Candidate->BTag1);
//         if (JetPairs.size() > 1) {
//             FillCandidate(JetPairs.at(1), &Candidate->InvMass2, &Candidate->DeltaR2, &Candidate->Pull2, &Candidate->BTag2);
//             if (JetPairs.size() > 2) {
//                 FillCandidate(JetPairs.at(2), &Candidate->InvMass3, &Candidate->DeltaR3, &Candidate->Pull3, &Candidate->BTag3);
//             }
//
//         }
//
//         if (Candidate->Pull3 != -10)return 1;
//
//     }



// void hheavyhiggs::HAnalysisMva::FillCandidate(
//     const hdelphes::HSuperStructure &JetPair,
//     float *const InvMass,
//     float *const DeltaR,
//     float *const Pull,
//     float *const BTag
// ) const
// {
//
//     Print(HInformation, "FillCandidate", JetPair.GetPosition1(), JetPair.GetPosition2());
//
//     *InvMass = JetPair.GetInvariantMass();
//     *DeltaR = JetPair.GetDeltaR();
//     if (JetPair.GetJet1().has_constituents()) *Pull = JetPair.GetPullAngle();
//
//     *BTag = JetPair.GetBTag();
//
//
//
// }






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


//     std::sort(Jets.begin(), Jets.end(), SortJetByPt());

// std::vector<hdelphes::HSuperStructure> JetPairs;
// for (unsigned JetPosition1 = 0; JetPosition1 < Jets.size(); ++JetPosition1)
// {
//
//     //         if (!(Jets[JetPosition1].has_user_info<hanalysis::HJetInfo>())) continue;
//     //         hanalysis::HJetInfo = Jets[JetPosition1].user_info<hanalysis::HJetInfo>();
//     //         if (Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement() <= 0) continue;
//
//     //         Print(HDebug, "Distance", Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement());
//     for (unsigned JetPosition2 = JetPosition1 + 1; JetPosition2 < Jets.size() ; ++JetPosition2) {
//
//         //             if (!(Jets[JetPosition1].has_user_info<hanalysis::HJetInfo>())) continue;
//         //             if (Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetJetDisplacement() <= 0) continue;
//
//         hdelphes::HSuperStructure JetPair(Jets[JetPosition1], Jets[JetPosition2]);
//         JetPair.SetPosition1(JetPosition1);
//         JetPair.SetPosition2(JetPosition2);
//         JetPair.SetBTag(Jets[JetPosition1].user_info<hanalysis::HJetInfo>().GetBTag(), Jets[JetPosition2].user_info<hanalysis::HJetInfo>().GetBTag());
//         JetPairs.push_back(JetPair);
//     }
// }
//
//
// std::sort(JetPairs.begin(), JetPairs.end(), SortByInvMass());
//
// Print(HInformation, "Got pairs", JetPairs.size());
//
// for (std::vector<hdelphes::HSuperStructure>::iterator it = JetPairs.begin(); it != JetPairs.end(); ++it)
// {
//     for (std::vector<hdelphes::HSuperStructure>::iterator it2 = JetPairs.begin(); it2 != JetPairs.end();) {
//         if ((*it).IsSamePair(*it2) && it2 > it) {
//             it2 = JetPairs.erase(it2);
//         } else {
//             ++it2;
//         }
//     }
//     if (it == JetPairs.end()) break;
// }
//
//
// if (JetPairs.size() <= 1)
// {
//     Print(HInformation, "Number of Jet Pairs", JetPairs.size());
//     return 0;
// }

