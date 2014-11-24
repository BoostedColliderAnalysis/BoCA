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

    delete JetTag;
    delete SubStructure;

}

HStrings hhiggscpv::HAnalysis::GetStudyNames(const HTagger Tagger)
{
    Print(HNotification, "Get Study Names", Tagger);

//     Tagger = NewTagger;

    if (Tagger == HBottomTagger) {
        return {"Bottom", "NotBottom"};
    } else if (Tagger == HTopTagger) {
        return  {"Top", "NotTop"};
    } else if (Tagger == HHiggsTagger) {
        return  {"Higgs", "NotHiggs"};
    } else if (Tagger == HEventTagger) {
        return  {"Signal", "Background"};
    } else {
        Print(HError, "unexpected TaggerName", Tagger);
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


void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter,const HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    if (Tagger == HBottomTagger) {
        BottomBranch = TreeWriter->NewBranch("Bottom", HBottomBranch::Class());
    } else if (Tagger == HTopTagger) {
        TopBranch = TreeWriter->NewBranch("Top", HTopBranch::Class());
    } else if (Tagger == HHiggsTagger) {
        HiggsBranch = TreeWriter->NewBranch("Higgs", HHiggsBranch::Class());
    } else if (Tagger == HEventTagger) {
        EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    }
//     } else {
//         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
}

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName,const HTagger Tagger)
{

    Print(HInformation, "Analysis", StudyName);

    if (Tagger == HBottomTagger) {
        if (GetBottomTag(Event, StudyName)) return 1;
    } else if (Tagger == HTopTagger) {
        if (GetTopTag(Event, StudyName)) return 1;
    } else if (Tagger == HHiggsTagger) {
        if (GetHiggsTag(Event, StudyName)) return 1;
    } else if (Tagger == HEventTagger) {
        if (GetSignalTag(Event, StudyName)) return 1;
    } else {
        Print(HError, "unknown Tagger", Tagger);
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
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != BottomId
//                 || (*Jet).user_info<hanalysis::HJetInfo>().GetMaximalFraction() < .8
               ) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    } else if (StudyName == "NotBottom") {
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

    Print(HInformation, "Fill Bottom Tagger");

    if (Jet.has_user_info<hanalysis::HJetInfo>()) {
        Print(HInformation, "Has Info", Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement());
        BTagger->VertexMass = Jet.user_info<hanalysis::HJetInfo>().GetVertexMass();
        BTagger->Mass = Jet.m();
        BTagger->Pt = Jet.pt();
        BTagger->Displacement = Jet.user_info<hanalysis::HJetInfo>().GetJetDisplacement();
        BTagger->Multipliticity = Jet.user_info<hanalysis::HJetInfo>().GetVertexNumber();
        BTagger->DeltaR = GetDeltaR(Jet);
        if (std::abs(Jet.user_info<hanalysis::HJetInfo>().GetMaximalId()) == BottomId) {
            BTagger->BottomTag = 1;
        } else {
            BTagger->BottomTag = 0;
        }
        
    } else {
        Print(HError, "BJet without user info");
    }

}

float hhiggscpv::HAnalysis::GetDeltaR(const fastjet::PseudoJet &Jet)
{

    Print(HInformation, "Get Delta R");

    float DeltaR;
    for (const auto & Constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(Constituent);
        if (TempDeltaR > DeltaR) DeltaR = TempDeltaR;
    }
    return DeltaR;

}

float hhiggscpv::HAnalysis::GetBottomBdt(const fastjet::PseudoJet &Bottom)
{

    HBottomBranch *BottomTagger = new HBottomBranch();
    FillBottomBranch(Bottom, BottomTagger);
    const float Bdt = Mva->GetBdt(BottomTagger, Reader->Reader);
    delete BottomTagger;

    return Bdt;

}

bool hhiggscpv::HAnalysis::GetTopTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    
    Print(HInformation, "Get Tops", StudyName);

    JetTag->SetHeavyParticles( {TopId});
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());
    if (Jets.size() < 1) return 0;

    if (StudyName == "Top") {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            Print(HInformation, "Truth Level", GetParticleName((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()));
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) != TopId
               ) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    } else if (StudyName == "NotTop") {
        for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end();) {
            if (std::abs((*Jet).user_info<hanalysis::HJetInfo>().GetMaximalId()) == TopId) {
                Jet = Jets.erase(Jet);
            } else {
                ++Jet;
            }
        }
    }


    HJets Leptons = Event->GetLeptons()->GetTaggedJets(JetTag);
    Print(HInformation, "Lepton Number", Leptons.size());
    if (Leptons.size() < 1) return 0;

    std::vector<hdelphes::HSuperStructure> JetPairs;

    for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
        const float Bdt = GetBottomBdt((*Jet));
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        JetInfo->SetBTag(Bdt);
        (*Jet).set_user_info(JetInfo);
        for (HJets::iterator Lepton = Leptons.begin(); Lepton != Leptons.end(); ++Lepton) {
            Print(HDebug, "Lepton Tagging",GetParticleName((*Lepton).user_index()),GetParticleName ((*Jet).user_index()));
            if ((StudyName == "Top" && (*Lepton).user_index() == (*Jet).user_index()) || (StudyName == "NotTop")) {
                
                hdelphes::HSuperStructure JetPair((*Jet), (*Lepton));
                JetPair.SetBTag((*Jet).user_info<hanalysis::HJetInfo>().GetBTag());
                if(std::abs((*Jet).user_index()) == TopId) JetPair.Tag = 1;
                JetPairs.push_back(JetPair);
            }
        }
    }

    Print(HInformation, "Number JetPairs", JetPairs.size());
    if (JetPairs.size() < 1) return 0;

    for (const auto & JetPair : JetPairs) {
        HTopBranch *TopTagger = static_cast<HTopBranch *>(TopBranch->NewEntry());
        FillTopBranch(JetPair, TopTagger);
    }


    return 1;

}

void hhiggscpv::HAnalysis::FillTopBranch(const hdelphes::HSuperStructure &Pair, HTopBranch *TopTagger)
{
    Print(HInformation, "Fill Top Tagger", Pair.GetBTag());

    TopTagger->Mass = Pair.GetInvariantMass();
    TopTagger->Pt = Pair.GetPtSum();
    TopTagger->DeltaR = Pair.GetDeltaR();
    TopTagger->DeltaEta = Pair.GetDeltaEta();
    TopTagger->DeltaPhi = Pair.GetPhiDelta();
    TopTagger->BottomTag = Pair.GetBTag();
    if (Pair.Tag == 1) {
        TopTagger->TopTag = 1;
    } else {
        TopTagger->TopTag = 0;
    }

}

float hhiggscpv::HAnalysis::GetTopBdt(const hdelphes::HSuperStructure &Top)
{

    HTopBranch *TopTagger = new HTopBranch();
    FillTopBranch(Top, TopTagger);
    const float Bdt = Mva->GetBdt(TopTagger, Reader->Reader);
    delete TopTagger;

    return Bdt;

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

        const float Bdt = GetBottomBdt(Jet);
        JetInfo->SetBTag(Bdt);
        Jet.set_user_info(JetInfo);
        Print(HInformation, "Bottom Bdt", Bdt);

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
                JetPair.Tag = 1;
                JetPairs.push_back(JetPair);
            }
        }
    }

    if (StudyName == "NotHiggs") {
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
        HHiggsBranch *HiggsTagger = static_cast<HHiggsBranch *>(HiggsBranch->NewEntry());
        FillHiggsBranch(Pair, HiggsTagger);
    }

    return 1;

}

void hhiggscpv::HAnalysis::FillHiggsBranch(const hdelphes::HSuperStructure &Pair, HHiggsBranch *HiggsTagger)
{
    Print(HInformation, "FillPairTagger", Pair.GetBTag());

    HiggsTagger->Mass = Pair.GetInvariantMass();
    HiggsTagger->Pt = Pair.GetPtSum();
    HiggsTagger->DeltaR = Pair.GetDeltaR();
    HiggsTagger->DeltaEta = Pair.GetDeltaEta();
    HiggsTagger->DeltaPhi = Pair.GetPhiDelta();
    HiggsTagger->BottomTag = Pair.GetBTag();
    HiggsTagger->Pull1 = Pair.GetPullAngle1();
    HiggsTagger->Pull2 = Pair.GetPullAngle2();
    HiggsTagger->Pull = Pair.GetPullAngle();
    if (Pair.Tag == 1) {
        HiggsTagger->HiggsTag = 1;
    } else {
        HiggsTagger->HiggsTag = 0;
    }


}

float hhiggscpv::HAnalysis::GetHiggsBdt(const hdelphes::HSuperStructure &Higgs)
{

    HHiggsBranch *HiggsTagger = new HHiggsBranch();
    FillHiggsBranch(Higgs, HiggsTagger);
    const float Bdt = Mva->GetBdt(HiggsTagger, Reader->Reader);
    delete HiggsTagger;
    return Bdt;
}


struct SortHiggsCpv {
    inline bool operator()(const HHiggsCpv &Event1, const HHiggsCpv &Event2) {
        return (Event1.GetBdt() > Event2.GetBdt());
    }
};

bool hhiggscpv::HAnalysis::GetSignalTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Event", StudyName);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;

    HJets Jets = Event->GetJets()->GetStructuredJets();
    if (Jets.size() < 4) return 0;

    for (auto & Jet : Jets) {

        const float Bdt = GetBottomBdt(Jet);
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        JetInfo->SetBTag(Bdt);
        Jet.set_user_info(JetInfo);

    }

    std::vector<HHiggsCpv> HiggsCpvs;
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
                            std::vector<HHiggsCpv> NewHiggsCpvs = GetHiggsCpvs(EventJets, EventLeptons);
                            HiggsCpvs.insert(HiggsCpvs.end(), NewHiggsCpvs.begin(), NewHiggsCpvs.end());
                        }
                    }
                }
            }
        }
    }

    std::sort(HiggsCpvs.begin(), HiggsCpvs.end(), SortHiggsCpv());


//     std::vector<hdelphes::HSuperStructure> JetJetPairs;
//     for (HJets::iterator Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
//         for (HJets::iterator Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
//             hdelphes::HSuperStructure JetPair((*Jet1), (*Jet2));
//             JetPair.SetPositions(Jet1 - Jets.begin(), Jet2 - Jets.begin());
//             JetJetPairs.push_back(JetPair);
//         }
//     }
//
//     for (auto & JetPair : JetJetPairs) {
//
//         HHiggsBranch *HiggsTagger = new HHiggsBranch();
//         FillHiggsBranch(JetPair, HiggsTagger);
//         const float Bdt = Mva->GetBdt(HiggsTagger, Reader->Reader);
//         JetPair.Tag = Bdt;
//
//         Print(HInformation, "Higgs Bdt", Bdt);
//     }
//
//     std::vector<hdelphes::HSuperStructure> JetLeptonPairs;
//     for (HJets::iterator Jet = Jets.begin(); Jet != Jets.end(); ++Jet) {
//         for (HJets::iterator Lepton = Leptons.begin(); Lepton != Leptons.end(); ++Lepton) {
//             hdelphes::HSuperStructure JetLeptonPair((*Jet), (*Lepton));
//             JetLeptonPair.SetPositions(Jet - Jets.begin(), Lepton - Leptons.begin());
//             JetLeptonPairs.push_back(JetLeptonPair);
//         }
//     }
//
//     for (auto & JetLeptonPair : JetLeptonPairs) {
//
//         HTopBranch *TopTagger = new HTopBranch();
//         FillTopBranch(JetLeptonPair, TopTagger);
//         const float Bdt = Mva->GetBdt(TopTagger, Reader->Reader);
//         JetLeptonPair.TopTag = Bdt;
//
//         Print(HInformation, "Higgs Bdt", Bdt);
//     }
//
//     std::sort(JetJetPairs.begin(), JetJetPairs.end(), SortPairsByLikeliness());
//
//     for (const auto & JetPair : JetJetPairs) Print(HInformation, "Jet Pairs Likeliness", JetPair.Tag);

    HEventBranch *EventTagger = static_cast<HEventBranch *>(EventBranch->NewEntry());

    EventTagger->ScalarHt = Event->GetJets()->GetScalarHt();
    EventTagger->JetNumber = Event->GetJets()->GetJets().size();
    EventTagger->BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventTagger->LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
    EventTagger->HeavyParticleTag = HiggsCpvs.front().GetBdt();
    if (StudyName == "Signal") {
        EventTagger->Signal = 1;
    } else {
        EventTagger->Signal = 0;
    }

    return 1;

}

std::vector< HHiggsCpv > hhiggscpv::HAnalysis::GetHiggsCpvs(const HJets &Jets, const HJets &Leptons)
{

    std::vector<HHiggsCpv> HiggsCpvs;

    hdelphes::HSuperStructure HiggsPair01 = hdelphes::HSuperStructure(Jets[0], Jets[1]);
    HiggsPair01.Tag = GetHiggsBdt(HiggsPair01);
    hdelphes::HSuperStructure HiggsPair02 = hdelphes::HSuperStructure(Jets[0], Jets[2]);
    HiggsPair02.Tag = GetHiggsBdt(HiggsPair02);
    hdelphes::HSuperStructure HiggsPair03 = hdelphes::HSuperStructure(Jets[0], Jets[3]);
    HiggsPair03.Tag = GetHiggsBdt(HiggsPair03);
    hdelphes::HSuperStructure HiggsPair12 = hdelphes::HSuperStructure(Jets[1], Jets[2]);
    HiggsPair12.Tag = GetHiggsBdt(HiggsPair12);
    hdelphes::HSuperStructure HiggsPair13 = hdelphes::HSuperStructure(Jets[1], Jets[3]);
    HiggsPair13.Tag = GetHiggsBdt(HiggsPair13);
    hdelphes::HSuperStructure HiggsPair23 = hdelphes::HSuperStructure(Jets[2], Jets[3]);
    HiggsPair23.Tag = GetHiggsBdt(HiggsPair23);

    hdelphes::HSuperStructure Top0 = hdelphes::HSuperStructure(Jets[0], Leptons[0]);
    Top0.Tag = GetTopBdt(Top0);
    hdelphes::HSuperStructure Top1 = hdelphes::HSuperStructure(Jets[1], Leptons[0]);
    Top1.Tag = GetTopBdt(Top1);
    hdelphes::HSuperStructure Top2 = hdelphes::HSuperStructure(Jets[2], Leptons[0]);
    Top2.Tag = GetTopBdt(Top2);
    hdelphes::HSuperStructure Top3 = hdelphes::HSuperStructure(Jets[3], Leptons[0]);
    Top3.Tag = GetTopBdt(Top3);

    hdelphes::HSuperStructure AntiTop0 = hdelphes::HSuperStructure(Jets[0], Leptons[1]);
    AntiTop0.Tag = GetTopBdt(AntiTop0);
    hdelphes::HSuperStructure AntiTop1 = hdelphes::HSuperStructure(Jets[1], Leptons[1]);
    AntiTop1.Tag = GetTopBdt(AntiTop1);
    hdelphes::HSuperStructure AntiTop2 = hdelphes::HSuperStructure(Jets[2], Leptons[1]);
    AntiTop2.Tag = GetTopBdt(AntiTop2);
    hdelphes::HSuperStructure AntiTop3 = hdelphes::HSuperStructure(Jets[3], Leptons[1]);
    AntiTop3.Tag = GetTopBdt(AntiTop3);


    HiggsCpvs.push_back(HHiggsCpv(HiggsPair01, Top2, AntiTop3));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair01, Top3, AntiTop2));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair02, Top1, AntiTop3));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair02, Top3, AntiTop1));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair03, Top1, AntiTop2));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair03, Top2, AntiTop1));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair12, Top0, AntiTop3));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair12, Top3, AntiTop0));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair13, Top0, AntiTop2));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair13, Top2, AntiTop0));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair23, Top0, AntiTop1));
    HiggsCpvs.push_back(HHiggsCpv(HiggsPair23, Top1, AntiTop0));

    return HiggsCpvs;

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

