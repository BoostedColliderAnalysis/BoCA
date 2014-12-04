# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{

//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");

    JetTag = new hanalysis::HJetTag();

}

hheavyhiggs::HAnalysisMva::~HAnalysisMva()
{

    Print(HNotification, "Destructor");

    delete JetTag;

}

HStrings hheavyhiggs::HAnalysisMva::GetStudyNames(const HTagger Tagger)
{
    Print(HNotification, "Get Study Names", Tagger);

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

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const std::string &StudyName)
{
    Print(HNotification, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile *> Files;

    if(StudyName != "HeavyHiggs" && StudyName != "Signal") Files.push_back(new hanalysis::HFile("BG"));
    Files.push_back(new hanalysis::HFile("h2bb"));
    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_ttbb_wwbbbb_llbbbb_Delphes.root");

    Print(HNotification, "Files prepared");

    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
    BottomTagger->SetSignalTreeNames( {"BG-run_01", "h2bb-run_01"});
    BottomTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});

    if (StudyName != "Bottom" && StudyName != "NotBottom") {

        BottomReader = new hanalysis::HReader(BottomTagger);

        LeptonicTopTagger = new hanalysis::HLeptonicTopTagger(BottomTagger);
        LeptonicTopTagger->SetAnalysisName(GetProjectName());
        LeptonicTopTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
        LeptonicTopTagger->SetSignalTreeNames( {"BG-run_01", "h2bb-run_01"});
        LeptonicTopTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});

        if (StudyName != "Top" && StudyName != "NotTop") {

            TopReader = new hanalysis::HReader(LeptonicTopTagger);

            HeavyHiggsTagger = new hanalysis::HHeavyHiggsTagger(BottomTagger, LeptonicTopTagger);
            HeavyHiggsTagger->SetAnalysisName(GetProjectName());
            HeavyHiggsTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
            HeavyHiggsTagger->SetSignalTreeNames( {"h2bb-run_01"});
            HeavyHiggsTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});

            Print(HError,"StudyName",StudyName);

            if (StudyName != "HeavyHiggs" && StudyName != "NotHeavyHiggs") {

                HeavyHiggsReader = new hanalysis::HReader(HeavyHiggsTagger);
            }
        }
    }
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
        HeavyHiggsBranch = TreeWriter->NewBranch("HeavyHiggs", HHeavyHiggsBranch::Class());
    } else if (Tagger == HEventTagger) {
        EventBranch = TreeWriter->NewBranch("Event", HEventBranch::Class());
    }
//     } else {
//         ConstituentBranch = TreeWriter->NewBranch("Constituent", HParticleBranch::Class());
}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger)
{

    Print(HInformation, "Analysis", StudyName);

    HState State;
    if (Tagger == HBottomTagger) {
        if (StudyName == "Bottom") State = HSignal;
        if (StudyName == "NotBottom") State = HBackground;
        if (GetBottomTag(Event, State)) return 1;
    } else if (Tagger == HTopTagger) {
        if (StudyName == "Top") State = HSignal;
        if (StudyName == "NotTop") State = HBackground;
        if (GetTopTag(Event, State)) return 1;
    } else if (Tagger == HHiggsTagger) {
        if (StudyName == "HeavyHiggs") State = HSignal;
        if (StudyName == "NotHeavyHiggs") State = HBackground;
        if (GetHeavyHiggsTag(Event, State)) return 1;
    } else if (Tagger == HEventTagger) {
        if (GetSignalTag(Event, StudyName)) return 1;
    } else {
        Print(HError, "unknown Tagger", Tagger);
    }

    return 0;

}


bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent *const Event, const HState State)
{

    Print(HDebug, "Get Bottom Tag", State);

    std::vector<HBottomBranch *> Bottoms = BottomTagger->GetBranches(Event, State);

    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get Tops", State);

    std::vector<HLeptonicTopBranch *> Tops = LeptonicTopTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HLeptonicTopBranch *TopTagger = static_cast<HLeptonicTopBranch *>(TopBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get HeavyHiggs Tag", State);


    std::vector<HHeavyHiggsBranch *> Higgses = HeavyHiggsTagger->GetBranches(Event, State);
    if (Higgses.size()<1) return 0;

    for (const auto & Higgs : Higgses) {
//         if (Higgs->HeavyHiggsMass < 1) return 0;
        HHeavyHiggsBranch *HiggsTagger = static_cast<HHeavyHiggsBranch *>(HeavyHiggsBranch->NewEntry());
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
        hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
        BottomTagger->FillBranch(Jet);
        JetInfo->SetBdt(BottomReader->GetBdt());
        Jet.set_user_info(JetInfo);
    }

    std::vector<HHeavyHiggsEvent> HeavyHiggsEvents;
    for (auto Lepton1 = Leptons.begin(); Lepton1 != Leptons.end(); ++Lepton1) {
        for (auto Lepton2 = Lepton1 + 1; Lepton2 != Leptons.end(); ++Lepton2) {
            const HJets EventLeptons {
                (*Lepton1), (*Lepton2)
            };
            for (auto Jet1 = Jets.begin(); Jet1 != Jets.end(); ++Jet1) {
                for (auto Jet2 = Jet1 + 1; Jet2 != Jets.end(); ++Jet2) {
                    for (auto Jet3 = Jet2 + 1; Jet3 != Jets.end(); ++Jet3) {
                        for (auto Jet4 = Jet3 + 1; Jet4 != Jets.end(); ++Jet4) {
                            const HJets EventJets = {(*Jet1), (*Jet2), (*Jet3), (*Jet4)};
                            std::vector<HHeavyHiggsEvent> NewHeavyHiggsEvents = GetHeavyHiggsEvents(EventJets, EventLeptons);
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
    EventTagger->HeavyParticleTag = HeavyHiggsEvents.front().GetBdt();
    EventTagger->DeltaRap = HeavyHiggsEvents.front().GetDeltaRap();
    EventTagger->DeltaPhi = HeavyHiggsEvents.front().GetDeltaPhi();
    EventTagger->DeltaR = HeavyHiggsEvents.front().GetDeltaR();
    if (StudyName == "Signal") {
        EventTagger->Signal = 1;
    } else {
        EventTagger->Signal = 0;
    }

    return 1;

}

std::vector<HHeavyHiggsEvent > hheavyhiggs::HAnalysisMva::GetHeavyHiggsEvents(const HJets &Jets, const HJets &Leptons)
{

    std::vector<HHeavyHiggsEvent> HeavyHiggsEvents;

//     std::vector<hanalysis::HJetLeptonPair> Tops;
//     for (const auto & Jet : Jets) {
//         hanalysis::HJetLeptonPair Top = hanalysis::HJetLeptonPair(Jet, Leptons[0]);
//         Top.SetBdt(LeptonicTopTagger->GetTopBdt(Top));
//         Tops.push_back(Top);
//     }
//
//     std::vector<hanalysis::HJetLeptonPair> AntiTops;
//     for (const auto & Jet : Jets) {
//         hanalysis::HJetLeptonPair AntiTop = hanalysis::HJetLeptonPair(Jet, Leptons[1]);
//         AntiTop.SetBdt(LeptonicTopTagger->GetTopBdt(AntiTop));
//         AntiTops.push_back(AntiTop);
//     }


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

    hanalysis::HPairPair HeavyHiggs01 = hanalysis::HPairPair(Top0, AntiTop1);
    HeavyHiggsTagger->FillBranch(HeavyHiggs01.GetTriplePair());
    HeavyHiggs01.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs02 = hanalysis::HPairPair(Top0, AntiTop2);
    HeavyHiggsTagger->FillBranch(HeavyHiggs02.GetTriplePair());
    HeavyHiggs02.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs03 = hanalysis::HPairPair(Top0, AntiTop3);
    HeavyHiggsTagger->FillBranch(HeavyHiggs03.GetTriplePair());
    HeavyHiggs03.SetBdt(HeavyHiggsReader->GetBdt());

    hanalysis::HPairPair HeavyHiggs10 = hanalysis::HPairPair(Top1, AntiTop0);
    HeavyHiggsTagger->FillBranch(HeavyHiggs10.GetTriplePair());
    HeavyHiggs10.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs12 = hanalysis::HPairPair(Top1, AntiTop2);
    HeavyHiggsTagger->FillBranch(HeavyHiggs12.GetTriplePair());
    HeavyHiggs12.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs13 = hanalysis::HPairPair(Top1, AntiTop3);
    HeavyHiggsTagger->FillBranch(HeavyHiggs13.GetTriplePair());
    HeavyHiggs13.SetBdt(HeavyHiggsReader->GetBdt());

    hanalysis::HPairPair HeavyHiggs20 = hanalysis::HPairPair(Top2, AntiTop0);
    HeavyHiggsTagger->FillBranch(HeavyHiggs20.GetTriplePair());
    HeavyHiggs20.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs21 = hanalysis::HPairPair(Top2, AntiTop1);
    HeavyHiggsTagger->FillBranch(HeavyHiggs21.GetTriplePair());
    HeavyHiggs21.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs23 = hanalysis::HPairPair(Top2, AntiTop3);
    HeavyHiggsTagger->FillBranch(HeavyHiggs23.GetTriplePair());
    HeavyHiggs23.SetBdt(HeavyHiggsReader->GetBdt());

    hanalysis::HPairPair HeavyHiggs30 = hanalysis::HPairPair(Top3, AntiTop0);
    HeavyHiggsTagger->FillBranch(HeavyHiggs30.GetTriplePair());
    HeavyHiggs30.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs31 = hanalysis::HPairPair(Top3, AntiTop1);
    HeavyHiggsTagger->FillBranch(HeavyHiggs31.GetTriplePair());
    HeavyHiggs31.SetBdt(HeavyHiggsReader->GetBdt());
    hanalysis::HPairPair HeavyHiggs32 = hanalysis::HPairPair(Top3, AntiTop2);
    HeavyHiggsTagger->FillBranch(HeavyHiggs32.GetTriplePair());
    HeavyHiggs32.SetBdt(HeavyHiggsReader->GetBdt());

    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs01, Jets[2], Jets[3]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs02, Jets[1], Jets[3]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs03, Jets[1], Jets[2]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs10, Jets[2], Jets[3]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs12, Jets[0], Jets[3]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs13, Jets[0], Jets[2]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs20, Jets[1], Jets[3]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs21, Jets[0], Jets[3]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs23, Jets[0], Jets[1]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs30, Jets[1], Jets[2]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs31, Jets[0], Jets[2]));
    HeavyHiggsEvents.push_back(HHeavyHiggsEvent(HeavyHiggs32, Jets[0], Jets[1]));

    return HeavyHiggsEvents;

}
