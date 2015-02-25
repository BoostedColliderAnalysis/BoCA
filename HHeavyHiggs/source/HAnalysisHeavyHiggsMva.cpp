# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    BottomTagger.SetAnalysisName(ProjectName());
    JetPairTagger.SetAnalysisName(ProjectName());
    WHadronicTagger.SetAnalysisName(ProjectName());
    WSemiTagger.SetAnalysisName(ProjectName());
    TopHadronicTagger.SetAnalysisName(ProjectName());
    TopSemiTagger.SetAnalysisName(ProjectName());
    HeavyHiggsSemiTagger.SetAnalysisName(ProjectName());
    SignatureSemiTagger.SetAnalysisName(ProjectName());
    EventSemiTagger.SetAnalysisName(ProjectName());
}

std::string hheavyhiggs::HAnalysisMva::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
{
    Print(HNotification, "Get Study Names", Tagger);

    switch (Tagger) {
    case  HBottomTagger :
        return "Bottom";
    case  HBottomReader :
        return "BottomReader";
    case HWSemiTagger:
        return  "WSemi";
    case HWSemiReader:
        return  "WSemiReader";
    case HWHadronicTagger:
        return  "WHadronic";
    case HWHadronicReader:
        return  "WHadronicReader";
    case HJetPairTagger:
        return  "JetPair";
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
    case HEventLeptonicReader:
        return  "EventLeptonicReader";
    case HSignatureSemiTagger:
        return  "SignatureSemi";
    case HSignatureSemiReader:
        return  "SignatureSemiReader";
    case HEventSemiTagger:
        return  "EventSemi";
    case HEventSemiReader:
        return  "EventSemiReader";
    default :
        Print(HError, "unexpected TaggerName", Tagger);
        return "";
    }
}

std::vector<hanalysis::HFile> hheavyhiggs::HAnalysisMva::Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag)
{
    Print(HNotification, "Set File Vector", Tagger, Tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;
    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::HFile> SignalSemiFiles;
    std::vector<hanalysis::HFile> BackgroundSemiFiles;

    // LHC

//     SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-14TeV-400GeV", 15.457345846238557, 400));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-14TeV-500GeV",10.57186928542166,500));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-14TeV-1000GeV",0.6300105025483057,1000));
//     SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-14TeV-2000GeV",0.011364910695033002,2000));


    //     HStrings BG1 = {"ttbb-ljbbbb-14TeV-80pt_0", "ttbb-ljbbbb-14TeV-80pt_1", "ttbb-ljbbbb-14TeV-80pt_2", "ttbb-ljbbbb-14TeV-80pt_3", "ttbb-ljbbbb-14TeV-80pt_4"}; // LHC 80
    //     BackgroundSemiFiles.push_back(hanalysis::HFile(BG1 , 89.32)); // LHC 80
    //     HStrings BG2 = {"ttcc-ljbbcc-14TeV-80pt_0", "ttcc-ljbbcc-14TeV-80pt_1", "ttcc-ljbbcc-14TeV-80pt_2", "ttcc-ljbbcc-14TeV-80pt_3", "ttcc-ljbbcc-14TeV-80pt_4"}; // LHC 80
    //     BackgroundSemiFiles.push_back(hanalysis::HFile(BG2 , 78.42)); // LHC 80

//     HStrings BG1 = {"ttbb-ljbbbb-14TeV-30pt_0", "ttbb-ljbbbb-14TeV-30pt_1", "ttbb-ljbbbb-14TeV-30pt_2", "ttbb-ljbbbb-14TeV-30pt_3", "ttbb-ljbbbb-14TeV-30pt_4", "ttbb-ljbbbb-14TeV-30pt_5", "ttbb-ljbbbb-14TeV-30pt_6", "ttbb-ljbbbb-14TeV-30pt_7", "ttbb-ljbbbb-14TeV-30pt_8", "ttbb-ljbbbb-14TeV-30pt_9"}; // LHC 30
//     BackgroundSemiFiles.push_back(hanalysis::HFile(BG1 , 298.2)); // LHC 30
//     HStrings BG2 = {"ttcc-ljbbcc-14TeV-30pt_0", "ttcc-ljbbcc-14TeV-30pt_1", "ttcc-ljbbcc-14TeV-30pt_2", "ttcc-ljbbcc-14TeV-30pt_3", "ttcc-ljbbcc-14TeV-30pt_4", "ttcc-ljbbcc-14TeV-30pt_5", "ttcc-ljbbcc-14TeV-30pt_6", "ttcc-ljbbcc-14TeV-30pt_7", "ttcc-ljbbcc-14TeV-30pt_8", "ttcc-ljbbcc-14TeV-30pt_9"}; // LHC 30
//     BackgroundSemiFiles.push_back(hanalysis::HFile(BG2 , 264.6)); // LHC 30

// 100 TeV

    SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-400GeV", 465.78976127779805, 400));
//    SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-500GeV",403.1726637894434,500));
//     SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-600GeV",272.6441648068077,600));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-1000GeV",60.62802137818876,1000));
//     SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-1500GeV",14.625345866484361,1500));
//     SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-2000GeV", 4.920796866551275, 2000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-3000GeV",0.9234071865754303,3000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-4000GeV",0.25736547733711523,4000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-5000GeV",0.08899831451027759,5000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-6000GeV",0.03602204622881514,6000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-7000GeV",0.01576206604679042,7000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-8000GeV",0.0076693087930297206, 8000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-9000GeV",0.0039008532687324735,9000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-10000GeV",0.002076042904956223,10000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-12000GeV",0.0006621537122277095,12000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-15000GeV",0.0001442241864611344,15000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-20000GeV",0.000015425841205626978, 20000));

//             HStrings BG1 = {"ttbb-ljbbbb-100TeV-300pt_0", "ttbb-ljbbbb-100TeV-300pt_1"}; // 100TeV 300 GeV
//             BackgroundSemiFiles.push_back(hanalysis::HFile( BG1 , 35.04)); // 100 TeV 300 GeV
//             HStrings BG2 = {"ttcc-ljbbcc-100TeV-300pt_0", "ttcc-ljbbcc-100TeV-300pt_1"}; // 100 TeV 300 GeV
//             BackgroundSemiFiles.push_back(hanalysis::HFile( BG2 , 30.72)); // 100 TeV 300 GeV


    HStrings BG1_150 = {"ttbb-ljbbbb-100TeV-150pt_0", "ttbb-ljbbbb-100TeV-150pt_1", "ttbb-ljbbbb-100TeV-150pt_2", "ttbb-ljbbbb-100TeV-150pt_3"}; // 100TeV 150 GeV
    BackgroundSemiFiles.push_back(hanalysis::HFile(BG1_150 , 605.199003171 * 2)); // 100TeV 150 GeV
    HStrings BG2_150 = {"ttcc-ljbbcc-100TeV-150pt_0", "ttcc-ljbbcc-100TeV-150pt_1", "ttcc-ljbbcc-100TeV-150pt_2", "ttcc-ljbbcc-100TeV-150pt_3"}; // 100TeV 150 GeV
    BackgroundSemiFiles.push_back(hanalysis::HFile(BG2_150 , 468.061778817 * 2)); // 100TeV 150 GeV
    HStrings BG3_150 = {"ttjj-ljbbjj-100TeV-150pt_0", "ttjj-ljbbjj-100TeV-150pt_1", "ttjj-ljbbjj-100TeV-150pt_2", "ttjj-ljbbjj-100TeV-150pt_3"}; // 100TeV 150 GeV
    BackgroundSemiFiles.push_back(hanalysis::HFile(BG3_150 , 61.9287096863 * 2 * 1000)); // 100TeV 150 GeV

//     HStrings BG1_80 = {"ttbb-ljbbbb-100TeV-80pt_0", "ttbb-ljbbbb-100TeV-80pt_1", "ttbb-ljbbbb-100TeV-80pt_2", "ttbb-ljbbbb-100TeV-80pt_3", "ttbb-ljbbbb-100TeV-80pt_4"}; // 100TeV 80 GeV
//     BackgroundSemiFiles.push_back(hanalysis::HFile(BG1_80 , 1171.6));  // 100TeV 80 GeV
//     HStrings BG2_80 = {"ttcc-ljbbcc-100TeV-80pt_0", "ttcc-ljbbcc-100TeV-80pt_1", "ttcc-ljbbcc-100TeV-80pt_2", "ttcc-ljbbcc-100TeV-80pt_3", "ttcc-ljbbcc-100TeV-80pt_4"}; // 100TeV 80 GeV
//     BackgroundSemiFiles.push_back(hanalysis::HFile(BG2_80 , 1042.0));  // 100TeV 80 GeV

//     HStrings BG1_80 = {"ttbb-ljbbbb-100TeV-30pt_0", "ttbb-ljbbbb-100TeV-30pt_1", "ttbb-ljbbbb-100TeV-30pt_2", "ttbb-ljbbbb-100TeV-30pt_3", "ttbb-ljbbbb-100TeV-30pt_4"}; // 100TeV 30 GeV
//     BackgroundSemiFiles.push_back(hanalysis::HFile(BG1_80 , 2990));  // 100TeV 30 GeV
//     HStrings BG2_80 = {"ttcc-ljbbcc-100TeV-30pt_0", "ttcc-ljbbcc-100TeV-30pt_1", "ttcc-ljbbcc-100TeV-30pt_2", "ttcc-ljbbcc-100TeV-30pt_3", "ttcc-ljbbcc-100TeV-30pt_4"}; // 100TeV 30 GeV
//                 BackgroundSemiFiles.push_back(hanalysis::HFile(BG2_80 , 2684));  // 100TeV 30 GeV


//             SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-H-1000GeV",60.62802137818876,1000));
//             SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-A-1000GeV",60.62802137818876,1000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-H-5000GeV",0.08899831451027759,5000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-A-5000GeV",0.08899831451027759,5000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-H-10000GeV",0.002076042904956223,10000));
// SignalSemiFiles.push_back(hanalysis::HFile("H0bb-ljbbbb-100TeV-A-10000GeV",0.002076042904956223,10000));

    std::vector<hanalysis::HFile> SignalHadronicFiles;

    std::vector<hanalysis::HFile> BackgroundHadronicFiles;

    std::vector<hanalysis::HFile> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::HFile> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::HFile> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::HFile> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::HFile> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);

    std::vector<hanalysis::HFile> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::HFile> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::HFile> NewFiles;

    switch (Tagger) {
    case  HBottomTagger :
        NewFiles = CombinedFiles;
        break;
    case  HBottomReader :
        NewFiles = CombinedFiles;
        break;
    case HJetPairTagger:
        if (Tag == HSignal) NewFiles = CombinedSignalFiles;
        else NewFiles = CombinedFiles;
        break;
    case HJetPairReader:
        if (Tag == HSignal) NewFiles = CombinedSignalFiles;
        else NewFiles = CombinedFiles;
        break;
    case HWSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = SemiFiles;
        break;
    case HWSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = SemiFiles;
        break;
    case HWHadronicTagger:
        if (Tag == HSignal) NewFiles = NonLeptonicSignalFiles;
        else NewFiles = NotLeptonicFiles;
        break;
    case HWHadronicReader:
        if (Tag == HSignal) NewFiles = NonLeptonicSignalFiles;
        else NewFiles = NotLeptonicFiles;
        break;
    case HTopLeptonicTagger:
        if (Tag == HSignal) NewFiles = SignalLeptonicFiles;
        else NewFiles = LeptonicFiles;
        break;
    case HTopLeptonicReader:
        if (Tag == HSignal) NewFiles = SignalLeptonicFiles;
        else NewFiles = LeptonicFiles;
        break;
    case HTopHadronicTagger:
        if (Tag == HSignal) NewFiles = NonLeptonicSignalFiles;
        else NewFiles = NotLeptonicFiles;
        break;
    case HTopSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = SemiFiles;
        break;
    case HTopHadronicReader:
        if (Tag == HSignal) NewFiles = NonLeptonicSignalFiles;
        else NewFiles = NotLeptonicFiles;
        break;
    case HTopSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = SemiFiles;
        break;
    case HHeavyHiggsLeptonicTagger:
        if (Tag == HSignal) NewFiles = SignalLeptonicFiles;
        else NewFiles = LeptonicFiles;
        break;
    case HHeavyHiggsLeptonicReader:
        if (Tag == HSignal) NewFiles = SignalLeptonicFiles;
        else NewFiles = LeptonicFiles;
        break;
    case HHeavyHiggsHadronicTagger:
        if (Tag == HSignal) NewFiles = SignalHadronicFiles;
        else NewFiles = HadronicFiles;
        break;
    case HHeavyHiggsSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HHeavyHiggsSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HEventLeptonicTagger:
        if (Tag == HSignal) NewFiles = SignalLeptonicFiles;
        else NewFiles = BackgroundLeptonicFiles;
        break;
    case HEventHadronicTagger:
        if (Tag == HSignal) NewFiles = SignalHadronicFiles;
        else NewFiles = BackgroundHadronicFiles;
        break;
    case HEventLeptonicReader:
        if (Tag == HSignal) NewFiles = SignalLeptonicFiles;
        else NewFiles = BackgroundLeptonicFiles;
        break;
    case HSignatureSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HSignatureSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HEventSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HEventSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    default:
        Print(HError, "unknown tagger name");
    }

    NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
    NewFiles.front().SetFileSuffix(".root");
    SetTrees(Tagger, Tag);
    PrepareReader(Tagger, Tag);
    return NewFiles;

}


void hheavyhiggs::HAnalysisMva::SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag)
{

    HStrings SignalLeptonicTrees {};
    HStrings BackgroundLeptonicTrees {};

    HStrings SignalSemiTrees {

        // LHC

//         "H0bb-ljbbbb-14TeV-400GeV-run_01"
//               "H0bb-ljbbbb-14TeV-500GeV-run_01"
//               "H0bb-ljbbbb-14TeV-1000GeV-run_01"
//       "H0bb-ljbbbb-14TeV-2000GeV-run_01"

        // 100TeV

        "H0bb-ljbbbb-100TeV-400GeV-run_01"
//               "H0bb-ljbbbb-100TeV-500GeV-run_01"
//               "H0bb-ljbbbb-100TeV-600GeV-run_01"
//               "H0bb-ljbbbb-100TeV-1000GeV-run_01"
//               "H0bb-ljbbbb-100TeV-1500GeV-run_01"
//         "H0bb-ljbbbb-100TeV-2000GeV-run_01"
//                 "H0bb-ljbbbb-100TeV-3000GeV-run_01"
//                 "H0bb-ljbbbb-100TeV-4000GeV-run_01"
//                 "H0bb-ljbbbb-100TeV-5000GeV-run_01"
        //         "H0bb-ljbbbb-100TeV-6000GeV-run_01"
        //         "H0bb-ljbbbb-100TeV-7000GeV-run_01"
        //         "H0bb-ljbbbb-100TeV-8000GeV-run_01"
        //         "H0bb-ljbbbb-100TeV-9000GeV-run_01"
//                 "H0bb-ljbbbb-100TeV-10000GeV-run_01"
        //         "H0bb-ljbbbb-100TeV-12000GeV-run_01"
//                 "H0bb-ljbbbb-100TeV-15000GeV-run_01"
//                 "H0bb-ljbbbb-100TeV-20000GeV-run_01"

        // separated

//               "H0bb-ljbbbb-100TeV-H-1000GeV-run_01"
//               "H0bb-ljbbbb-100TeV-A-1000GeV-run_01"
//               "H0bb-ljbbbb-100TeV-H-5000GeV-run_01"
        //               "H0bb-ljbbbb-100TeV-A-5000GeV-run_01"
//                     "H0bb-ljbbbb-100TeV-H-10000GeV-run_01"
//                     "H0bb-ljbbbb-100TeV-A-10000GeV-run_01"
    };

    HStrings BackgroundSemiTrees {
//         "ttbb-ljbbbb-14TeV-80pt_0-run_01",
        //         "ttcc-ljbbcc-14TeV-80pt_0-run_01"
//               "ttbb-ljbbbb-14TeV-30pt_0-run_01",
//               "ttcc-ljbbcc-14TeV-30pt_0-run_01"
//                 "ttbb-ljbbbb-100TeV-300pt_0-run_01",
//                 "ttcc-ljbbcc-100TeV-300pt_0-run_01"
        "ttbb-ljbbbb-100TeV-150pt_0-run_01",
        "ttcc-ljbbcc-100TeV-150pt_0-run_01",
        "ttjj-ljbbjj-100TeV-150pt_0-run_01",
//         "ttbb-ljbbbb-100TeV-80pt_0-run_01",
//         "ttcc-ljbbcc-100TeV-80pt_0-run_01"
//         "ttbb-ljbbbb-100TeV-30pt_0-run_01",
//         "ttcc-ljbbcc-100TeV-30pt_0-run_01"
    };

    HStrings SignalHadronicTree {};
    HStrings BackgroundHadronicTrees {};

    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);

    switch (Tagger) {
    case HBottomTagger:
        BottomTagger.SetSignalTreeNames(CombinedTrees);
        BottomTagger.SetBackgroundTreeNames(CombinedTrees);
        if (Tag == HSignal)  BottomTagger.SetTagger();
        break;
    case HBottomReader:
        break;
    case HJetPairTagger :
        JetPairTagger.SetSignalTreeNames(CombinedTrees);
        JetPairTagger.SetBackgroundTreeNames(CombinedTrees);
        if (Tag == HSignal) JetPairTagger.SetTagger(BottomTagger);
        break;
    case HJetPairReader :
        break;
    case HWHadronicTagger:
        WHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
        WHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
        if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
        break;
    case HWHadronicReader :
        BottomTagger.SetSignalTreeNames(CombinedTrees);
        BottomTagger.SetBackgroundTreeNames(CombinedTrees);
        if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
        break;
    case HWSemiTagger :
        if (Tag == HSignal) WSemiTagger.SetTagger();
        WSemiTagger.SetSignalTreeNames(SemiTrees);
        WSemiTagger.SetBackgroundTreeNames(SemiTrees);
        break;
    case HWSemiReader :
        break;
    case HTopHadronicTagger :
        if (Tag == HSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        TopHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
        TopHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
        break;
    case HTopHadronicReader :
        break;
    case HTopSemiTagger :
        if (Tag == HSignal) TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        TopSemiTagger.SetSignalTreeNames(SemiTrees);
        TopSemiTagger.SetBackgroundTreeNames(SemiTrees);
        break;
    case HTopSemiReader :
        break;
    case HHeavyHiggsSemiTagger  :
        if (Tag == HSignal) HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        HeavyHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        HeavyHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
        break;
    case HHeavyHiggsSemiReader :
        break;
    case HSignatureSemiTagger :
        if (Tag == HSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
        SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HSignatureSemiReader :
        break;
    case HEventSemiTagger :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger, SignatureSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HEventSemiReader :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger, SignatureSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    default :
        Print(HError, "unhandeled case");
    }
}

void hheavyhiggs::HAnalysisMva::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HInformation, "Prepare Reader", Tagger);
    if (Tag == HBackground) return;
    switch (Tagger) {
    case HBottomTagger:
        break;
    case HBottomReader:
        BottomReader.SetMva(BottomTagger);
        break;
    case HWHadronicTagger:
        WHadronicTagger.BottomTagger.SetTagger();
        WHadronicTagger.BottomReader.SetMva(WHadronicTagger.BottomTagger);
        break;
    case HWHadronicReader:
        BottomReader.SetMva(BottomTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        break;
    case HWSemiTagger :
        break;
    case HWSemiReader :
        WSemiReader.SetMva(WSemiTagger);
        break;
    case HTopHadronicTagger :
        TopHadronicTagger.BottomTagger.SetTagger();
        TopHadronicTagger.BottomReader.SetMva(TopHadronicTagger.BottomTagger);
        TopHadronicTagger.WTagger.SetTagger(BottomTagger);
        TopHadronicTagger.WReader.SetMva(TopHadronicTagger.WTagger);
        break;
    case HTopHadronicReader :
        BottomReader.SetMva(BottomTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        break;
    case HTopSemiTagger :
        TopSemiTagger.BottomTagger.SetTagger();
        TopSemiTagger.BottomReader.SetMva(TopSemiTagger.BottomTagger);
        TopSemiTagger.WSemiTagger.SetTagger();
        TopSemiTagger.WSemiReader.SetMva(TopSemiTagger.WSemiTagger);
        break;
    case HTopSemiReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        break;
    case HHeavyHiggsSemiTagger :
        HeavyHiggsSemiTagger.BottomTagger.SetTagger();
        HeavyHiggsSemiTagger.BottomReader.SetMva(HeavyHiggsSemiTagger.BottomTagger);
        HeavyHiggsSemiTagger.WSemiTagger.SetTagger();
        HeavyHiggsSemiTagger.WSemiReader.SetMva(HeavyHiggsSemiTagger.WSemiTagger);
        HeavyHiggsSemiTagger.WTagger.SetTagger(BottomTagger);
        HeavyHiggsSemiTagger.WReader.SetMva(HeavyHiggsSemiTagger.WTagger);
        HeavyHiggsSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        HeavyHiggsSemiTagger.TopSemiReader.SetMva(HeavyHiggsSemiTagger.TopSemiTagger);
        HeavyHiggsSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        HeavyHiggsSemiTagger.TopHadronicReader.SetMva(HeavyHiggsSemiTagger.TopHadronicTagger);
        break;
    case HHeavyHiggsSemiReader  :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        HeavyHiggsSemiReader.SetMva(HeavyHiggsSemiTagger);
        break;
    case HJetPairTagger :
        JetPairTagger.BottomTagger.SetTagger();
        JetPairTagger.BottomReader.SetMva(JetPairTagger.BottomTagger);
        break;
    case HJetPairReader :
        BottomReader.SetMva(BottomTagger);
        JetPairReader.SetMva(JetPairTagger);
        break;
    case HSignatureSemiTagger :
        SignatureSemiTagger.BottomTagger.SetTagger();
        SignatureSemiTagger.BottomReader.SetMva(SignatureSemiTagger.BottomTagger);
        SignatureSemiTagger.WSemiTagger.SetTagger();
        SignatureSemiTagger.WSemiReader.SetMva(SignatureSemiTagger.WSemiTagger);
        SignatureSemiTagger.WTagger.SetTagger(BottomTagger);
        SignatureSemiTagger.WReader.SetMva(SignatureSemiTagger.WTagger);
        SignatureSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        SignatureSemiTagger.TopSemiReader.SetMva(SignatureSemiTagger.TopSemiTagger);
        SignatureSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        SignatureSemiTagger.TopHadronicReader.SetMva(SignatureSemiTagger.TopHadronicTagger);
        SignatureSemiTagger.HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        SignatureSemiTagger.HeavyHiggsSemiReader.SetMva(SignatureSemiTagger.HeavyHiggsSemiTagger);
        SignatureSemiTagger.JetPairTagger.SetTagger(BottomTagger);
        SignatureSemiTagger.JetPairReader.SetMva(SignatureSemiTagger.JetPairTagger);
        break;
    case HSignatureSemiReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        JetPairReader.SetMva(JetPairTagger);
        HeavyHiggsSemiReader.SetMva(HeavyHiggsSemiTagger);
        SignatureSemiReader.SetMva(SignatureSemiTagger);
        break;
    case HEventSemiTagger :
        EventSemiTagger.BottomTagger.SetTagger();
        EventSemiTagger.BottomReader.SetMva(EventSemiTagger.BottomTagger);
        EventSemiTagger.WSemiTagger.SetTagger();
        EventSemiTagger.WSemiReader.SetMva(EventSemiTagger.WSemiTagger);
        EventSemiTagger.WTagger.SetTagger(BottomTagger);
        EventSemiTagger.WReader.SetMva(EventSemiTagger.WTagger);
        EventSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        EventSemiTagger.TopSemiReader.SetMva(EventSemiTagger.TopSemiTagger);
        EventSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        EventSemiTagger.TopHadronicReader.SetMva(EventSemiTagger.TopHadronicTagger);
        EventSemiTagger.HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        EventSemiTagger.HeavyHiggsSemiReader.SetMva(EventSemiTagger.HeavyHiggsSemiTagger);
        EventSemiTagger.JetPairTagger.SetTagger(BottomTagger);
        EventSemiTagger.JetPairReader.SetMva(EventSemiTagger.JetPairTagger);
        EventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
        EventSemiTagger.SignatureSemiReader.SetMva(EventSemiTagger.SignatureSemiTagger);
        break;
    case HEventSemiReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        JetPairReader.SetMva(JetPairTagger);
        HeavyHiggsSemiReader.SetMva(HeavyHiggsSemiTagger);
        SignatureSemiReader.SetMva(SignatureSemiTagger);
        EventSemiReader.SetMva(EventSemiTagger);
        break;
    default :
        Print(HError, "unhandled case");
    }
}

void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HBottomReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HJetPairTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventJetPairBranch::Class());
        break;
    case HJetPairReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventJetPairBranch::Class());
        break;
    case HWSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWHadronicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
        break;
    case HWHadronicReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
        break;
    case HTopLeptonicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopLeptonicReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopHadronicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HTopHadronicReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HHeavyHiggsLeptonicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsLeptonicReader:
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsHadronicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
        break;
    case HHeavyHiggsSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
        break;
    case HHeavyHiggsSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
        break;
    case HEventLeptonicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    case HEventHadronicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventHadronicBranch::Class());
        break;
    case HEventLeptonicReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    case HSignatureSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HOctetBranch::Class());
        break;
    case HSignatureSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HOctetBranch::Class());
        break;
    case HEventSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventSemiBranch::Class());
        break;
    case HEventSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventSemiBranch::Class());
        break;
    default :
        Print(HError, "No Branch filled");
    }

}

bool hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HInformation, "Analysis", Tagger);
    HJets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets());
    if (Leptons.size() < 1) return 0;
//     if (Leptons.front().pt() < 300) return 0;
    if (Leptons.front().pt() < 150) return 0;
//     if (Leptons.front().pt() < 80) return 0;
//     if (Leptons.front().pt() < 30) return 0;
    ++EventSumM;

    switch (Tagger) {
    case HBottomTagger :
        return GetBottomTag(Event, Tag);
    case HBottomReader:
        return GetBottomReader(Event, Tag);
    case HJetPairTagger :
        return GetJetPairTag(Event, Tag);
    case HJetPairReader :
        return GetJetPairReader(Event, Tag);
    case HWHadronicTagger :
        return GetWTag(Event, Tag);
    case HWHadronicReader :
        return GetWReader(Event, Tag);
    case HWSemiTagger :
        return GetWSemiTag(Event, Tag);
    case HWSemiReader :
        return GetWSemiReader(Event, Tag);
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
    case HEventLeptonicReader :
        return GetEventLeptonicReader(Event, Tag);
    case HSignatureSemiTagger :
        return GetSignatureSemiTag(Event, Tag);
    case HSignatureSemiReader :
        return GetSignatureSemiReader(Event, Tag);
    case HEventSemiTagger :
        return GetEventSemiTag(Event, Tag);
    case HEventSemiReader :
        return GetEventSemiReader(Event, Tag);
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Tag", Tag);
    std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

//     Jets = static_cast<hanalysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(Jets);

    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
    }

    for (const auto & Jet : Jets) {
        if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > 2.5) continue;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetJetPairTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Tag", Tag);
    std::vector<HEventJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag);
    if (JetPairs.size() < 1) return 0;
    for (const auto & JetPair : JetPairs) *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPair;
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetJetPairReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsFamily(BottomId, GluonId)), Particles.end());
    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
    }

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(Doublet);
    return 1;

}

bool hheavyhiggs::HAnalysisMva::GetWSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
    if (WSemis.size() < 1) return 0;
    for (const auto & WSemi : WSemis) *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetWSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Reader", Tag);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);

    if (Doublets.size() < 1) return 0;

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(Doublet);
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetWTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get W Tag", Tag);
    std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
    if (Ws.size() < 1) return 0;
    for (const auto & W : Ws) *static_cast<HWBranch *>(Branch->NewEntry()) = W;
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetWReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);


    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get leptonic top", Tag);
    std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetTopLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(Doublet);
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get hadronic tops", Tag);
    std::vector<HTopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);


    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(Triplet);
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get Tops", Tag);
    std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic Heavy Higgs Tag", Tag);
    std::vector<HHeavyHiggsLeptonicBranch> Higgses = HeavyHiggsLeptonicTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry()) = Higgs;
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry())  = HeavyHiggsLeptonicTagger.GetBranch(Sextet);
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Hadronic HeavyHiggs Tag", Tag);
    std::vector<HHeavyHiggsHadronicBranch> Higgses = HeavyHiggsHadronicTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) *static_cast<HHeavyHiggsHadronicBranch *>(Branch->NewEntry()) = Higgs;
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Semi HeavyHiggs Tag", Tag);
    std::vector<HHeavyHiggsSemiBranch> Higgses = HeavyHiggsSemiTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = HeavyHiggsSemiTagger.GetBranch(Sextet);

    return 1;
}




bool hheavyhiggs::HAnalysisMva::GetEventLeptonicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event leptonic", Tag);
    std::vector<hheavyhiggs::HEventLeptonicBranch *> LeptonicEventBranches = EventLeptonicTagger.GetBranches(Event, Tag);
    if (LeptonicEventBranches.size() < 1) return 0;
    for (const auto & LeptonicEvent : LeptonicEventBranches) {
        HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(Branch->NewEntry());
        *NewEventBranch = *LeptonicEvent;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetEventHadronicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event hadronic", Tag);
    std::vector<hheavyhiggs::HEventHadronicBranch *> HadronicEvents = EventHadronicTagger.GetBranches(Event, Tag);
    if (HadronicEvents.size() < 1) return 0;
    for (const auto & HadronicEvent : HadronicEvents) {
        HEventHadronicBranch *NewEventBranch = static_cast<HEventHadronicBranch *>(Branch->NewEntry());
        *NewEventBranch = *HadronicEvent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetEventLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic reader", Tag);

    HJets Jets = Event.GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    Print(HInformation, "Jet Pair");

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    Print(HInformation, "Top");
    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> LeptonicDoublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(LeptonicDoublets, MissingEt, HeavyHiggsLeptonicReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();

    std::vector<HOctet> Octets = EventLeptonicTagger.GetBdt(Sextets, Doublets, Jets, EventStruct, EventLeptonicReader);
    if (Octets.size() < 1) return 0;
    Octets.front().SetTag(Tag);

    hheavyhiggs::HEventLeptonicBranch *LeptonicEvent = new hheavyhiggs::HEventLeptonicBranch();
    EventLeptonicTagger.FillBranch(LeptonicEvent, Octets.front());

    HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(Branch->NewEntry());
    *NewEventBranch = *LeptonicEvent;

    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetSignatureSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Signature semi", Tag);
    std::vector<hheavyhiggs::HOctetBranch> Signatures = SignatureSemiTagger.GetBranches(Event, Tag);
    if (Signatures.size() < 1) return 0;
    for (const auto & Signature : Signatures) {
        *static_cast<HOctetBranch *>(Branch->NewEntry()) = Signature;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetSignatureSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Signature Semi Reader", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Doublets, SignatureSemiReader);
    if (Octets.size() < 1) return 0;

    if (Octets.size() > 1) {
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }
    Octets.front().SetTag(Tag);

    *static_cast<HOctetBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(Octets.front());
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);
    std::vector<hheavyhiggs::HEventSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
    if (SemiEvents.size() < 1) return 0;
    for (const auto & SemiEvent : SemiEvents) {
        *static_cast<HEventSemiBranch *>(Branch->NewEntry()) = SemiEvent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Doublets, SignatureSemiReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
//   if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets()).front().pt();

    std::vector<HEventMultiplet<HOctet>> Events = EventSemiTagger.GetBdt(Octets, Jets, Leptons,  EventStruct, EventSemiReader);
    if (Events.size() < 1) return 0;
    Events.front().SetTag(Tag);

    *static_cast<HEventSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(Events.front());
    return 1;
}
