# include "HAnalysisHeavyHiggsMva.hh"

// hheavyhiggs::HAnalysisMva::HAnalysisMva()
// {
// //     ReadConfig();
// //     DebugLevel = hanalysis::HObject::HDebug;
//     Print(HNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     JetPairTagger.SetAnalysisName(ProjectName());
//     WHadronicTagger.SetAnalysisName(ProjectName());
//     WSemiTagger.SetAnalysisName(ProjectName());
//     TopHadronicTagger.SetAnalysisName(ProjectName());
//     TopSemiTagger.SetAnalysisName(ProjectName());
//     HeavyHiggsSemiTagger.SetAnalysisName(ProjectName());
//     SignatureSemiTagger.SetAnalysisName(ProjectName());
//     EventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hheavyhiggs::HAnalysisMva::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(HNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  BottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case HWSemiTagger:
//         return  "WSemi";
//     case HWSemiReader:
//         return  "WSemiReader";
//     case HWHadronicTagger:
//         return  "WHadronic";
//     case HWHadronicReader:
//         return  "WHadronicReader";
//     case HJetPairTagger:
//         return  "JetPair";
//     case HJetPairReader:
//         return  "JetPairReader";
//     case HTopLeptonicTagger:
//         return  "TopLeptonic";
//     case HTopLeptonicReader:
//         return  "TopLeptonicReader";
//     case HTopHadronicTagger:
//         return  "TopHadronic";
//     case HTopSemiTagger:
//         return  "TopSemi";
//     case HTopHadronicReader:
//         return  "TopHadronicReader";
//     case HTopSemiReader:
//         return  "TopSemiReader";
//     case HHeavyHiggsLeptonicTagger:
//         return  "HeavyHiggsLeptonic";
//     case HHeavyHiggsHadronicTagger:
//         return  "HeavyHiggsHadronic";
//     case HHeavyHiggsSemiTagger:
//         return  "HeavyHiggsSemi";
//     case HHeavyHiggsSemiReader:
//         return  "HeavyHiggsSemiReader";
//     case HHeavyHiggsLeptonicReader:
//         return  "HeavyHiggsLeptonicReader";
//     case HEventLeptonicTagger:
//         return  "EventLeptonic";
//     case HEventHadronicTagger:
//         return  "EventHadronic";
//     case HEventLeptonicReader:
//         return  "EventLeptonicReader";
//     case HSignatureSemiTagger:
//         return  "SignatureSemi";
//     case HSignatureSemiReader:
//         return  "SignatureSemiReader";
//     case HEventSemiTagger:
//         return  "EventSemi";
//     case HEventSemiReader:
//         return  "EventSemiReader";
//     default :
//         Print(HError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<hanalysis::RootFile> hheavyhiggs::HAnalysisMva::Files(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

    std::vector<hanalysis::RootFile> SignalLeptonicFiles;
    std::vector<hanalysis::RootFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::RootFile> SignalSemiFiles;
    std::vector<hanalysis::RootFile> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(hanalysis::RootFile(SignalName, SignalCrosssection(), Mass()));
//     SignalSemiFiles.emplace_back(BackgroundFile(ttbb));

//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

    std::vector<hanalysis::RootFile> SignalHadronicFiles;

    std::vector<hanalysis::RootFile> BackgroundHadronicFiles;

    std::vector<hanalysis::RootFile> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::RootFile> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::RootFile> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::RootFile> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::RootFile> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);

    std::vector<hanalysis::RootFile> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::RootFile> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::RootFile> NewFiles;

    switch (tag) {
    case HObject::kSignal :
        NewFiles = SignalSemiFiles;
        break;
    case HObject::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

//     switch (Tagger) {
//     case  BottomTagger :
//         NewFiles = CombinedFiles;
//         break;
//     case  HBottomReader :
//         NewFiles = CombinedFiles;
//         break;
//     case HJetPairTagger:
//         if (Tag == kSignal) NewFiles = CombinedSignalFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HJetPairReader:
//         if (Tag == kSignal) NewFiles = CombinedSignalFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HWSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HWSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HWHadronicTagger:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HWHadronicReader:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HTopLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HTopHadronicTagger:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HTopHadronicReader:
//         if (Tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HHeavyHiggsLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HHeavyHiggsLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HHeavyHiggsHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = HadronicFiles;
//         break;
//     case HHeavyHiggsSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HHeavyHiggsSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HEventHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case HEventLeptonicReader:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HSignatureSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HSignatureSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         Print(HError, "unknown tagger name");
//     }

    NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
    NewFiles.front().set_file_suffix(".root");
    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;

}


void hheavyhiggs::HAnalysisMva::SetTrees()
{

    Strings SignalLeptonicTrees {};
    Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    Strings SignalSemiTrees {
        SignalTree
//         BackgroundTree(ttbb)
    };

    Strings BackgroundSemiTrees {
//         BackgroundTree(ttbb),
//         BackgroundTree(ttcc),
//         BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    Strings SignalHadronicTree {};
    Strings BackgroundHadronicTrees {};

    Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetSignalTreeNames(CombinedTrees);
//         BottomTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         break;
//     case HBottomReader:
//         break;
//     case HJetPairTagger :
//         JetPairTagger.SetSignalTreeNames(SignalSemiTrees);
//         JetPairTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) JetPairTagger.SetTagger(BottomTagger);
//         break;
//     case HJetPairReader :
//         break;
//     case HWHadronicTagger:
//         WHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
//         WHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
//         if (Tag == kSignal) WHadronicTagger.SetTagger(BottomTagger);
//         break;
//     case HWHadronicReader :
//         BottomTagger.SetSignalTreeNames(CombinedTrees);
//         BottomTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal) WHadronicTagger.SetTagger(BottomTagger);
//         break;
//     case HWSemiTagger :
//         if (Tag == kSignal) WSemiTagger.SetTagger();
//         WSemiTagger.SetSignalTreeNames(SemiTrees);
//         WSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HWSemiReader :
//         break;
//     case HTopHadronicTagger :
//         if (Tag == kSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         TopHadronicTagger.SetSignalTreeNames(NotLeptonicTrees);
//         TopHadronicTagger.SetBackgroundTreeNames(NotLeptonicTrees);
//         break;
//     case HTopHadronicReader :
//         break;
//     case HTopSemiTagger :
//         if (Tag == kSignal) TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         TopSemiTagger.SetSignalTreeNames(SemiTrees);
//         TopSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HTopSemiReader :
//         break;
//     case HHeavyHiggsSemiTagger  :
//         if (Tag == kSignal) HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         HeavyHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         HeavyHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HHeavyHiggsSemiReader :
//         break;
//     case HSignatureSemiTagger :
//         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HSignatureSemiReader :
//         break;
//     case HEventSemiTagger :
//         if (Tag == kSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger, SignatureSemiTagger);
//         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HEventSemiReader :
//         if (Tag == kSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger, SignatureSemiTagger);
//         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(HError, "unhandeled case");
//     }
}

// void hheavyhiggs::HAnalysisMva::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(HInformation, "Prepare Reader", Tagger);
//     if (Tag == kBackground) return;
//     switch (Tagger) {
//     case HBottomTagger:
//         break;
//     case HBottomReader:
//         BottomReader.set_tagger(bottom_tagger_);
//         break;
//     case HWHadronicTagger:
//         WHadronicTagger.BottomTagger.SetTagger();
//         WHadronicTagger.BottomReader.set_tagger(WHadronicTagger.BottomTagger);
//         break;
//     case HWHadronicReader:
//         BottomReader.set_tagger(bottom_tagger_);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         break;
//     case HWSemiTagger :
//         break;
//     case HWSemiReader :
//         WSemiReader.set_tagger(WSemiTagger);
//         break;
//     case HTopHadronicTagger :
//         TopHadronicTagger.BottomTagger.SetTagger();
//         TopHadronicTagger.BottomReader.set_tagger(TopHadronicTagger.BottomTagger);
//         TopHadronicTagger.WTagger.SetTagger(BottomTagger);
//         TopHadronicTagger.WReader.set_tagger(TopHadronicTagger.WTagger);
//         break;
//     case HTopHadronicReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         break;
//     case HTopSemiTagger :
//         TopSemiTagger.BottomTagger.SetTagger();
//         TopSemiTagger.BottomReader.set_tagger(TopSemiTagger.BottomTagger);
//         TopSemiTagger.WSemiTagger.SetTagger();
//         TopSemiTagger.WSemiReader.set_tagger(TopSemiTagger.WSemiTagger);
//         break;
//     case HTopSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         break;
//     case HHeavyHiggsSemiTagger :
//         HeavyHiggsSemiTagger.BottomTagger.SetTagger();
//         HeavyHiggsSemiTagger.BottomReader.set_tagger(HeavyHiggsSemiTagger.BottomTagger);
//         HeavyHiggsSemiTagger.WSemiTagger.SetTagger();
//         HeavyHiggsSemiTagger.WSemiReader.set_tagger(HeavyHiggsSemiTagger.WSemiTagger);
//         HeavyHiggsSemiTagger.WTagger.SetTagger(BottomTagger);
//         HeavyHiggsSemiTagger.WReader.set_tagger(HeavyHiggsSemiTagger.WTagger);
//         HeavyHiggsSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         HeavyHiggsSemiTagger.TopSemiReader.set_tagger(HeavyHiggsSemiTagger.TopSemiTagger);
//         HeavyHiggsSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         HeavyHiggsSemiTagger.TopHadronicReader.set_tagger(HeavyHiggsSemiTagger.TopHadronicTagger);
//         break;
//     case HHeavyHiggsSemiReader  :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         break;
//     case HJetPairTagger :
//         JetPairTagger.BottomTagger.SetTagger();
//         JetPairTagger.BottomReader.set_tagger(JetPairTagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         JetPairReader.set_tagger(JetPairTagger);
//         break;
//     case HSignatureSemiTagger :
//         SignatureSemiTagger.BottomTagger.SetTagger();
//         SignatureSemiTagger.BottomReader.set_tagger(SignatureSemiTagger.BottomTagger);
//         SignatureSemiTagger.WSemiTagger.SetTagger();
//         SignatureSemiTagger.WSemiReader.set_tagger(SignatureSemiTagger.WSemiTagger);
//         SignatureSemiTagger.WTagger.SetTagger(BottomTagger);
//         SignatureSemiTagger.WReader.set_tagger(SignatureSemiTagger.WTagger);
//         SignatureSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         SignatureSemiTagger.TopSemiReader.set_tagger(SignatureSemiTagger.TopSemiTagger);
//         SignatureSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         SignatureSemiTagger.TopHadronicReader.set_tagger(SignatureSemiTagger.TopHadronicTagger);
//         SignatureSemiTagger.HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         SignatureSemiTagger.HeavyHiggsSemiReader.set_tagger(SignatureSemiTagger.HeavyHiggsSemiTagger);
//         SignatureSemiTagger.JetPairTagger.SetTagger(BottomTagger);
//         SignatureSemiTagger.JetPairReader.set_tagger(SignatureSemiTagger.JetPairTagger);
//         break;
//     case HSignatureSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         break;
//     case HEventSemiTagger :
//         EventSemiTagger.BottomTagger.SetTagger();
//         EventSemiTagger.BottomReader.set_tagger(EventSemiTagger.BottomTagger);
//         EventSemiTagger.WSemiTagger.SetTagger();
//         EventSemiTagger.WSemiReader.set_tagger(EventSemiTagger.WSemiTagger);
//         EventSemiTagger.WTagger.SetTagger(BottomTagger);
//         EventSemiTagger.WReader.set_tagger(EventSemiTagger.WTagger);
//         EventSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         EventSemiTagger.TopSemiReader.set_tagger(EventSemiTagger.TopSemiTagger);
//         EventSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         EventSemiTagger.TopHadronicReader.set_tagger(EventSemiTagger.TopHadronicTagger);
//         EventSemiTagger.HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         EventSemiTagger.HeavyHiggsSemiReader.set_tagger(EventSemiTagger.HeavyHiggsSemiTagger);
//         EventSemiTagger.JetPairTagger.SetTagger(BottomTagger);
//         EventSemiTagger.JetPairReader.set_tagger(EventSemiTagger.JetPairTagger);
//         EventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
//         EventSemiTagger.SignatureSemiReader.set_tagger(EventSemiTagger.SignatureSemiTagger);
//         break;
//     case HEventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         EventSemiReader.set_tagger(EventSemiTagger);
//         break;
//     default :
//         Print(HError, "unhandled case");
//     }
// }

// void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter &tree_writer, const hanalysis::HAnalysis::HTagger tagger)
// {
//     Print(HNotification, "New Branches", tagger);
//
//     switch (tagger) {
//     case BottomTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HBottomBranch::Class());
//         break;
//     case HBottomReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HBottomBranch::Class());
//         break;
//     case HJetPairTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventJetPairBranch::Class());
//         break;
//     case HWSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HWBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HWBranch::Class());
//         break;
//     case HTopLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopHadronicBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopSemiBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopHadronicBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopSemiBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicReader:
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
//         break;
//     case HHeavyHiggsSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HHeavyHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HHeavyHiggsSemiBranch::Class());
//         break;
//     case HEventLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventLeptonicBranch::Class());
//         break;
//     case HEventHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventHadronicBranch::Class());
//         break;
//     case HEventLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventLeptonicBranch::Class());
//         break;
//     case HSignatureSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HOctetBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HOctetBranch::Class());
//         break;
//     case HEventSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventSemiBranch::Class());
//         break;
//     case HEventSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HEventSemiBranch::Class());
//         break;
//     default :
//         Print(HError, "No Branch filled");
//     }
//
// }

int hheavyhiggs::HAnalysisMva::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{
    Print(HInformation, "Analysis");

    HJets Particles = event.GetParticles()->Generator();
    HJets Tops = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Tops.size() != 2) {
        Print(HError, "Not enough top quarks", Tops.size());
        return 0;
    } else {
        if (Tops.at(0).pt() < PreCut()) return 0;
        if (Tops.at(1).pt() < PreCut()) return 0;
    }

    if (event.GetJets()->GetMissingEt().pt() < MissingEt()) return 0;
    HJets Leptons = fastjet::sorted_by_pt(event.GetLeptons()->GetLeptonJets());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    HJets Jets = event.GetJets()->GetJets();
    if (Jets.size() < 4) return 0;


    ++event_sum_;

    tagger_.GetBranches(event, stage, tag);

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(Event, Tag);
//     case HBottomReader:
//         return GetBottomReader(Event, Tag);
//     case HJetPairTagger :
//         return GetJetPairTag(Event, Tag);
//     case HJetPairReader :
//         return GetJetPairReader(Event, Tag);
//     case HWHadronicTagger :
//         return GetWTag(Event, Tag);
//     case HWHadronicReader :
//         return GetWReader(Event, Tag);
//     case HWSemiTagger :
//         return GetWSemiTag(Event, Tag);
//     case HWSemiReader :
//         return GetWSemiReader(Event, Tag);
//     case HTopLeptonicTagger :
//         return GetTopLeptonicTag(Event, Tag);
//     case HTopHadronicTagger :
//         return GetTopHadronicTag(Event, Tag);
//     case HTopSemiTagger :
//         return GetTopSemiTag(Event, Tag);
//     case HTopHadronicReader :
//         return GetTopHadronicReader(Event, Tag);
//     case HTopLeptonicReader :
//         return GetTopLeptonicReader(Event, Tag);
//     case HTopSemiReader :
//         return GetTopSemiReader(Event, Tag);
//     case HHeavyHiggsLeptonicTagger :
//         return GetHeavyHiggsLeptonicTag(Event, Tag);
//     case HHeavyHiggsHadronicTagger :
//         return GetHeavyHiggsHadronicTag(Event, Tag);
//     case HHeavyHiggsSemiTagger :
//         return GetHeavyHiggsSemiTag(Event, Tag);
//     case HHeavyHiggsSemiReader :
//         return GetHeavyHiggsSemiReader(Event, Tag);
//     case HHeavyHiggsLeptonicReader :
//         return GetHeavyHiggsLeptonicReader(Event, Tag);
//     case HEventLeptonicTagger :
//         return GetEventLeptonicTag(Event, Tag);
//     case HEventHadronicTagger :
//         return GetEventHadronicTag(Event, Tag);
//     case HEventLeptonicReader :
//         return GetEventLeptonicReader(Event, Tag);
//     case HSignatureSemiTagger :
//         return GetSignatureSemiTag(Event, Tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(Event, Tag);
//     case HEventSemiTagger :
//         return GetEventSemiTag(Event, Tag);
//     case HEventSemiReader :
//         return GetEventSemiReader(Event, Tag);
//     default :
//         Print(HError, "unknown Tagger", Tagger);
//         return 0;
//     }
}


// bool hheavyhiggs::HAnalysisMva::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Tag", Tag);
//     std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
//     if (Bottoms.empty()) return 0;
//     for (const auto & Bottom : Bottoms) {
//         ++ObjectNumber;
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Reader", Tag);
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//
//     if (Jets.empty()) return 0;
//
// //     Jets = static_cast<hanalysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(Jets);
//
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetJetPairTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get JetPair Tag", Tag);
//     std::vector<HEventJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag);
//     if (JetPairs.empty()) return 0;
//     for (const auto & JetPair : JetPairs) {
//         ++ObjectNumber;
//         *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetJetPairReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get JetPair Reader", Tag);
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
//     if (Jets.empty()) return 0;
//
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsFamily(BottomId, GluonId)), Particles.end());
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) {
//         ++ObjectNumber;
//         *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(Doublet);
//     }
//     return 1;
//
// }
//
// bool hheavyhiggs::HAnalysisMva::GetWSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get W Semi Tag", Tag);
//     std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
//     if (WSemis.empty()) return 0;
//     for (const auto & WSemi : WSemis) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetWSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get W Semi Reader", Tag);
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//
//     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//
//     if (Doublets.empty()) return 0;
//
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(Doublet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetWTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get W Tag", Tag);
//     std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
//     if (Ws.empty()) return 0;
//     for (const auto & W : Ws) {
//         ++ObjectNumber;
//         *static_cast<HWBranch *>(Branch->NewEntry()) = W;
//     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetWReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) {
//         ++ObjectNumber;
//         *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(hanalysis::HEvent &, const hanalysis::HObject::Tag)
// {
// //     Print(HInformation, "Get leptonic top", Tag);
// //     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) {
// //         ++ObjectNumber;
// //         *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
// //     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetTopLeptonicReader(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = bottom_tagger_.GetJets(Event);
// //     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
// //     if (Jets.empty()) return 0;
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);
// //
// //     if (Doublets.size() > 1) {
// //         std::sort(Doublets.begin(), Doublets.end());
// //         Doublets.erase(Doublets.begin() + 1, Doublets.end());
// //     }
// //
// //     for (const auto & Doublet : Doublets)  {
// //         ++ObjectNumber;
// //         *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(Doublet);
// //     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(HInformation, "Get hadronic tops", Tag);
//     std::vector<HTopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetTopHadronicReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//
// //     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //     std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Doublets, Jets, TopHadronicReader);
//
//
//     std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (Triplets.size() > 1) {
//         std::sort(Triplets.begin(), Triplets.end());
//         Triplets.erase(Triplets.begin() + 1, Triplets.end());
//     }
//
//     for (const auto & Triplet : Triplets) {
//         ++ObjectNumber;
//         *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(Triplet);
//     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetTopSemiTag(hanalysis::HEvent &Event, const hanalysis::HObject::Tag Tag)
// {
//     Print(HInformation, "Get Tops", Tag);
//     std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetTopSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);
//
//     if (Triplets.size() > 1) {
//         std::sort(Triplets.begin(), Triplets.end());
//         Triplets.erase(Triplets.begin() + 1, Triplets.end());
//     }
//
//     for (const auto & Triplet : Triplets) {
//         ++ObjectNumber;
//         *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);
//     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Leptonic Heavy Higgs Tag", Tag);
// //     std::vector<HHeavyHiggsLeptonicBranch> Higgses = HeavyHiggsLeptonicTagger.GetBranches(Event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry()) = Higgs;
// //     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicReader(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = bottom_tagger_.GetJets(Event);
// //     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
// //     if (Jets.empty()) return 0;
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> Doublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Doublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     if (Sextets.size() > 1) {
// //         std::sort(Sextets.begin(), Sextets.end());
// //         Sextets.erase(Sextets.begin() + 1, Sextets.end());
// //     }
// //
// //     for (const auto & Sextet : Sextets)  {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry())  = HeavyHiggsLeptonicTagger.GetBranch(Sextet);
// //     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Hadronic HeavyHiggs Tag", Tag);
// //     std::vector<HHeavyHiggsHadronicBranch> Higgses = HeavyHiggsHadronicTagger.GetBranches(Event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsHadronicBranch *>(Branch->NewEntry()) = Higgs;
// //     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Semi HeavyHiggs Tag", Tag);
//     std::vector<HHeavyHiggsSemiBranch> Higgses = HeavyHiggsSemiTagger.GetBranches(Event, Tag);
//     if (Higgses.empty()) return 0;
//     for (const auto & Higgs : Higgses) {
//         ++ObjectNumber;
//         *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
//
// //     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);
//
//     if (Sextets.size() > 1) {
//         std::sort(Sextets.begin(), Sextets.end());
//         Sextets.erase(Sextets.begin() + 1, Sextets.end());
//     }
//
//     for (const auto & Sextet : Sextets) {
//         ++ObjectNumber;
//         *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = HeavyHiggsSemiTagger.GetBranch(Sextet);
//     }
//
//     return 1;
// }
//
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetEventLeptonicTag(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Event leptonic", Tag);
// //     std::vector<hheavyhiggs::HEventLeptonicBranch *> LeptonicEventBranches = EventLeptonicTagger.GetBranches(Event, Tag);
// //     if (LeptonicEventBranches.empty()) return 0;
// //     for (const auto & LeptonicEvent : LeptonicEventBranches) {
// //         ++ObjectNumber;
// //         *static_cast<HEventLeptonicBranch *>(Branch->NewEntry()) = *LeptonicEvent;
// //     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetEventHadronicTag(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Event hadronic", Tag);
// //     std::vector<hheavyhiggs::HEventHadronicBranch *> HadronicEvents = EventHadronicTagger.GetBranches(Event, Tag);
// //     if (HadronicEvents.empty()) return 0;
// //     for (const auto & HadronicEvent : HadronicEvents) {
// //         ++ObjectNumber;
// //         *static_cast<HEventHadronicBranch *>(Branch->NewEntry()) = *HadronicEvent;
// //     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetEventLeptonicReader(hanalysis::HEvent &, const Tag)
// {
// //     Print(HInformation, "Get Leptonic reader", Tag);
// //
// //     HJets Jets = bottom_tagger_.GetJets(Event);
// //     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
// //     if (Jets.empty()) return 0;
// //
// //     Print(HInformation, "Jet Pair");
// //
// //     std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
// //
// //     Print(HInformation, "Top");
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> LeptonicDoublets = TopLeptonicTagger.GetBdt(Jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(LeptonicDoublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     HEventStruct EventStruct;
// //     EventStruct.LeptonNumber = Leptons.size();
// //     EventStruct.JetNumber = Jets.size();
// //     EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
// //     EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
// //
// //     std::vector<HOctet> Octets = EventLeptonicTagger.GetBdt(Sextets, Doublets, Jets, EventStruct, EventLeptonicReader);
// //     if (Octets.empty()) return 0;
// //     Octets.front().SetTag(Tag);
// //
// //     hheavyhiggs::HEventLeptonicBranch *LeptonicEvent = new hheavyhiggs::HEventLeptonicBranch();
// //     EventLeptonicTagger.FillBranch(LeptonicEvent, Octets.front());
// //
// //     ++ObjectNumber;
// //     HEventLeptonicBranch *NewEventBranch = static_cast<HEventLeptonicBranch *>(Branch->NewEntry());
// //     *NewEventBranch = *LeptonicEvent;
// //
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetSignatureSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Signature semi", Tag);
//     std::vector<hheavyhiggs::HOctetBranch> Signatures = SignatureSemiTagger.GetBranches(Event, Tag);
//     if (Signatures.empty()) return 0;
//     for (const auto & Signature : Signatures) {
//         ++ObjectNumber;
//         *static_cast<HOctetBranch *>(Branch->NewEntry()) = Signature;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetSignatureSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Signature Semi Reader", Tag);
//
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//     std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
//
// //     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
//     //     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);
//
//     std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Doublets, SignatureSemiReader);
//     if (Octets.empty()) return 0;
//
//     if (Octets.size() > 1) {
//         std::sort(Octets.begin(), Octets.end());
//         Octets.erase(Octets.begin() + 1, Octets.end());
//     }
//     Octets.front().SetTag(Tag);
//     ++ObjectNumber;
//     *static_cast<HOctetBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(Octets.front());
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetEventSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//     std::vector<hheavyhiggs::HEventSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
//     if (SemiEvents.empty()) return 0;
//     for (const auto & SemiEvent : SemiEvents) {
//         ++ObjectNumber;
//         *static_cast<HEventSemiBranch *>(Branch->NewEntry()) = SemiEvent;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetEventSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//     //must be in the beginning to get the counting right
//
//     HJets PreJets = bottom_tagger_.GetJets(Event);
//     HJets Jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
//     HJets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
//     if (Jets.empty()) return 0;
//     if (SubJets.empty()) return 0;
//
//     std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(Jets, JetPairReader);
// //     Print(HError, "Doublets", Doublets.size());
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> DoubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HTriplet> TripletsSemi = TopSemiTagger.GetBdt(DoubletsSemi, Jets, TopSemiReader);
// //     Print(HError, "Triplets Semi", TripletsSemi.size());
//
// //     std::vector<hanalysis::HDoublet> DoubletsHadronic = WHadronicTagger.GetBdt(Jets, WHadronicReader);
// //     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(DoubletsHadronic, Jets, TopHadronicReader);
//     std::vector<hanalysis::HTriplet> TripletsHadronic = TopHadronicTagger.GetBdt(Jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
// //     Print(HError, "Triplets Hadronic", TripletsHadronic.size());
//
//     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(TripletsSemi, TripletsHadronic, HeavyHiggsSemiReader);
// //     Print(HError, "Sextets", Sextets.size());
//
//     std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, Doublets, SignatureSemiReader);
// //     Print(HError, "Octets", Octets.size());
//
//     HEventStruct EventStruct;
//     EventStruct.LeptonNumber = Leptons.size();
//     EventStruct.JetNumber = Jets.size();
//     EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
//     EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
//     EventStruct.MissingEt = Event.GetJets()->GetMissingEt().pt();
// //   if (EventStruct.LeptonNumber > 0) EventStruct.LeptonPt = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets()).front().pt();
//
//     std::vector<HEventMultiplet<HOctet>> Events = EventSemiTagger.GetBdt(Octets, Jets, SubJets, Leptons,  EventStruct, EventSemiReader);
//     if (Events.empty()) return 0;
//     Events.front().SetTag(Tag);
// //     ++ObjectNumber; // FIXME should be switched on to avoid long duration of last step
//     *static_cast<HEventSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(Events.front());
//     return 1;
// }
