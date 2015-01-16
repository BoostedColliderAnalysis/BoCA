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
    case HWReader:
        return  "WReader";
    case HJetPairTagger:
        return  "JetPair";
        return  "WReader";
    case HJetPairReader:
        return  "JetPairReader";
    case HTopLeptonicTagger:
        return  "TopLeptonic";
    case HTopLeptonicReader:
        return  "TopLeptonicReader";
    case HTopHadronicTagger:
        return  "TopHadronic";
    case HTopSemiTagger:
        return  "TopSemi";
    case HTopHadronicReader:
        return  "TopHadronicReader";
    case HTopSemiReader:
        return  "TopSemiReader";
    case HHeavyHiggsLeptonicTagger:
        return  "HeavyHiggsLeptonic";
    case HHeavyHiggsHadronicTagger:
        return  "HeavyHiggsHadronic";
    case HHeavyHiggsSemiTagger:
        return  "HeavyHiggsSemi";
    case HHeavyHiggsSemiReader:
        return  "HeavyHiggsSemiReader";
    case HHeavyHiggsLeptonicReader:
        return  "HeavyHiggsLeptonicReader";
    case HEventLeptonicTagger:
        return  "EventLeptonic";
    case HEventHadronicTagger:
        return  "EventHadronic";
    case HEventSemiTagger:
        return  "EventSemi";
    case HEventLeptonicReader:
        return  "EventLeptonicReader";
    case HEventSemiReader:
        return  "EventSemiReader";
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

std::vector<hanalysis::HFile *>  hheavyhiggs::HAnalysisMva::JoinFiles(const std::vector< hanalysis::HFile * > &Files1, const std::vector< hanalysis::HFile * > &Files2)
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
//     SignalLeptonicFiles.back()->SetCrosssection(3.31);
//     SignalLeptonicFiles.back()->SetMass(400);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("600GeV_h2bb_llbbbb"));
    //     SignalLeptonicFiles.back()->SetCrosssection(0.933);
//     SignalLeptonicFiles.back()->SetMass(600);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("800GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.359);
//     SignalLeptonicFiles.back()->SetMass(800);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("1000GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.167);
//     SignalLeptonicFiles.back()->SetMass(1000);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("1500GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0379);
//     SignalLeptonicFiles.back()->SetMass(1500);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("2000GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0563);
//     SignalLeptonicFiles.back()->SetMass(2000);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("2500GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0224);
//     SignalLeptonicFiles.back()->SetMass(2500);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("3000GeV_h2bb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0104);
//     SignalLeptonicFiles.back()->SetMass(3000);

    std::vector<hanalysis::HFile *> BackgroundLeptonicFiles;
//     BackgroundLeptonicFiles.push_back(new hanalysis::HFile("BG_ttbb_llbbbb"));
//     BackgroundLeptonicFiles.back()->SetCrosssection(4.773);
//     BackgroundLeptonicFiles.push_back(new hanalysis::HFile("BG_ttcc_llbbcc"));
//     BackgroundLeptonicFiles.back()->SetCrosssection(4.161);

    std::vector<hanalysis::HFile *> SignalSemiFiles;
//     SignalSemiFiles.push_back(new hanalysis::HFile("400GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(94.7);
//     SignalSemiFiles.back()->SetMass(400);
//     SignalSemiFiles.push_back(new hanalysis::HFile("600GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(26.6);
//     SignalSemiFiles.back()->SetMass(600);
//     SignalSemiFiles.push_back(new hanalysis::HFile("800GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(10.3);
//     SignalSemiFiles.back()->SetMass(800);
    SignalSemiFiles.push_back(new hanalysis::HFile("1000GeV_h2bb_ljbbbb"));
    SignalSemiFiles.back()->SetCrosssection(4.75);
    SignalSemiFiles.back()->SetMass(1000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("1500GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(1.08);
//     SignalSemiFiles.back()->SetMass(1500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("2000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.357);
//     SignalSemiFiles.back()->SetMass(2000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("2500GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.141);
//     SignalSemiFiles.back()->SetMass(2500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("3000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(3000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("3500GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(3500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("4000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(4000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("4500GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(4500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("5000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(5000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("6000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(6000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("7000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(7000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("8000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(8000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("9000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(9000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("10000GeV_h2bb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00294);
//     SignalSemiFiles.back()->SetMass(10000);

    std::vector<hanalysis::HFile *> BackgroundSemiFiles;
    BackgroundSemiFiles.push_back(new hanalysis::HFile("BG_ttbb_ljbbbb"));
    BackgroundSemiFiles.back()->SetCrosssection(25.55);
//     BackgroundSemiFiles.push_back(new hanalysis::HFile("BG_ttcc_ljbbcc"));
//     BackgroundSemiFiles.back()->SetCrosssection(22.25);

    std::vector<hanalysis::HFile *> SignalHadronicFiles;
//     SignalHadronicFiles.push_back(new hanalysis::HFile("1TeV_h2bb_jjbbbb"));

    std::vector<hanalysis::HFile *> BackgroundHadronicFiles;
//     BackgroundHadronicFiles.push_back(new hanalysis::HFile("BG_jjbbbb"));

    std::vector<hanalysis::HFile *> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::HFile *> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::HFile *> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::HFile *> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::HFile *> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);


    std::vector<hanalysis::HFile *> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::HFile *> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::HFile *> Files;

    switch (Tagger) {
    case  HBottomTagger :
        if (Tag == HBackground) Files = CombinedFiles;
        if (Tag == HSignal) Files = CombinedSignalFiles;
        break;
    case HJetPairTagger:
        if (Tag == HBackground) Files = CombinedFiles;
        if (Tag == HSignal) Files = CombinedSignalFiles;
        break;
    case HJetPairReader:
        if (Tag == HBackground) Files = CombinedFiles;
        if (Tag == HSignal) Files = CombinedSignalFiles;
        break;
    case HWSemiTagger:
        if (Tag == HBackground) Files = SemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    case HWTagger:
        if (Tag == HBackground) Files = NotLeptonicFiles;
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        break;
    case HWReader:
        if (Tag == HBackground) Files = NotLeptonicFiles;
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        break;
    case HTopLeptonicTagger:
        if (Tag == HBackground) Files = LeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HTopLeptonicReader:
        if (Tag == HBackground) Files = LeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HTopHadronicTagger:
        if (Tag == HBackground) Files = NotLeptonicFiles;
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        break;
    case HTopSemiTagger:
        if (Tag == HBackground) Files = SemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    case HTopHadronicReader:
        if (Tag == HBackground) Files = NotLeptonicFiles;
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        break;
    case HTopSemiReader:
        if (Tag == HBackground) Files = SemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    case HHeavyHiggsLeptonicTagger:
        if (Tag == HBackground) Files = LeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HHeavyHiggsLeptonicReader:
        if (Tag == HBackground) Files = LeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HHeavyHiggsHadronicTagger:
        if (Tag == HBackground) Files = HadronicFiles;
        if (Tag == HSignal) Files = SignalHadronicFiles;
        break;
    case HHeavyHiggsSemiTagger:
        if (Tag == HBackground) Files = BackgroundSemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    case HHeavyHiggsSemiReader:
        if (Tag == HBackground) Files = BackgroundSemiFiles;
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
    case HEventLeptonicReader:
        if (Tag == HBackground) Files = BackgroundLeptonicFiles;
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        break;
    case HEventSemiReader:
        if (Tag == HBackground) Files = BackgroundSemiFiles;
        if (Tag == HSignal) Files = SignalSemiFiles;
        break;
    default:
        Print(HError, "unknown tagger name");
    }

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix(".root");

    Print(HNotification, "Files prepared");

    HStrings SignalLeptonicTrees {
//         "400GeV_h2bb_llbbbb-run_01",
//         "600GeV_h2bb_llbbbb-run_01",
//         "800GeV_h2bb_llbbbb-run_01",
//         "1000GeV_h2bb_llbbbb-run_01",
//         "1500GeV_h2bb_llbbbb-run_01",
//         "2000GeV_h2bb_llbbbb-run_01",
//         "2500GeV_h2bb_llbbbb-run_01",
//         "3000GeV_h2bb_llbbbb-run_01"
    };
    HStrings BackgroundLeptonicTrees {
//         "BG_ttbb_llbbbb-run_01",
//         "BG_ttcc_llbbcc-run_01"
    };

    HStrings SignalSemiTrees {
//         "400GeV_h2bb_ljbbbb-run_01",
//         "600GeV_h2bb_ljbbbb-run_01",
//         "800GeV_h2bb_ljbbbb-run_01",
        "1000GeV_h2bb_ljbbbb-run_01",
//         "1500GeV_h2bb_ljbbbb-run_01",
//         "2000GeV_h2bb_ljbbbb-run_01",
//         "2500GeV_h2bb_ljbbbb-run_01",
//         "3000GeV_h2bb_ljbbbb-run_01"
    };

    HStrings BackgroundSemiTrees {
        "BG_ttbb_ljbbbb-run_01",
//         "BG_ttcc_ljbbcc-run_01"
    };

    HStrings SignalHadronicTree {
//       "1TeV_h2bb_jjbbbb-run_01"
    };
    HStrings BackgroundHadronicTrees {
//       "BG_jjbbbb-run_01"
    };


    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);


    BottomTagger = new hanalysis::HBottomTagger();
    BottomTagger->SetAnalysisName(GetProjectName());
    BottomTagger->SetSignalTreeNames(CombinedTrees);
    BottomTagger->SetBackgroundTreeNames(CombinedTrees);
    if (Tagger == HBottomTagger) return Files;
    BottomReader = new hanalysis::HReader(BottomTagger);

    JetPairTagger = new hanalysis::HJetPairTagger(BottomTagger);
    JetPairTagger->SetAnalysisName(GetProjectName());
    JetPairTagger->SetSignalTreeNames(CombinedTrees);
    JetPairTagger->SetBackgroundTreeNames(CombinedTrees);
    if (Tagger == HJetPairTagger)  return Files;
    JetPairReader = new hanalysis::HReader(JetPairTagger);
    if (Tagger == HJetPairReader)  return Files;

    WTagger = new hanalysis::HWTagger(BottomTagger);
    WTagger->SetAnalysisName(GetProjectName());
    WTagger->SetSignalTreeNames(NotLeptonicTrees);
    WTagger->SetBackgroundTreeNames(NotLeptonicTrees);
    if (Tagger == HWTagger)  return Files;
    WReader = new hanalysis::HReader(WTagger);
    if (Tagger == HWReader) return Files;

    if (Tagger == HTopLeptonicTagger || Tagger == HTopLeptonicReader || Tagger == HHeavyHiggsLeptonicTagger || Tagger == HEventLeptonicTagger || Tagger == HHeavyHiggsLeptonicReader || Tagger == HEventLeptonicReader) {

        TopLeptonicTagger = new hanalysis::HTopLeptonicTagger(BottomTagger);
        TopLeptonicTagger->SetAnalysisName(GetProjectName());
        TopLeptonicTagger->SetSignalTreeNames(LeptonicTrees);
        TopLeptonicTagger->SetBackgroundTreeNames(LeptonicTrees);
        if (Tagger == HTopLeptonicTagger)  return Files;
        TopLeptonicReader = new hanalysis::HReader(TopLeptonicTagger);
        if (Tagger == HTopLeptonicReader) return Files;

        HeavyHiggsLeptonicTagger = new hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
        HeavyHiggsLeptonicTagger->SetAnalysisName(GetProjectName());
        HeavyHiggsLeptonicTagger->SetSignalTreeNames(SignalLeptonicTrees);
        HeavyHiggsLeptonicTagger->SetBackgroundTreeNames(LeptonicTrees);
        if (Tagger == HHeavyHiggsLeptonicTagger)  return Files;
        HeavyHiggsLeptonicReader = new hanalysis::HReader(HeavyHiggsLeptonicTagger);
        if (Tagger == HHeavyHiggsLeptonicReader)  return Files;

        EventLeptonicTagger = new hheavyhiggs::HEventLeptonicTagger(BottomTagger, JetPairTagger, TopLeptonicTagger, HeavyHiggsLeptonicTagger);
        EventLeptonicTagger->SetAnalysisName(GetProjectName());
        EventLeptonicTagger->SetSignalTreeNames(SignalLeptonicTrees);
        EventLeptonicTagger->SetBackgroundTreeNames(BackgroundLeptonicTrees);
        if (Tagger == HEventLeptonicTagger)  return Files;
        EventLeptonicReader = new hanalysis::HReader(EventLeptonicTagger);


        Print(HError, "Tree names set");
        return Files;

    }

    if (Tagger == HWSemiTagger || Tagger == HTopSemiTagger || Tagger == HTopSemiReader || Tagger == HHeavyHiggsSemiTagger  || Tagger == HHeavyHiggsSemiReader || Tagger == HEventSemiTagger || Tagger == HEventSemiReader) {

        WSemiTagger = new hanalysis::HWSemiTagger();
        WSemiTagger->SetAnalysisName(GetProjectName());
        WSemiTagger->SetSignalTreeNames(SemiTrees);
        WSemiTagger->SetBackgroundTreeNames(SemiTrees);
        if (Tagger == HWSemiTagger) return Files;
        WSemiReader = new hanalysis::HReader(WSemiTagger);

        TopHadronicTagger = new hanalysis::HTopHadronicTagger(BottomTagger, WTagger);
        TopHadronicTagger->SetAnalysisName(GetProjectName());
        TopHadronicTagger->SetSignalTreeNames(NotLeptonicTrees);
        TopHadronicTagger->SetBackgroundTreeNames(NotLeptonicTrees);
        if (Tagger == HTopHadronicTagger)  return Files;
        TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);


        TopSemiTagger = new hanalysis::HTopSemiTagger(BottomTagger, WSemiTagger);
        TopSemiTagger->SetAnalysisName(GetProjectName());
        TopSemiTagger->SetSignalTreeNames(SemiTrees);
        TopSemiTagger->SetBackgroundTreeNames(SemiTrees);
        if (Tagger == HTopSemiTagger) return Files;
        TopSemiReader = new hanalysis::HReader(TopSemiTagger);
        if (Tagger == HTopSemiReader) return Files;

        HeavyHiggsSemiTagger = new hanalysis::HHeavyHiggsSemiTagger(BottomTagger, WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger);
        HeavyHiggsSemiTagger->SetAnalysisName(GetProjectName());
        HeavyHiggsSemiTagger->SetSignalTreeNames(SignalSemiTrees);
        HeavyHiggsSemiTagger->SetBackgroundTreeNames(BackgroundSemiTrees);
        if (Tagger == HHeavyHiggsSemiTagger)  return Files;
        HeavyHiggsSemiReader = new hanalysis::HReader(HeavyHiggsSemiTagger);
        if (Tagger == HHeavyHiggsSemiReader) return Files;

        EventSemiTagger = new hheavyhiggs::HEventSemiTagger(BottomTagger, JetPairTagger, WSemiTagger, WTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
        EventSemiTagger->SetAnalysisName(GetProjectName());
        EventSemiTagger->SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger->SetBackgroundTreeNames(BackgroundSemiTrees);
        if (Tagger == HEventSemiTagger)  return Files;
        EventSemiReader = new hanalysis::HReader(EventSemiTagger);

        Print(HError, "Tree names set");
        return Files;
    }

    if (Tagger == HTopHadronicTagger || Tagger == HTopHadronicReader || Tagger == HHeavyHiggsHadronicTagger || Tagger == HEventHadronicTagger) {

        TopHadronicTagger = new hanalysis::HTopHadronicTagger(BottomTagger, WTagger);
        TopHadronicTagger->SetAnalysisName(GetProjectName());
        TopHadronicTagger->SetSignalTreeNames(NotLeptonicTrees);
        TopHadronicTagger->SetBackgroundTreeNames(NotLeptonicTrees);
        if (Tagger == HTopHadronicTagger)  return Files;
        TopHadronicReader = new hanalysis::HReader(TopHadronicTagger);
        if (Tagger == HTopHadronicReader)  return Files;

        HeavyHiggsHadronicTagger = new hanalysis::HHeavyHiggsHadronicTagger(BottomTagger, WTagger, TopHadronicTagger);
        HeavyHiggsHadronicTagger->SetAnalysisName(GetProjectName());
        HeavyHiggsHadronicTagger->SetSignalTreeNames(SignalHadronicTree);
        HeavyHiggsHadronicTagger->SetBackgroundTreeNames(HadronicTrees);
        if (Tagger == HHeavyHiggsHadronicTagger)  return Files;

        EventHadronicTagger = new hheavyhiggs::HEventHadronicTagger(BottomTagger, WTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
        EventHadronicTagger->SetAnalysisName(GetProjectName());
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
        JetPairBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventJetPairBranch::Class());
        break;
    case HJetPairReader :
        JetPairReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventJetPairBranch::Class());
        break;
    case HWSemiTagger :
        WSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWTagger :
        WBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HWReader :
        WReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HTopLeptonicTagger :
        TopLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopLeptonicReader :
        TopLeptonicReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopHadronicTagger :
        TopHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiTagger :
        TopSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HTopHadronicReader :
        TopHadronicReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiReader :
        TopSemiReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HHeavyHiggsLeptonicTagger :
        HeavyHiggsLeptonicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsLeptonicReader:
        HeavyHiggsLeptonicReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsHadronicTagger :
        HeavyHiggsHadronicBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
        break;
    case HHeavyHiggsSemiTagger :
        HeavyHiggsSemiBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
        break;
    case HHeavyHiggsSemiReader :
        HeavyHiggsSemiReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
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
    case HEventSemiReader :
        EventSemiReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventSemiBranch::Class());
        break;
    case HEventLeptonicReader :
        EventLeptonicReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
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
    case HJetPairReader :
        return GetJetPairReader(Event, Tag);
    case HWTagger :
        return GetWTag(Event, Tag);
    case HWReader :
        return GetWReader(Event, Tag);
    case HWSemiTagger :
        return GetWSemiTag(Event, Tag);
    case HTopLeptonicTagger :
        return GetTopLeptonicTag(Event, Tag);
    case HTopHadronicTagger :
        return GetTopHadronicTag(Event, Tag);
    case HTopSemiTagger :
        return GetTopSemiTag(Event, Tag);
    case HTopHadronicReader :
        return GetTopHadronicReader(Event, Tag);
    case HTopLeptonicReader :
        return GetTopLeptonicReader(Event, Tag);
    case HTopSemiReader :
        return GetTopSemiReader(Event, Tag);
    case HHeavyHiggsLeptonicTagger :
        return GetHeavyHiggsLeptonicTag(Event, Tag);
    case HHeavyHiggsHadronicTagger :
        return GetHeavyHiggsHadronicTag(Event, Tag);
    case HHeavyHiggsSemiTagger :
        return GetHeavyHiggsSemiTag(Event, Tag);
    case HHeavyHiggsSemiReader :
        return GetHeavyHiggsSemiReader(Event, Tag);
    case HHeavyHiggsLeptonicReader :
        return GetHeavyHiggsLeptonicReader(Event, Tag);
    case HEventLeptonicTagger :
        return GetEventLeptonicTag(Event, Tag);
    case HEventHadronicTagger :
        return GetEventHadronicTag(Event, Tag);
    case HEventSemiTagger :
        return GetEventSemiTag(Event, Tag);
    case HEventSemiReader :
        return GetEventSemiReader(Event, Tag);
    case HEventLeptonicReader :
        return GetEventLeptonicReader(Event, Tag);
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Tag", Tag);
    std::vector<HBottomBranch *> Bottoms = BottomTagger->GetBranches(Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetJetPairTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Tag", Tag);
    std::vector<HEventJetPairBranch *> JetPairs = JetPairTagger->GetBranches(Event, Tag);
    if (JetPairs.size() < 1) return 0;
    for (const auto & JetPair : JetPairs) {
        HEventJetPairBranch *NewJetPairBranch = static_cast<HEventJetPairBranch *>(JetPairBranch->NewEntry());
        *NewJetPairBranch = *JetPair;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetJetPairReader(hanalysis::HEvent *const Event, const HTag Tag)
{
  Print(HDebug, "Get JetPair Reader", Tag);
  HJets Jets = Event->GetJets()->GetStructuredJets();
  Jets = BottomTagger->GetBdt(Jets, BottomReader);
  std::vector<hanalysis::HDoublet> Doublets = JetPairTagger->GetBdt(Jets, JetPairReader);

  if (Doublets.size() > 1) {
    std::sort(Doublets.begin(), Doublets.end());
    Doublets.erase(Doublets.begin() + 1, Doublets.end());
  }

  for (const auto & Doublet : Doublets) {
    HEventJetPairBranch *JetPair = new HEventJetPairBranch();
    HEventJetPairBranch *JetPairBranchTagger = static_cast<HEventJetPairBranch *>(JetPairReaderBranch->NewEntry());
    JetPairTagger->FillBranch(JetPair, Doublet);
    *JetPairBranchTagger = *JetPair;
  }

  return 1;

}

bool hheavyhiggs::HAnalysisMva::GetWSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch *> WSemis = WSemiTagger->GetBranches(Event, Tag);
    if (WSemis.size() < 1) return 0;
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
    if (Ws.size() < 1) return 0;
    for (const auto & W : Ws) {
        HWBranch *NewWBranch = static_cast<HWBranch *>(WBranch->NewEntry());
        *NewWBranch = *W;
    }
    return 1;
}




bool hheavyhiggs::HAnalysisMva::GetWReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);


    std::vector<hanalysis::HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HWBranch *W = new HWBranch();
        HWBranch *TopTagger = static_cast<HWBranch *>(WReaderBranch->NewEntry());
        WTagger->FillBranch(W, Doublet);
        *TopTagger = *W;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get leptonic top", Tag);
    std::vector<HTopLeptonicBranch *> Tops = TopLeptonicTagger->GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        HTopLeptonicBranch *TopTagger = static_cast<HTopLeptonicBranch *>(TopLeptonicBranch->NewEntry());
        *TopTagger = *Top;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetTopLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HTopLeptonicBranch *Top = new HTopLeptonicBranch();
        HTopLeptonicBranch *TopTagger = static_cast<HTopLeptonicBranch *>(TopLeptonicReaderBranch->NewEntry());
        TopLeptonicTagger->FillBranch(Top, Doublet);
        *TopTagger = *Top;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get hadronic tops", Tag);
    std::vector<HTopHadronicBranch *> Tops = TopHadronicTagger->GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
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
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        HTopSemiBranch *TopTagger = static_cast<HTopSemiBranch *>(TopSemiBranch->NewEntry());
        *TopTagger = *Top;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetTopHadronicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);


    std::vector<hanalysis::HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger->GetBdt(Doublets, Jets, TopHadronicReader);


    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *Top = new HTopHadronicBranch();
        HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(TopHadronicReaderBranch->NewEntry());
        TopHadronicTagger->FillBranch(Top, Triplet);
        *TopTagger = *Top;
    }

    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetTopSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HError, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger->GetBdt(Doublets, Jets,MissingEt, TopSemiReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        HTopSemiBranch *Top = new HTopSemiBranch();
        HTopSemiBranch *TopTagger = static_cast<HTopSemiBranch *>(TopSemiReaderBranch->NewEntry());
        TopSemiTagger->FillBranch(Top, Triplet);
        *TopTagger = *Top;
    }

    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic Heavy Higgs Tag", Tag);
    std::vector<HHeavyHiggsLeptonicBranch *> Higgses = HeavyHiggsLeptonicTagger->GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) {
        HHeavyHiggsLeptonicBranch *HiggsTagger = static_cast<HHeavyHiggsLeptonicBranch *>(HeavyHiggsLeptonicBranch->NewEntry());
        *HiggsTagger = *Higgs;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger->GetBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) {
        HHeavyHiggsLeptonicBranch *Higgs = new HHeavyHiggsLeptonicBranch();
        HHeavyHiggsLeptonicBranch *HiggsTagger = static_cast<HHeavyHiggsLeptonicBranch *>(HeavyHiggsLeptonicReaderBranch->NewEntry());
        HeavyHiggsLeptonicTagger->FillBranch(Higgs, Sextet);
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

bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets,MissingEt, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger->GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) {
        HHeavyHiggsSemiBranch *Higgs = new HHeavyHiggsSemiBranch();
        HHeavyHiggsSemiBranch *HiggsTagger = static_cast<HHeavyHiggsSemiBranch *>(HeavyHiggsSemiReaderBranch->NewEntry());
        HeavyHiggsSemiTagger->FillBranch(Higgs, Sextet);
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



bool hheavyhiggs::HAnalysisMva::GetEventSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger->GetBdt(Jets, JetPairReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger->GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger->GetBdt(DoubletsSemi, Jets,MissingEt, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WTagger->GetBdt(Jets, WReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger->GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger->GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();

    std::vector<HOctet> Octets = EventSemiTagger->GetBdt(Sextets, Doublets, Jets,  EventStruct, EventSemiReader);
    if (Octets.size() < 1) return 0;
    Octets.front().SetTag(Tag);

    hheavyhiggs::HEventSemiBranch *SemiEvent = new hheavyhiggs::HEventSemiBranch();
    EventSemiTagger->FillBranch(SemiEvent, Octets.front());

    HEventSemiBranch *NewEventBranch = static_cast<HEventSemiBranch *>(EventSemiReaderBranch->NewEntry());
    *NewEventBranch = *SemiEvent;

//     Print(HError, "Bdt", Octet.GetBdt());

    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetEventLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic reader", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger->GetBdt(Jets, BottomReader);

    Print(HInformation, "Jet Pair");

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger->GetBdt(Jets, JetPairReader);

    Print(HInformation, "Top");
    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> LeptonicDoublets = TopLeptonicTagger->GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger->GetBdt(LeptonicDoublets, MissingEt, HeavyHiggsLeptonicReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();

    std::vector<HOctet> Octets = EventLeptonicTagger->GetBdt(Sextets, Doublets, Jets, EventStruct, EventLeptonicReader);
    if (Octets.size() < 1) return 0;
    Octets.front().SetTag(Tag);

    hheavyhiggs::HEventLeptonicBranch *LeptonicEvent = new hheavyhiggs::HEventLeptonicBranch();
    EventLeptonicTagger->FillBranch(LeptonicEvent, Octets.front());

    HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(EventLeptonicReaderBranch->NewEntry());
    *NewEventBranch = *LeptonicEvent;

    return 1;
}

