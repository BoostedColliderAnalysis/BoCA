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


std::string hheavyhiggs::HAnalysisMva::GetStudyNames(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HState State) const
{
    Print(HNotification, "Get Study Names", Tagger, State);

    switch(Tagger) {
    case  HBottomTagger :
        return "Bottom";
    case HWTagger:
        return  "W";
    case HTopLeptonicTagger:
        return  "TopLeptonic";
    case HTopHadronicTagger:
        return  "TopHadronic";
    case HTopSemiTagger:
        return  "TopSemi";
    case HHeavyHiggsLeptonicTagger:
        return  "HeavyHiggsLeptonic";
    case HHeavyHiggsHadronicTagger:
        return  "HeavyHiggsHadronic";
    case HHeavyHiggsSemiTagger:
        return  "HeavyHiggsSemi";
    case HEventLeptonicTagger:
        return  "EventLeptonic";
    case HEventHadronicTagger:
        return  "EventHadronic";
    case HEventSemiTagger:
        return  "EventSemi";
    }

    Print(HError, "unexpected TaggerName", Tagger);
    return "";

}

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const hanalysis::HAnalysis::HTagger Tagger, const HState State)
{
    Print(HNotification, "Set File Vector", Tagger,State);

    std::vector<hanalysis::HFile *> Files;

    switch(Tagger) {
    case  HBottomTagger :
        Files.push_back(new hanalysis::HFile("BG_jjbbbb"));
        Files.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));
        Files.push_back(new hanalysis::HFile("BG_llbbbb"));
        Files.push_back(new hanalysis::HFile("1TeV_h2bb_llbbbb"));
        Files.push_back(new hanalysis::HFile("BG_ljbbbb"));
        Files.push_back(new hanalysis::HFile("1TeV_h2bb_ljbbbb"));
        break;
    case HWTagger:
        Files.push_back(new hanalysis::HFile("BG_jjbbbb"));
	Files.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));
	Files.push_back(new hanalysis::HFile("BG_ljbbbb"));
	Files.push_back(new hanalysis::HFile("1TeV_h2bb_ljbbbb"));
        break;
    case HTopLeptonicTagger:
        Files.push_back(new hanalysis::HFile("BG_llbbbb"));
        Files.push_back(new hanalysis::HFile("1TeV_h2bb_llbbbb"));
        break;
    case HTopHadronicTagger:
        Files.push_back(new hanalysis::HFile("BG_jjbbbb"));
        Files.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));
        break;
    case HTopSemiTagger:
        Files.push_back(new hanalysis::HFile("BG_ljbbbb"));
        Files.push_back(new hanalysis::HFile("1TeV_h2bb_ljbbbb"));
        break;
    case HHeavyHiggsLeptonicTagger:
        if(State == HBackground) Files.push_back(new hanalysis::HFile("BG_llbbbb"));
        if(State == HSignal)Files.push_back(new hanalysis::HFile("1TeV_h2bb_llbbbb"));
        break;
    case HHeavyHiggsHadronicTagger:
        if(State == HBackground) Files.push_back(new hanalysis::HFile("BG_jjbbbb"));
        if(State == HSignal)Files.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));
        break;
    case HHeavyHiggsSemiTagger:
        if(State == HBackground) Files.push_back(new hanalysis::HFile("BG_ljbbbb"));
        if(State == HSignal) Files.push_back(new hanalysis::HFile("1TeV_h2bb_ljbbbb"));
        break;
    case HEventLeptonicTagger:
        if(State == HBackground) Files.push_back(new hanalysis::HFile("BG_llbbbb"));
        if(State == HSignal) Files.push_back(new hanalysis::HFile("1TeV_h2bb_llbbbb"));
        break;
    case HEventHadronicTagger:
        if(State == HBackground) Files.push_back(new hanalysis::HFile("BG_jjbbbb"));
        if(State == HSignal) Files.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));
        break;
    case HEventSemiTagger:
        if(State == HBackground) Files.push_back(new hanalysis::HFile("BG_ljbbbb"));
        if(State == HSignal) Files.push_back(new hanalysis::HFile("1TeV_h2bb_ljbbbb"));
        break;
    }

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_Delphes.root");

    Print(HNotification, "Files prepared");

    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetTestTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01","BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01","BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    BottomTagger->SetSignalTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01","BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01","BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    BottomTagger->SetBackgroundTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01","BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01","BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    if (Tagger == HBottomTagger) return Files;
    BottomReader = new hanalysis::HReader(BottomTagger);

    WTagger = new hanalysis::HWTagger(BottomTagger);
    WTagger->SetAnalysisName(GetProjectName());
    WTagger->SetTestTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01","BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    WTagger->SetSignalTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01","BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    WTagger->SetBackgroundTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01","BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    if (Tagger == HWTagger)  return Files;
    WReader = new hanalysis::HReader(WTagger);

    TopLeptonicTagger = new hanalysis::HTopLeptonicTagger(BottomTagger);
    TopLeptonicTagger->SetAnalysisName(GetProjectName());
    TopLeptonicTagger->SetTestTreeNames( {"BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"});
    TopLeptonicTagger->SetSignalTreeNames( {"BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"});
    TopLeptonicTagger->SetBackgroundTreeNames( {"BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"});
    if (Tagger == HTopLeptonicTagger)  return Files;
    TopLeptonicReader = new hanalysis::HReader(TopLeptonicTagger);

    TopHadronicTagger = new hanalysis::HTopHadronicTagger(BottomTagger, WTagger);
    TopHadronicTagger->SetAnalysisName(GetProjectName());
    TopHadronicTagger->SetTestTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01"});
    TopHadronicTagger->SetSignalTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01"});
    TopHadronicTagger->SetBackgroundTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01"});
    if (Tagger == HTopHadronicTagger)  return Files;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);

    TopSemiTagger = new hanalysis::HTopSemiTagger(BottomTagger);
    TopSemiTagger->SetAnalysisName(GetProjectName());
    TopSemiTagger->SetTestTreeNames( {"BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    TopSemiTagger->SetSignalTreeNames( {"BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    TopSemiTagger->SetBackgroundTreeNames( {"BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    if (Tagger == HTopSemiTagger) return Files;
    TopSemiReader = new hanalysis::HReader(TopSemiTagger);

    HeavyHiggsLeptonicTagger = new hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
    HeavyHiggsLeptonicTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsLeptonicTagger->SetTestTreeNames( {"BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"});
    HeavyHiggsLeptonicTagger->SetSignalTreeNames( {"1TeV_h2bb_llbbbb-run_01"});
    HeavyHiggsLeptonicTagger->SetBackgroundTreeNames( {"BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"});
    if (Tagger == HHeavyHiggsLeptonicTagger)  return Files;
    HeavyHiggsLeptonicReader = new hanalysis::HReader(HeavyHiggsLeptonicTagger);

    HeavyHiggsHadronicTagger = new hanalysis::HHeavyHiggsHadronicTagger(BottomTagger, WTagger, TopHadronicTagger);
    HeavyHiggsHadronicTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsHadronicTagger->SetTestTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01"});
    HeavyHiggsHadronicTagger->SetSignalTreeNames( {"1TeV_h2bb_jjbbbb-run_01"});
    HeavyHiggsHadronicTagger->SetBackgroundTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01"});
    if (Tagger == HHeavyHiggsHadronicTagger)  return Files;
    HeavyHiggsHadronicReader = new hanalysis::HReader(HeavyHiggsHadronicTagger);

    HeavyHiggsSemiTagger = new hanalysis::HHeavyHiggsSemiTagger(BottomTagger, WTagger, TopSemiTagger,TopHadronicTagger);
    HeavyHiggsSemiTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsSemiTagger->SetTestTreeNames( {"BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    HeavyHiggsSemiTagger->SetSignalTreeNames( {"1TeV_h2bb_ljbbbb-run_01"});
    HeavyHiggsSemiTagger->SetBackgroundTreeNames( {"BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    if (Tagger == HHeavyHiggsSemiTagger)  return Files;
    HeavyHiggsSemiReader = new hanalysis::HReader(HeavyHiggsSemiTagger);

    EventLeptonicTagger = new hheavyhiggs::HEventLeptonicTagger(BottomTagger, TopLeptonicTagger, HeavyHiggsLeptonicTagger);
    EventLeptonicTagger->SetAnalysisName(GetProjectName());
    EventLeptonicTagger->SetTestTreeNames( {"BG_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"});
    EventLeptonicTagger->SetSignalTreeNames( {"1TeV_h2bb_llbbbb-run_01"});
    EventLeptonicTagger->SetBackgroundTreeNames( {"BG_llbbbb-run_01"});

    EventHadronicTagger = new hheavyhiggs::HEventHadronicTagger(BottomTagger, WTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
    EventHadronicTagger->SetAnalysisName(GetProjectName());
    EventHadronicTagger->SetTestTreeNames( {"BG_jjbbbb-run_01", "1TeV_h2bb_jjbbbb-run_01"});
    EventHadronicTagger->SetSignalTreeNames( {"1TeV_h2bb_jjbbbb-run_01"});
    EventHadronicTagger->SetBackgroundTreeNames( {"BG_jjbbbb-run_01"});

    EventSemiTagger = new hheavyhiggs::HEventSemiTagger(BottomTagger, WTagger, TopSemiTagger,TopHadronicTagger, HeavyHiggsSemiTagger);
    EventSemiTagger->SetAnalysisName(GetProjectName());
    EventSemiTagger->SetTestTreeNames( {"BG_ljbbbb-run_01", "1TeV_h2bb_ljbbbb-run_01"});
    EventSemiTagger->SetSignalTreeNames( {"1TeV_h2bb_ljbbbb-run_01"});
    EventSemiTagger->SetBackgroundTreeNames( {"BG_ljbbbb-run_01"});


    return Files;

}


void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter *TreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch(Tagger) {
    case HBottomTagger :
        BottomBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HBottomBranch::Class());
        break;
    case HWTagger :
        WBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HWBranch::Class());
        break;
    case HTopLeptonicTagger :
        TopLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopHadronicTagger :
        TopHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiTagger :
        TopSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HTopSemiBranch::Class());
        break;
    case HHeavyHiggsLeptonicTagger :
        HeavyHiggsLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsHadronicTagger :
        HeavyHiggsHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HHeavyHiggsHadronicBranch::Class());
        break;
    case HHeavyHiggsSemiTagger :
        HeavyHiggsSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HHeavyHiggsSemiBranch::Class());
        break;
    case HEventLeptonicTagger :
        EventLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HEventLeptonicBranch::Class());
        break;
    case HEventHadronicTagger :
        EventHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HEventHadronicBranch::Class());
        break;
    case HEventSemiTagger :
        EventSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger,HSignal).c_str(), HEventSemiBranch::Class());
        break;
    default :
        Print(HError,"No Branch filled");
    }

}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const HState State)
{

    Print(HInformation, "Analysis", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        if (GetBottomTag(Event, State)) return 1;
    case HWTagger :
        if (GetWTag(Event, State)) return 1;
    case HTopLeptonicTagger :
        if (GetTopLeptonicTag(Event, State)) return 1;
    case HTopHadronicTagger :
        if (GetTopHadronicTag(Event, State)) return 1;
    case HTopSemiTagger :
        if (GetTopSemiTag(Event, State)) return 1;
    case HHeavyHiggsLeptonicTagger :
        if (GetHeavyHiggsLeptonicTag(Event, State)) return 1;
    case HHeavyHiggsHadronicTagger :
        if (GetHeavyHiggsHadronicTag(Event, State)) return 1;
    case HHeavyHiggsSemiTagger :
        if (GetHeavyHiggsSemiTag(Event, State)) return 1;
    case HEventLeptonicTagger :
        if (GetEventLeptonicTag(Event, State)) return 1;
    case HEventHadronicTagger :
        if (GetEventHadronicTag(Event, State)) return 1;
    case HEventSemiTagger :
        if (GetEventSemiTag(Event, State)) return 1;
    default :
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


bool hheavyhiggs::HAnalysisMva::GetWTag(hanalysis::HEvent *const Event, const HState State)
{

    Print(HDebug, "Get W Tag", State);

    std::vector<HWBranch *> Ws = WTagger->GetBranches(Event, State);

    for (const auto & W : Ws) {
        HWBranch *NewWBranch = static_cast<HWBranch *>(WBranch->NewEntry());
        *NewWBranch = *W;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get leptonic top", State);

    std::vector<HTopLeptonicBranch *> Tops = TopLeptonicTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HTopLeptonicBranch *TopTagger = static_cast<HTopLeptonicBranch *>(TopLeptonicBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get hadronic tops", State);

    std::vector<HTopHadronicBranch *> Tops = TopHadronicTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(TopHadronicBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopSemiTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get Tops", State);

    std::vector<HTopSemiBranch *> Tops = TopSemiTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HTopSemiBranch *TopTagger = static_cast<HTopSemiBranch *>(TopSemiBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Leptonic Heavy Higgs Tag", State);


    std::vector<HHeavyHiggsLeptonicBranch *> Higgses = HeavyHiggsLeptonicTagger->GetBranches(Event, State);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsLeptonicBranch *HiggsTagger = static_cast<HHeavyHiggsLeptonicBranch *>(HeavyHiggsLeptonicBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Hadronic HeavyHiggs Tag", State);


    std::vector<HHeavyHiggsHadronicBranch *> Higgses = HeavyHiggsHadronicTagger->GetBranches(Event, State);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsHadronicBranch *HiggsTagger = static_cast<HHeavyHiggsHadronicBranch *>(HeavyHiggsHadronicBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Semi HeavyHiggs Tag", State);


    std::vector<HHeavyHiggsSemiBranch *> Higgses = HeavyHiggsSemiTagger->GetBranches(Event, State);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsSemiBranch *HiggsTagger = static_cast<HHeavyHiggsSemiBranch *>(HeavyHiggsSemiBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetEventLeptonicTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Event", State);


    std::vector<hheavyhiggs::HEventLeptonicBranch *> LeptonicEventBranches = EventLeptonicTagger->GetBranches(Event, State);
    if (LeptonicEventBranches.size() < 1) return 0;

    for (const auto & LeptonicEvent : LeptonicEventBranches) {
        HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(EventLeptonicBranch->NewEntry());
        *NewEventBranch = *LeptonicEvent;
    }

    return 1;

}



bool hheavyhiggs::HAnalysisMva::GetEventHadronicTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Event", State);


    std::vector<hheavyhiggs::HEventHadronicBranch *> HadronicEvents = EventHadronicTagger->GetBranches(Event, State);
    if (HadronicEvents.size() < 1) return 0;

    for (const auto & HadronicEvent : HadronicEvents) {
        HEventHadronicBranch *NewEventBranch = static_cast<HEventHadronicBranch *>(EventHadronicBranch->NewEntry());
        *NewEventBranch = *HadronicEvent;
    }

    return 1;

}



bool hheavyhiggs::HAnalysisMva::GetEventSemiTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Event", State);


    std::vector<hheavyhiggs::HEventSemiBranch *> SemiEvents = EventSemiTagger->GetBranches(Event, State);
    if (SemiEvents.size() < 1) return 0;

    for (const auto & SemiEvent : SemiEvents) {
        HEventSemiBranch *NewEventBranch = static_cast<HEventSemiBranch *>(EventSemiBranch->NewEntry());
        *NewEventBranch = *SemiEvent;
    }

    return 1;

}
