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
//     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     WSemiTagger.SetAnalysisName(ProjectName());
//     top_hadronic_tagger.SetAnalysisName(ProjectName());
//     TopSemiTagger.SetAnalysisName(ProjectName());
//     ChargedHiggsSemiTagger.SetAnalysisName(ProjectName());
//     SignatureSemiTagger.SetAnalysisName(ProjectName());
//     eventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hheavyhiggs::HAnalysisCharged::StudyName(const analysis::HAnalysis::HTagger Tagger) const
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
//     case WHadronicTagger:
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
//     case TopHadronicTagger:
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
//     case EventLeptonicTagger:
//         return  "eventLeptonic";
//     case EventHadronicTagger:
//         return  "eventHadronic";
//     case EventLeptonicReader:
//         return  "ChargdLeptonicReader";
//     case HSignatureSemiTagger:
//         return  "ChargedSignatureSemi";
//     case HSignatureSemiReader:
//         return  "ChargedSignatureSemiReader";
//     case EventSemiTagger:
//         return  "ChargedeventSemi";
//     case EventSemiReader:
//         return  "ChargedeventSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
//
// }

std::vector<analysis::File> hheavyhiggs::HAnalysisCharged::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;

    std::vector<analysis::File> BackgroundLeptonicFiles;

    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Htb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(analysis::File(SignalName, SignalCrosssection(), Mass()));

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
//     case WHadronicTagger:
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
//     case TopHadronicTagger:
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
//     case EventLeptonicTagger:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case EventHadronicTagger:
//         if (tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case EventLeptonicReader:
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
//     case EventSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//     }

    switch (tag) {
      case Object::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case Object::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

//     NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
//     NewFiles.front().set_file_suffix(".root");
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
//         if (Tag == kSignal) JetPairTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
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
//         if (Tag == kSignal) ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         ChargedHiggsSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         ChargedHiggsSemiTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HHeavyHiggsSemiReader :
//         break;
//     case HSignatureSemiTagger :
//         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HSignatureSemiReader :
// //         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger);
// //         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiTagger :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiReader :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }

//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void hheavyhiggs::HAnalysisCharged::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         ChargedHiggsSemiTagger.BottomTagger.SetTagger();
//         ChargedHiggsSemiTagger.BottomReader.set_tagger(ChargedHiggsSemiTagger.BottomTagger);
//         ChargedHiggsSemiTagger.WSemiTagger.SetTagger();
//         ChargedHiggsSemiTagger.WSemiReader.set_tagger(ChargedHiggsSemiTagger.WSemiTagger);
//         ChargedHiggsSemiTagger.WTagger.SetTagger(BottomTagger);
//         ChargedHiggsSemiTagger.WReader.set_tagger(ChargedHiggsSemiTagger.WTagger);
//         ChargedHiggsSemiTagger.TopSemiTagger.SetTagger(BottomTagger, WSemiTagger);
//         ChargedHiggsSemiTagger.TopSemiReader.set_tagger(ChargedHiggsSemiTagger.TopSemiTagger);
//         ChargedHiggsSemiTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         ChargedHiggsSemiTagger.TopHadronicReader.set_tagger(ChargedHiggsSemiTagger.top_hadronic_tagger);
//         break;
//     case HHeavyHiggsSemiReader  :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
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
//         JetPairTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         JetPairTagger.TopHadronicReader.set_tagger(JetPairTagger.top_hadronic_tagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
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
//         SignatureSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         SignatureSemiTagger.ChargedHiggsSemiReader.set_tagger(SignatureSemiTagger.ChargedHiggsSemiTagger);
//         SignatureSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         SignatureSemiTagger.ChargedJetPairReader.set_tagger(SignatureSemiTagger.ChargedJetPairTagger);
//         break;
//     case HSignatureSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
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
//         eventSemiTagger.ChargedHiggsSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         eventSemiTagger.ChargedHiggsSemiReader.set_tagger(eventSemiTagger.ChargedHiggsSemiTagger);
//         eventSemiTagger.ChargedJetPairTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger);
//         eventSemiTagger.ChargedJetPairReader.set_tagger(eventSemiTagger.ChargedJetPairTagger);
//         eventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, JetPairTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, ChargedHiggsSemiTagger);
//         eventSemiTagger.SignatureSemiReader.set_tagger(eventSemiTagger.SignatureSemiTagger);
//         break;
//     case EventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(JetPairTagger);
//         ChargedHiggsSemiReader.set_tagger(ChargedHiggsSemiTagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         eventSemiReader.set_tagger(eventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
//
// }
//
// void hheavyhiggs::HAnalysisCharged::NewBranches(ExRootTreeWriter &tree_writer, const analysis::HAnalysis::HTagger Tagger, const analysis::Tagger::Stage stage)
// {
//     Print(kNotification, "New Branches", Tagger);
//
//     switch (Tagger) {
//     case BottomTagger :
//         BottomTagger.SetTreeBranch(tree_writer, stage);
// //         Branch = BottomTagger.SetBranch(tree_writer, analysis::Tagger::kTrainer);
// //         break;
// //     case HBottomReader :
// //         Branch = BottomTagger.SetBranch(tree_writer, analysis::Tagger::kReader);
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
//     case WHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), WHadronicBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), WHadronicBranch::Class());
//         break;
//     case HTopLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case TopHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopSemiBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopSemiBranch::Class());
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
//     case EventLeptonicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case EventHadronicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventHadronicBranch::Class());
//         break;
//     case HSignatureSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
//         break;
//     case EventSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
//         break;
//     case EventSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedSemiBranch::Class());
//         break;
//     case EventLeptonicReader :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hheavyhiggs::HAnalysisCharged::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{
    Print(kInformation, "Analysis");

    Jets Particles = event.Partons().Generator();
    Jets Quarks = fastjet::sorted_by_pt(analysis::RemoveIfNot5Quarks(Particles));
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


    if (event.hadrons().GetMissingEt().pt() < MissingEt()) return 0;
    Jets Leptons = fastjet::sorted_by_pt(event.Leptons().GetLeptonJets());
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
//     case WHadronicTagger :
//         return GetWTag(event, tag);
//     case HWHadronicReader :
//         return GetWReader(event, tag);
//     case HWSemiTagger :
//         return GetWSemiTag(event, tag);
//     case HWSemiReader :
//         return GetWSemiReader(event, tag);
//     case HTopLeptonicTagger :
//         return GetTopLeptonicTag(event, tag);
//     case TopHadronicTagger :
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
// //         return GetHeavyHiggsLeptonicTag(event, Tag);
//     case HHeavyHiggsHadronicTagger :
// //         return GetHeavyHiggsHadronicTag(event, Tag);
//     case HHeavyHiggsSemiTagger :
//         return GetChargedHiggsSemiTag(event, tag);
//     case HHeavyHiggsSemiReader :
//         return GetChargdHiggsSemiReader(event, tag);
//     case HHeavyHiggsLeptonicReader :
// //         return GetHeavyHiggsLeptonicReader(event, Tag);
//     case EventLeptonicTagger :
// //         return GeteventLeptonicTag(event, Tag);
//     case EventHadronicTagger :
// //         return GeteventHadronicTag(event, Tag);
//     case HSignatureSemiTagger :
//         return GetSignatureSemiTag(event, tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(event, tag);
//     case EventSemiTagger :
//         return GeteventSemiTag(event, tag);
//     case EventSemiReader :
//         return GeteventSemiReader(event, tag);
//     case EventLeptonicReader :
// //         return GeteventLeptonicReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
//     }

    return tagger_.GetBranches(event, stage, tag);
}

/*
bool hheavyhiggs::HAnalysisCharged::GetBottomTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get Bottom Tag", Tag);
    std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(event, Tag);
    if (Bottoms.empty()) return 0;
    for (const auto & Bottom : Bottoms) {
        *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
        ++ObjectNumber;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetBottomReader(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Get Bottom Reader", Tag);
    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Particles = event.Partons().Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
        static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }


//     for (const auto Jet : jets)  Print(kError, "B Bdt", Jet.user_info<analysis::JetInfo>().Bdt());
    for (const auto & Jet : jets)  {
//         static_cast<analysis::JetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         static_cast<analysis::JetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(BottomTagger.GetTag(Jet));
        if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) continue;
//         if (Tag == kSignal && Jet.user_info<analysis::JetInfo>().MaximalFraction() < .8)continue;
        if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
        *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
        ++ObjectNumber;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Get W Semi Tag", Tag);
    std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(event, Tag);
    if (WSemis.empty()) return 0;
    for (const auto & WSemi : WSemis) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetWSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Get W Semi Reader", Tag);

    Jets Leptons = event.Leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<analysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);

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

bool hheavyhiggs::HAnalysisCharged::GetWTag(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Get W Tag", Tag);
    std::vector<WHadronicBranch> Ws = w_hadronic_tagger.GetBranches(event, Tag);
    if (Ws.empty()) return 0;
    for (const auto & W : Ws) {
        ++ObjectNumber;
        *static_cast<WHadronicBranch *>(Branch->NewEntry()) = W;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetWReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);

    for (const auto & Jet : jets)  {
        Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 2);
        Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
        std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
        doublets.insert(doublets.end(), Piecedoublets.begin(), Piecedoublets.end());
    }

    for (const auto & Jet : jets)  {
        Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 3);
        Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
        std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
        doublets.insert(doublets.end(), Piecedoublets.begin(), Piecedoublets.end());
    }


    if (doublets.size() > 1) {
        std::sort(doublets.begin(), doublets.end());
        doublets.erase(doublets.begin() + 1, doublets.end());
    }

    for (const auto & doublet : doublets) {
        ++ObjectNumber;
        *static_cast<WHadronicBranch *>(Branch->NewEntry()) = w_hadronic_tagger.GetBranch(doublet);
    }

    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicTag(analysis::Event &,  Tag)
{
    Print(kInformation, "Get leptonic top");
//     std::vector<HTopLeptonicBranch> Tops = TopLeptonicTagger.GetBranches(event, Tag);
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetTopLeptonicReader(analysis::Event &, const Tag)
{
    Print(kInformation, "Get event semi");

//     Jets jets = event.hadrons().GetStructuredJets();
//     jets = BottomTagger.GetBdt(jets, BottomReader);
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     if (Leptons.size() < 2) return 0;
//
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) *static_cast<HTopLeptonicBranch *>(Branch->NewEntry()) = TopLeptonicTagger.GetBranch(doublet);
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopHadronicTag(analysis::Event &event,  Tag Tag)
{
    Print(kInformation, "Get hadronic tops", Tag);
    std::vector<TopHadronicBranch> Tops = top_hadronic_tagger.GetBranches(event, Tag);
    if (Tops.empty()) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = Top;
    }
    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetTopHadronicReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);

    Jets jets = top_hadronic_tagger.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);


    std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);

//     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
//     for (const auto & Jet : jets)  {
//         Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 2);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//         Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
//         std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//         triplets.insert(triplets.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }


    if (triplets.size() > 1) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    for (const auto & triplet : triplets) {
        ++ObjectNumber;
        TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = top_hadronic_tagger.GetBranch(triplet);
    }

    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetTopSemiTag(analysis::Event &event,  Tag Tag)
{
    Print(kInformation, "Get Tops", Tag);
    std::vector<TopSemiBranch> Tops = TopSemiTagger.GetBranches(event, Tag, PreCut());
    if (Tops.empty()) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetTopSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);

//     Jets jets = event.hadrons().GetStructuredJets();

    Jets jets = bottom_tagger_.GetJets(event);

    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = event.Leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);

    if (triplets.size() > 1) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    for (const auto & triplet : triplets) {
        ++ObjectNumber;
        *static_cast<TopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(triplet);
    }

    return 1;
}



bool hheavyhiggs::HAnalysisCharged::GetJetPairTag(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Get JetPair Tag", Tag);
    std::vector<HChargedJetPairBranch> JetPairs = JetPairTagger.GetBranches(event, Tag);
    if (JetPairs.empty()) return 0;
    for (const auto & JetPair : JetPairs) {
        ++ObjectNumber;
        *static_cast<HChargedJetPairBranch *>(Branch->NewEntry()) = JetPair;
    }
    return 1;
}


bool hheavyhiggs::HAnalysisCharged::GetJetPairReader(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Get JetPair Reader", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
    std::vector<analysis::HQuartet31> Quartets = JetPairTagger.GetBdt(triplets, jets, JetPairReader);

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


bool hheavyhiggs::HAnalysisCharged::GetChargedHiggsSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get Semi HeavyHiggs Tag", Tag);
    std::vector<HChargedHiggsSemiBranch> Higgses = ChargedHiggsSemiTagger.GetBranches(event, Tag);
    if (Higgses.empty()) return 0;
    for (const auto & Higgs : Higgses) {
        ++ObjectNumber;
        *static_cast<HChargedHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetChargdHiggsSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = event.Leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> triplets = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());

    std::vector<analysis::HQuartet31> Quartets = ChargedHiggsSemiTagger.GetBdt(triplets, jets, ChargedHiggsSemiReader);

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

bool hheavyhiggs::HAnalysisCharged::GetSignatureSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);
    std::vector<HChargedOctetBranch> Semievents = SignatureSemiTagger.GetBranches(event, Tag);
    if (Semievents.empty()) return 0;
    for (const auto & Semievent : Semievents) {
        ++ObjectNumber;
        *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = Semievent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GetSignatureSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = event.Leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);

    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    //     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());

    std::vector<analysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);

    std::vector<analysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(tripletsHadronic, jets, JetPairReader);

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

bool hheavyhiggs::HAnalysisCharged::GeteventSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);
    std::vector<hheavyhiggs::HChargedSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
    if (Semievents.empty()) return 0;
    for (const auto & Semievent : Semievents) {
        ++ObjectNumber;
        static_cast<HChargedSemiBranch &>(*Branch->NewEntry()) = Semievent;
    }
    return 1;
}

bool hheavyhiggs::HAnalysisCharged::GeteventSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Get event semi", Tag);

    Jets PreJets = bottom_tagger_.GetJets(event);
    Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
    if (jets.empty()) return 0;
    if (SubJets.empty()) return 0;

    Jets Leptons = event.Leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    std::vector<analysis::HQuartet31> HiggsQuartets = ChargedHiggsSemiTagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);


    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);

//     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     for (const auto & Jet : jets)  {
//       Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 2);
//       Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//       std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
//       std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//       tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//
//     for (const auto & Jet : jets)  {
//       Jets Pieces = w_hadronic_tagger.GetSubJets(Jet, 3);
//       Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//       std::vector<analysis::Doublet> Piecedoublets = w_hadronic_tagger.GetBdt(Pieces, WHadronicReader);
//       std::vector<analysis::Triplet> Piecetriplets = top_hadronic_tagger.GetBdt(Piecedoublets, jets, TopHadronicReader);
//       tripletsHadronic.insert(tripletsHadronic.end(), Piecetriplets.begin(), Piecetriplets.end());
//     }
//     std::vector<analysis::Triplet> Finaltriplets;
//     if (Tag == kSignal) {
//       Jets Particles = event.Partons().Generator();
//       Jets TopParticles = w_hadronic_tagger.RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
//       if (TopParticles.size() != 1) Print(kError, "Where is the Top?");
//       else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.at(0)) < w_hadronic_tagger.detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
//     } else Finaltriplets = tripletsHadronic;


    std::vector<analysis::HQuartet31> JetQuartets = JetPairTagger.GetBdt(tripletsHadronic, jets, JetPairReader);

    std::vector<HOctet44> Octets = SignatureSemiTagger.GetBdt(HiggsQuartets, JetQuartets, SignatureSemiReader);

    EventStruct eventStruct;
    eventStruct.LeptonNumber = Leptons.size();
    eventStruct.JetNumber = jets.size();
    eventStruct.BottomNumber = event.hadrons().GetBottomJets().size();
    eventStruct.ScalarHt = event.hadrons().GetScalarHt();
    eventStruct.MissingEt = event.hadrons().GetMissingEt().pt();

    std::vector<EventMultiplet<HOctet44>> events = eventSemiTagger.GetBdt(Octets, jets, SubJets, Leptons, eventStruct, eventSemiReader);
    if (events.empty()) return 0;
    events.front().SetTag(Tag);

//     ++ObjectNumber; // this should be switched on otherwise the last step of the analysis takes very long
    static_cast<HChargedSemiBranch &>(*Branch->NewEntry()) = eventSemiTagger.GetBranch(events.front());
    return 1;
}*/
