# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");

    SubStructure = new hdelphes::HSubStructure();
    JetTag = new hanalysis::HJetTag();

}

hhiggscpv::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    delete Reader;
//     delete Mva;
    delete JetTag;
    delete SubStructure;

}

HStrings hhiggscpv::HAnalysis::GetStudyNames(const std::string &NewTaggerName)
{
    Print(HNotification, "Get Study Names", NewTaggerName);

    TaggerName = NewTaggerName;

    if (TaggerName == "BottomTagger") {
        return {"Bottom", "LightJet"};
    } else if (TaggerName == "TopTagger") {
        return  {"Top", "Light"};
    } else if (TaggerName == "HiggsTagger") {
        return  {"Higgs", "Pair"};
    } else if (TaggerName == "EventTagger") {
        return  {"Signal", "Background"};
    } else {
        Print(HError, "unexpected TaggerName", TaggerName);
        return {};
    }
}

std::vector<hanalysis::HFile *> hhiggscpv::HAnalysis::GetFiles(const std::string &StudyName) const
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
//     Files.push_back(Mix);

    hdelphes::HFile *Odd = new hdelphes::HFile("pp-x0tt-bblvlv", "odd");
    Odd->SetCrosssection(30.008951); // pb
    Odd->SetError(0.000035); // pb
//     Odd->TagString="tag_2";
//     Files.push_back(Odd);

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


void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter)
{
    Print(HNotification, "New Branches", TaggerName);

    if (TaggerName == "EventTagger") {
        EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    } else if (TaggerName == "HiggsTagger") {
        HiggsBranch = TreeWriter->NewBranch("Higgs", HHiggsBranch::Class());
    } else if (TaggerName == "BottomTagger") {
        TopBranch = TreeWriter->NewBranch("Top", HHiggsBranch::Class());
    } else if (TaggerName == "BottomTagger") {
        BottomBranch = TreeWriter->NewBranch("Bottom", HBottomBranch::Class());
//     } else {
//         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
    }
}

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HInformation, "Analysis", StudyName);

    if (TaggerName == "BottomTagger") {
        if (GetBottomTag(Event, StudyName)) return 1;
    } else if (TaggerName == "TopTagger") {
        if (GetTopTag(Event, StudyName)) return 1;
    } else if (TaggerName == "HiggsTagger") {
        if (GetHiggsTag(Event, StudyName)) return 1;
    } else if (TaggerName == "EventTagger") {
        if (GetSignalTag(Event, StudyName)) return 1;
    } else {
        Print(HError, "unknown Tagger", TaggerName);
    }

    return 0;

}


bool hhiggscpv::HAnalysis::GetBottomTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HInformation, "Analysis", StudyName);

    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Number Jets", Jets.size());

    if (StudyName == "Bottom") {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", (*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId());
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != BottomId
//                 || (*Jet).user_info<hanalysis::HJetInfo>().GetMaximalFraction() < .8
               ) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    } else if (StudyName == "LightJet") {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    }

    Print(HInformation, "Number Jets", Jets.size());
    if (Jets.size() < 1) return 0;

    for (const auto & Jet : Jets) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        FillBottomBranch(Jet, BTagger);
    }

    return 1;

}

void hhiggscpv::HAnalysis::FillBottomBranch(const fastjet::PseudoJet &Jet, HBottomBranch *BTagger)
{

    Print(HInformation, "Fill BTagger", Jet.m());

    if (Jet.has_user_info<hanalysis::HJetInfo>()) {
        Print(HInformation, "Has Info", Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement());
        BTagger->VertexMass = Jet.user_info<hanalysis::HJetInfo>().GetVertexMass();
        BTagger->Mass = Jet.m();
        BTagger->Pt = Jet.pt();
        BTagger->Displacement = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        BTagger->Multipliticity = Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber();
        BTagger->DeltaR = GetDeltaR(Jet);
        if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
            BTagger->Bottom = 1;
        } else {
            BTagger->Bottom = 0;
        }

    } else {
        Print(HError, "BJet without user info");
    }

}

float hhiggscpv::HAnalysis::GetDeltaR(const fastjet::PseudoJet &Jet)
{

    Print(HInformation, "GetDeltaR");

    float DeltaR;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;

}

bool hhiggscpv::HAnalysis::GetTopTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Tops", StudyName);

    JetTag->SetHeavyParticles( {TopId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    if (Jets.size() < 1) return 0;

    if (StudyName == "Top") {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", (*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId());
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId
                    //                 || (*Jet).user_info<hanalysis::HJetInfo>().GetMaximalFraction() < .8
               ) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    } else if (StudyName == "LightJet") {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    }

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 1) return 0;

    std::vector<hdelphes::HSuperStructure> JetPairs;

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        for (HJets::iterator Lepton = Leptons.begin(); Lepton != Leptons.end(); ++Lepton) {
            hdelphes::HSuperStructure JetPair((*Jet), (*Lepton));
            JetPairs.push_back(JetPair);
        }
    }

    Print(HInformation, "Number Jets", Jets.size());
    if (JetPairs.size() < 1) return 0;

    for (const auto & JetPair : JetPairs) {
        HTopBranch *TopTagger = static_cast<HTopBranch *>(TopBranch->NewEntry());
        FillTopBranch(JetPair, TopTagger);
    }


    return 1;

}

void hhiggscpv::HAnalysis::FillTopBranch(const hdelphes::HSuperStructure &Pair, HTopBranch *PairTagger)
{
    Print(HInformation, "FillPairTagger", Pair.GetBTag());
    
    PairTagger->Mass = Pair.GetInvariantMass();
    PairTagger->Pt = Pair.GetPtSum();
    PairTagger->DeltaR = Pair.GetDeltaR();
    PairTagger->DeltaEta = Pair.GetDeltaEta();
    PairTagger->DeltaPhi = Pair.GetPhiDelta();
    PairTagger->BTag = Pair.GetBTag();    
    
}

bool hhiggscpv::HAnalysis::GetHiggsTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Event", StudyName);

    JetTag->SetHeavyParticles( {CpvHiggsId, HiggsId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    if (Jets.size() < 2) return 0;

    HJets HiggsJets;
    HJets OtherJets;
    for (auto & Jet : Jets) {

        Print(HInformation, "Dominant Fraction", GetParticleName(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()));

        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        if (Jet.user_info<hanalysis::HJetInfo>().GetMaximalId() == CpvHiggsId) {
            JetInfo->SetHiggsTag(1);
        } else {
            JetInfo->SetHiggsTag(0);
        }

        HBottomBranch *BTagger = new HBottomBranch();
        FillBottomBranch(Jet, BTagger);
        const float Bdt = Mva->GetBdt(BTagger, Reader->Reader);
        JetInfo->SetBTag(Bdt);
        Print(HInformation, "Bottom Bdt", Bdt);

        Jet.set_user_info(JetInfo);

        if (JetInfo->GetHiggsTag()) {
            HiggsJets.push_back(Jet);
        } else {
            OtherJets.push_back(Jet);
        }
    }

    Print(HInformation, "Higgsness", Jets[0].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId), Jets[1].user_info<hanalysis::HJetInfo>().GetFraction(CpvHiggsId));

    std::vector<hdelphes::HSuperStructure> JetPairs;

    if (StudyName == "Higgs") {
        if (HiggsJets.size() < 2) return 0;
        Print(HInformation, "Higgs Jets", HiggsJets.size());
        for (HJets::iterator Jet1 = HiggsJets.begin(); Jet1 != HiggsJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != HiggsJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPairs.push_back(JetPair);
            }
        }
    }

    if (StudyName == "Pair") {
        if (OtherJets.size() < 2 || (OtherJets.size() < 1 && HiggsJets.size() < 1)) return 0;
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != OtherJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPairs.push_back(JetPair);
            }
        }
        for (HJets::iterator Jet1 = OtherJets.begin(); Jet1 != OtherJets.end(); ++Jet1) {
            for (HJets::iterator Jet2 = HiggsJets.begin(); Jet2 != HiggsJets.end(); ++Jet2) {
                hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
                JetPair.SetBTag((*Jet1).user_info<hanalysis::HJetInfo>().GetBTag(), (*Jet2).user_info<hanalysis::HJetInfo>().GetBTag());
                JetPairs.push_back(JetPair);
            }
        }
    }

    Print(HInformation, "Number of Jet Pairs", JetPairs.size());
    if (JetPairs.size() <= 1) return 0;

    for (const auto & Pair : JetPairs) {
        HHiggsBranch *Pairs = static_cast<HHiggsBranch *>(HiggsBranch->NewEntry());
        FillHiggsBranch(Pair, Pairs);
    }

    return 1;

}

void hhiggscpv::HAnalysis::FillHiggsBranch(const hdelphes::HSuperStructure &Pair, HHiggsBranch *PairTagger)
{
    Print(HInformation, "FillPairTagger", Pair.GetBTag());

    PairTagger->Mass = Pair.GetInvariantMass();
    PairTagger->Pt = Pair.GetPtSum();
    PairTagger->DeltaR = Pair.GetDeltaR();
    PairTagger->DeltaEta = Pair.GetDeltaEta();
    PairTagger->DeltaPhi = Pair.GetPhiDelta();
    PairTagger->BTag = Pair.GetBTag();
    PairTagger->Pull1 = Pair.GetPullAngle1();
    PairTagger->Pull2 = Pair.GetPullAngle2();
    PairTagger->Pull = Pair.GetPullAngle();


}

struct SortPairsByLikeliness {
    inline bool operator()(const hdelphes::HSuperStructure &Pair1, const hdelphes::HSuperStructure &Pair2) {
//         std::cout<< "Pair Tags " << Pair1.Tag << "  " << Pair2.Tag << std::endl;
        return (Pair1.Tag > Pair2.Tag);
    }
};

bool hhiggscpv::HAnalysis::GetSignalTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Event", StudyName);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    if (Jets.size() < 2) return 0;

    std::vector<hdelphes::HSuperStructure> JetPairs;
    for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
        for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
            hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
            JetPairs.push_back(JetPair);
        }
    }

    for (auto & JetPair : JetPairs) {

        HHiggsBranch *PairTagger = new HHiggsBranch();
        FillHiggsBranch(JetPair, PairTagger);
        const float Bdt = Mva->GetBdt(PairTagger, Reader->Reader);
        JetPair.Tag = Bdt;

        Print(HInformation, "B Bdt", Bdt);
    }


    std::sort(JetPairs.begin(), JetPairs.end(), SortPairsByLikeliness());

    for (const auto & JetPair : JetPairs) Print(HInformation, "Jet Pairs Likeliness", JetPair.Tag);

    HEventBranch *EventTagger = static_cast<HEventBranch *>(EventBranch->NewEntry());

    EventTagger->ScalarHt = Event->GetJets()->GetScalarHt();
    EventTagger->JetNumber = Event->GetJets()->GetJets().size();
    EventTagger->BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventTagger->HiggsTag = JetPairs.front().Tag;
    if (StudyName == "Signal") {
        EventTagger->Signal = 1;
    } else {
        EventTagger->Signal = 0;
    }

    return 1;

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



// void hhiggscpv::HAnalysis::FillCandidate(
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

