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
    if (Tagger == HBottomTagger) return {"Bottom", "NotBottom"};
    else if (Tagger == HWTagger) return  {"W", "NotW"};
    else if (Tagger == HTopLeptonicTagger) return  {"TopLeptonic", "NotTopLeptonic"};
    else if (Tagger == HTopHadronicTagger) return  {"TopHadronic", "NotTopHadronic"};
    else if (Tagger == HHeavyHiggsLeptonicTagger) return  {"HeavyHiggsLeptonic", "NotHeavyHiggsLeptonic"};
    else if (Tagger == HHeavyHiggsHadronicTagger) return  {"HeavyHiggsHadronic", "NotHeavyHiggsHadronic"};
    else if (Tagger == HLeptonicEventTagger) return  {"LeptonicEvent", "NotLeptonicEvent"};
    else if (Tagger == HHadronicEventTagger) return  {"HadronicEvent", "NotHadronicEvent"};
    else {
        Print(HError, "unexpected TaggerName", Tagger);
        return {};
    }
}

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const std::string &StudyName)
{
    Print(HNotification, "Set File Vector", StudyName);

    std::vector<hanalysis::HFile *> Files;

    if (StudyName != "HeavyHiggs" && StudyName != "Signal") Files.push_back(new hanalysis::HFile("BG"));
    Files.push_back(new hanalysis::HFile("1TeV_h2bb"));
    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_llbbbb_Delphes.root");

    Print(HNotification, "Files prepared");

    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    BottomTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    BottomTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (StudyName == "Bottom" && StudyName == "NotBottom") return Files;
    BottomReader = new hanalysis::HReader(BottomTagger);

    WTagger = new hanalysis::HWTagger(BottomTagger);
    WTagger->SetAnalysisName(GetProjectName());
    WTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    WTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    WTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (StudyName == "W" && StudyName == "NotW") return Files;
    WReader = new hanalysis::HReader(WTagger);

    TopLeptonicTagger = new hanalysis::HLeptonicTopTagger(BottomTagger);
    TopLeptonicTagger->SetAnalysisName(GetProjectName());
    TopLeptonicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    TopLeptonicTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    TopLeptonicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (StudyName == "TopLeptonic" && StudyName != "NotTopLeptonic") return Files;
    TopLeptonicReader = new hanalysis::HReader(TopLeptonicTagger);

    TopHadronicTagger = new hanalysis::HHadronicTopTagger(BottomTagger,WTagger);
    TopHadronicTagger->SetAnalysisName(GetProjectName());
    TopHadronicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    TopHadronicTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    TopHadronicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (StudyName == "TopHadronic" && StudyName != "NotTopHadronic")return Files;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);

    HeavyHiggsLeptonicTagger = new hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
    HeavyHiggsLeptonicTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsLeptonicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    HeavyHiggsLeptonicTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    HeavyHiggsLeptonicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (StudyName == "HeavyHiggsLeptonic" && StudyName != "NotHeavyHiggsLeptonic" )return Files;
    HeavyHiggsLeptonicReader = new hanalysis::HReader(HeavyHiggsLeptonicTagger);

    HeavyHiggsHadronicTagger = new hanalysis::HHeavyHiggsHadronicTagger(BottomTagger,WTagger, TopHadronicTagger);
    HeavyHiggsHadronicTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsHadronicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    HeavyHiggsHadronicTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    HeavyHiggsHadronicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (StudyName == "HeavyHiggsHadronic" && StudyName != "NotHeavyHiggsHadronic" )return Files;
    HeavyHiggsHadronicReader = new hanalysis::HReader(HeavyHiggsHadronicTagger);


    LeptonicEventTagger = new hheavyhiggs::HLeptonicEventTagger(BottomTagger, TopLeptonicTagger, HeavyHiggsLeptonicTagger);
    LeptonicEventTagger->SetAnalysisName(GetProjectName());
    LeptonicEventTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    LeptonicEventTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    LeptonicEventTagger->SetBackgroundTreeNames( {"BG-run_01"});

    HadronicEventTagger = new hheavyhiggs::HHadronicEventTagger(BottomTagger,WTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
    HadronicEventTagger->SetAnalysisName(GetProjectName());
    HadronicEventTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    HadronicEventTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    HadronicEventTagger->SetBackgroundTreeNames( {"BG-run_01"});


    return Files;

}

std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const HTagger Tagger, const HState State)
{
    Print(HNotification, "Set File Vector", Tagger);

    std::vector<hanalysis::HFile *> Files;

    if ((Tagger != HEventTagger && Tagger != HHiggsLeptonicTagger) || State == HBackground) Files.push_back(new hanalysis::HFile("BG"));
    Files.push_back(new hanalysis::HFile("1TeV_h2bb"));
    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_ttbb_wwbbbb_llbbbb_Delphes.root");

    Print(HNotification, "Files prepared");

    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
    BottomTagger->SetSignalTreeNames( {"BG-run_01", "h2bb-run_01"});
    BottomTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});
    if (Tagger == HBottomTagger) return Files;
    BottomReader = new hanalysis::HReader(BottomTagger);

    WTagger = new hanalysis::HWTagger(BottomTagger);
    WTagger->SetAnalysisName(GetProjectName());
    WTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    WTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    WTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (Tagger == HWTagger)  return Files;
    WReader = new hanalysis::HReader(WTagger);

    TopLeptonicTagger = new hanalysis::HLeptonicTopTagger(BottomTagger);
    TopLeptonicTagger->SetAnalysisName(GetProjectName());
    TopLeptonicTagger->SetTestTreeNames( {"BG-run_01", "h2bb-run_01"});
    TopLeptonicTagger->SetSignalTreeNames( {"BG-run_01", "h2bb-run_01"});
    TopLeptonicTagger->SetBackgroundTreeNames( {"BG-run_01", "h2bb-run_01"});
    if (Tagger == HTopLeptonicTagger)  return Files;
    TopLeptonicReader = new hanalysis::HReader(TopLeptonicTagger);

    TopHadronicTagger = new hanalysis::HHadronicTopTagger(BottomTagger,WTagger);
    TopHadronicTagger->SetAnalysisName(GetProjectName());
    TopHadronicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    TopHadronicTagger->SetSignalTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    TopHadronicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (Tagger == HTopHadronicTagger)  return Files;
    TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);

    HeavyHiggsLeptonicTagger = new hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
    HeavyHiggsLeptonicTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsLeptonicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    HeavyHiggsLeptonicTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    HeavyHiggsLeptonicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (Tagger == HHeavyHiggsLeptonicTagger)  return Files;
    TopHadronicReader = new hanalysis::HReader(HeavyHiggsLeptonicTagger);

    HeavyHiggsHadronicTagger = new hanalysis::HHeavyHiggsHadronicTagger(BottomTagger,WTagger, TopHadronicTagger);
    HeavyHiggsHadronicTagger->SetAnalysisName(GetProjectName());
    HeavyHiggsHadronicTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    HeavyHiggsHadronicTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    HeavyHiggsHadronicTagger->SetBackgroundTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    if (Tagger == HHeavyHiggsHadronicTagger)  return Files;
    HeavyHiggsLeptonicReader = new hanalysis::HReader(HeavyHiggsHadronicTagger);

    LeptonicEventTagger = new hheavyhiggs::HLeptonicEventTagger(BottomTagger, TopLeptonicTagger, HeavyHiggsLeptonicTagger);
    LeptonicEventTagger->SetAnalysisName(GetProjectName());
    LeptonicEventTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    LeptonicEventTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    LeptonicEventTagger->SetBackgroundTreeNames( {"BG-run_01"});

    HadronicEventTagger = new hheavyhiggs::HHadronicEventTagger(BottomTagger,WTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
    HadronicEventTagger->SetAnalysisName(GetProjectName());
    HadronicEventTagger->SetTestTreeNames( {"BG-run_01", "1TeV_h2bb-run_01"});
    HadronicEventTagger->SetSignalTreeNames( {"1TeV_h2bb-run_01"});
    HadronicEventTagger->SetBackgroundTreeNames( {"BG-run_01"});

    return Files;

}


void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter *TreeWriter, const HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    if (Tagger == HBottomTagger) BottomBranch = TreeWriter->NewBranch("Bottom", HBottomBranch::Class());
    else if (Tagger == HWTagger) WBranch = TreeWriter->NewBranch("W", HLeptonicTopBranch::Class());
    else if (Tagger == HTopLeptonicTagger) TopLeptonicBranch = TreeWriter->NewBranch("TopLeptonic", HLeptonicTopBranch::Class());
    else if (Tagger == HTopHadronicTagger) TopHadronicBranch = TreeWriter->NewBranch("TopHadronic", HLeptonicTopBranch::Class());
    else if (Tagger == HHeavyHiggsLeptonicTagger) HeavyHiggsLeptonicBranch = TreeWriter->NewBranch("HeavyHiggsLeptonic", HHeavyHiggsLeptonicBranch::Class());
    else if (Tagger == HHeavyHiggsHadronicTagger) HeavyHiggsHadronicBranch = TreeWriter->NewBranch("HeavyHiggsHadronic", HHeavyHiggsHadronicBranch::Class());
    else if (Tagger == HLeptonicEventTagger) LeptonicEventBranch = TreeWriter->NewBranch("Event", HLeptonicEventBranch::Class());
    else if (Tagger == HHadronicEventTagger) HadronicEventBranch = TreeWriter->NewBranch("Event", HHadronicEventBranch::Class());

}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const std::string &StudyName, const HTagger Tagger)
{

    Print(HInformation, "Analysis", StudyName);

    HState State;
    if (Tagger == HBottomTagger) {
        if (StudyName == "Bottom") State = HSignal;
        if (StudyName == "NotBottom") State = HBackground;
        if (GetBottomTag(Event, State)) return 1;
    } else if (Tagger == HWTagger) {
        if (StudyName == "W") State = HSignal;
        if (StudyName == "NotW") State = HBackground;
        if (GetWTag(Event, State)) return 1;
    } else if (Tagger == HTopLeptonicTagger) {
        if (StudyName == "TopLeptonic") State = HSignal;
        if (StudyName == "NotTopLeptonic") State = HBackground;
        if (GetTopLeptonicTag(Event, State)) return 1;
    } else if (Tagger == HTopHadronicTagger) {
        if (StudyName == "TopHadronic") State = HSignal;
        if (StudyName == "NotTopHadronic") State = HBackground;
        if (GetTopHadronicTag(Event, State)) return 1;
    } else if (Tagger == HHeavyHiggsLeptonicTagger) {
        if (StudyName == "HeavyHiggsLeptonic") State = HSignal;
        if (StudyName == "NotHeavyHiggsLeptonic") State = HBackground;
        if (GetHeavyHiggsLeptonicTag(Event, State)) return 1;
    } else if (Tagger == HHeavyHiggsHadronicTagger) {
        if (StudyName == "HeavyHiggsHadronic") State = HSignal;
        if (StudyName == "NotHeavyHiggsHadronic") State = HBackground;
        if (GetHeavyHiggsHadronicTag(Event, State)) return 1;
    } else if (Tagger == HLeptonicEventTagger) {
        if (StudyName == "LeptonicEvent") State = HSignal;
        if (StudyName == "HadronicEvent") State = HBackground;
        if (GetLeptonicEventTag(Event, State)) return 1;
    } else if (Tagger == HHadronicEventTagger) {
        if (StudyName == "HadronicEvent") State = HSignal;
        if (StudyName == "HadronicEvent") State = HBackground;
        if (GetHadronicEventTag(Event, State)) return 1;
    } else {
        Print(HError, "unknown Tagger", Tagger);
    }

    return 0;

}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const HTagger Tagger, const HState State)
{

    Print(HInformation, "Analysis", Tagger);

    if (Tagger == HBottomTagger) if (GetBottomTag(Event, State)) return 1;
        else if (Tagger == HWTagger) if (GetWTag(Event, State)) return 1;
            else if (Tagger == HTopLeptonicTagger) if (GetTopLeptonicTag(Event, State)) return 1;
                else if (Tagger == HTopHadronicTagger) if (GetTopHadronicTag(Event, State)) return 1;
                    else if (Tagger == HHeavyHiggsLeptonicTagger) if (GetHeavyHiggsLeptonicTag(Event, State)) return 1;
                        else if (Tagger == HHeavyHiggsHadronicTagger) if (GetHeavyHiggsHadronicTag(Event, State)) return 1;
                            else if (Tagger == HLeptonicEventTagger) if (GetLeptonicEventTag(Event, State)) return 1;
                            else if (Tagger == HHadronicEventTagger) if (GetHadronicEventTag(Event, State)) return 1;
                                else Print(HError, "unknown Tagger", Tagger);

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

    std::vector<HHadronicWBranch *> Ws = WTagger->GetBranches(Event, State);

    for (const auto & W : Ws) {
        HHadronicWBranch *WTagger = static_cast<HHadronicWBranch *>(WBranch->NewEntry());
        *WTagger = *W;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get Tops", State);

    std::vector<HLeptonicTopBranch *> Tops = TopLeptonicTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HLeptonicTopBranch *TopTagger = static_cast<HLeptonicTopBranch *>(TopLeptonicBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent *const Event,  HState State)
{

    Print(HInformation, "Get Tops", State);

    std::vector<HHadronicTopBranch *> Tops = TopHadronicTagger->GetBranches(Event, State);

    for (const auto & Top : Tops) {
        HHadronicTopBranch *TopTagger = static_cast<HHadronicTopBranch *>(TopHadronicBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get HeavyHiggs Tag", State);


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
    Print(HInformation, "Get HeavyHiggs Tag", State);


    std::vector<HHeavyHiggsHadronicBranch *> Higgses = HeavyHiggsHadronicTagger->GetBranches(Event, State);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsHadronicBranch *HiggsTagger = static_cast<HHeavyHiggsHadronicBranch *>(HeavyHiggsHadronicBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetLeptonicEventTag(hanalysis::HEvent *const Event, const HState State)
{
    Print(HInformation, "Get Event", State);


    std::vector<hheavyhiggs::HLeptonicEventBranch *> Events = LeptonicEventTagger->GetBranches(Event, State);
    if (Events.size() < 1) return 0;

    for (const auto & Event : Events) {
        HLeptonicEventBranch *EventTagger = static_cast<HLeptonicEventBranch *>(LeptonicEventBranch->NewEntry());
        *EventTagger = *Event;
    }

    return 1;

}



bool hheavyhiggs::HAnalysisMva::GetHadronicEventTag(hanalysis::HEvent *const Event, const HState State)
{
  Print(HInformation, "Get Event", State);


  std::vector<hheavyhiggs::HHadronicEventBranch *> Events = HadronicEventTagger->GetBranches(Event, State);
  if (Events.size() < 1) return 0;

  for (const auto & Event : Events) {
    HHadronicEventBranch *EventTagger = static_cast<HHadronicEventBranch *>(HadronicEventBranch->NewEntry());
    *EventTagger = *Event;
  }

  return 1;

}
