# include "HAnalysisHiggsCpv.hh"

hhiggscpv::HAnalysis::HAnalysis()
{

//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");

    JetTag = new hanalysis::HJetTag();

}

hhiggscpv::HAnalysis::~HAnalysis()
{

    Print(HNotification, "Destructor");

    delete JetTag;

    delete BottomTagger;
    delete LeptonicTopTagger;
    delete HiggsTagger;

    delete BottomReader;
    delete LeptonicTopTagger;
    delete HiggsReader;

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

std::vector<hanalysis::HFile *> hhiggscpv::HAnalysis::GetFiles(const std::string &StudyName)
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



        BottomTagger = new hdelphes::HBottomTagger();
        BottomTagger->SetAnalysisName(GetProjectName());
        BottomTagger->SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
        BottomTagger->SetSignalTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
        BottomTagger->SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});

    if (StudyName != "Bottom" && StudyName != "NotBottom") {

        BottomReader = new hmva::HReader(BottomTagger);

        LeptonicTopTagger = new hdelphes::HLeptonicTopTagger(BottomTagger);
        LeptonicTopTagger->SetAnalysisName(GetProjectName());
        LeptonicTopTagger->SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
        LeptonicTopTagger->SetSignalTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
        LeptonicTopTagger->SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});



        HiggsTagger = new hdelphes::HMvaHiggsTagger(BottomTagger);
        HiggsTagger->SetAnalysisName(GetProjectName());
        HiggsTagger->SetTestTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
        HiggsTagger->SetSignalTreeNames( {"pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});
        HiggsTagger->SetBackgroundTreeNames( {"pp-bbtt-bblvlv-background", "pp-x0tt-bblvlv-even", "pp-x0tt-bblvlv-mix", "pp-x0tt-bblvlv-odd"});

        if (StudyName != "Top" && StudyName != "NotTop" && StudyName != "Higgs" && StudyName != "NotHiggs") {
        HiggsReader = new hmva::HReader(HiggsTagger);
        TopReader = new hmva::HReader(LeptonicTopTagger);
        }

    }

    return Files;

}


void hhiggscpv::HAnalysis::NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    if (Tagger == HBottomTagger) {
        BottomBranch = TreeWriter->NewBranch("Bottom", HBottomBranch::Class());
    } else if (Tagger == HTopTagger) {
        TopBranch = TreeWriter->NewBranch("Top", HLeptonicTopBranch::Class());
    } else if (Tagger == HHiggsTagger) {
        HiggsBranch = TreeWriter->NewBranch("Higgs", HHiggsBranch::Class());
        ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
    } else if (Tagger == HEventTagger) {
        EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    }
//     } else {
//         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
}

bool hhiggscpv::HAnalysis::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger)
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

    Print(HDebug, "Get Bottom Tag", StudyName);

    HState State;
    if (StudyName == "Bottom") State = HSignal;
    if (StudyName == "NotBottom") State = HBackground;

    std::vector<HBottomBranch *> Bottoms = BottomTagger->GetBranches(Event, State);

    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }

    return 1;

}


bool hhiggscpv::HAnalysis::GetTopTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{

    Print(HInformation, "Get Tops", StudyName);

    HState State;
    if (StudyName == "Top") State = HSignal;
    if (StudyName == "NotTop") State = HBackground;

    std::vector<HLeptonicTopBranch *> Tops = LeptonicTopTagger->GetBranches(Event, State);


    for (const auto & Top : Tops) {
        HLeptonicTopBranch *TopTagger = static_cast<HLeptonicTopBranch *>(TopBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hhiggscpv::HAnalysis::GetHiggsTag(hanalysis::HEvent *const Event, const std::string &StudyName)
{
    Print(HInformation, "Get Higgs Tag", StudyName);

    HState State;
    if (StudyName == "Higgs") State = HSignal;
    if (StudyName == "NotHiggs") State = HBackground;

    std::vector<HHiggsBranch *> Higgses = HiggsTagger->GetBranches(Event, State);

    for (const auto & Higgs : Higgses) {
        HHiggsBranch *HiggsTagger = static_cast<HHiggsBranch *>(HiggsBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    std::vector<HParticleBranch *> Constitents = HiggsTagger->GetConstituentBranches();

    for (const auto & Constituent : Constitents) {
        HParticleBranch *HiggsTagger = static_cast<HParticleBranch *>(ConstituentBranch->NewEntry());
        *HiggsTagger = *Constituent;
    }

    return 1;

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
    if (Leptons.size() < 2) {
        Print(HNotification, "Not enough Leptons", Leptons.size());
        return 0;
    }

    HJets Jets = Event->GetJets()->GetStructuredJets();
    if (Jets.size() < 4) {
        Print(HNotification, "Not enough Jets", Jets.size());
        return 0;

    }

    for (auto & Jet : Jets) {
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
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

    HEventBranch *EventTagger = static_cast<HEventBranch *>(EventBranch->NewEntry());

    EventTagger->ScalarHt = Event->GetJets()->GetScalarHt();
    EventTagger->JetNumber = Event->GetJets()->GetJets().size();
    EventTagger->BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventTagger->LeptonNumber = Event->GetLeptons()->GetLeptonJets().size();
    EventTagger->HeavyParticleTag = HiggsCpvs.front().GetBdt();
    EventTagger->TopDeltaRap = HiggsCpvs.front().GetTopDeltaRap();
    EventTagger->TopDeltaPhi = HiggsCpvs.front().GetTopDeltaPhi();
    EventTagger->TopDeltaR = HiggsCpvs.front().GetTopDeltaR();
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
    HiggsTagger->FillBranch(HiggsPair01);
    HiggsPair01.SetBdt(HiggsReader->GetBdt());
    hdelphes::HSuperStructure HiggsPair02 = hdelphes::HSuperStructure(Jets[0], Jets[2]);
    HiggsTagger->FillBranch(HiggsPair02);
    HiggsPair02.SetBdt(HiggsReader->GetBdt());
    hdelphes::HSuperStructure HiggsPair03 = hdelphes::HSuperStructure(Jets[0], Jets[3]);
    HiggsTagger->FillBranch(HiggsPair03);
    HiggsPair03.SetBdt(HiggsReader->GetBdt());
    hdelphes::HSuperStructure HiggsPair12 = hdelphes::HSuperStructure(Jets[1], Jets[2]);
    HiggsTagger->FillBranch(HiggsPair12);
    HiggsPair12.SetBdt(HiggsReader->GetBdt());
    hdelphes::HSuperStructure HiggsPair13 = hdelphes::HSuperStructure(Jets[1], Jets[3]);
    HiggsTagger->FillBranch(HiggsPair13);
    HiggsPair13.SetBdt(HiggsReader->GetBdt());
    hdelphes::HSuperStructure HiggsPair23 = hdelphes::HSuperStructure(Jets[2], Jets[3]);
    HiggsTagger->FillBranch(HiggsPair23);
    HiggsPair23.SetBdt(HiggsReader->GetBdt());

    hanalysis::HJetLeptonPair Top0 = hanalysis::HJetLeptonPair(Jets[0], Leptons[0]);
    LeptonicTopTagger->FillBranch(Top0);
    Top0.SetBdt(TopReader->GetBdt());
    hanalysis::HJetLeptonPair Top1 = hanalysis::HJetLeptonPair(Jets[1], Leptons[0]);
    LeptonicTopTagger->FillBranch(Top1);
    Top1.SetBdt(TopReader->GetBdt());
    hanalysis::HJetLeptonPair Top2 = hanalysis::HJetLeptonPair(Jets[2], Leptons[0]);
    LeptonicTopTagger->FillBranch(Top2);
    Top2.SetBdt(TopReader->GetBdt());
    hanalysis::HJetLeptonPair Top3 = hanalysis::HJetLeptonPair(Jets[3], Leptons[0]);
    LeptonicTopTagger->FillBranch(Top3);
    Top3.SetBdt(TopReader->GetBdt());

    hanalysis::HJetLeptonPair AntiTop0 = hanalysis::HJetLeptonPair(Jets[0], Leptons[1]);
    LeptonicTopTagger->FillBranch(AntiTop0);
    AntiTop0.SetBdt(TopReader->GetBdt());
    hanalysis::HJetLeptonPair AntiTop1 = hanalysis::HJetLeptonPair(Jets[1], Leptons[1]);
    LeptonicTopTagger->FillBranch(AntiTop1);
    AntiTop1.SetBdt(TopReader->GetBdt());
    hanalysis::HJetLeptonPair AntiTop2 = hanalysis::HJetLeptonPair(Jets[2], Leptons[1]);
    LeptonicTopTagger->FillBranch(AntiTop2);
    AntiTop2.SetBdt(TopReader->GetBdt());
    hanalysis::HJetLeptonPair AntiTop3 = hanalysis::HJetLeptonPair(Jets[3], Leptons[1]);
    LeptonicTopTagger->FillBranch(AntiTop3);
    AntiTop3.SetBdt(TopReader->GetBdt());


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
