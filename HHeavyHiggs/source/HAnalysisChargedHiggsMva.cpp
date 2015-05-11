# include "HAnalysisChargedHiggsMva.hh"
# include "Tagger.hh"

// hheavyhiggs::HAnalysisCharged::HAnalysisCharged() :
//     BottomTagger(ProjectName())
// {
//     Print(kNotification, "Constructor");
//
//     tagger_ =
//
//     JetPairTagger.SetAnalysisName(ProjectName());
//     WHadronicTagger.SetAnalysisName(ProjectName());
//     WSemiTagger.SetAnalysisName(ProjectName());
//     TopHadronicTagger.SetAnalysisName(ProjectName());
//     TopSemiTagger.SetAnalysisName(ProjectName());
//     ChargedHiggsSemiTagger.SetAnalysisName(ProjectName());
//     SignatureSemiTagger.SetAnalysisName(ProjectName());
//     EventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hheavyhiggs::HAnalysisCharged::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  BottomTagger :
//         return BottomTagger.tagger_name();
//     case  HBottomReader :
//         return BottomTagger.tagger_name() + "Reader";
//     case HWSemiTagger:
//         return  "WSemi";
//     case HWSemiReader:
//         return  "WSemiReader";
//     case HWHadronicTagger:
//         return  "WHadronic";
//     case HWHadronicReader:
//         return  "WHadronicReader";
//     case HJetPairTagger:
//         return  "ChargedJetPair";
//     case HJetPairReader:
//         return  "ChargedJetPairReader";
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
//         return  "ChargedHiggsLeptonic";
//     case HHeavyHiggsHadronicTagger:
//         return  "ChargedHiggsHadronic";
//     case HHeavyHiggsSemiTagger:
//         return  "ChargedHiggsSemi";
//     case HHeavyHiggsSemiReader:
//         return  "ChargedHiggsSemiReader";
//     case HHeavyHiggsLeptonicReader:
//         return  "ChargedHiggsLeptonicReader";
//     case HEventLeptonicTagger:
//         return  "EventLeptonic";
//     case HEventHadronicTagger:
//         return  "EventHadronic";
//     case HEventLeptonicReader:
//         return  "ChargdLeptonicReader";
//     case HSignatureSemiTagger:
//         return  "ChargedSignatureSemi";
//     case HSignatureSemiReader:
//         return  "ChargedSignatureSemiReader";
//     case HEventSemiTagger:
//         return  "ChargedEventSemi";
//     case HEventSemiReader:
//         return  "ChargedEventSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
//
// }

std::vector<hanalysis::RootFile> hheavyhiggs::HAnalysisCharged::Files(const hanalysis::HObject::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<hanalysis::RootFile> SignalLeptonicFiles;

    std::vector<hanalysis::RootFile> BackgroundLeptonicFiles;

    std::vector<hanalysis::RootFile> SignalSemiFiles;
    std::vector<hanalysis::RootFile> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Htb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(hanalysis::RootFile(SignalName, SignalCrosssection(), Mass()));

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

//     switch (Tagger) {
//     case  BottomTagger :
//         NewFiles = CombinedFiles;
//         break;
//     case  HBottomReader :
//         NewFiles = CombinedFiles;
//         break;
//     case HJetPairTagger:
//         if (tag == kSignal) NewFiles = CombinedSignalFiles;
//         else NewFiles = CombinedFiles;
//         break;
//     case HJetPairReader:
//         if (tag == kSignal) NewFiles = CombinedSignalFiles;
//         else NewFiles = CombinedFiles;
//         break;
//     case HWSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HWSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HWHadronicTagger:
//         if (tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HWHadronicReader:
//         if (tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopLeptonicTagger:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HTopLeptonicReader:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HTopHadronicTagger:
//         if (tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HTopHadronicReader:
//         if (tag == kSignal) NewFiles = NonLeptonicSignalFiles;
//         else NewFiles = NotLeptonicFiles;
//         break;
//     case HTopSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;
//         break;
//     case HHeavyHiggsLeptonicTagger:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HHeavyHiggsLeptonicReader:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = LeptonicFiles;
//         break;
//     case HHeavyHiggsHadronicTagger:
//         if (tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = HadronicFiles;
//         break;
//     case HHeavyHiggsSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = SemiFiles;//BackgroundSemiFiles;
//         break;
// //     case HHeavyHiggsSemiReader:
// //         if (Tag == kSignal) NewFiles = SignalSemiFiles;
// //         else NewFiles = BackgroundSemiFiles;
// //         break;
//     case HEventLeptonicTagger:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HEventHadronicTagger:
//         if (tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case HEventLeptonicReader:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HSignatureSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HSignatureSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//     }

    switch (tag) {
      case HObject::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case HObject::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

    NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
    NewFiles.front().set_file_suffix(".root");
    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;
}

void hheavyhiggs::HAnalysisCharged::SetTrees()
{

    Strings SignalLeptonicTrees {};
    Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Htb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    Strings SignalSemiTrees {SignalTree};

    Strings BackgroundSemiTrees {
//       BackgroundTree(ttbb),
//       BackgroundTree(ttcc),
//       BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    Strings SignalHadronicTree {};
    Strings BackgroundHadronicTrees {};

    Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetTreeNames(CombinedTrees);
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         break;
//     case HBottomReader:
//         break;
//     case HJetPairTagger :
//         JetPairTagger.SetSignalTreeNames(CombinedTrees);
//         JetPairTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal) JetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
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
//         if (Tag == kSignal) ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         ChargedHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         ChargedHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HHeavyHiggsSemiReader :
//         break;
//     case HSignatureSemiTagger :
//         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HSignatureSemiReader :
// //         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
// //         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HEventSemiTagger :
//         if (Tag == kSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger, SignatureSemiTagger);
//         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HEventSemiReader :
//         if (Tag == kSignal) EventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger, SignatureSemiTagger);
//         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }

//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void hheavyhiggs::HAnalysisCharged::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(kInformation, "Prepare Reader", Tagger);
//
//     if (Tag == kBackground) return;
//
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
//         ChargedHiggsSemiTagger.BottomTagger.SetTagger();
//         ChargedHiggsSemiTagger.BottomReader.set_tagger(ChargedHiggsSemiTagger.BottomTagger);
//         ChargedHiggsSemiTagger.WSemiTagger.SetTagger();
//         ChargedHiggsSemiTagger.WSemiReader.set_tagger(ChargedHiggsSemiTagger.WSemiTagger);
//         ChargedHiggsSemiTagger.WTagger.SetTagger(BottomTagger);
//         ChargedHiggsSemiTagger.WReader.set_tagger(ChargedHiggsSemiTagger.WTagger);
//         ChargedHiggsSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         ChargedHiggsSemiTagger.TopSemiReader.set_tagger(ChargedHiggsSemiTagger.TopSemiTagger);
//         ChargedHiggsSemiTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         ChargedHiggsSemiTagger.TopHadronicReader.set_tagger(ChargedHiggsSemiTagger.TopHadronicTagger);
//         break;
//     case HHeavyHiggsSemiReader  :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
//         break;
//     case HJetPairTagger :
//         JetPairTagger.BottomTagger.SetTagger();
//         JetPairTagger.BottomReader.set_tagger(JetPairTagger.BottomTagger);
//         JetPairTagger.WSemiTagger.SetTagger();
//         JetPairTagger.WSemiReader.set_tagger(JetPairTagger.WSemiTagger);
//         JetPairTagger.WTagger.SetTagger(BottomTagger);
//         JetPairTagger.WReader.set_tagger(JetPairTagger.WTagger);
//         JetPairTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         JetPairTagger.TopSemiReader.set_tagger(JetPairTagger.TopSemiTagger);
//         JetPairTagger.TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         JetPairTagger.TopHadronicReader.set_tagger(JetPairTagger.TopHadronicTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
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
//         SignatureSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         SignatureSemiTagger.ChargedHiggsSemiReader.set_tagger(SignatureSemiTagger.ChargedHiggsSemiTagger);
//         SignatureSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         SignatureSemiTagger.ChargedJetPairReader.set_tagger(SignatureSemiTagger.ChargedJetPairTagger);
//         break;
//     case HSignatureSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
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
//         EventSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         EventSemiTagger.ChargedHiggsSemiReader.set_tagger(EventSemiTagger.ChargedHiggsSemiTagger);
//         EventSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger);
//         EventSemiTagger.ChargedJetPairReader.set_tagger(EventSemiTagger.ChargedJetPairTagger);
//         EventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, ChargedHiggsSemiTagger);
//         EventSemiTagger.SignatureSemiReader.set_tagger(EventSemiTagger.SignatureSemiTagger);
//         break;
//     case HEventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         EventSemiReader.set_tagger(EventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
//
// }
//
// void hheavyhiggs::HAnalysisCharged::NewBranches(ExRootTreeWriter &tree_writer, const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::Tagger::Stage stage)
// {
//     Print(kNotification, "New Branches", Tagger);
//
//     switch (Tagger) {
//     case BottomTagger :
//         BottomTagger.SetTreeBranch(tree_writer, stage);
// //         Branch = BottomTagger.SetBranch(tree_writer, hanalysis::Tagger::kTrainer);
// //         break;
// //     case HBottomReader :
// //         Branch = BottomTagger.SetBranch(tree_writer, hanalysis::Tagger::kReader);
//         break;
//     case HJetPairTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedJetPairBranch::Class());
//         break;
//     case HWSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
//         break;
//     case HTopLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicReader:
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsHadronicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
//         break;
//     case HHeavyHiggsSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedHiggsSemiBranch::Class());
//         break;
//     case HEventLeptonicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
//         break;
//     case HEventHadronicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventHadronicBranch::Class());
//         break;
//     case HSignatureSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
//         break;
//     case HEventSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
//         break;
//     case HEventSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
//         break;
//     case HEventLeptonicReader :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HEventLeptonicBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hheavyhiggs::HAnalysisCharged::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Analysis");

    Jets Particles = event.GetParticles()->Generator();
    Jets Quarks = fastjet::sorted_by_pt(RemoveIfNot5Quarks(Particles));
    Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, TopId));
    if (Quarks.empty()) {
//       if (Tag == kSignal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
//       if (PreCut() > 0)
        Print(kError, "Not enough bottom quarks", Quarks.size());
        return 0;
    } else if (Quarks.front().pt() < PreCut()) return 0;


    Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, TopId));
    if (TopQuarks.size() != 2) {
        Print(kError, "Not enough top quarks", TopQuarks.size());
        return 0;
    } else if (TopQuarks.front().pt() < PreCut()) return 0;


    if (event.GetJets()->GetMissingEt().pt() < MissingEt()) return 0;
    Jets Leptons = fastjet::sorted_by_pt(event.GetLeptons()->GetLeptonJets());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    Jets jets = bottom_tagger_.GetJets(event);
    if (jets.size() < 4) return 0;

    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, tag);
//     case HBottomReader:
//         return GetBottomReader(event, tag);
//     case HJetPairTagger :
//         return GetJetPairTag(event, tag);
//     case HJetPairReader :
//         return GetJetPairReader(event, tag);
//     case HWHadronicTagger :
//         return GetWTag(event, tag);
//     case HWHadronicReader :
//         return GetWReader(event, tag);
//     case HWSemiTagger :
//         return GetWSemiTag(event, tag);
//     case HWSemiReader :
//         return GetWSemiReader(event, tag);
//     case HTopLeptonicTagger :
//         return GetTopLeptonicTag(event, tag);
//     case HTopHadronicTagger :
//         return GetTopHadronicTag(event, tag);
//     case HTopSemiTagger :
//         return GetTopSemiTag(event, tag);
//     case HTopHadronicReader :
//         return GetTopHadronicReader(event, tag);
//     case HTopLeptonicReader :
//         return GetTopLeptonicReader(event, tag);
//     case HTopSemiReader :
//         return GetTopSemiReader(event, tag);
//     case HHeavyHiggsLeptonicTagger :
// //         return GetHeavyHiggsLeptonicTag(Event, Tag);
//     case HHeavyHiggsHadronicTagger :
// //         return GetHeavyHiggsHadronicTag(Event, Tag);
//     case HHeavyHiggsSemiTagger :
//         return GetChargedHiggsSemiTag(event, tag);
//     case HHeavyHiggsSemiReader :
//         return GetChargdHiggsSemiReader(event, tag);
//     case HHeavyHiggsLeptonicReader :
// //         return GetHeavyHiggsLeptonicReader(Event, Tag);
//     case HEventLeptonicTagger :
// //         return GetEventLeptonicTag(Event, Tag);
//     case HEventHadronicTagger :
// //         return GetEventHadronicTag(Event, Tag);
//     case HSignatureSemiTagger :
//         return GetSignatureSemiTag(event, tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(event, tag);
//     case HEventSemiTagger :
//         return GetEventSemiTag(event, tag);
//     case HEventSemiReader :
//         return GetEventSemiReader(event, tag);
//     case HEventLeptonicReader :
// //         return GetEventLeptonicReader(Event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
//     }

    return tagger_.GetBranches(event, stage, tag);
}

/*
bool hheavyhiggs::HAnalysisCharged::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Bottom Tag", Tag);
    std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.empty()) return 0;
    for (const auto & Bottom : Bottoms) {
        *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
        ++ObjectNumber;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kDebug, "Get Bottom Reader", Tag);
    Jets jets = bottom_tagger_.GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
        static_cast<hanalysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }


//     for (const auto Jet : jets)  Print(kError, "B Bdt", Jet.user_info<hanalysis::JetInfo>().Bdt());
    for (const auto & Jet : jets)  {
//         static_cast<hanalysis::JetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         static_cast<hanalysis::JetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(BottomTagger.GetTag(Jet));
        if (Tag != Jet.user_info<hanalysis::JetInfo>().Tag()) continue;
//         if (Tag == kSignal && Jet.user_info<hanalysis::JetInfo>().MaximalFraction() < .8)continue;
        if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
        *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
        ++ObjectNumber;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWSemiTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
    if (WSemis.empty()) return 0;
    for (const auto & WSemi : WSemis) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWSemiReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kDebug, "Get W Semi Reader", Tag);

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();

    std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);

    if (doublets.empty()) return 0;

    if (doublets.size() > 1) {
        std::sort(doublets.begin(), doublets.end());
        doublets.erase(doublets.begin() + 1, doublets.end());
    }

    for (const auto & doublet : doublets) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(doublet);
    }

    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kDebug, "Get W Tag", Tag);
    std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
    if (Ws.empty()) return 0;
    for (const auto & W : Ws) {
        ++ObjectNumber;
        *static_cast<HWBranch *>(Branch->NewEntry()) = W;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetWReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    std::vector<hanalysis::Doublet> doublets = WHadronicTagger.GetBdt(jets, WHadronicReader);

    for (const auto & Jet : jets)  {
        Jets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
        Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::Doublet> Piecedoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
        doublets.insert(doublets.end(), Piecedoublets.begin(), Piecedoublets.end());
    }

    for (const auto & Jet : jets)  {
        Jets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
        Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
        std::vector<hanalysis::Doublet> Piecedoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
        doublets.insert(doublets.end(), Piecedoublets.begin(), Piecedoublets.end());
    }


    if (doublets.size() > 1) {
        std::sort(doublets.begin(), doublets.end());
        doublets.erase(doublets.begin() + 1, doublets.end());
    }

    for (const auto & doublet : doublets) {
        ++ObjectNumber;
        *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(doublet);
    }

    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicTag(hanalysis::HEvent &,  Tag)
{
    Print(kInformation, "Get leptonic top");
//     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(Event, Tag);
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicReader(hanalysis::HEvent &, const Tag)
{
    Print(kInformation, "Get Event semi");

//     Jets jets = Event.GetJets()->GetStructuredJets();
//     jets = BottomTagger.GetBdt(jets, BottomReader);
//
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
//     if (Leptons.size() < 2) return 0;
//
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(doublet);
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopHadronicTag(hanalysis::HEvent &Event,  Tag Tag)
{
    Print(kInformation, "Get hadronic tops", Tag);
    std::vector<TopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
    if (Tops.empty()) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = Top;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetTopHadronicReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);

    Jets jets = TopHadronicTagger.GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);


    std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);

//     std::vector<hanalysis::Doublet> doublets = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(doublets, jets, TopHadronicReader);
//     for (const auto & Jet : jets)  {
//         Jets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<hanalysis::Doublet> Piecedoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
//         std::vector<hanalysis::Triplet> Piecetriplets = TopHadronicTagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<hanalysis::Doublet> Piecedoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
//         std::vector<hanalysis::Triplet> Piecetriplets = TopHadronicTagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }


    if (triplets.size() > 1) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    for (const auto & triplet : triplets) {
        ++ObjectNumber;
        TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = TopHadronicTagger.GetBranch(triplet);
    }

    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetTopSemiTag(hanalysis::HEvent &Event,  Tag Tag)
{
    Print(kInformation, "Get Tops", Tag);
    std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag, PreCut());
    if (Tops.empty()) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopSemiReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);

//     Jets jets = Event.GetJets()->GetStructuredJets();

    Jets jets = bottom_tagger_.GetJets(Event);

    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);

    if (triplets.size() > 1) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    for (const auto & triplet : triplets) {
        ++ObjectNumber;
        *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(triplet);
    }

    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetJetPairTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kDebug, "Get JetPair Tag", Tag);
    std::vector<HChargedJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag);
    if (JetPairs.empty()) return 0;
    for (const auto & JetPair : JetPairs) {
        ++ObjectNumber;
        *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPair;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetJetPairReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kDebug, "Get JetPair Reader", Tag);

    Jets jets = bottom_tagger_.GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    std::vector<hanalysis::Doublet> doubletsHadronic = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
    std::vector<hanalysis::HQuartet31> Quartets = JetPairTagger.GetBdt(triplets, jets, JetPairReader);

    if (Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end());
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    for (const auto & Quartet : Quartets) {
        ++ObjectNumber;
        *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPairTagger.GetBranch(Quartet);
    }

    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetChargedHiggsSemiTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Semi HeavyHiggs Tag", Tag);
    std::vector<HChargedHiggsSemiBranch> Higgses = ChargedHiggsSemiTagger.GetBranches(Event, Tag);
    if (Higgses.empty()) return 0;
    for (const auto & Higgs : Higgses) {
        ++ObjectNumber;
        *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetChargdHiggsSemiReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::Triplet> triplets = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<hanalysis::Doublet> doubletsHadronic = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());

    std::vector<hanalysis::HQuartet31> Quartets = ChargedHiggsSemiTagger.GetBdt(triplets, jets, ChargedHiggsSemiReader);

    if (Quartets.size() > 1) {
        std::sort(Quartets.begin(), Quartets.end());
        Quartets.erase(Quartets.begin() + 1, Quartets.end());
    }

    for (const auto & Quartet : Quartets) {
        ++ObjectNumber;
        *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = ChargedHiggsSemiTagger.GetBranch(Quartet);
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetSignatureSemiTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);
    std::vector<HChargedOctetBranch> SemiEvents = SignatureSemiTagger.GetBranches(Event, Tag);
    if (SemiEvents.empty()) return 0;
    for (const auto & SemiEvent : SemiEvents) {
        ++ObjectNumber;
        *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = SemiEvent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetSignatureSemiReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(Event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

    std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//     std::vector<hanalysis::Doublet> doubletsHadronic = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    //     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());

    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);

    std::vector<hanalysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(tripletsHadronic, jets, JetPairReader);

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);
    if (Octets.empty()) return 0;

    if (Octets.size() > 1) {
        std::sort(Octets.begin(), Octets.end());
        Octets.erase(Octets.begin() + 1, Octets.end());
    }
    Octets.front().SetTag(Tag);

    for (const auto & Octet : Octets) {
        *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(Octet);
        ++ObjectNumber;
    }

    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetEventSemiTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);
    std::vector<hheavyhiggs::HChargedSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
    if (SemiEvents.empty()) return 0;
    for (const auto & SemiEvent : SemiEvents) {
        ++ObjectNumber;
        static_cast<HChargedSemiBranch &>(*Branch->NewEntry()) = SemiEvent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetEventSemiReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(kInformation, "Get Event semi", Tag);

    Jets PreJets = bottom_tagger_.GetJets(Event);
    Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
    if (jets.empty()) return 0;
    if (SubJets.empty()) return 0;

    Jets Leptons = Event.GetLeptons()->GetLeptonJets();
    fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
    std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    std::vector<hanalysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);


    std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);

//     std::vector<hanalysis::Doublet> doubletsHadronic = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     for (const auto & Jet : jets)  {
//       Jets Pieces = WHadronicTagger.GetSubJets(Jet, 2);
//       Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//       std::vector<hanalysis::Doublet> Piecedoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
//       std::vector<hanalysis::Triplet> Piecetriplets = TopHadronicTagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//       tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//       Jets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
//       Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//       std::vector<hanalysis::Doublet> Piecedoublets = WHadronicTagger.GetBdt(Pieces, WHadronicReader);
//       std::vector<hanalysis::Triplet> Piecetriplets = TopHadronicTagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//       tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     std::vector<hanalysis::Triplet> Finaltriplets;
//     if (Tag == kSignal) {
//       Jets Particles = Event.GetParticles()->Generator();
//       Jets TopParticles = WHadronicTagger.RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
//       if (TopParticles.size() != 1) Print(kError, "Where is the Top?");
//       else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.at(0)) < WHadronicTagger.detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
//     } else Finaltriplets = tripletsHadronic;


    std::vector<hanalysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(tripletsHadronic, jets, JetPairReader);

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);

    HEventStruct EventStruct;
    EventStruct.LeptonNumber = Leptons.size();
    EventStruct.JetNumber = jets.size();
    EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
    EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
    EventStruct.MissingEt = Event.GetJets()->GetMissingEt().pt();

    std::vector<HEventMultiplet<HOctet44>> Events = EventSemiTagger.GetBdt(Octets, jets, SubJets, Leptons, EventStruct, EventSemiReader);
    if (Events.empty()) return 0;
    Events.front().SetTag(Tag);

//     ++ObjectNumber; // this should be switched on otherwise the last step of the analysis takes very long
    static_cast<HChargedSemiBranch &>(*Branch->NewEntry()) = EventSemiTagger.GetBranch(Events.front());
    return 1;
}*/
