# include "AnalysisNeutral.hh"

// heavyhiggs::AnalysisNeutral::AnalysisNeutral()
// {
// //     ReadConfig();
// //     DebugLevel = analysis::Object::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     jet_pair_tagger.SetAnalysisName(ProjectName());
//     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     w_semi_tagger.SetAnalysisName(ProjectName());
//     top_hadronic_tagger.SetAnalysisName(ProjectName());
//     top_semi_tagger.SetAnalysisName(ProjectName());
//     heavy_higgs_semi_tagger.SetAnalysisName(ProjectName());
//     SignatureSemiTagger.SetAnalysisName(ProjectName());
//     eventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string heavyhiggs::AnalysisNeutral::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Study Names", Tagger);
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
//     case JetPairTagger:
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
//     case HeavyHiggsSemiTagger:
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
//     case SignatureNeutralTagger:
//         return  "SignatureSemi";
//     case HSignatureSemiReader:
//         return  "SignatureSemiReader";
//     case EventNeutralTagger:
//         return  "eventSemi";
//     case EventSemiReader:
//         return  "eventSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<analysis::File> heavyhiggs::AnalysisNeutral::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;
    std::vector<analysis::File> BackgroundLeptonicFiles;
    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
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
//     case JetPairTagger:
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
//     case HeavyHiggsSemiTagger:
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
//     case SignatureNeutralTagger:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HSignatureSemiReader:
//         if (Tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventNeutralTagger:
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


void heavyhiggs::AnalysisNeutral::SetTrees()
{

  analysis::Strings SignalLeptonicTrees {};
  analysis::Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    analysis::Strings SignalSemiTrees {
        SignalTree
//         BackgroundTree(ttbb)
    };

    analysis::Strings BackgroundSemiTrees {
//         BackgroundTree(ttbb),
//         BackgroundTree(ttcc),
//         BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    analysis::Strings SignalHadronicTree {};
    analysis::Strings BackgroundHadronicTrees {};

    analysis::Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    analysis::Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    analysis::Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    analysis::Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    analysis::Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

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
//     case JetPairTagger :
//         jet_pair_tagger.SetSignalTreeNames(SignalSemiTrees);
//         jet_pair_tagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) jet_pair_tagger.SetTagger(BottomTagger);
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
//         if (Tag == kSignal) w_semi_tagger.SetTagger();
//         w_semi_tagger.SetSignalTreeNames(SemiTrees);
//         w_semi_tagger.SetBackgroundTreeNames(SemiTrees);
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
//         if (Tag == kSignal) top_semi_tagger.SetTagger(BottomTagger, w_semi_tagger);
//         top_semi_tagger.SetSignalTreeNames(SemiTrees);
//         top_semi_tagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HTopSemiReader :
//         break;
//     case HeavyHiggsSemiTagger  :
//         if (Tag == kSignal) heavy_higgs_semi_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         heavy_higgs_semi_tagger.SetSignalTreeNames(SignalSemiTrees);
//         heavy_higgs_semi_tagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HHeavyHiggsSemiReader :
//         break;
//     case SignatureNeutralTagger :
//         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, heavy_higgs_semi_tagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HSignatureSemiReader :
//         break;
//     case EventNeutralTagger :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, heavy_higgs_semi_tagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiReader :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, heavy_higgs_semi_tagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandeled case");
//     }
}

// void heavyhiggs::AnalysisNeutral::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         WSemiReader.set_tagger(w_semi_tagger);
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
//         top_semi_tagger.BottomTagger.SetTagger();
//         top_semi_tagger.BottomReader.set_tagger(top_semi_tagger.BottomTagger);
//         top_semi_tagger.w_semi_tagger.SetTagger();
//         top_semi_tagger.WSemiReader.set_tagger(top_semi_tagger.w_semi_tagger);
//         break;
//     case HTopSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         break;
//     case HeavyHiggsSemiTagger :
//         heavy_higgs_semi_tagger.BottomTagger.SetTagger();
//         heavy_higgs_semi_tagger.BottomReader.set_tagger(heavy_higgs_semi_tagger.BottomTagger);
//         heavy_higgs_semi_tagger.w_semi_tagger.SetTagger();
//         heavy_higgs_semi_tagger.WSemiReader.set_tagger(heavy_higgs_semi_tagger.w_semi_tagger);
//         heavy_higgs_semi_tagger.WTagger.SetTagger(BottomTagger);
//         heavy_higgs_semi_tagger.WReader.set_tagger(heavy_higgs_semi_tagger.WTagger);
//         heavy_higgs_semi_tagger.top_semi_tagger.SetTagger(BottomTagger, w_semi_tagger);
//         heavy_higgs_semi_tagger.TopSemiReader.set_tagger(heavy_higgs_semi_tagger.top_semi_tagger);
//         heavy_higgs_semi_tagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         heavy_higgs_semi_tagger.TopHadronicReader.set_tagger(heavy_higgs_semi_tagger.top_hadronic_tagger);
//         break;
//     case HHeavyHiggsSemiReader  :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         HeavyHiggsSemiReader.set_tagger(heavy_higgs_semi_tagger);
//         break;
//     case JetPairTagger :
//         jet_pair_tagger.BottomTagger.SetTagger();
//         jet_pair_tagger.BottomReader.set_tagger(jet_pair_tagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         JetPairReader.set_tagger(jet_pair_tagger);
//         break;
//     case SignatureNeutralTagger :
//         SignatureSemiTagger.BottomTagger.SetTagger();
//         SignatureSemiTagger.BottomReader.set_tagger(SignatureSemiTagger.BottomTagger);
//         SignatureSemiTagger.w_semi_tagger.SetTagger();
//         SignatureSemiTagger.WSemiReader.set_tagger(SignatureSemiTagger.w_semi_tagger);
//         SignatureSemiTagger.WTagger.SetTagger(BottomTagger);
//         SignatureSemiTagger.WReader.set_tagger(SignatureSemiTagger.WTagger);
//         SignatureSemiTagger.top_semi_tagger.SetTagger(BottomTagger, w_semi_tagger);
//         SignatureSemiTagger.TopSemiReader.set_tagger(SignatureSemiTagger.top_semi_tagger);
//         SignatureSemiTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         SignatureSemiTagger.TopHadronicReader.set_tagger(SignatureSemiTagger.top_hadronic_tagger);
//         SignatureSemiTagger.heavy_higgs_semi_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         SignatureSemiTagger.HeavyHiggsSemiReader.set_tagger(SignatureSemiTagger.heavy_higgs_semi_tagger);
//         SignatureSemiTagger.jet_pair_tagger.SetTagger(BottomTagger);
//         SignatureSemiTagger.JetPairReader.set_tagger(SignatureSemiTagger.jet_pair_tagger);
//         break;
//     case HSignatureSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(jet_pair_tagger);
//         HeavyHiggsSemiReader.set_tagger(heavy_higgs_semi_tagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         break;
//     case EventNeutralTagger :
//         eventSemiTagger.BottomTagger.SetTagger();
//         eventSemiTagger.BottomReader.set_tagger(eventSemiTagger.BottomTagger);
//         eventSemiTagger.w_semi_tagger.SetTagger();
//         eventSemiTagger.WSemiReader.set_tagger(eventSemiTagger.w_semi_tagger);
//         eventSemiTagger.WTagger.SetTagger(BottomTagger);
//         eventSemiTagger.WReader.set_tagger(eventSemiTagger.WTagger);
//         eventSemiTagger.top_semi_tagger.SetTagger(BottomTagger, w_semi_tagger);
//         eventSemiTagger.TopSemiReader.set_tagger(eventSemiTagger.top_semi_tagger);
//         eventSemiTagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         eventSemiTagger.TopHadronicReader.set_tagger(eventSemiTagger.top_hadronic_tagger);
//         eventSemiTagger.heavy_higgs_semi_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         eventSemiTagger.HeavyHiggsSemiReader.set_tagger(eventSemiTagger.heavy_higgs_semi_tagger);
//         eventSemiTagger.jet_pair_tagger.SetTagger(BottomTagger);
//         eventSemiTagger.JetPairReader.set_tagger(eventSemiTagger.jet_pair_tagger);
//         eventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, heavy_higgs_semi_tagger);
//         eventSemiTagger.SignatureSemiReader.set_tagger(eventSemiTagger.SignatureSemiTagger);
//         break;
//     case EventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(jet_pair_tagger);
//         HeavyHiggsSemiReader.set_tagger(heavy_higgs_semi_tagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         eventSemiReader.set_tagger(eventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
// }

// void heavyhiggs::AnalysisNeutral::NewBranches(exroot::TreeWriter &tree_writer, const analysis::HAnalysis::HTagger tagger)
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
//     case JetPairTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), JetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), JetPairBranch::Class());
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
//     case HeavyHiggsSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HeavyHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HeavyHiggsSemiBranch::Class());
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
//     case SignatureNeutralTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), OctetNeutralBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), OctetNeutralBranch::Class());
//         break;
//     case EventNeutralTagger :
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

int heavyhiggs::AnalysisNeutral::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{
    Print(kInformation, "Analysis");

    analysis::Jets Particles = event.partons().Generator();
    analysis::Jets Tops = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Tops.size() != 2) {
        Print(kError, "Not enough top quarks", Tops.size());
        return 0;
    } else {
        if (Tops.at(0).pt() < PreCut()) return 0;
        if (Tops.at(1).pt() < PreCut()) return 0;
    }

    if (event.hadrons().MissingEt().pt() < MissingEt()) return 0;
    analysis::Jets Leptons = fastjet::sorted_by_pt(event.leptons().leptons());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    analysis::Jets jets = event.hadrons().Jets();
    if (jets.size() < 4) return 0;


    ++event_sum_;

    tagger_.GetBranches(event, stage, tag);

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, Tag);
//     case HBottomReader:
//         return GetBottomReader(event, Tag);
//     case JetPairTagger :
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
//     case HeavyHiggsSemiTagger :
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
//     case SignatureNeutralTagger :
//         return GetSignatureSemiTag(event, Tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(event, Tag);
//     case EventNeutralTagger :
//         return GeteventSemiTag(event, Tag);
//     case EventSemiReader :
//         return GeteventSemiReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
//     }
}


// bool heavyhiggs::AnalysisNeutral::GetBottomTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Tag", Tag);
//     std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(event, Tag);
//     if (Bottoms.empty()) return 0;
//     for (const auto & Bottom : Bottoms) {
//         ++ObjectNumber;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetBottomReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     if (jets.empty()) return 0;
//
// //     jets = static_cast<analysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(jets);
//
//     Jets Particles = event.partons().Generator();
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
// bool heavyhiggs::AnalysisNeutral::GetJetPairTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "JetPair Tag", Tag);
//     std::vector<JetPairBranch> JetPairs = jet_pair_tagger.GetBranches(event, Tag);
//     if (JetPairs.empty()) return 0;
//     for (const auto & JetPair : JetPairs) {
//         ++ObjectNumber;
//         *static_cast<JetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetJetPairReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "JetPair Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
//     if (jets.empty()) return 0;
//
//     Jets Particles = event.partons().Generator();
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
//         *static_cast<JetPairBranch *>(Branch->NewEntry()) = jet_pair_tagger.GetBranch(doublet);
//     }
//     return 1;
//
// }
//
// bool heavyhiggs::AnalysisNeutral::GetWSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "W Semi Tag", Tag);
//     std::vector<HWSemiBranch> WSemis = w_semi_tagger.GetBranches(event, Tag);
//     if (WSemis.empty()) return 0;
//     for (const auto & WSemi : WSemis) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetWSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "W Semi Reader", Tag);
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//
//     std::vector<analysis::Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
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
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = w_semi_tagger.GetBranch(doublet);
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetWTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "W Tag", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetWReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetTopLeptonicTag(analysis::Event &, const analysis::Object::Tag)
// {
// //     Print(kInformation, "leptonic top", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetTopLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event semi", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
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
// bool heavyhiggs::AnalysisNeutral::GetTopHadronicTag(analysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "hadronic tops", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetTopHadronicReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetTopSemiTag(analysis::Event &event, const analysis::Object::Tag Tag)
// {
//     Print(kInformation, "Tops", Tag);
//     std::vector<TopSemiBranch> Tops = top_semi_tagger.GetBranches(event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetTopSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> triplets = top_semi_tagger.GetBdt(doublets, jets, TopSemiReader);
//
//     if (triplets.size() > 1) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + 1, triplets.end());
//     }
//
//     for (const auto & triplet : triplets) {
//         ++ObjectNumber;
//         *static_cast<TopSemiBranch *>(Branch->NewEntry()) = top_semi_tagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsLeptonicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Leptonic Heavy Higgs Tag", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event semi", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<analysis::Hsextet> sextets = HeavyHiggsLeptonicTagger.GetBdt(doublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     if (sextets.size() > 1) {
// //         std::sort(sextets.begin(), sextets.end());
// //         sextets.erase(sextets.begin() + 1, sextets.end());
// //     }
// //
// //     for (const auto & sextet : sextets)  {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsLeptonicBranch *>(Branch->NewEntry())  = HeavyHiggsLeptonicTagger.GetBranch(sextet);
// //     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsHadronicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Hadronic HeavyHiggs Tag", Tag);
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
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Semi HeavyHiggs Tag", Tag);
//     std::vector<HeavyHiggsSemiBranch> Higgses = heavy_higgs_semi_tagger.GetBranches(event, Tag);
//     if (Higgses.empty()) return 0;
//     for (const auto & Higgs : Higgses) {
//         ++ObjectNumber;
//         *static_cast<HeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::Hsextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     if (sextets.size() > 1) {
//         std::sort(sextets.begin(), sextets.end());
//         sextets.erase(sextets.begin() + 1, sextets.end());
//     }
//
//     for (const auto & sextet : sextets) {
//         ++ObjectNumber;
//         *static_cast<HeavyHiggsSemiBranch *>(Branch->NewEntry()) = heavy_higgs_semi_tagger.GetBranch(sextet);
//     }
//
//     return 1;
// }
//
//
//
//
// bool heavyhiggs::AnalysisNeutral::GeteventLeptonicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event leptonic", Tag);
// //     std::vector<heavyhiggs::EventLeptonicBranch *> LeptoniceventBranches = eventLeptonicTagger.GetBranches(event, Tag);
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
// bool heavyhiggs::AnalysisNeutral::GeteventHadronicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event hadronic", Tag);
// //     std::vector<heavyhiggs::EventHadronicBranch *> Hadronicevents = eventHadronicTagger.GetBranches(event, Tag);
// //     if (Hadronicevents.empty()) return 0;
// //     for (const auto & Hadronicevent : Hadronicevents) {
// //         ++ObjectNumber;
// //         *static_cast<EventHadronicBranch *>(Branch->NewEntry()) = *Hadronicevent;
// //     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GeteventLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Leptonic reader", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Print(kInformation, "Jet Pair");
// //
// //     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
// //
// //     Print(kInformation, "Top");
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> Leptonicdoublets = TopLeptonicTagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<analysis::Hsextet> sextets = HeavyHiggsLeptonicTagger.GetBdt(Leptonicdoublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     EventStruct global_observables;
// //     global_observables.LeptonNumber = Leptons.size();
// //     global_observables.JetNumber = jets.size();
// //     global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
// //     global_observables.ScalarHt = event.hadrons().GetScalarHt();
// //
// //     std::vector<HOctet> octets = eventLeptonicTagger.GetBdt(sextets, doublets, jets, global_observables, eventLeptonicReader);
// //     if (octets.empty()) return 0;
// //     octets.front().SetTag(Tag);
// //
// //     heavyhiggs::EventLeptonicBranch *Leptonicevent = new heavyhiggs::EventLeptonicBranch();
// //     eventLeptonicTagger.FillBranch(Leptonicevent, octets.front());
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
// bool heavyhiggs::AnalysisNeutral::GetSignatureSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Signature semi", Tag);
//     std::vector<heavyhiggs::OctetNeutralBranch> Signatures = SignatureSemiTagger.GetBranches(event, Tag);
//     if (Signatures.empty()) return 0;
//     for (const auto & Signature : Signatures) {
//         ++ObjectNumber;
//         *static_cast<OctetNeutralBranch *>(Branch->NewEntry()) = Signature;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetSignatureSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Signature Semi Reader", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::Hsextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     std::vector<HOctet> octets = SignatureSemiTagger.GetBdt(sextets, doublets, SignatureSemiReader);
//     if (octets.empty()) return 0;
//
//     if (octets.size() > 1) {
//         std::sort(octets.begin(), octets.end());
//         octets.erase(octets.begin() + 1, octets.end());
//     }
//     octets.front().SetTag(Tag);
//     ++ObjectNumber;
//     *static_cast<OctetNeutralBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(octets.front());
//     return 1;
// }
//
//
//
// bool heavyhiggs::AnalysisNeutral::GeteventSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//     std::vector<heavyhiggs::EventSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
//     if (Semievents.empty()) return 0;
//     for (const auto & Semievent : Semievents) {
//         ++ObjectNumber;
//         *static_cast<EventSemiBranch *>(Branch->NewEntry()) = Semievent;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GeteventSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//     //must be in the beginning to get the counting right
//
//     Jets PreJets = bottom_tagger_.GetJets(event);
//     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
//     Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
//     if (jets.empty()) return 0;
//     if (SubJets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
// //     Print(kError, "doublets", doublets.size());
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
// //     Print(kError, "triplets Semi", tripletsSemi.size());
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
// //     Print(kError, "triplets Hadronic", tripletsHadronic.size());
//
//     std::vector<analysis::Hsextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
// //     Print(kError, "sextets", sextets.size());
//
//     std::vector<HOctet> octets = SignatureSemiTagger.GetBdt(sextets, doublets, SignatureSemiReader);
// //     Print(kError, "Octets", octets.size());
//
//     EventStruct global_observables;
//     global_observables.LeptonNumber = Leptons.size();
//     global_observables.JetNumber = jets.size();
//     global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
//     global_observables.ScalarHt = event.hadrons().GetScalarHt();
//     global_observables.MissingEt = event.hadrons().GetMissingEt().pt();
// //   if (global_observables.LeptonNumber > 0) global_observables.LeptonPt = fastjet::sorted_by_pt(event.leptons().GetLeptonJets()).front().pt();
//
//     std::vector<MultipletEvent<HOctet>> events = eventSemiTagger.GetBdt(octets, jets, SubJets, Leptons,  global_observables, eventSemiReader);
//     if (events.empty()) return 0;
//     events.front().SetTag(Tag);
// //     ++ObjectNumber; // FIXME should be switched on to avoid long duration of last step
//     *static_cast<EventSemiBranch *>(Branch->NewEntry()) = eventSemiTagger.GetBranch(events.front());
//     return 1;
// }
