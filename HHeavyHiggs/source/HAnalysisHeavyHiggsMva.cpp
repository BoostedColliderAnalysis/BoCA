# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{
//     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    BottomTagger.SetAnalysisName(GetProjectName());
    JetPairTagger.SetAnalysisName(GetProjectName());
    WHadronicTagger.SetAnalysisName(GetProjectName());
    WSemiTagger.SetAnalysisName(GetProjectName());
    TopHadronicTagger.SetAnalysisName(GetProjectName());
    TopSemiTagger.SetAnalysisName(GetProjectName());
    HeavyHiggsSemiTagger.SetAnalysisName(GetProjectName());
    EventSemiTagger.SetAnalysisName(GetProjectName());
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
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("400GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(3.31);
    //     SignalLeptonicFiles.back()->SetMass(400);
//         SignalLeptonicFiles.push_back(new hanalysis::HFile("500GeV_Hbb_ttbb_llbbbb"));
//         SignalLeptonicFiles.back()->SetCrosssection(3.31);
//         SignalLeptonicFiles.back()->SetMass(500);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("600GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.933);
//     SignalLeptonicFiles.back()->SetMass(600);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("800GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.359);
//     SignalLeptonicFiles.back()->SetMass(800);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("1000GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.167);
//     SignalLeptonicFiles.back()->SetMass(1000);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("1500GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0379);
//     SignalLeptonicFiles.back()->SetMass(1500);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("2000GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0563);
//     SignalLeptonicFiles.back()->SetMass(2000);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("2500GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0224);
//     SignalLeptonicFiles.back()->SetMass(2500);
//     SignalLeptonicFiles.push_back(new hanalysis::HFile("3000GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back()->SetCrosssection(0.0104);
//     SignalLeptonicFiles.back()->SetMass(3000);

    std::vector<hanalysis::HFile *> BackgroundLeptonicFiles;
//     BackgroundLeptonicFiles.push_back(new hanalysis::HFile("BG_ttbb_llbbbb"));
//     BackgroundLeptonicFiles.back()->SetCrosssection(4.773);
//     BackgroundLeptonicFiles.push_back(new hanalysis::HFile("BG_ttcc_llbbcc"));
//     BackgroundLeptonicFiles.back()->SetCrosssection(4.161);

    std::vector<hanalysis::HFile *> SignalSemiFiles;
//     SignalSemiFiles.push_back(new hanalysis::HFile("400GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.4664420104710373);
//     SignalSemiFiles.back()->SetMass(400);
//     SignalSemiFiles.push_back(new hanalysis::HFile("500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.40374978749300205);
//     SignalSemiFiles.back()->SetMass(500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("600GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.27296286310330137);
//     SignalSemiFiles.back()->SetMass(600);
//     SignalSemiFiles.push_back(new hanalysis::HFile("800GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.12290283022989924);
//     SignalSemiFiles.back()->SetMass(800);
    SignalSemiFiles.push_back(new hanalysis::HFile("1000GeV_Hbb_ttbb_ljbbbb"));
    SignalSemiFiles.back()->SetCrosssection(0.06066398537600679);
    SignalSemiFiles.back()->SetMass(1000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("1500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.01463088296143972);
//     SignalSemiFiles.back()->SetMass(1500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("2000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.0049222865674137285);
//     SignalSemiFiles.back()->SetMass(2000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("2500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.0019740943034789638);
//     SignalSemiFiles.back()->SetMass(2500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("3000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.0009236377918540127);
//     SignalSemiFiles.back()->SetMass(3000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("3500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00046594405915062573);
//     SignalSemiFiles.back()->SetMass(3500);
//     SignalSemiFiles.push_back(new hanalysis::HFile("4000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.0002574230655570727);
//     SignalSemiFiles.back()->SetMass(4000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("4500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00014742115323150884);
//     SignalSemiFiles.back()->SetMass(4500);
    SignalSemiFiles.push_back(new hanalysis::HFile("5000GeV_Hbb_ttbb_ljbbbb"));
    SignalSemiFiles.back()->SetCrosssection(0.00008901729172672865);
    SignalSemiFiles.back()->SetMass(5000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("6000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.0000360296898244432);
//     SignalSemiFiles.back()->SetMass(6000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("7000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(0.00001576534159133895);
//     SignalSemiFiles.back()->SetMass(7000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("8000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(7.670893789952377e-6);
//     SignalSemiFiles.back()->SetMass(8000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("9000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(3.9016557786192155e-6);
//     SignalSemiFiles.back()->SetMass(9000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("10000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back()->SetCrosssection(2.076468481227161e-6);
//     SignalSemiFiles.back()->SetMass(10000);
//     SignalSemiFiles.push_back(new hanalysis::HFile("zbb"));
//     SignalSemiFiles.back()->SetCrosssection(22.25);

    std::vector<hanalysis::HFile *> BackgroundSemiFiles;
    BackgroundSemiFiles.push_back(new hanalysis::HFile("BG_ttbb_ljbbbb"));
    BackgroundSemiFiles.back()->SetCrosssection(25.55);
    BackgroundSemiFiles.push_back(new hanalysis::HFile("BG_ttcc_ljbbcc"));
    BackgroundSemiFiles.back()->SetCrosssection(22.25);
//     BackgroundSemiFiles.push_back(new hanalysis::HFile("zcc"));
//     BackgroundSemiFiles.back()->SetCrosssection(22.25);
//     BackgroundSemiFiles.push_back(new hanalysis::HFile("zjj"));
//     BackgroundSemiFiles.back()->SetCrosssection(22.25);

    std::vector<hanalysis::HFile *> SignalHadronicFiles;
//     SignalHadronicFiles.push_back(new hanalysis::HFile("1TeV_Hbb_ttbb_jjbbbb"));

    std::vector<hanalysis::HFile *> BackgroundHadronicFiles;
//     BackgroundHadronicFiles.push_back(new hanalysis::HFile("BG_jjbbbb"));



    HStrings SignalLeptonicTrees {
        //         "400GeV_Hbb_ttbb_llbbbb-run_01",
        //         "600GeV_Hbb_ttbb_llbbbb-run_01",
        //         "800GeV_Hbb_ttbb_llbbbb-run_01",
        //         "1000GeV_Hbb_ttbb_llbbbb-run_01",
        //         "1500GeV_Hbb_ttbb_llbbbb-run_01",
        //         "2000GeV_Hbb_ttbb_llbbbb-run_01",
        //         "2500GeV_Hbb_ttbb_llbbbb-run_01",
        //         "3000GeV_Hbb_ttbb_llbbbb-run_01"
    };
    HStrings BackgroundLeptonicTrees {
        //         "BG_ttbb_llbbbb-run_01",
        //         "BG_ttcc_llbbcc-run_01"
    };

    HStrings SignalSemiTrees {
        //         "400GeV_Hbb_ttbb_ljbbbb-run_01",
        //         "500GeV_Hbb_ttbb_ljbbbb-run_01",
        //         "600GeV_Hbb_ttbb_ljbbbb-run_01",
        //         "800GeV_Hbb_ttbb_ljbbbb-run_01",
        "1000GeV_Hbb_ttbb_ljbbbb-run_01",
        //         "1500GeV_Hbb_ttbb_ljbbbb-run_01",
//               "2000GeV_Hbb_ttbb_ljbbbb-run_01",
        //         "2500GeV_Hbb_ttbb_ljbbbb-run_01",
//               "3000GeV_Hbb_ttbb_ljbbbb-run_01"
//               "4000GeV_Hbb_ttbb_ljbbbb-run_01"
        "5000GeV_Hbb_ttbb_ljbbbb-run_01"
//         "6000GeV_Hbb_ttbb_ljbbbb-run_01"
//       "7000GeV_Hbb_ttbb_ljbbbb-run_01"
        //         "8000GeV_Hbb_ttbb_ljbbbb-run_01"
        //         "9000GeV_Hbb_ttbb_ljbbbb-run_01"
        //         "10000GeV_Hbb_ttbb_ljbbbb-run_01"
        //         "zbb-run_01"
    };

    HStrings BackgroundSemiTrees {
        "BG_ttbb_ljbbbb-run_01",
        "BG_ttcc_ljbbcc-run_01"
        //         "zcc-run_01",
        //         "zjj-run_01"
    };

    HStrings SignalHadronicTree {
        //       "1TeV_Hbb_ttbb_jjbbbb-run_01"
    };
    HStrings BackgroundHadronicTrees {
        //       "BG_jjbbbb-run_01"
    };

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
        Files = CombinedFiles;
        break;
    case  HBottomReader :
        Files = CombinedFiles;
        break;
    case HJetPairTagger:
        if (Tag == HSignal) Files = CombinedSignalFiles;
        else Files = CombinedFiles;
        break;
    case HJetPairReader:
        if (Tag == HSignal) Files = CombinedSignalFiles;
        else Files = CombinedFiles;
        break;
    case HWSemiTagger:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = SemiFiles;
        break;
    case HWSemiReader:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = SemiFiles;
        break;
    case HWHadronicTagger:
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        else Files = NotLeptonicFiles;
        break;
    case HWHadronicReader:
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        else Files = NotLeptonicFiles;
        break;
    case HTopLeptonicTagger:
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        else Files = LeptonicFiles;
        break;
    case HTopLeptonicReader:
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        else Files = LeptonicFiles;
        break;
    case HTopHadronicTagger:
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        else Files = NotLeptonicFiles;
        break;
    case HTopSemiTagger:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = SemiFiles;
        break;
    case HTopHadronicReader:
        if (Tag == HSignal) Files = NonLeptonicSignalFiles;
        else Files = NotLeptonicFiles;
        break;
    case HTopSemiReader:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = SemiFiles;
        break;
    case HHeavyHiggsLeptonicTagger:
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        else Files = LeptonicFiles;
        break;
    case HHeavyHiggsLeptonicReader:
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        else Files = LeptonicFiles;
        break;
    case HHeavyHiggsHadronicTagger:
        if (Tag == HSignal) Files = SignalHadronicFiles;
        else Files = HadronicFiles;
        break;
    case HHeavyHiggsSemiTagger:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = BackgroundSemiFiles;
        break;
    case HHeavyHiggsSemiReader:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = BackgroundSemiFiles;
        break;
    case HEventLeptonicTagger:
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        else Files = BackgroundLeptonicFiles;
        break;
    case HEventHadronicTagger:
        if (Tag == HSignal) Files = SignalHadronicFiles;
        else Files = BackgroundHadronicFiles;
        break;
    case HEventSemiTagger:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = BackgroundSemiFiles;
        break;
    case HEventLeptonicReader:
        if (Tag == HSignal) Files = SignalLeptonicFiles;
        else Files = BackgroundLeptonicFiles;
        break;
    case HEventSemiReader:
        if (Tag == HSignal) Files = SignalSemiFiles;
        else Files = BackgroundSemiFiles;
        break;
    default:
        Print(HError, "unknown tagger name");
    }

    Files.front()->SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front()->SetFileSuffix(".root");


    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);

    Print(HNotification, "Files prepared");


    switch (Tagger) {
    case HBottomTagger:
        BottomTagger.SetSignalTreeNames(CombinedTrees);
        BottomTagger.SetBackgroundTreeNames(CombinedTrees);
        if (Tag == HSignal)  BottomTagger.SetTagger();
        break;
    case HBottomReader:
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        break;
    case HJetPairTagger :
        JetPairTagger.SetSignalTreeNames(CombinedTrees);
        JetPairTagger.SetBackgroundTreeNames(CombinedTrees);
        if (Tag == HSignal) JetPairTagger.SetTagger(BottomTagger);
        break;
    case HJetPairReader :
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        if (Tag == HSignal) PrepareReader(HJetPairTagger);
        break;
    case HWHadronicTagger:
        WHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
        WHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
        if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
        break;
    case HWHadronicReader :
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        if (Tag == HSignal) PrepareReader(HWHadronicTagger);
        break;
    case HWSemiTagger :
        if (Tag == HSignal) WSemiTagger.SetTagger();
        WSemiTagger.SetSignalTreeNames(SemiTrees);
        WSemiTagger.SetBackgroundTreeNames(SemiTrees);
        break;
    case HWSemiReader :
        if (Tag == HSignal) PrepareReader(HWSemiTagger);
        break;
    case HTopHadronicTagger :
        if (Tag == HSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        TopHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
        TopHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
        break;
    case HTopHadronicReader :
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        if (Tag == HSignal) PrepareReader(HWHadronicTagger);
        if (Tag == HSignal) PrepareReader(HTopHadronicTagger);
        break;
    case HTopSemiTagger :
        if (Tag == HSignal) TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        TopSemiTagger.SetSignalTreeNames(SemiTrees);
        TopSemiTagger.SetBackgroundTreeNames(SemiTrees);
        break;
    case HTopSemiReader :
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        if (Tag == HSignal) PrepareReader(HWSemiTagger);
        if (Tag == HSignal) PrepareReader(HTopSemiTagger);
        break;
    case HHeavyHiggsSemiTagger  :
        if (Tag == HSignal) HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        HeavyHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        HeavyHiggsSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HHeavyHiggsSemiReader :
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        if (Tag == HSignal) PrepareReader(HWSemiTagger);
        if (Tag == HSignal) PrepareReader(HTopSemiTagger);
        if (Tag == HSignal) PrepareReader(HWHadronicTagger);
        if (Tag == HSignal) PrepareReader(HTopHadronicTagger);
        if (Tag == HSignal) PrepareReader(HHeavyHiggsSemiTagger);
        break;
    case HEventSemiTagger :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HEventSemiReader :
        if (Tag == HSignal) PrepareReader(HBottomTagger);
        if (Tag == HSignal) PrepareReader(HJetPairTagger);
        if (Tag == HSignal) PrepareReader(HWSemiTagger);
        if (Tag == HSignal) PrepareReader(HTopSemiTagger);
        if (Tag == HSignal) PrepareReader(HWHadronicTagger);
        if (Tag == HSignal) PrepareReader(HTopHadronicTagger);
        if (Tag == HSignal) PrepareReader(HHeavyHiggsSemiTagger);
        if (Tag == HSignal) PrepareReader(HEventSemiTagger);
        break;

    }






//     case HTopLeptonicTagger:
//     case HTopLeptonicReader  :
//     case HHeavyHiggsLeptonicTagger  :
//     case HEventLeptonicTagger  :
//     case HHeavyHiggsLeptonicReader  :
//     case HEventLeptonicReader : {
// //         TopLeptonicTagger = new hanalysis::HTopLeptonicTagger(BottomTagger);
//         TopLeptonicTagger = hanalysis::HTopLeptonicTagger(BottomTagger);
//         TopLeptonicTagger.SetAnalysisName(GetProjectName());
//         TopLeptonicTagger.SetSignalTreeNames(LeptonicTrees);
//         TopLeptonicTagger.SetBackgroundTreeNames(LeptonicTrees);
//         if (Tagger == HTopLeptonicTagger)  break;
// //         TopLeptonicReader.SetMva(TopLeptonicTagger);
//         if (Tagger == HTopLeptonicReader) break;
//
// //         HeavyHiggsLeptonicTagger = new hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
//         HeavyHiggsLeptonicTagger = hanalysis::HHeavyHiggsLeptonicTagger(BottomTagger, TopLeptonicTagger);
//         HeavyHiggsLeptonicTagger.SetAnalysisName(GetProjectName());
//         HeavyHiggsLeptonicTagger.SetSignalTreeNames(SignalLeptonicTrees);
//         HeavyHiggsLeptonicTagger.SetBackgroundTreeNames(LeptonicTrees);
//         if (Tagger == HHeavyHiggsLeptonicTagger)  break;
// //         HeavyHiggsLeptonicReader.SetMva(HeavyHiggsLeptonicTagger);
//         if (Tagger == HHeavyHiggsLeptonicReader)  break;
//
// //         EventLeptonicTagger = new hheavyhiggs::HEventLeptonicTagger(BottomTagger, JetPairTagger, TopLeptonicTagger, HeavyHiggsLeptonicTagger);
//         EventLeptonicTagger.SetAnalysisName(GetProjectName());
//         EventLeptonicTagger.SetSignalTreeNames(SignalLeptonicTrees);
//         EventLeptonicTagger.SetBackgroundTreeNames(BackgroundLeptonicTrees);
//         if (Tagger == HEventLeptonicTagger)  break;
// //         EventLeptonicReader.SetMva(EventLeptonicTagger);
//
//         Print(HError, "Tree names set");
//         break;
//
//     }
//
//

//     }
// //     }
//
//     case HHeavyHiggsHadronicTagger :
//     case HEventHadronicTagger : {
//
//
// //         HeavyHiggsHadronicTagger = new hanalysis::HHeavyHiggsHadronicTagger(BottomTagger, WHadronicTagger, TopHadronicTagger);
//         HeavyHiggsHadronicTagger = hanalysis::HHeavyHiggsHadronicTagger(BottomTagger, WHadronicTagger, TopHadronicTagger);
//         HeavyHiggsHadronicTagger.SetAnalysisName(GetProjectName());
//         HeavyHiggsHadronicTagger.SetSignalTreeNames(SignalHadronicTree);
//         HeavyHiggsHadronicTagger.SetBackgroundTreeNames(HadronicTrees);
//         if (Tagger == HHeavyHiggsHadronicTagger)  break;
//
// //         EventHadronicTagger = new hheavyhiggs::HEventHadronicTagger(BottomTagger, WHadronicTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
//         EventHadronicTagger = hheavyhiggs::HEventHadronicTagger(BottomTagger, WHadronicTagger, TopHadronicTagger, HeavyHiggsHadronicTagger);
//         EventHadronicTagger.SetAnalysisName(GetProjectName());
//         EventHadronicTagger.SetSignalTreeNames(SignalHadronicTree);
//         EventHadronicTagger.SetBackgroundTreeNames(BackgroundHadronicTrees);
//
//     }
//     default :
//         Print(HError, "unhandled case");
//     }

    return Files;

}



void hheavyhiggs::HAnalysisMva::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HInformation, "Prepare Reader", Tagger);

    switch (Tagger) {
    case HBottomTagger:
        BottomReader.SetMva(BottomTagger);
        break;
    case HJetPairTagger :
        JetPairReader.SetMva(JetPairTagger);
        break;
    case HWHadronicTagger:
        WHadronicReader.SetMva(WHadronicTagger);
        break;
    case HTopLeptonicTagger:
        TopLeptonicReader.SetMva(TopLeptonicTagger);
        break;
    case HHeavyHiggsLeptonicTagger  :
        HeavyHiggsLeptonicReader.SetMva(HeavyHiggsLeptonicTagger);
        break;
    case HEventLeptonicTagger  :
        EventLeptonicReader.SetMva(EventLeptonicTagger);
        break;
    case HWSemiTagger :
        WSemiReader.SetMva(WSemiTagger);
        break;
    case HTopSemiTagger :
        TopSemiReader.SetMva(TopSemiTagger);
        break;
    case HHeavyHiggsSemiTagger  :
        HeavyHiggsSemiReader.SetMva(HeavyHiggsSemiTagger);
        break;
    case HHeavyHiggsSemiReader  :
        HeavyHiggsSemiReader.SetMva(HeavyHiggsSemiTagger);
        break;
    case HEventSemiTagger :
        EventSemiReader.SetMva(EventSemiTagger);
        break;
    case HEventSemiReader :
        EventSemiReader.SetMva(EventSemiTagger);
        break;
    case HTopHadronicTagger :
        TopHadronicReader.SetMva(TopHadronicTagger);
        break;
    case HTopHadronicReader :
        TopHadronicReader.SetMva(TopHadronicTagger);
        break;
    case HHeavyHiggsHadronicTagger :
//       HeavyHiggsHadronicReader.SetMva(HeavyHiggsHadronicTagger);
        break;
    case HEventHadronicTagger :
//       EventHadronicReader.SetMva(EventHadronicTagger);
        break;
    default :
        Print(HError, "unhandled case");
    }

}

void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter *TreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        BottomBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HBottomReader :
        BottomReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HBottomBranch::Class());
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
    case HWSemiReader :
        WSemiReaderBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWHadronicTagger :
        WBranch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HWHadronicReader :
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

//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
//     HJets Leptons = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets());

//     if (Leptons.size() < 1) return 0;
//     if (Leptons.front().pt() < 300 || MissingEt.pt() < 400) return 0;

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
    std::vector<HBottomBranch *> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) {
        HBottomBranch *BTagger = static_cast<HBottomBranch *>(BottomBranch->NewEntry());
        *BTagger = *Bottom;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetBottomReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);

    JetTag.HeavyParticles = {BottomId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    for (const auto & Jet : Jets) {
        static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
        static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(BottomTagger.GetTag(Jet));
        if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
        if (Tag == HSignal && Jet.user_info<hanalysis::HJetInfo>().MaximalFraction() < .8)continue;
        if (std::abs(Jet.rap()) > 2.5) continue;
        HBottomBranch *Bottom = new HBottomBranch();
        HBottomBranch *BottomsTagger = static_cast<HBottomBranch *>(BottomReaderBranch->NewEntry());
        BottomTagger.FillBranch(Bottom, Jet);
        *BottomsTagger = *Bottom;
    }

    return 1;

}

bool hheavyhiggs::HAnalysisMva::GetJetPairTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Tag", Tag);
    std::vector<HEventJetPairBranch *> JetPairs = JetPairTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);
    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HEventJetPairBranch *JetPair = new HEventJetPairBranch();
        HEventJetPairBranch *JetPairBranchTagger = static_cast<HEventJetPairBranch *>(JetPairReaderBranch->NewEntry());
        JetPairTagger.FillBranch(JetPair, Doublet);
        *JetPairBranchTagger = *JetPair;
    }

    return 1;

}

bool hheavyhiggs::HAnalysisMva::GetWSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch *> WSemis = WSemiTagger.GetBranches(Event, Tag);
    if (WSemis.size() < 1) return 0;
    for (const auto & WSemi : WSemis) {
        HWSemiBranch *NewWSemiBranch = static_cast<HWSemiBranch *>(WSemiBranch->NewEntry());
        *NewWSemiBranch = *WSemi;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetWSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Reader", Tag);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();

    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);

    if (Doublets.size() < 1) return 0;

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HWSemiBranch *WSemi = new HWSemiBranch();
        HWSemiBranch *TopTagger = static_cast<HWSemiBranch *>(WSemiReaderBranch->NewEntry());
        WSemiTagger.FillBranch(WSemi, Doublet);
        *TopTagger = *WSemi;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetWTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get W Tag", Tag);
    std::vector<HWBranch *> Ws = WHadronicTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);


    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HWBranch *W = new HWBranch();
        HWBranch *TopTagger = static_cast<HWBranch *>(WReaderBranch->NewEntry());
        WHadronicTagger.FillBranch(W, Doublet);
        *TopTagger = *W;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get leptonic top", Tag);
    std::vector<HTopLeptonicBranch *> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;

    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        HTopLeptonicBranch *Top = new HTopLeptonicBranch();
        HTopLeptonicBranch *TopTagger = static_cast<HTopLeptonicBranch *>(TopLeptonicReaderBranch->NewEntry());
        TopLeptonicTagger.FillBranch(Top, Doublet);
        *TopTagger = *Top;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get hadronic tops", Tag);
    std::vector<HTopHadronicBranch *> Tops = TopHadronicTagger.GetBranches(Event, Tag);
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
    std::vector<HTopSemiBranch *> Tops = TopSemiTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);


    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);


    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *Top = new HTopHadronicBranch();
        HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(TopHadronicReaderBranch->NewEntry());
        TopHadronicTagger.FillBranch(Top, Triplet);
        *TopTagger = *Top;
    }

    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetTopSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        HTopSemiBranch *Top = new HTopSemiBranch();
        HTopSemiBranch *TopTagger = static_cast<HTopSemiBranch *>(TopSemiReaderBranch->NewEntry());
        TopSemiTagger.FillBranch(Top, Triplet);
        *TopTagger = *Top;
    }

    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic Heavy Higgs Tag", Tag);
    std::vector<HHeavyHiggsLeptonicBranch *> Higgses = HeavyHiggsLeptonicTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) {
        HHeavyHiggsLeptonicBranch *Higgs = new HHeavyHiggsLeptonicBranch();
        HHeavyHiggsLeptonicBranch *HiggsTagger = static_cast<HHeavyHiggsLeptonicBranch *>(HeavyHiggsLeptonicReaderBranch->NewEntry());
        HeavyHiggsLeptonicTagger.FillBranch(Higgs, Sextet);
        *HiggsTagger = *Higgs;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Hadronic HeavyHiggs Tag", Tag);
    std::vector<HHeavyHiggsHadronicBranch *> Higgses = HeavyHiggsHadronicTagger.GetBranches(Event, Tag);
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
    std::vector<HHeavyHiggsSemiBranch *> Higgses = HeavyHiggsSemiTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets) {
        HHeavyHiggsSemiBranch *Higgs = new HHeavyHiggsSemiBranch();
        HHeavyHiggsSemiBranch *HiggsTagger = static_cast<HHeavyHiggsSemiBranch *>(HeavyHiggsSemiReaderBranch->NewEntry());
        HeavyHiggsSemiTagger.FillBranch(Higgs, Sextet);
        *HiggsTagger = *Higgs;
    }

    return 1;
}




bool hheavyhiggs::HAnalysisMva::GetEventLeptonicTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event leptonic", Tag);
    std::vector<hheavyhiggs::HEventLeptonicBranch *> LeptonicEventBranches = EventLeptonicTagger.GetBranches(Event, Tag);
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
    std::vector<hheavyhiggs::HEventSemiBranch *> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
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
    std::vector<hheavyhiggs::HEventHadronicBranch *> HadronicEvents = EventHadronicTagger.GetBranches(Event, Tag);
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
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
    if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets()).front().pt();

    std::vector<HOctet> Octets = EventSemiTagger.GetBdt(Sextets, Doublets, Jets,  EventStruct, EventSemiReader);
    if (Octets.size() < 1) return 0;
    Octets.front().SetTag(Tag);

    hheavyhiggs::HEventSemiBranch *SemiEvent = new hheavyhiggs::HEventSemiBranch();
    EventSemiTagger.FillBranch(SemiEvent, Octets.front());

    HEventSemiBranch *NewEventBranch = static_cast<HEventSemiBranch *>(EventSemiReaderBranch->NewEntry());
    *NewEventBranch = *SemiEvent;

//     Print(HError, "Bdt", Octet.Bdt());

    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetEventLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic reader", Tag);

    HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetBdt(Jets, BottomReader);

    Print(HInformation, "Jet Pair");

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);

    Print(HInformation, "Top");
    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> LeptonicDoublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(LeptonicDoublets, MissingEt, HeavyHiggsLeptonicReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();

    std::vector<HOctet> Octets = EventLeptonicTagger.GetBdt(Sextets, Doublets, Jets, EventStruct, EventLeptonicReader);
    if (Octets.size() < 1) return 0;
    Octets.front().SetTag(Tag);

    hheavyhiggs::HEventLeptonicBranch *LeptonicEvent = new hheavyhiggs::HEventLeptonicBranch();
    EventLeptonicTagger.FillBranch(LeptonicEvent, Octets.front());

    HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(EventLeptonicReaderBranch->NewEntry());
    *NewEventBranch = *LeptonicEvent;

    return 1;
}

