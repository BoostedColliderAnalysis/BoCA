# include "HAnalysisHeavyHiggsMva.hh"

// hheavyhiggs::HAnalysisMva::HAnalysisMva()
// {
// //     ReadConfig();
// //     DebugLevel = analysis::Object::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     JetPairTagger.SetAnalysisName(ProjectName());
//     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     WSemiTagger.SetAnalysisName(ProjectName());
//     top_hadronic_tagger.SetAnalysisName(ProjectName());
//     TopSemiTagger.SetAnalysisName(ProjectName());
//     HeavyHiggsSemiTagger.SetAnalysisName(ProjectName());
//     SignatureSemiTagger.SetAnalysisName(ProjectName());
//     eventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hheavyhiggs::HAnalysisMva::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Get Study Names", Tagger);
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
//     case WHadronicTagger:
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
//     case TopHadronicTagger:
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
//     case EventLeptonicTagger:
//         return  "eventLeptonic";
//     case EventHadronicTagger:
//         return  "eventHadronic";
//     case EventLeptonicReader:
//         return  "eventLeptonicReader";
//     case HSignatureSemiTagger:
//         return  "SignatureSemi";
//     case HSignatureSemiReader:
//         return  "SignatureSemiReader";
//     case EventSemiTagger:
//         return  "eventSemi";
//     case EventSemiReader:
//         return  "eventSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<analysis::File> hheavyhiggs::HAnalysisMva::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;
    std::vector<analysis::File> BackgroundLeptonicFiles;
    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(analysis::File(SignalName, SignalCrosssection(), Mass()));
//     SignalSemiFiles.emplace_back(BackgroundFile(ttbb));

//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

    std::vector<analysis::File> SignalHadronicFiles;

    std::vector<analysis::File> BackgroundHadronicFiles;

    std::vector<analysis::File> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<analysis::File> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<analysis::File> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<analysis::File> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<analysis::File> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);

    std::vector<analysis::File> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<analysis::File> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<analysis::File> NewFiles;

    switch (tag) {
    case Object::kSignal :
        NewFiles = SignalSemiFiles;
        break;
    case Object::kBackground :
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
//     case WHadronicTagger:
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
//     case TopHadronicTagger:
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
//     case EventLeptonicTagger:
//         if (Tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case EventHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case EventLeptonicReader:
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
//     case EventSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         Print(kError, "unknown tagger name");
//     }

//     NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
//     NewFiles.front().set_file_suffix(".root");
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
//     case WHadronicTagger:
//         w_hadronic_tagger.SetSignalTreeNames(NotLeptonicTrees);
//         w_hadronic_tagger.SetBackgroundTreeNames(NotLeptonicTrees);
//         if (Tag == kSignal) w_hadronic_tagger.SetTagger(BottomTagger);
//         break;
//     case HWHadronicReader :
//         BottomTagger.SetSignalTreeNames(CombinedTrees);
//         BottomTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal) w_hadronic_tagger.SetTagger(BottomTagger);
//         break;
//     case HWSemiTagger :
//         if (Tag == kSignal) WSemiTagger.SetTagger();
//         WSemiTagger.SetSignalTreeNames(SemiTrees);
//         WSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HWSemiReader :
//         break;
//     case TopHadronicTagger :
//         if (Tag == kSignal) top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         top_hadronic_tagger.SetSignalTreeNames(NotLeptonicTrees);
//         top_hadronic_tagger.SetBackgroundTreeNames(NotLeptonicTrees);
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
//         if (Tag == kSignal) HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         HeavyHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         HeavyHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HHeavyHiggsSemiReader :
//         break;
//     case HSignatureSemiTagger :
//         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, HeavyHiggsSemiTagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HSignatureSemiReader :
//         break;
//     case EventSemiTagger :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, HeavyHiggsSemiTagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiReader :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, HeavyHiggsSemiTagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandeled case");
//     }
}

// void hheavyhiggs::HAnalysisMva::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(kInformation, "Prepare Reader", Tagger);
//     if (Tag == kBackground) return;
//     switch (Tagger) {
//     case HBottomTagger:
//         break;
//     case HBottomReader:
//         BottomReader.set_tagger(bottom_tagger_);
//         break;
//     case WHadronicTagger:
//         w_hadronic_tagger.BottomTagger.SetTagger();
//         w_hadronic_tagger.BottomReader.set_tagger(w_hadronic_tagger.BottomTagger);
//         break;
//     case HWHadronicReader:
//         BottomReader.set_tagger(bottom_tagger_);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         break;
//     case HWSemiTagger :
//         break;
//     case HWSemiReader :
//         WSemiReader.set_tagger(WSemiTagger);
//         break;
//     case TopHadronicTagger :
//         top_hadronic_tagger.BottomTagger.SetTagger();
//         top_hadronic_tagger.BottomReader.set_tagger(top_hadronic_tagger.BottomTagger);
//         top_hadronic_tagger.WTagger.SetTagger(BottomTagger);
//         top_hadronic_tagger.WReader.set_tagger(top_hadronic_tagger.WTagger);
//         break;
//     case HTopHadronicReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
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
//         HeavyHiggsSemiTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         HeavyHiggsSemiTagger.TopHadronicReader.set_tagger(HeavyHiggsSemiTagger.top_hadronic_tagger);
//         break;
//     case HHeavyHiggsSemiReader  :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
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
//         SignatureSemiTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         SignatureSemiTagger.TopHadronicReader.set_tagger(SignatureSemiTagger.top_hadronic_tagger);
//         SignatureSemiTagger.HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         SignatureSemiTagger.HeavyHiggsSemiReader.set_tagger(SignatureSemiTagger.HeavyHiggsSemiTagger);
//         SignatureSemiTagger.JetPairTagger.SetTagger(BottomTagger);
//         SignatureSemiTagger.JetPairReader.set_tagger(SignatureSemiTagger.JetPairTagger);
//         break;
//     case HSignatureSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         break;
//     case EventSemiTagger :
//         eventSemiTagger.BottomTagger.SetTagger();
//         eventSemiTagger.BottomReader.set_tagger(eventSemiTagger.BottomTagger);
//         eventSemiTagger.WSemiTagger.SetTagger();
//         eventSemiTagger.WSemiReader.set_tagger(eventSemiTagger.WSemiTagger);
//         eventSemiTagger.WTagger.SetTagger(BottomTagger);
//         eventSemiTagger.WReader.set_tagger(eventSemiTagger.WTagger);
//         eventSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         eventSemiTagger.TopSemiReader.set_tagger(eventSemiTagger.TopSemiTagger);
//         eventSemiTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         eventSemiTagger.TopHadronicReader.set_tagger(eventSemiTagger.top_hadronic_tagger);
//         eventSemiTagger.HeavyHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         eventSemiTagger.HeavyHiggsSemiReader.set_tagger(eventSemiTagger.HeavyHiggsSemiTagger);
//         eventSemiTagger.JetPairTagger.SetTagger(BottomTagger);
//         eventSemiTagger.JetPairReader.set_tagger(eventSemiTagger.JetPairTagger);
//         eventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, HeavyHiggsSemiTagger);
//         eventSemiTagger.SignatureSemiReader.set_tagger(eventSemiTagger.SignatureSemiTagger);
//         break;
//     case EventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         eventSemiReader.set_tagger(eventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
// }

// void hheavyhiggs::HAnalysisMva::NewBranches(ExRootTreeWriter &tree_writer, const analysis::HAnalysis::HTagger tagger)
// {
//     Print(kNotification, "New Branches", tagger);
//
//     switch (tagger) {
//     case BottomTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), BottomBranch::Class());
//         break;
//     case HBottomReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), BottomBranch::Class());
//         break;
//     case HJetPairTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventJetPairBranch::Class());
//         break;
//     case HWSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case WHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), WHadronicBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), WHadronicBranch::Class());
//         break;
//     case HTopLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case TopHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), TopSemiBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), TopSemiBranch::Class());
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
//     case EventLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case EventHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventHadronicBranch::Class());
//         break;
//     case EventLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case HSignatureSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HOctetBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HOctetBranch::Class());
//         break;
//     case EventSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventSemiBranch::Class());
//         break;
//     case EventSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventSemiBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hheavyhiggs::HAnalysisMva::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{
    Print(kInformation, "Analysis");

    Jets Particles = event.Partons().Generator();
    Jets Tops = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Tops.size() != 2) {
        Print(kError, "Not enough top quarks", Tops.size());
        return 0;
    } else {
        if (Tops.at(0).pt() < PreCut()) return 0;
        if (Tops.at(1).pt() < PreCut()) return 0;
    }

    if (event.hadrons().GetMissingEt().pt() < MissingEt()) return 0;
    Jets Leptons = fastjet::sorted_by_pt(event.Leptons().GetLeptonJets());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    Jets jets = event.hadrons().GetJets();
    if (jets.size() < 4) return 0;


    ++event_sum_;

    tagger_.GetBranches(event, stage, tag);

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, Tag);
//     case HBottomReader:
//         return GetBottomReader(event, Tag);
//     case HJetPairTagger :
//         return GetJetPairTag(event, Tag);
//     case HJetPairReader :
//         return GetJetPairReader(event, Tag);
//     case WHadronicTagger :
//         return GetWTag(event, Tag);
//     case HWHadronicReader :
//         return GetWReader(event, Tag);
//     case HWSemiTagger :
//         return GetWSemiTag(event, Tag);
//     case HWSemiReader :
//         return GetWSemiReader(event, Tag);
//     case HTopLeptonicTagger :
//         return GetTopLeptonicTag(event, Tag);
//     case TopHadronicTagger :
//         return GetTopHadronicTag(event, Tag);
//     case HTopSemiTagger :
//         return GetTopSemiTag(event, Tag);
//     case HTopHadronicReader :
//         return GetTopHadronicReader(event, Tag);
//     case HTopLeptonicReader :
//         return GetTopLeptonicReader(event, Tag);
//     case HTopSemiReader :
//         return GetTopSemiReader(event, Tag);
//     case HHeavyHiggsLeptonicTagger :
//         return GetHeavyHiggsLeptonicTag(event, Tag);
//     case HHeavyHiggsHadronicTagger :
//         return GetHeavyHiggsHadronicTag(event, Tag);
//     case HHeavyHiggsSemiTagger :
//         return GetHeavyHiggsSemiTag(event, Tag);
//     case HHeavyHiggsSemiReader :
//         return GetHeavyHiggsSemiReader(event, Tag);
//     case HHeavyHiggsLeptonicReader :
//         return GetHeavyHiggsLeptonicReader(event, Tag);
//     case EventLeptonicTagger :
//         return GeteventLeptonicTag(event, Tag);
//     case EventHadronicTagger :
//         return GeteventHadronicTag(event, Tag);
//     case EventLeptonicReader :
//         return GeteventLeptonicReader(event, Tag);
//     case HSignatureSemiTagger :
//         return GetSignatureSemiTag(event, Tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(event, Tag);
//     case EventSemiTagger :
//         return GeteventSemiTag(event, Tag);
//     case EventSemiReader :
//         return GeteventSemiReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
//     }
}


// bool hheavyhiggs::HAnalysisMva::GetBottomTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Tag", Tag);
//     std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(event, Tag);
//     if (Bottoms.empty()) return 0;
//     for (const auto & Bottom : Bottoms) {
//         ++ObjectNumber;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetBottomReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     if (jets.empty()) return 0;
//
// //     jets = static_cast<analysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(jets);
//
//     Jets Particles = event.Partons().Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetJetPairTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get JetPair Tag", Tag);
//     std::vector<EventJetPairBranch> JetPairs = JetPairTagger.GetBranches(event, Tag);
//     if (JetPairs.empty()) return 0;
//     for (const auto & JetPair : JetPairs) {
//         ++ObjectNumber;
//         *static_cast<EventJetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetJetPairReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get JetPair Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);
//     if (jets.empty()) return 0;
//
//     Jets Particles = event.Partons().Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsFamily(BottomId, GluonId)), Particles.end());
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<EventJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(doublet);
//     }
//     return 1;
//
// }
//
// bool hheavyhiggs::HAnalysisMva::GetWSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get W Semi Tag", Tag);
//     std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(event, Tag);
//     if (WSemis.empty()) return 0;
//     for (const auto & WSemi : WSemis) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetWSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get W Semi Reader", Tag);
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//
//     std::vector<analysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//
//     if (doublets.empty()) return 0;
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(doublet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetWTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get W Tag", Tag);
//     std::vector<WHadronicBranch> Ws = w_hadronic_tagger.GetBranches(event, Tag);
//     if (Ws.empty()) return 0;
//     for (const auto & W : Ws) {
//         ++ObjectNumber;
//         *static_cast<WHadronicBranch *>(Branch->NewEntry()) = W;
//     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetWReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<WHadronicBranch *>(Branch->NewEntry()) = w_hadronic_tagger.GetBranch(doublet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetTopLeptonicTag(analysis::Event &, const analysis::Object::Tag)
// {
// //     Print(kInformation, "Get leptonic top", Tag);
// //     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) {
// //         ++ObjectNumber;
// //         *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
// //     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetTopLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Jets Leptons = event.Leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     if (doublets.size() > 1) {
// //         std::sort(doublets.begin(), doublets.end());
// //         doublets.erase(doublets.begin() + 1, doublets.end());
// //     }
// //
// //     for (const auto & doublet : doublets)  {
// //         ++ObjectNumber;
// //         *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(doublet);
// //     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetTopHadronicTag(analysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "Get hadronic tops", Tag);
//     std::vector<TopHadronicBranch> Tops = top_hadronic_tagger.GetBranches(event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<TopHadronicBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetTopHadronicReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//
// //     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
//
//
//     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (triplets.size() > 1) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + 1, triplets.end());
//     }
//
//     for (const auto & triplet : triplets) {
//         ++ObjectNumber;
//         *static_cast<TopHadronicBranch *>(Branch->NewEntry()) = top_hadronic_tagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetTopSemiTag(analysis::Event &event, const analysis::Object::Tag Tag)
// {
//     Print(kInformation, "Get Tops", Tag);
//     std::vector<TopSemiBranch> Tops = TopSemiTagger.GetBranches(event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetTopSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);
//
//     if (triplets.size() > 1) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + 1, triplets.end());
//     }
//
//     for (const auto & triplet : triplets) {
//         ++ObjectNumber;
//         *static_cast<TopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get Leptonic Heavy Higgs Tag", Tag);
// //     std::vector<HHeavyHiggsLeptonicBranch> Higgses = HeavyHiggsLeptonicTagger.GetBranches(event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry()) = Higgs;
// //     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get event semi", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Jets Leptons = event.Leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<analysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(doublets, MissingEt, HeavyHiggsLeptonicReader);
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
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsHadronicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get Hadronic HeavyHiggs Tag", Tag);
// //     std::vector<HHeavyHiggsHadronicBranch> Higgses = HeavyHiggsHadronicTagger.GetBranches(event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsHadronicBranch *>(Branch->NewEntry()) = Higgs;
// //     }
//     return 1;
// }
//
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get Semi HeavyHiggs Tag", Tag);
//     std::vector<HHeavyHiggsSemiBranch> Higgses = HeavyHiggsSemiTagger.GetBranches(event, Tag);
//     if (Higgses.empty()) return 0;
//     for (const auto & Higgs : Higgses) {
//         ++ObjectNumber;
//         *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetHeavyHiggsSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
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
// bool hheavyhiggs::HAnalysisMva::GeteventLeptonicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get event leptonic", Tag);
// //     std::vector<hheavyhiggs::EventLeptonicBranch *> LeptoniceventBranches = eventLeptonicTagger.GetBranches(event, Tag);
// //     if (LeptoniceventBranches.empty()) return 0;
// //     for (const auto & Leptonicevent : LeptoniceventBranches) {
// //         ++ObjectNumber;
// //         *static_cast<EventLeptonicBranch *>(Branch->NewEntry()) = *Leptonicevent;
// //     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GeteventHadronicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get event hadronic", Tag);
// //     std::vector<hheavyhiggs::EventHadronicBranch *> Hadronicevents = eventHadronicTagger.GetBranches(event, Tag);
// //     if (Hadronicevents.empty()) return 0;
// //     for (const auto & Hadronicevent : Hadronicevents) {
// //         ++ObjectNumber;
// //         *static_cast<EventHadronicBranch *>(Branch->NewEntry()) = *Hadronicevent;
// //     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GeteventLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Get Leptonic reader", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Print(kInformation, "Jet Pair");
// //
// //     std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);
// //
// //     Print(kInformation, "Top");
// //     Jets Leptons = event.Leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> Leptonicdoublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<analysis::HSextet> Sextets = HeavyHiggsLeptonicTagger.GetBdt(Leptonicdoublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     EventStruct eventStruct;
// //     eventStruct.LeptonNumber = Leptons.size();
// //     eventStruct.JetNumber = jets.size();
// //     eventStruct.BottomNumber = event.hadrons().GetBottomJets().size();
// //     eventStruct.ScalarHt = event.hadrons().GetScalarHt();
// //
// //     std::vector<HOctet> Octets = eventLeptonicTagger.GetBdt(Sextets, doublets, jets, eventStruct, eventLeptonicReader);
// //     if (Octets.empty()) return 0;
// //     Octets.front().SetTag(Tag);
// //
// //     hheavyhiggs::EventLeptonicBranch *Leptonicevent = new hheavyhiggs::EventLeptonicBranch();
// //     eventLeptonicTagger.FillBranch(Leptonicevent, Octets.front());
// //
// //     ++ObjectNumber;
// //     EventLeptonicBranch *NeweventBranch = static_cast<EventLeptonicBranch *>(Branch->NewEntry());
// //     *NeweventBranch = *Leptonicevent;
// //
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisMva::GetSignatureSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get Signature semi", Tag);
//     std::vector<hheavyhiggs::HOctetBranch> Signatures = SignatureSemiTagger.GetBranches(event, Tag);
//     if (Signatures.empty()) return 0;
//     for (const auto & Signature : Signatures) {
//         ++ObjectNumber;
//         *static_cast<HOctetBranch *>(Branch->NewEntry()) = Signature;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GetSignatureSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get Signature Semi Reader", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, doublets, SignatureSemiReader);
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
// bool hheavyhiggs::HAnalysisMva::GeteventSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//     std::vector<hheavyhiggs::EventSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
//     if (Semievents.empty()) return 0;
//     for (const auto & Semievent : Semievents) {
//         ++ObjectNumber;
//         *static_cast<EventSemiBranch *>(Branch->NewEntry()) = Semievent;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisMva::GeteventSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//     //must be in the beginning to get the counting right
//
//     Jets PreJets = bottom_tagger_.GetJets(event);
//     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
//     Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
//     if (jets.empty()) return 0;
//     if (SubJets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);
// //     Print(kError, "doublets", doublets.size());
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
// //     Print(kError, "triplets Semi", tripletsSemi.size());
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
// //     Print(kError, "triplets Hadronic", tripletsHadronic.size());
//
//     std::vector<analysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
// //     Print(kError, "Sextets", Sextets.size());
//
//     std::vector<HOctet> Octets = SignatureSemiTagger.GetBdt(Sextets, doublets, SignatureSemiReader);
// //     Print(kError, "Octets", Octets.size());
//
//     EventStruct eventStruct;
//     eventStruct.LeptonNumber = Leptons.size();
//     eventStruct.JetNumber = jets.size();
//     eventStruct.BottomNumber = event.hadrons().GetBottomJets().size();
//     eventStruct.ScalarHt = event.hadrons().GetScalarHt();
//     eventStruct.MissingEt = event.hadrons().GetMissingEt().pt();
// //   if (eventStruct.LeptonNumber > 0) eventStruct.LeptonPt = fastjet::sorted_by_pt(event.Leptons().GetLeptonJets()).front().pt();
//
//     std::vector<EventMultiplet<HOctet>> events = eventSemiTagger.GetBdt(Octets, jets, SubJets, Leptons,  eventStruct, eventSemiReader);
//     if (events.empty()) return 0;
//     events.front().SetTag(Tag);
// //     ++ObjectNumber; // FIXME should be switched on to avoid long duration of last step
//     *static_cast<EventSemiBranch *>(Branch->NewEntry()) = eventSemiTagger.GetBranch(events.front());
//     return 1;
// }
