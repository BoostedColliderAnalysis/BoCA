# include "HAnalysisHeavyHiggsMva.hh"

hheavyhiggs::HAnalysisMva::HAnalysisMva()
{
    ReadConfig();
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
    mkdir(ProjectName().c_str(), 0700);
}

void hheavyhiggs::HAnalysisMva::ReadConfig()
{
    try {
        Config_.readFile("HeavyHiggs.cfg");
    } catch (const libconfig::FileIOException &FileIOException) {
        std::cerr << "I/O error while reading file." << std::endl;
    } catch (const libconfig::ParseException &ParseException) {
        std::cerr << "Parse error at " << ParseException.getFile() << ":" << ParseException.getLine() << " - " << ParseException.getError() << std::endl;
    }
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

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.push_back(hanalysis::HFile(SignalName, SignalCrosssection(), Mass()));
//     SignalSemiFiles.push_back(BackgroundFile(ttbb));

//     BackgroundSemiFiles.push_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.push_back(BackgroundFile(tt));

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
        else NewFiles = BackgroundSemiFiles;
        break;
    case HJetPairReader:
        if (Tag == HSignal) NewFiles = CombinedSignalFiles;
        else NewFiles = BackgroundSemiFiles;
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

    std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    HStrings SignalSemiTrees {
        SignalTree
//         BackgroundTree(ttbb)
    };

    HStrings BackgroundSemiTrees {
//         BackgroundTree(ttbb),
//         BackgroundTree(ttcc),
//         BackgroundTree(ttjj)
        BackgroundTree(tt)
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
        JetPairTagger.SetSignalTreeNames(SignalSemiTrees);
        JetPairTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
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

//     const int NumberofBackgroundFiles = 3;
//     int ObjectMax;
//     switch(Tag){
//       case HSignal : ObjectMax = EventNumberMax();
//       case HBackground : ObjectMax = EventNumberMax() / NumberofBackgroundFiles; // might be stupid
//     }

    if (ObjectNumber > EventNumberMax()) {
//         if (Tag == HSignal) Print(HError, "more signals than events", "doesnt have to be bad");
        return 0;
    }

//     const float TopPtCut = 1000;
    HJets Particles = Event.GetParticles()->Generator();
    Particles = BottomTagger.RemoveIfWrongAbsParticle(Particles, TopId);
    if (Particles.size() != 2) {
        Print(HError, "Not enough top quarks", Particles.size());
        return 0;
    } else {
        if (Particles.at(0).pt() < PreCut()) return 0;
        if (Particles.at(1).pt() < PreCut()) return 0;
    }

//     Print(HError, "Top pt", Particles.at(0).pt(), Particles.at(1).pt());

//     HJets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets());
//     if (Leptons.size() < 1) return 0;
//     if (Leptons.front().pt() < PreCut()) return 0;

//     HJets Bottoms = Event.GetJets()->GetBottomJets();
//     if (Bottoms.size() < 3) return 0;
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
    for (const auto & Bottom : Bottoms) {
        ++ObjectNumber;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    if (Jets.size() < 1) return 0;

//     Jets = static_cast<hanalysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(Jets);

    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
    }

    for (const auto & Jet : Jets) {
        if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
        if (std::abs(Jet.rap()) > BottomTagger.DetectorGeometry.TrackerEtaMax) continue;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetJetPairTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Tag", Tag);
    std::vector<HEventJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag);
    if (JetPairs.size() < 1) return 0;
    for (const auto & JetPair : JetPairs) {
        ++ObjectNumber;
        *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPair;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetJetPairReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get JetPair Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
    if (Jets.size() < 1) return 0;

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

    for (const auto & Doublet : Doublets) {
        ++ObjectNumber;
        *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(Doublet);
    }
    return 1;

}

bool hheavyhiggs::HAnalysisMva::GetWSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
    if (WSemis.size() < 1) return 0;
    for (const auto & WSemi : WSemis) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
    }
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

    for (const auto & Doublet : Doublets) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(Doublet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetWTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get W Tag", Tag);
    std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
    if (Ws.size() < 1) return 0;
    for (const auto & W : Ws) {
        ++ObjectNumber;
        *static_cast<HWBranch *>(Branch->NewEntry()) = W;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetWReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;


    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        ++ObjectNumber;
        *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get leptonic top", Tag);
    std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetTopLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;

    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    if (Doublets.size() > 1) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 1, Doublets.end());
    }

    for (const auto & Doublet : Doublets)  {
        ++ObjectNumber;
        *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(Doublet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get hadronic tops", Tag);
    std::vector<HTopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;


    std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        ++ObjectNumber;
        *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(Triplet);
    }
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get Tops", Tag);
    std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);

    if (Triplets.size() > 1) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        ++ObjectNumber;
        *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic Heavy Higgs Tag", Tag);
    std::vector<HHeavyHiggsLeptonicBranch> Higgses = HeavyHiggsLeptonicTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) {
        ++ObjectNumber;
        *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry()) = Higgs;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    if (Leptons.size() < 2) return 0;
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader);

    if (Sextets.size() > 1) {
        std::sort(Sextets.begin(), Sextets.end());
        Sextets.erase(Sextets.begin() + 1, Sextets.end());
    }

    for (const auto & Sextet : Sextets)  {
        ++ObjectNumber;
        *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry())  = HeavyHiggsLeptonicTagger.GetBranch(Sextet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Hadronic HeavyHiggs Tag", Tag);
    std::vector<HHeavyHiggsHadronicBranch> Higgses = HeavyHiggsHadronicTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) {
        ++ObjectNumber;
        *static_cast<HHeavyHiggsHadronicBranch *>(Branch->NewEntry()) = Higgs;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Semi HeavyHiggs Tag", Tag);
    std::vector<HHeavyHiggsSemiBranch> Higgses = HeavyHiggsSemiTagger.GetBranches(Event, Tag);
    if (Higgses.size() < 1) return 0;
    for (const auto & Higgs : Higgses) {
        ++ObjectNumber;
        *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

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

    for (const auto & Sextet : Sextets) {
        ++ObjectNumber;
        *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = HeavyHiggsSemiTagger.GetBranch(Sextet);
    }

    return 1;
}




bool hheavyhiggs::HAnalysisMva::GetEventLeptonicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event leptonic", Tag);
    std::vector<hheavyhiggs::HEventLeptonicBranch *> LeptonicEventBranches = EventLeptonicTagger.GetBranches(Event, Tag);
    if (LeptonicEventBranches.size() < 1) return 0;
    for (const auto & LeptonicEvent : LeptonicEventBranches) {
        ++ObjectNumber;
        *static_cast<HEventLeptonicBranch *>(Branch->NewEntry()) = *LeptonicEvent;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetEventHadronicTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event hadronic", Tag);
    std::vector<hheavyhiggs::HEventHadronicBranch *> HadronicEvents = EventHadronicTagger.GetBranches(Event, Tag);
    if (HadronicEvents.size() < 1) return 0;
    for (const auto & HadronicEvent : HadronicEvents) {
        ++ObjectNumber;
        *static_cast<HEventHadronicBranch *>(Branch->NewEntry()) = *HadronicEvent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetEventLeptonicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Leptonic reader", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

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

    ++ObjectNumber;
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
        ++ObjectNumber;
        *static_cast<HOctetBranch *>(Branch->NewEntry()) = Signature;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetSignatureSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Signature Semi Reader", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

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
    ++ObjectNumber;
    *static_cast<HOctetBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(Octets.front());
    return 1;
}



bool hheavyhiggs::HAnalysisMva::GetEventSemiTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);
    std::vector<hheavyhiggs::HEventSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
    if (SemiEvents.size() < 1) return 0;
    for (const auto & SemiEvent : SemiEvents) {
        ++ObjectNumber;
        *static_cast<HEventSemiBranch *>(Branch->NewEntry()) = SemiEvent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisMva::GetEventSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets PreJets = BottomTagger.GetJets(Event);
    HJets Jets = BottomTagger.GetJetBdt(PreJets, BottomReader);
    HJets SubJets = BottomTagger.GetMultiJetBdt(PreJets, BottomReader);
    if (Jets.size() < 1) return 0;
    if (SubJets.size() < 1) return 0;

    std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
//     Print(HError, "Doublets", Doublets.size());

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
//     Print(HError, "Triplets Semi", TripletsSemi.size());

    std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     Print(HError, "Triplets Hadronic", TripletsHadronic.size());

    std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);
//     Print(HError, "Sextets", Sextets.size());

    std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Doublets, SignatureSemiReader);
//     Print(HError, "Octets", Octets.size());

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = Jets.size();
    EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
//   if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets()).front().pt();

    std::vector<HEventMultiplet<HOctet>> Events = EventSemiTagger.GetBdt(Octets, Jets, SubJets, Leptons,  EventStruct, EventSemiReader);
    if (Events.size() < 1) return 0;
    Events.front().SetTag(Tag);
    ++ObjectNumber;
    *static_cast<HEventSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(Events.front());
    return 1;
}
