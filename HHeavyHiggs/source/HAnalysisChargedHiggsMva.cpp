# include "HAnalysisChargedHiggsMva.hh"

hheavyhiggs::HAnalysisCharged::HAnalysisCharged()
{
    Print(HNotification, "Constructor");
    BottomTagger.SetAnalysisName(GetProjectName());
    JetPairTagger.SetAnalysisName(GetProjectName());
    WHadronicTagger.SetAnalysisName(GetProjectName());
    WSemiTagger.SetAnalysisName(GetProjectName());
    TopHadronicTagger.SetAnalysisName(GetProjectName());
    TopSemiTagger.SetAnalysisName(GetProjectName());
    ChargedHiggsSemiTagger.SetAnalysisName(GetProjectName());
    EventSemiTagger.SetAnalysisName(GetProjectName());
}

hheavyhiggs::HAnalysisCharged::~HAnalysisCharged()
{
    Print(HNotification, "Destructor");
}


std::string hheavyhiggs::HAnalysisCharged::GetStudyNames(const hanalysis::HAnalysis::HTagger Tagger) const
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
        return  "ChargedJetPair";
    case HJetPairReader:
        return  "ChargedJetPairReader";
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
        return  "ChargedHiggsLeptonic";
    case HHeavyHiggsHadronicTagger:
        return  "ChargedHiggsHadronic";
    case HHeavyHiggsSemiTagger:
        return  "ChargedHiggsSemi";
    case HHeavyHiggsSemiReader:
        return  "ChargedHiggsSemiReader";
    case HHeavyHiggsLeptonicReader:
        return  "ChargedHiggsLeptonicReader";
    case HEventLeptonicTagger:
        return  "EventLeptonic";
    case HEventHadronicTagger:
        return  "EventHadronic";
    case HEventSemiTagger:
        return  "ChargedSemi";
    case HEventLeptonicReader:
        return  "ChargdLeptonicReader";
    case HEventSemiReader:
        return  "ChargedSemiReader";
    default :
        Print(HError, "unexpected TaggerName", Tagger);
        return "";
    }

}

std::vector<hanalysis::HFile> hheavyhiggs::HAnalysisCharged::GetFiles(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HNotification, "Set File Vector", Tagger, Tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;
//     SignalLeptonicFiles.push_back(hanalysis::HFile("400GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(3.31);
    //     SignalLeptonicFiles.back().SetMass(400);
//         SignalLeptonicFiles.push_back(hanalysis::HFile("500GeV_Hbb_ttbb_llbbbb"));
//         SignalLeptonicFiles.back().SetCrosssection(3.31);
//         SignalLeptonicFiles.back().SetMass(500);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("600GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.933);
//     SignalLeptonicFiles.back().SetMass(600);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("800GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.359);
//     SignalLeptonicFiles.back().SetMass(800);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("1000GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.167);
//     SignalLeptonicFiles.back().SetMass(1000);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("1500GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.0379);
//     SignalLeptonicFiles.back().SetMass(1500);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("2000GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.0563);
//     SignalLeptonicFiles.back().SetMass(2000);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("2500GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.0224);
//     SignalLeptonicFiles.back().SetMass(2500);
//     SignalLeptonicFiles.push_back(hanalysis::HFile("3000GeV_Hbb_ttbb_llbbbb"));
//     SignalLeptonicFiles.back().SetCrosssection(0.0104);
//     SignalLeptonicFiles.back().SetMass(3000);

    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;
//     BackgroundLeptonicFiles.push_back(hanalysis::HFile("BG_ttbb_llbbbb"));
//     BackgroundLeptonicFiles.back().SetCrosssection(4.773);
//     BackgroundLeptonicFiles.push_back(hanalysis::HFile("BG_ttcc_llbbcc"));
//     BackgroundLeptonicFiles.back().SetCrosssection(4.161);

    std::vector<hanalysis::HFile> SignalSemiFiles;
//     SignalSemiFiles.push_back(hanalysis::HFile("400GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(0.4664420104710373);
//     SignalSemiFiles.back().SetMass(400);
//     SignalSemiFiles.push_back(hanalysis::HFile("500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(0.40374978749300205);
//     SignalSemiFiles.back().SetMass(500);
//     SignalSemiFiles.push_back(hanalysis::HFile("600GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(0.27296286310330137);
//     SignalSemiFiles.back().SetMass(600);
//     SignalSemiFiles.push_back(hanalysis::HFile("800GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(0.12290283022989924);
//     SignalSemiFiles.back().SetMass(800);
//     SignalSemiFiles.push_back(hanalysis::HFile("1TeV"));
//     SignalSemiFiles.back().SetCrosssection(0.0385019528768195);
//     SignalSemiFiles.back().SetMass(1000);
//     SignalSemiFiles.push_back(hanalysis::HFile("1500GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(0.01463088296143972);
//     SignalSemiFiles.back().SetMass(1500);
    SignalSemiFiles.push_back(hanalysis::HFile("2TeV"));
    SignalSemiFiles.back().SetCrosssection(0.0049222865674137285);
    SignalSemiFiles.back().SetMass(2000);
//     SignalSemiFiles.push_back(hanalysis::HFile("3TeV"));
//     SignalSemiFiles.back().SetCrosssection(0.0007636108315783771);
//     SignalSemiFiles.back().SetMass(3000);
//     SignalSemiFiles.push_back(hanalysis::HFile("4TeV"));
//     SignalSemiFiles.back().SetCrosssection(0.00022232809767415668);
//     SignalSemiFiles.back().SetMass(4000);
//     SignalSemiFiles.push_back(hanalysis::HFile("5TeV"));
//     SignalSemiFiles.back().SetCrosssection(0.00007946706739238737);
//     SignalSemiFiles.back().SetMass(5000);
//     SignalSemiFiles.push_back(hanalysis::HFile("6TeV"));
//     SignalSemiFiles.back().SetCrosssection(0.0000360296898244432);
//     SignalSemiFiles.back().SetMass(6000);
//     SignalSemiFiles.push_back(hanalysis::HFile("7TeV"));
//     SignalSemiFiles.back().SetCrosssection(0.00001576534159133895);
//     SignalSemiFiles.back().SetMass(7000);
//     SignalSemiFiles.push_back(hanalysis::HFile("8000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(7.670893789952377e-6);
//     SignalSemiFiles.back().SetMass(8000);
//     SignalSemiFiles.push_back(hanalysis::HFile("9000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(3.9016557786192155e-6);
//     SignalSemiFiles.back().SetMass(9000);
//     SignalSemiFiles.push_back(hanalysis::HFile("10000GeV_Hbb_ttbb_ljbbbb"));
//     SignalSemiFiles.back().SetCrosssection(2.076468481227161e-6);
//     SignalSemiFiles.back().SetMass(10000);
//     SignalSemiFiles.push_back(hanalysis::HFile("zbb"));
//     SignalSemiFiles.back().SetCrosssection(22.25);

    std::vector<hanalysis::HFile> BackgroundSemiFiles;
    BackgroundSemiFiles.push_back(hanalysis::HFile("BG_ttbb_ljbbbb"));
    //     BackgroundSemiFiles.back().SetCrosssection(25.55);
    BackgroundSemiFiles.back().SetCrosssection(0.03504);
    BackgroundSemiFiles.push_back(hanalysis::HFile("BG_ttcc_ljbbcc"));
    //     BackgroundSemiFiles.back().SetCrosssection(22.25);
    BackgroundSemiFiles.back().SetCrosssection(0.03072);
//     BackgroundSemiFiles.push_back(hanalysis::HFile("zcc"));
//     BackgroundSemiFiles.back().SetCrosssection(22.25);
//     BackgroundSemiFiles.push_back(hanalysis::HFile("zjj"));
//     BackgroundSemiFiles.back().SetCrosssection(22.25);

    std::vector<hanalysis::HFile> SignalHadronicFiles;
//     SignalHadronicFiles.push_back(hanalysis::HFile("1TeV_Hbb_ttbb_jjbbbb"));

    std::vector<hanalysis::HFile> BackgroundHadronicFiles;
//     BackgroundHadronicFiles.push_back(hanalysis::HFile("BG_jjbbbb"));



    std::vector<hanalysis::HFile> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::HFile> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::HFile> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::HFile> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::HFile> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);


    std::vector<hanalysis::HFile> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::HFile> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::HFile> Files;

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
        else Files = SemiFiles;//BackgroundSemiFiles;
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

    Files.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
    Files.front().SetFileSuffix(".root");

    Print(HNotification, "Files prepared");

    SetTrees(Tagger, Tag);

    PrepareReader(Tagger, Tag);

    return Files;

}

void hheavyhiggs::HAnalysisCharged::SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag)
{

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
//                 "1TeV-run_01",
        //         "1500GeV_Hbb_ttbb_ljbbbb-run_01",
                      "2TeV-run_01",
//                       "3TeV-run_01"
//                       "4TeV-run_01"
//         "5TeV-run_01"
//                 "6TeV-run_01"
//               "7TeV-run_01"
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


    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);



//     BottomTagger.SetSignalTreeNames(CombinedTrees);
//     BottomTagger.SetBackgroundTreeNames(CombinedTrees);
//     if (Tag == HSignal)  BottomTagger.SetTagger();
// //         break;
// //       case HBottomReader:
// //         break;
// //       case HJetPairTagger :
//     JetPairTagger.SetSignalTreeNames(CombinedTrees);
//     JetPairTagger.SetBackgroundTreeNames(CombinedTrees);
//     if (Tag == HSignal) JetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
// //         break;
// //       case HJetPairReader :
// //         break;
// //       case HWHadronicTagger:
//     WHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
//     WHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
//     if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
// //         break;
// //       case HWHadronicReader :
// //         BottomTagger.SetSignalTreeNames(CombinedTrees);
// //         BottomTagger.SetBackgroundTreeNames(CombinedTrees);
// //         if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
// //         break;
// //       case HWSemiTagger :
//     if (Tag == HSignal) WSemiTagger.SetTagger();
//     WSemiTagger.SetSignalTreeNames(SemiTrees);
//     WSemiTagger.SetBackgroundTreeNames(SemiTrees);
// //         break;
// //       case HWSemiReader :
// //         break;
// //       case HTopHadronicTagger :
//     if (Tag == HSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//     TopHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
//     TopHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
// //         break;
// //       case HTopHadronicReader :
// //         break;
// //       case HTopSemiTagger :
//     if (Tag == HSignal) TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//     TopSemiTagger.SetSignalTreeNames(SemiTrees);
//     TopSemiTagger.SetBackgroundTreeNames(SemiTrees);
// //         break;
// //       case HTopSemiReader :
// //         break;
// //       case HHeavyHiggsSemiTagger  :
//     if (Tag == HSignal) ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//     ChargedHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//     ChargedHiggsSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
// //       case HHeavyHiggsSemiReader :
// //         break;
// //       case HEventSemiTagger :
//     if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
//     EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//     EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
// //       case HEventSemiReader :
//     if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
//     EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//     EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
// //         break;
//
// //     }

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
        if (Tag == HSignal) JetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
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
        if (Tag == HSignal) ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        ChargedHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        ChargedHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
        break;
    case HHeavyHiggsSemiReader :
        break;
    case HEventSemiTagger :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HEventSemiReader :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;

    }

}



void hheavyhiggs::HAnalysisCharged::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
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
        ChargedHiggsSemiTagger.BottomTagger.SetTagger();
        ChargedHiggsSemiTagger.BottomReader.SetMva(ChargedHiggsSemiTagger.BottomTagger);
        ChargedHiggsSemiTagger.WSemiTagger.SetTagger();
        ChargedHiggsSemiTagger.WSemiReader.SetMva(ChargedHiggsSemiTagger.WSemiTagger);
        ChargedHiggsSemiTagger.WTagger.SetTagger(BottomTagger);
        ChargedHiggsSemiTagger.WReader.SetMva(ChargedHiggsSemiTagger.WTagger);
        ChargedHiggsSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        ChargedHiggsSemiTagger.TopSemiReader.SetMva(ChargedHiggsSemiTagger.TopSemiTagger);
        ChargedHiggsSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        ChargedHiggsSemiTagger.TopHadronicReader.SetMva(ChargedHiggsSemiTagger.TopHadronicTagger);
        break;
    case HHeavyHiggsSemiReader  :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);
        break;
    case HJetPairTagger :
        JetPairTagger.BottomTagger.SetTagger();
        JetPairTagger.BottomReader.SetMva(JetPairTagger.BottomTagger);
        JetPairTagger.WSemiTagger.SetTagger();
        JetPairTagger.WSemiReader.SetMva(JetPairTagger.WSemiTagger);
        JetPairTagger.WTagger.SetTagger(BottomTagger);
        JetPairTagger.WReader.SetMva(JetPairTagger.WTagger);
        JetPairTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
        JetPairTagger.TopSemiReader.SetMva(JetPairTagger.TopSemiTagger);
        JetPairTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        JetPairTagger.TopHadronicReader.SetMva(JetPairTagger.TopHadronicTagger);
        break;
    case HJetPairReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        JetPairReader.SetMva(JetPairTagger);
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
        EventSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        EventSemiTagger.ChargedHiggsSemiReader.SetMva(EventSemiTagger.ChargedHiggsSemiTagger);
        EventSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        EventSemiTagger.ChargedJetPairReader.SetMva(EventSemiTagger.ChargedJetPairTagger);
        break;
    case HEventSemiReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        JetPairReader.SetMva(JetPairTagger);
        ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);
        EventSemiReader.SetMva(EventSemiTagger);
        break;
    default :
        Print(HError, "unhandled case");
    }

}

void hheavyhiggs::HAnalysisCharged::ResetBranch()
{
    //         Branch.reset();
}

void hheavyhiggs::HAnalysisCharged::NewBranches(ExRootTreeWriter *TreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HBottomReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HJetPairTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HChargedJetPairBranch::Class());
        break;
    case HJetPairReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HChargedJetPairBranch::Class());
        break;
    case HWSemiTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWSemiReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWHadronicTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HWHadronicReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HWBranch::Class());
        break;
    case HTopLeptonicTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopLeptonicReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopLeptonicBranch::Class());
        break;
    case HTopHadronicTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HTopHadronicReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HTopSemiBranch::Class());
        break;
    case HHeavyHiggsLeptonicTagger :
//         Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsLeptonicReader:
//         Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsHadronicTagger :
//         Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
        break;
    case HHeavyHiggsSemiTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
        break;
    case HHeavyHiggsSemiReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
        break;
    case HEventLeptonicTagger :
//         Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    case HEventHadronicTagger :
//         Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventHadronicBranch::Class());
        break;
    case HEventSemiTagger :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HChargedSemiBranch::Class());
        break;
    case HEventSemiReader :
        Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HChargedSemiBranch::Class());
        break;
    case HEventLeptonicReader :
//         Branch = TreeWriter->NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    default :
        Print(HError, "No Branch filled");
    }

}


struct MinPt {
  MinPt(const float NewPt) {
    this->Pt = NewPt;
  }
  bool operator()(const fastjet::PseudoJet &Jet) {
    return (Jet.pt() < Pt);
  }
  float Pt;
};

bool hheavyhiggs::HAnalysisCharged::Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{

    Print(HInformation, "Analysis", Tagger);

//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Leptons = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets());

    if (Leptons.size() < 1) return 0;
//     if (Leptons.front().pt() < 300 || MissingEt.pt() < 400) return 0;
    if (Leptons.front().pt() < 300) return 0;

//     HJets Jets = Event->GetJets()->GetJets();
//     Jets.erase(std::remove_if(Jets.begin(), Jets.end(), MinPt(40)), Jets.end() );
//     Print(HError,"Jet Number",Jets.size());

//     if(Jets.size()<3) return 0;
    ++EventSum;

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
//         return GetHeavyHiggsLeptonicTag(Event, Tag);
    case HHeavyHiggsHadronicTagger :
//         return GetHeavyHiggsHadronicTag(Event, Tag);
    case HHeavyHiggsSemiTagger :
        return GetChargedHiggsSemiTag(Event, Tag);
    case HHeavyHiggsSemiReader :
        return GetChargdHiggsSemiReader(Event, Tag);
    case HHeavyHiggsLeptonicReader :
//         return GetHeavyHiggsLeptonicReader(Event, Tag);
    case HEventLeptonicTagger :
//         return GetEventLeptonicTag(Event, Tag);
    case HEventHadronicTagger :
//         return GetEventHadronicTag(Event, Tag);
    case HEventSemiTagger :
        return GetEventSemiTag(Event, Tag);
    case HEventSemiReader :
        return GetEventSemiReader(Event, Tag);
    case HEventLeptonicReader :
//         return GetEventLeptonicReader(Event, Tag);
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool hheavyhiggs::HAnalysisCharged::GetBottomTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Tag", Tag);
    std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetBottomReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    JetTag.HeavyParticles = {BottomId};
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    HJets Jets = BottomTagger.GetJets(Event,JetTag);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Particles = Event->GetParticles()->GetGeneratorJets();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
      std::sort(Jets.begin(), Jets.end(), SortByDeltaR(Particle));
      static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
    }


//     for (const auto Jet : Jets) Print(HError, "B Bdt", Jet.user_info<hanalysis::HJetInfo>().Bdt());
    for (const auto & Jet : Jets) {
//         static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         static_cast<hanalysis::HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(BottomTagger.GetTag(Jet));
        if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (Tag == HSignal && Jet.user_info<hanalysis::HJetInfo>().MaximalFraction() < .8)continue;
        if (std::abs(Jet.rap()) > 2.5) continue;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
    if (WSemis.size() < 1) return 0;
    for (const auto & WSemi : WSemis) *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
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

    for (const auto & Doublet : Doublets) *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(Doublet);

    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get W Tag", Tag);
    std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
    if (Ws.size() < 1) return 0;
    for (const auto & W : Ws) *static_cast<HWBranch *>(Branch->NewEntry()) = W;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetWReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);

    for(const auto& Jet : Jets){
      HJets Pieces = WHadronicTagger.GetSubJets(Jet,2);
      Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
      std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
      Doublets.insert(Doublets.end(),PieceDoublets.begin(),PieceDoublets.end());
    }

    for(const auto& Jet : Jets){
      HJets Pieces = WHadronicTagger.GetSubJets(Jet,3);
      Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
      std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
      Doublets.insert(Doublets.end(),PieceDoublets.begin(),PieceDoublets.end());
    }


    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);

    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get leptonic top", Tag);
    std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag)
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

    for (const auto & Doublet : Doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(Doublet);
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopHadronicTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get hadronic tops", Tag);
    std::vector<HTopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = Top;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetTopHadronicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = TopHadronicTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);

    for(const auto& Jet : Jets){
      HJets Pieces = WHadronicTagger.GetSubJets(Jet,2);
      Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
      std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
      std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
      Triplets.insert(Triplets.end(),PieceTriplets.begin(),PieceTriplets.end());
    }

    for(const auto& Jet : Jets){
      HJets Pieces = WHadronicTagger.GetSubJets(Jet,3);
      Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
      std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
      std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
      Triplets.insert(Triplets.end(),PieceTriplets.begin(),PieceTriplets.end());
    }


    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *TopTagger = static_cast<HTopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = TopHadronicTagger.GetBranch(Triplet);
    }

    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetTopSemiTag(hanalysis::HEvent *const Event,  HTag Tag)
{
    Print(HInformation, "Get Tops", Tag);
    std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

//     HJets Jets = Event->GetJets()->GetStructuredJets();

    HJets Jets = BottomTagger.GetJets(Event);

    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);

    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetJetPairTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Tag", Tag);
    std::vector<HChargedJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag);
    if (JetPairs.size() < 1) return 0;
    for (const auto & JetPair : JetPairs) *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPair;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetJetPairReader(hanalysis::HEvent *const Event, const HTag Tag)
{
  Print(HDebug, "Get JetPair Reader", Tag);
  HJets Jets = BottomTagger.GetJets(Event);
//     HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

//     HJets Leptons = Event->GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);

//     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

    std::vector<hanalysis::HQuartet31> Quartets = JetPairTagger.GetBdt(Triplets, Jets, JetPairReader);

    if (Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end());
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    for (const auto & Quartet : Quartets) *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(Quartet);

    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetChargedHiggsSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Semi HeavyHiggs Tag", Tag);
    std::vector<HChargedHiggsSemiBranch> Higgses = ChargedHiggsSemiTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetChargdHiggsSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);

//     HJets Jets = Event->GetJets()->GetStructuredJets();
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

//     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsSemiTagger.GetBdt(Triplets, Jets, ChargedHiggsSemiReader);

    if (Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end());
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    for (const auto & Quartet : Quartets) *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = ChargedHiggsSemiTagger.GetBranch(Quartet);
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetEventSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);
    std::vector<hheavyhiggs::HChargedSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
    if (SemiEvents.size() < 1) return 0;
    for (const auto & SemiEvent : SemiEvents) *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = SemiEvent;
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetEventSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event->GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     Triplets.insert(Triplets.end(), TripletsHadronic.begin(), TripletsHadronic.end());

    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(TripletsSemi, Jets, ChargedHiggsSemiReader);

    std::vector<hanalysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(TripletsHadronic, Jets, JetPairReader);

    HChargedEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();
    if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets()).front().pt();

    std::vector<HOctet44> Octets = EventSemiTagger.GetBdt(HiggsQuartets, JetQuartets, Jets, EventStruct, EventSemiReader);
    if (Octets.size() < 1) return 0;
    Octets.front().SetTag(Tag);

    *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(Octets.front());
    return 1;
}
