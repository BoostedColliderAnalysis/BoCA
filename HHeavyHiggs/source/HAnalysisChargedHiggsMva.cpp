# include "HAnalysisChargedHiggsMva.hh"

hheavyhiggs::HAnalysisCharged::HAnalysisCharged()
{
    Print(HNotification, "Constructor");
    BottomTagger.SetAnalysisName(ProjectName());
    JetPairTagger.SetAnalysisName(ProjectName());
    WHadronicTagger.SetAnalysisName(ProjectName());
    WSemiTagger.SetAnalysisName(ProjectName());
    TopHadronicTagger.SetAnalysisName(ProjectName());
    TopSemiTagger.SetAnalysisName(ProjectName());
    ChargedHiggsSemiTagger.SetAnalysisName(ProjectName());
    SignatureSemiTagger.SetAnalysisName(ProjectName());
    EventSemiTagger.SetAnalysisName(ProjectName());
}

hheavyhiggs::HAnalysisCharged::~HAnalysisCharged()
{
    Print(HNotification, "Destructor");
}


std::string hheavyhiggs::HAnalysisCharged::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
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
    case HEventLeptonicReader:
        return  "ChargdLeptonicReader";
    case HSignatureSemiTagger:
        return  "ChargedSignatureSemi";
    case HSignatureSemiReader:
        return  "ChargedSignatureSemiReader";
    case HEventSemiTagger:
        return  "ChargedEventSemi";
    case HEventSemiReader:
        return  "ChargedEventSemiReader";
    default :
        Print(HError, "unexpected TaggerName", Tagger);
        return "";
    }

}

std::vector<hanalysis::HFile> hheavyhiggs::HAnalysisCharged::Files(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HNotification, "Set File Vector", Tagger, Tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;

    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;

    std::vector<hanalysis::HFile> SignalSemiFiles;

//     SignalSemiFiles.push_back(hanalysis::HFile("1TeV",38.501952876819495/2,1000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("2TeV",3.7429107249252125/2,2000));
//         SignalSemiFiles.push_back(hanalysis::HFile("3TeV",0.7636108315783771/2,3000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("4TeV",0.22232809767415665/2,4000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("5TeV",0.07946706739238736/2,5000));
//             SignalSemiFiles.push_back(hanalysis::HFile("6TeV",0.03291534649650638/2,6000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("8TeV",0.00738551034925011/2,8000));
    //     SignalSemiFiles.push_back(hanalysis::HFile("10TeV",0.002068335074918064/2,10000));
//         SignalSemiFiles.push_back(hanalysis::HFile("12TeV",0.0006693740636689783/2,12000));
//         SignalSemiFiles.push_back(hanalysis::HFile("15TeV",0.00015145887990818783/2,15000));
    SignalSemiFiles.push_back(hanalysis::HFile("20TeV", 0.000016677670760729152 / 2, 20000));

    std::vector<hanalysis::HFile> BackgroundSemiFiles;
    HStrings BG1 = {"BG_ttbb_ljbbbb", "BG_ttbb_ljbbbb_1"};
    BackgroundSemiFiles.push_back(hanalysis::HFile( BG1 , 35.04));
    HStrings BG2 = {"BG_ttcc_ljbbcc", "BG_ttcc_ljbbcc_1"};
    BackgroundSemiFiles.push_back(hanalysis::HFile( BG2 , 30.72));

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
        else NewFiles = SemiFiles;//BackgroundSemiFiles;
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

void hheavyhiggs::HAnalysisCharged::SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag)
{

    HStrings SignalLeptonicTrees {
    };
    HStrings BackgroundLeptonicTrees {
    };

    HStrings SignalSemiTrees {
//         "1TeV-run_01",
//         "2TeV-run_01",
//         "3TeV-run_01"
//         "4TeV-run_01"
//         "5TeV-run_01"
//         "6TeV-run_01"
//         "7TeV-run_01"
//         "8TeV-run_01"
//         "9TeV-run_01"
//         "10TeV-run_01"
//         "12TeV-run_01"
//         "15TeV-run_01"
        "20TeV-run_01"
    };

    HStrings BackgroundSemiTrees {
        "BG_ttbb_ljbbbb-run_01",
        "BG_ttcc_ljbbcc-run_01"
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
    case HSignatureSemiTagger :
        if (Tag == HSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
        SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HSignatureSemiReader :
//         if (Tag == HSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HEventSemiTagger :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger, SignatureSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HEventSemiReader :
        if (Tag == HSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger, SignatureSemiTagger);
        EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    default :
        Print(HError, "unhandled case");
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
        SignatureSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        SignatureSemiTagger.ChargedHiggsSemiReader.SetMva(SignatureSemiTagger.ChargedHiggsSemiTagger);
        SignatureSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        SignatureSemiTagger.ChargedJetPairReader.SetMva(SignatureSemiTagger.ChargedJetPairTagger);
        break;
    case HSignatureSemiReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        JetPairReader.SetMva(JetPairTagger);
        ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);
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
        EventSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        EventSemiTagger.ChargedHiggsSemiReader.SetMva(EventSemiTagger.ChargedHiggsSemiTagger);
        EventSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
        EventSemiTagger.ChargedJetPairReader.SetMva(EventSemiTagger.ChargedJetPairTagger);
        EventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
        EventSemiTagger.SignatureSemiReader.SetMva(EventSemiTagger.SignatureSemiTagger);
        break;
    case HEventSemiReader :
        BottomReader.SetMva(BottomTagger);
        WSemiReader.SetMva(WSemiTagger);
        TopSemiReader.SetMva(TopSemiTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        JetPairReader.SetMva(JetPairTagger);
        ChargedHiggsSemiReader.SetMva(ChargedHiggsSemiTagger);
        SignatureSemiReader.SetMva(SignatureSemiTagger);
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

void hheavyhiggs::HAnalysisCharged::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
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
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedJetPairBranch::Class());
        break;
    case HJetPairReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedJetPairBranch::Class());
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
//         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsLeptonicReader:
//         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
        break;
    case HHeavyHiggsHadronicTagger :
//         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
        break;
    case HHeavyHiggsSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
        break;
    case HHeavyHiggsSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
        break;
    case HEventLeptonicTagger :
//         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    case HEventHadronicTagger :
//         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventHadronicBranch::Class());
        break;
    case HSignatureSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
        break;
    case HSignatureSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
        break;
    case HEventSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
        break;
    case HEventSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
        break;
    case HEventLeptonicReader :
//         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
        break;
    default :
        Print(HError, "No Branch filled");
    }

}


// struct MinPt {
//   MinPt(const float NewPt) {
//     this->Pt = NewPt;
//   }
//   bool operator()(const fastjet::PseudoJet &Jet) {
//     return (Jet.pt() < Pt);
//   }
//   float Pt;
// };

bool hheavyhiggs::HAnalysisCharged::Analysis(hanalysis::HEvent *const Event, const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{

    Print(HInformation, "Analysis", Tagger);

//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
    HJets Leptons = fastjet::sorted_by_pt(Event->GetLeptons()->GetLeptonJets());

    if (Leptons.size() < 1) return 0;
//     if (Leptons.front().pt() < 300 || MissingEt.pt() < 400) return 0;
    if (Leptons.front().pt() < 300) return 0;
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
    case HSignatureSemiTagger :
        return GetSignatureSemiTag(Event, Tag);
    case HSignatureSemiReader :
        return GetSignatureSemiReader(Event, Tag);
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
    std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(*Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetBottomReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    JetTag.HeavyParticles = {BottomId};
//     HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    HJets Jets = BottomTagger.GetJets(Event, JetTag);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Particles = Event->GetParticles()->GetGeneratorJets();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
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

    HJets Leptons = Event->Leptons().GetLeptonJets();
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

    for (const auto & Jet : Jets) {
        HJets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
        Doublets.insert(Doublets.end(), PieceDoublets.begin(), PieceDoublets.end());
    }

    for (const auto & Jet : Jets) {
        HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
        Doublets.insert(Doublets.end(), PieceDoublets.begin(), PieceDoublets.end());
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
//     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
//     if (Tops.size() < 1) return 0;
//     for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicReader(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

//     HJets Jets = Event->GetJets()->GetStructuredJets();
//     Jets = BottomTagger.GetBdt(Jets, BottomReader);
//
//     HJets Leptons = Event->GetLeptons()->GetLeptonJets();
//     if (Leptons.size() < 2) return 0;
//
//     fastjet::PseudoJet MissingEt = Event->GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);
//
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(Doublet);
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

    for (const auto & Jet : Jets) {
        HJets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
    }

    for (const auto & Jet : Jets) {
        HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::HDoublet> PieceDoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
        std::vector<hanalysis::HTriplet> PieceTriplets = TopHadronicTagger.GetBdt(PieceDoublets, Jets, TopHadronicReader);
        Triplets.insert(Triplets.end(), PieceTriplets.begin(), PieceTriplets.end());
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

bool hheavyhiggs::HAnalysisCharged::GetSignatureSemiTag(hanalysis::HEvent *const Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);
    std::vector<HChargedOctetBranch> SemiEvents = SignatureSemiTagger.GetBranches(Event, Tag);
    if (SemiEvents.size() < 1) return 0;
    for (const auto & SemiEvent : SemiEvents) *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = SemiEvent;
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetSignatureSemiReader(hanalysis::HEvent *const Event, const HTag Tag)
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

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);
    if (Octets.size() < 1) return 0;

    if (Octets.size() > 1) {
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }
    Octets.front().SetTag(Tag);

    for (const auto & Octet : Octets) *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(Octet);
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

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event->GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event->GetJets()->GetScalarHt();

    std::vector<HEventMultiplet<HOctet44>> Events = EventSemiTagger.GetBdt(Octets, Jets, Leptons, EventStruct, EventSemiReader);
    if (Events.size() < 1) return 0;
    Events.front().SetTag(Tag);

    *static_cast<HChargedSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(Events.front());
    return 1;
}
