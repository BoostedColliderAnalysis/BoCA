# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
}

hheavyhiggs::HAnalysisMva::~HAnalysisMva()
{
    Print(HNotification, "Destructor");
}


std::string hheavyhiggs::HAnalysisMva::GetStudyNames(const hanalysis::HAnalysis::HTagger Tagger) const
{
    Print(HNotification, "Get Study Names", Tagger);

    switch (Tagger) {
    case  HBottomTagger :
        return "Bottom";
    case HWSemiTagger:
      return  "WSemi";
    case HWTagger:
      return  "W";
    case HJetPairTagger:
        return  "JetPair";
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
    case HEventLeptonicReader:
        return  "EventLeptonic";
    case HEventSemiReader:
        return  "EventSemi";
    default :
        Print(HError, "unexpected TaggerName", Tagger);
        return "";
    }

}

HStrings hheavyhiggs::HAnalysisMva::JoinHStrings(const HStrings &Strings1, const HStrings &Strings2)
{

    HStrings Combined;
    Combined.reserve(Strings1.size() + Strings2.size());
    Combined.insert(Combined.end(), Strings1.begin(), Strings1.end());
    Combined.insert(Combined.end(), Strings2.begin(), Strings2.end());
    return Combined;
}

std::vector<hanalysis::HFile *>  hheavyhiggs::HAnalysisMva::JoinFiles(std::vector<hanalysis::HFile *> Files1, std::vector<hanalysis::HFile *> Files2)
{

    std::vector<hanalysis::HFile *>  Combined;
    Combined.reserve(Files1.size() + Files2.size());
    Combined.insert(Combined.end(), Files1.begin(), Files1.end());
    Combined.insert(Combined.end(), Files2.begin(), Files2.end());
    return Combined;
}


std::vector<hanalysis::HFile *> hheavyhiggs::HAnalysisMva::GetFiles(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HNotification, "Set File Vector", Tagger, Tag);

    std::vector<hanalysis::HFile *> SignalLeptonicFiles;
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("400GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(30.58);
//     SignalLeptonicFiles.back()->SetMass(400);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("600GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(9.501);
//     SignalLeptonicFiles.back()->SetMass(600);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("800GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(3.831);
//     SignalLeptonicFiles.back()->SetMass(800);
    SignalLeptonicFiles.push_back(new hanalysis::HFile("1TeV_h2bb_llbbbb"));
    SignalLeptonicFiles.back()->SetCrosssection(1.812);
    SignalLeptonicFiles.back()->SetMass(1000);

    std::vector<hanalysis::HFile *> BackgroundLeptonicFiles;
    BackgroundLeptonicFiles.push_back(new hanalysis::HFile("BG_llbbbb"));
    BackgroundLeptonicFiles.back()->SetCrosssection(416.7);

    std::vector<hanalysis::HFile *> SignalSemiFiles;
    SignalSemiFiles.push_back(new hanalysis::HFile("1TeV_h2bb_ljbbbb"));
    SignalSemiFiles.back()->SetCrosssection(1.812);
    SignalSemiFiles.back()->SetMass(1000);

    std::vector<hanalysis::HFile *> BackgroundSemiFiles;
    BackgroundSemiFiles.push_back(new hanalysis::HFile("BG_ljbbbb"));
    BackgroundSemiFiles.back()->SetCrosssection(416.7);

    std::vector<hanalysis::HFile *> SignalHadronicFiles;
    SignalHadronicFiles.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));

    std::vector<hanalysis::HFile *> BackgroundHadronicFiles;
    BackgroundHadronicFiles.push_back(new hanalysis::HFile("BG_jjbbbb"));

    std::vector<hanalysis::HFile *> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::HFile *> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::HFile *> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::HFile *> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::HFile *> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);



    std::vector<hanalysis::HFile *> Files;

    switch (Tagger) {
    case  HBottomTagger :
        Files = CombinedFiles;
        break;
    case HJetPairTagger:
        Files = CombinedFiles;
        break;
    case HWSemiTagger:
        Files = SemiFiles;
        break;
    case HWTagger:
        Files = NotLeptonicFiles;
        break;
    case HTopLeptonicTagger:
        Files = LeptonicFiles;
        break;
    case HTopHadronicTagger:
        Files = NotLeptonicFiles;
        break;
    case HTopSemiTagger:
        Files = SemiFiles;
        break;
    case HHeavyHiggsLeptonicTagger:
        if (Tag == HBackground) Files = LeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HHeavyHiggsHadronicTagger:
        if (Tag == HBackground) Files = HadronicFiles;
        if (Tag == HSignal) Files = SignalHadronicFiles;
        break;
    case HHeavyHiggsSemiTagger:
        if (Tag == HBackground) Files = SemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    case HEventLeptonicTagger:
        if (Tag == HBackground) Files = BackgroundLeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HEventHadronicTagger:
        if (Tag == HBackground) Files = BackgroundHadronicFiles;
        if (Tag == HSignal) Files = SignalHadronicFiles;
        break;
    case HEventSemiTagger:
        if (Tag == HBackground) Files = BackgroundSemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    case HEventLeptonicReader: // TODO do we need this?
        Files = LeptonicFiles;
        break;
    case HEventSemiReader:
        Files = SemiFiles;
        break;
    default:
        Print(HError, "unknown tagger name");
    }

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix("_Delphes.root");

    Print(HNotification, "Files prepared");

    HStrings SignalLeptonicTrees {"400GeV_h2bb_llbbbb-run_01", "600GeV_h2bb_llbbbb-run_01", "800GeV_h2bb_llbbbb-run_01", "1TeV_h2bb_llbbbb-run_01"};
    HStrings BackgroundLeptonicTrees {"BG_llbbbb-run_01"};

    HStrings SignalSemiTrees {"1TeV_h2bb_ljbbbb-run_01"};
    HStrings BackgroundSemiTrees {"BG_ljbbbb-run_01"};

    HStrings SignalHadronicTree {"1TeV_h2bb_jjbbbb-run_01"};
    HStrings BackgroundHadronicTrees {"BG_jjbbbb-run_01"};


    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);








    if (Tagger == HEventLeptonicReader) {

        EventLeptonicTagger = new hheavyhiggs::HEventLeptonicTagger();
        EventLeptonicTagger->SetAnalysisName(GetProjectName());
//         EventLeptonicTagger->SetTestTreeNames(LeptonicTrees);
        EventLeptonicTagger->SetSignalTreeNames(SignalLeptonicTrees);
        EventLeptonicTagger->SetBackgroundTreeNames(BackgroundLeptonicTrees);
        Print(HError, "Tree names set");
        return Files;

    }





    if (Tagger == HEventSemiReader) {

        EventSemiTagger = new hheavyhiggs::HEventSemiTagger();
        EventSemiTagger->SetAnalysisName(GetProjectName());
//         EventSemiTagger->SetTestTreeNames(SemiTrees);
        EventSemiTagger->SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger->SetBackgroundTreeNames(BackgroundSemiTrees);
        Print(HError, "Tree names set");
        return Files;

    }








    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
//     BottomTagger->SetTestTreeNames(CombinedTrees);
    BottomTagger->SetSignalTreeNames(CombinedTrees);
    BottomTagger->SetBackgroundTreeNames(CombinedTrees);
    if (Tagger == HBottomTagger) return Files;

    JetPairTagger = new hanalysis::HJetPairTagger(BottomTagger);
    JetPairTagger->SetAnalysisName(GetProjectName());
//     JetPairTagger->SetTestTreeNames(CombinedTrees);
    JetPairTagger->SetSignalTreeNames(CombinedTrees);
    JetPairTagger->SetBackgroundTreeNames(CombinedTrees);
    if (Tagger == HJetPairTagger)  return Files;

    WTagger = new hanalysis::HWTagger(BottomTagger);
    WTagger->SetAnalysisName(GetProjectName());
//     WTagger->SetTestTreeNames(NotLeptonicTrees);
    WTagger->SetSignalTreeNames(NotLeptonicTrees);
    WTagger->SetBackgroundTreeNames(NotLeptonicTrees);
    if (Tagger == HWTagger)  return Files;

    if (Tagger == HTopLeptonicTagger || Tagger == HHeavyHiggsLeptonicTagger || Tagger == HEventLeptonicTagger) {

        TopLeptonicTagger = new hanalysis::HTopLeptonicTagger(BottomTagger);
        TopLeptonicTagger->SetAnalysisName(GetProjectName());
//         TopLeptonicTagger->SetTestTreeNames(LeptonicTrees);
        TopLeptonicTagger->SetSignalTreeNames(LeptonicTrees);
        TopLeptonicTagger->SetBackgroundTreeNames(LeptonicTrees);
        if (Tagger == HTopLeptonicTagger)  return Files;

        HeavyHiggsLeptonicTagger = new hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
        HeavyHiggsLeptonicTagger->SetAnalysisName(GetProjectName());
//         HeavyHiggsLeptonicTagger->SetTestTreeNames(LeptonicTrees);
        HeavyHiggsLeptonicTagger->SetSignalTreeNames(SignalLeptonicTrees);
        HeavyHiggsLeptonicTagger->SetBackgroundTreeNames(LeptonicTrees);
        if (Tagger == HHeavyHiggsLeptonicTagger)  return Files;

        EventLeptonicTagger = new hheavyhiggs::HEventLeptonicTagger(BottomTagger, TopLeptonicTagger, HeavyHiggsLeptonicTagger);
        EventLeptonicTagger->SetAnalysisName(GetProjectName());
//         EventLeptonicTagger->SetTestTreeNames(LeptonicTrees);
        EventLeptonicTagger->SetSignalTreeNames(SignalLeptonicTrees);
        EventLeptonicTagger->SetBackgroundTreeNames(BackgroundLeptonicTrees);
        Print(HError, "Tree names set");

    }

    TopHadronicTagger = new hanalysis::HTopHadronicTagger(BottomTagger, WTagger);
    TopHadronicTagger->SetAnalysisName(GetProjectName());
//     TopHadronicTagger->SetTestTreeNames(NotLeptonicTrees);
    TopHadronicTagger->SetSignalTreeNames(NotLeptonicTrees);
    TopHadronicTagger->SetBackgroundTreeNames(NotLeptonicTrees);
    if (Tagger == HTopHadronicTagger)  return Files;

    if (Tagger == HTopSemiTagger || Tagger == HHeavyHiggsSemiTagger || Tagger == HEventSemiTagger || Tagger == HWSemiTagger) {

      WSemiTagger = new hanalysis::HWSemiTagger();
      WSemiTagger->SetAnalysisName(GetProjectName());
      //         WSemiTagger->SetTestTreeNames(SemiTrees);
      WSemiTagger->SetSignalTreeNames(SemiTrees);
      WSemiTagger->SetBackgroundTreeNames(SemiTrees);
      if (Tagger == HWSemiTagger) return Files;

        HeavyHiggsSemiTagger = new hanalysis::HHeavyHiggsSemiTagger(BottomTagger,WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger);
        HeavyHiggsSemiTagger->SetAnalysisName(GetProjectName());
//         HeavyHiggsSemiTagger->SetTestTreeNames(SemiTrees);
        HeavyHiggsSemiTagger->SetSignalTreeNames(SignalSemiTrees);
        HeavyHiggsSemiTagger->SetBackgroundTreeNames(SemiTrees);
        if (Tagger == HHeavyHiggsSemiTagger)  return Files;

        EventSemiTagger = new hheavyhiggs::HEventSemiTagger(BottomTagger,WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
        EventSemiTagger->SetAnalysisName(GetProjectName());
//         EventSemiTagger->SetTestTreeNames(SemiTrees);
        EventSemiTagger->SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger->SetBackgroundTreeNames(BackgroundSemiTrees);

    }

    if (Tagger == HTopHadronicTagger || Tagger == HHeavyHiggsHadronicTagger || Tagger == HEventHadronicTagger) {

        HeavyHiggsHadronicTagger = new hanalysis::HHeavyHiggsHadronicTagger(BottomTagger, WTagger, TopHadronicTagger);
        HeavyHiggsHadronicTagger->SetAnalysisName(GetProjectName());
//         HeavyHiggsHadronicTagger->SetTestTreeNames(HadronicTrees);
        HeavyHiggsHadronicTagger->SetSignalTreeNames(SignalHadronicTree);
        HeavyHiggsHadronicTagger->SetBackgroundTreeNames(HadronicTrees);
        if (Tagger == HHeavyHiggsHadronicTagger)  return Files;

        EventHadronicTagger = new hheavyhiggs::HEventHadronicTagger(BottomTagger, WTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
        EventHadronicTagger->SetAnalysisName(GetProjectName());
//         EventHadronicTagger->SetTestTreeNames(HadronicTrees);
        EventHadronicTagger->SetSignalTreeNames(SignalHadronicTree);
        EventHadronicTagger->SetBackgroundTreeNames(BackgroundHadronicTrees);

    }

    return Files;

}


void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter *TreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        BottomBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HJetPairTagger :
        JetPairBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HWSemiTagger :
      WSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWSemiBranch::Class());
      break;
    case HWTagger :
        WBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HTopLeptonicTagger :
        TopLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopHadronicTagger :
        TopHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiTagger :
        TopSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HHeavyHiggsLeptonicTagger :
        HeavyHiggsLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsHadronicTagger :
        HeavyHiggsHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
        break;
    case HHeavyHiggsSemiTagger :
        HeavyHiggsSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
        break;
    case HEventLeptonicTagger :
        EventLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    case HEventHadronicTagger :
        EventHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventHadronicBranch::Class());
        break;
    case HEventSemiTagger :
        EventSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventSemiBranch::Class());
        break;
    default :
        Print(HError, "No Branch filled");
    }

}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{

    Print(HInformation, "Analysis", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        return GetBottomTag(Event, Tag);
    case HJetPairTagger :
        return GetJetPairTag(Event, Tag);
    case HWTagger :
        return GetWTag(Event, Tag);
    case HWSemiTagger :
        return GetWSemiTag(Event, Tag);
    case HTopLeptonicTagger :
        return GetTopLeptonicTag(Event, Tag);
    case HTopHadronicTagger :
        return GetTopHadronicTag(Event, Tag);
    case HTopSemiTagger :
        return GetTopSemiTag(Event, Tag);
    case HHeavyHiggsLeptonicTagger :
        return GetHeavyHiggsLeptonicTag(Event, Tag);
    case HHeavyHiggsHadronicTagger :
        return GetHeavyHiggsHadronicTag(Event, Tag);
    case HHeavyHiggsSemiTagger :
        return GetHeavyHiggsSemiTag(Event, Tag);
    case HEventLeptonicTagger :
        return GetEventLeptonicTag(Event, Tag);
    case HEventHadronicTagger :
        return GetEventHadronicTag(Event, Tag);
    case HEventSemiTagger :
      return GetEventSemiTag(Event, Tag);
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent *const Event, const HTag Tag)
{

    Print(HDebug, "Get Bottom Tag", Tag);

    std::vector<HBottomBranch *> Bottoms = BottomTagger->GetBranches(Event, Tag);

    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetJetPairTag(hanalysis::HEvent *const Event, const HTag Tag)
{

    Print(HDebug, "Get W Tag", Tag);

    std::vector<HWBranch *> JetPairs = JetPairTagger->GetBranches(Event, Tag);

    for (const auto & JetPair : JetPairs) {
        HWBranch *NewWBranch = static_cast<HWBranch *>(WBranch->NewEntry());
        *NewWBranch = *JetPair;
    }

    return 1;

}



bool hheavyhiggs::HAnalysisMva::GetWSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{

  Print(HDebug, "Get WSemi Tag", Tag);

  std::vector<HWSemiBranch *> WSemis = WSemiTagger->GetBranches(Event, Tag);

  for (const auto & WSemi : WSemis) {
    HWSemiBranch *NewWSemiBranch = static_cast<HWSemiBranch *>(WSemiBranch->NewEntry());
    *NewWSemiBranch = *WSemi;
  }

  return 1;

}

bool hheavyhiggs::HAnalysisMva::GetWTag(hanalysis::HEvent *const Event, const HTag Tag)
{

    Print(HDebug, "Get W Tag", Tag);

    std::vector<HWBranch *> Ws = WTagger->GetBranches(Event, Tag);

    for (const auto & W : Ws) {
        HWBranch *NewWBranch = static_cast<HWBranch *>(WBranch->NewEntry());
        *NewWBranch = *W;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent *const Event,  HTag Tag)
{

    Print(HInformation, "Get leptonic top", Tag);

    std::vector<HTopLeptonicBranch *> Tops = TopLeptonicTagger->GetBranches(Event, Tag);

    for (const auto & Top : Tops) {
        HTopLeptonicBranch *TopTagger = static_cast<HTopLeptonicBranch *>(TopLeptonicBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent *const Event,  HTag Tag)
{

    Print(HInformation, "Get hadronic tops", Tag);

    std::vector<HTopHadronicBranch *> Tops = TopHadronicTagger->GetBranches(Event, Tag);

    for (const auto & Top : Tops) {
        HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(TopHadronicBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetTopSemiTag(hanalysis::HEvent *const Event,  HTag Tag)
{

    Print(HInformation, "Get Tops", Tag);

    std::vector<HTopSemiBranch *> Tops = TopSemiTagger->GetBranches(Event, Tag);

    for (const auto & Top : Tops) {
        HTopSemiBranch *TopTagger = static_cast<HTopSemiBranch *>(TopSemiBranch->NewEntry());
        *TopTagger = *Top;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic Heavy Higgs Tag", Tag);


    std::vector<HHeavyHiggsLeptonicBranch *> Higgses = HeavyHiggsLeptonicTagger->GetBranches(Event, Tag);
    Print(HInformation, "Number of Higgses", Higgses.size());
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsLeptonicBranch *HiggsTagger = static_cast<HHeavyHiggsLeptonicBranch *>(HeavyHiggsLeptonicBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Hadronic HeavyHiggs Tag", Tag);


    std::vector<HHeavyHiggsHadronicBranch *> Higgses = HeavyHiggsHadronicTagger->GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsHadronicBranch *HiggsTagger = static_cast<HHeavyHiggsHadronicBranch *>(HeavyHiggsHadronicBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Semi HeavyHiggs Tag", Tag);


    std::vector<HHeavyHiggsSemiBranch *> Higgses = HeavyHiggsSemiTagger->GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;

    for (const auto & Higgs : Higgses) {
        HHeavyHiggsSemiBranch *HiggsTagger = static_cast<HHeavyHiggsSemiBranch *>(HeavyHiggsSemiBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }

    return 1;

}


bool hheavyhiggs::HAnalysisMva::GetEventLeptonicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event leptonic", Tag);


    std::vector<hheavyhiggs::HEventLeptonicBranch *> LeptonicEventBranches = EventLeptonicTagger->GetBranches(Event, Tag);
    if (LeptonicEventBranches.size() < 1) return 0;

    for (const auto & LeptonicEvent : LeptonicEventBranches) {
        HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(EventLeptonicBranch->NewEntry());
        *NewEventBranch = *LeptonicEvent;
    }

    return 1;

}



bool hheavyhiggs::HAnalysisMva::GetEventSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);


    std::vector<hheavyhiggs::HEventSemiBranch *> SemiEvents = EventSemiTagger->GetBranches(Event, Tag);
    if (SemiEvents.size() < 1) return 0;

    for (const auto & SemiEvent : SemiEvents) {
        HEventSemiBranch *NewEventBranch = static_cast<HEventSemiBranch *>(EventSemiBranch->NewEntry());
        *NewEventBranch = *SemiEvent;
    }

    return 1;

}



bool hheavyhiggs::HAnalysisMva::GetEventHadronicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event hadronic", Tag);


    std::vector<hheavyhiggs::HEventHadronicBranch *> HadronicEvents = EventHadronicTagger->GetBranches(Event, Tag);
    if (HadronicEvents.size() < 1) return 0;

    for (const auto & HadronicEvent : HadronicEvents) {
        HEventHadronicBranch *NewEventBranch = static_cast<HEventHadronicBranch *>(EventHadronicBranch->NewEntry());
        *NewEventBranch = *HadronicEvent;
    }

    return 1;

}



