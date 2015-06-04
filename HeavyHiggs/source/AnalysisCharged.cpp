# include "AnalysisCharged.hh"
# include "Tagger.hh"

// heavyhiggs::AnalysisCharged::AnalysisCharged() :
//     BottomTagger(ProjectName())
// {
//     Print(kNotification, "Constructor");
//
//     tagger_ =
//
//     jet_pair_tagger.SetAnalysisName(ProjectName());
//     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     w_semi_tagger.SetAnalysisName(ProjectName());
//     top_hadronic_tagger.SetAnalysisName(ProjectName());
//     top_semi_tagger.SetAnalysisName(ProjectName());
//     charged_higgs_semi_tagger.SetAnalysisName(ProjectName());
//     SignatureSemiTagger.SetAnalysisName(ProjectName());
//     eventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string heavyhiggs::AnalysisCharged::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Study Names", Tagger);
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
//     case JetPairTagger:
//         return  "ChargedJetPair";
//     case HJetPairReader:
//         return  "ChargedJetPairReader";
//     case TopLeptonicTagger:
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
//     case HeavyHiggsLeptonicTagger:
//         return  "ChargedHiggsLeptonic";
//     case HHeavyHiggsHadronicTagger:
//         return  "ChargedHiggsHadronic";
//     case HeavyHiggsSemiTagger:
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
//     case SignatureNeutralTagger:
//         return  "ChargedSignatureSemi";
//     case HSignatureSemiReader:
//         return  "ChargedSignatureSemiReader";
//     case EventNeutralTagger:
//         return  "ChargedeventSemi";
//     case EventSemiReader:
//         return  "ChargedeventSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
//
// }

std::vector<analysis::File> heavyhiggs::AnalysisCharged::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;

    std::vector<analysis::File> BackgroundLeptonicFiles;

    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Htb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
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
//     case JetPairTagger:
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
//     case TopLeptonicTagger:
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
//     case HeavyHiggsLeptonicTagger:
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
//     case HeavyHiggsSemiTagger:
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
//     case SignatureNeutralTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HSignatureSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventNeutralTagger:
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

void heavyhiggs::AnalysisCharged::SetTrees()
{

  analysis::Strings SignalLeptonicTrees {};
  analysis::Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Htb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    analysis::Strings SignalSemiTrees {SignalTree};

    analysis::Strings BackgroundSemiTrees {
//       BackgroundTree(ttbb),
//       BackgroundTree(ttcc),
//       BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    analysis::Strings SignalHadronicTree {};
    analysis::Strings BackgroundHadronicTrees {};

    analysis::Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    analysis::Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    analysis::Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    analysis::Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    analysis::Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetTreeNames(CombinedTrees);
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         break;
//     case HBottomReader:
//         break;
//     case JetPairTagger :
//         jet_pair_tagger.SetSignalTreeNames(CombinedTrees);
//         jet_pair_tagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal) jet_pair_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
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
//         if (Tag == kSignal) charged_higgs_semi_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         charged_higgs_semi_tagger.SetSignalTreeNames(SignalSemiTrees);
//         charged_higgs_semi_tagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HHeavyHiggsSemiReader :
//         break;
//     case SignatureNeutralTagger :
//         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, charged_higgs_semi_tagger);
//         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HSignatureSemiReader :
// //         if (Tag == kSignal) SignatureSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, charged_higgs_semi_tagger);
// //         SignatureSemiTagger.SetSignalTreeNames(SignalSemiTrees);
// //         SignatureSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventNeutralTagger :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, charged_higgs_semi_tagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiReader :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, charged_higgs_semi_tagger, SignatureSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }

//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void heavyhiggs::AnalysisCharged::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         charged_higgs_semi_tagger.BottomTagger.SetTagger();
//         charged_higgs_semi_tagger.BottomReader.set_tagger(charged_higgs_semi_tagger.BottomTagger);
//         charged_higgs_semi_tagger.w_semi_tagger.SetTagger();
//         charged_higgs_semi_tagger.WSemiReader.set_tagger(charged_higgs_semi_tagger.w_semi_tagger);
//         charged_higgs_semi_tagger.WTagger.SetTagger(BottomTagger);
//         charged_higgs_semi_tagger.WReader.set_tagger(charged_higgs_semi_tagger.WTagger);
//         charged_higgs_semi_tagger.top_semi_tagger.SetTagger(BottomTagger, w_semi_tagger);
//         charged_higgs_semi_tagger.TopSemiReader.set_tagger(charged_higgs_semi_tagger.top_semi_tagger);
//         charged_higgs_semi_tagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         charged_higgs_semi_tagger.TopHadronicReader.set_tagger(charged_higgs_semi_tagger.top_hadronic_tagger);
//         break;
//     case HHeavyHiggsSemiReader  :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         ChargedHiggsSemiReader.set_tagger(charged_higgs_semi_tagger);
//         break;
//     case JetPairTagger :
//         jet_pair_tagger.BottomTagger.SetTagger();
//         jet_pair_tagger.BottomReader.set_tagger(jet_pair_tagger.BottomTagger);
//         jet_pair_tagger.w_semi_tagger.SetTagger();
//         jet_pair_tagger.WSemiReader.set_tagger(jet_pair_tagger.w_semi_tagger);
//         jet_pair_tagger.WTagger.SetTagger(BottomTagger);
//         jet_pair_tagger.WReader.set_tagger(jet_pair_tagger.WTagger);
//         jet_pair_tagger.top_semi_tagger.SetTagger(BottomTagger, w_semi_tagger);
//         jet_pair_tagger.TopSemiReader.set_tagger(jet_pair_tagger.top_semi_tagger);
//         jet_pair_tagger.top_hadronic_tagger.SetTagger(BottomTagger, w_hadronic_tagger);
//         jet_pair_tagger.TopHadronicReader.set_tagger(jet_pair_tagger.top_hadronic_tagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
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
//         SignatureSemiTagger.charged_higgs_semi_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         SignatureSemiTagger.ChargedHiggsSemiReader.set_tagger(SignatureSemiTagger.charged_higgs_semi_tagger);
//         SignatureSemiTagger.Chargedjet_pair_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         SignatureSemiTagger.ChargedJetPairReader.set_tagger(SignatureSemiTagger.Chargedjet_pair_tagger);
//         break;
//     case HSignatureSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(jet_pair_tagger);
//         ChargedHiggsSemiReader.set_tagger(charged_higgs_semi_tagger);
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
//         eventSemiTagger.charged_higgs_semi_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         eventSemiTagger.ChargedHiggsSemiReader.set_tagger(eventSemiTagger.charged_higgs_semi_tagger);
//         eventSemiTagger.Chargedjet_pair_tagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger);
//         eventSemiTagger.ChargedJetPairReader.set_tagger(eventSemiTagger.Chargedjet_pair_tagger);
//         eventSemiTagger.SignatureSemiTagger.SetTagger(BottomTagger, jet_pair_tagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, charged_higgs_semi_tagger);
//         eventSemiTagger.SignatureSemiReader.set_tagger(eventSemiTagger.SignatureSemiTagger);
//         break;
//     case EventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         JetPairReader.set_tagger(jet_pair_tagger);
//         ChargedHiggsSemiReader.set_tagger(charged_higgs_semi_tagger);
//         SignatureSemiReader.set_tagger(SignatureSemiTagger);
//         eventSemiReader.set_tagger(eventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
//
// }
//
// void heavyhiggs::AnalysisCharged::NewBranches(exroot::TreeWriter &tree_writer, const analysis::HAnalysis::HTagger Tagger, const analysis::Tagger::Stage stage)
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
//     case JetPairTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TripletJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TripletJetPairBranch::Class());
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
//     case TopLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), TopLeptonicBranch::Class());
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
//     case HeavyHiggsLeptonicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicReader:
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsHadronicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
//         break;
//     case HeavyHiggsSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), ChargedHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), ChargedHiggsSemiBranch::Class());
//         break;
//     case EventLeptonicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case EventHadronicTagger :
// //         Branch = TreeWriter.NewBranch(GetStudyNames(Tagger).c_str(), EventHadronicBranch::Class());
//         break;
//     case SignatureNeutralTagger :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(Tagger).c_str(), HChargedOctetBranch::Class());
//         break;
//     case EventNeutralTagger :
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

int heavyhiggs::AnalysisCharged::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{
    Print(kInformation, "Analysis");

    analysis::Jets Particles = event.partons().GenParticles();
    analysis::Jets Quarks = fastjet::sorted_by_pt(analysis::RemoveIfNot5Quarks(Particles));
    Quarks = fastjet::sorted_by_pt(RemoveIfAbsMother(Quarks, TopId));
    if (Quarks.empty()) {
//       if (Tag == kSignal && PreCut() > 0 && !(Tagger == BottomTagger || Tagger == HBottomReader))
//       if (PreCut() > 0)
        Print(kError, "Not enough bottom quarks", Quarks.size());
        return 0;
    } else if (Quarks.front().pt() < PreCut()) return 0;


    analysis::Jets TopQuarks = fastjet::sorted_by_pt(RemoveIfWrongAbsParticle(Particles, TopId));
    if (TopQuarks.size() != 2) {
        Print(kError, "Not enough top quarks", TopQuarks.size());
        return 0;
    } else if (TopQuarks.front().pt() < PreCut()) return 0;


    if (event.hadrons().MissingEt().pt() < MissingEt()) return 0;
    analysis::Jets Leptons = fastjet::sorted_by_pt(event.leptons().leptons());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    analysis::Jets jets = event.hadrons().Jets();
    if (jets.size() < 4) return 0;

    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, tag);
//     case HBottomReader:
//         return GetBottomReader(event, tag);
//     case JetPairTagger :
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
//     case TopLeptonicTagger :
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
//     case HeavyHiggsLeptonicTagger :
// //         return GetHeavyHiggsLeptonicTag(event, Tag);
//     case HHeavyHiggsHadronicTagger :
// //         return GetHeavyHiggsHadronicTag(event, Tag);
//     case HeavyHiggsSemiTagger :
//         return GetChargedHiggsSemiTag(event, tag);
//     case HHeavyHiggsSemiReader :
//         return GetChargdHiggsSemiReader(event, tag);
//     case HHeavyHiggsLeptonicReader :
// //         return GetHeavyHiggsLeptonicReader(event, Tag);
//     case EventLeptonicTagger :
// //         return GeteventLeptonicTag(event, Tag);
//     case EventHadronicTagger :
// //         return GeteventHadronicTag(event, Tag);
//     case SignatureNeutralTagger :
//         return GetSignatureSemiTag(event, tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(event, tag);
//     case EventNeutralTagger :
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
bool heavyhiggs::AnalysisCharged::GetBottomTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Bottom Tag", Tag);
    std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(event, Tag);
    if (Bottoms.empty()) return 0;
    for (const auto & Bottom : Bottoms) {
        *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
        ++ObjectNumber;
    }
    return 1;
}


bool heavyhiggs::AnalysisCharged::GetBottomReader(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "Bottom Reader", Tag);
    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Particles = event.partons().GenParticles();
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

bool heavyhiggs::AnalysisCharged::GetWSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "W Semi Tag", Tag);
    std::vector<HWSemiBranch> WSemis = w_semi_tagger.GetBranches(event, Tag);
    if (WSemis.empty()) return 0;
    for (const auto & WSemi : WSemis) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
    }
    return 1;
}

bool heavyhiggs::AnalysisCharged::GetWSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "W Semi Reader", Tag);

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();

    std::vector<analysis::Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);

    if (doublets.empty()) return 0;

    if (doublets.size() > 1) {
        std::sort(doublets.begin(), doublets.end());
        doublets.erase(doublets.begin() + 1, doublets.end());
    }

    for (const auto & doublet : doublets) {
        ++ObjectNumber;
        *static_cast<HWSemiBranch *>(Branch->NewEntry()) = w_semi_tagger.GetBranch(doublet);
    }

    return 1;
}

bool heavyhiggs::AnalysisCharged::GetWTag(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "W Tag", Tag);
    std::vector<WHadronicBranch> Ws = w_hadronic_tagger.GetBranches(event, Tag);
    if (Ws.empty()) return 0;
    for (const auto & W : Ws) {
        ++ObjectNumber;
        *static_cast<WHadronicBranch *>(Branch->NewEntry()) = W;
    }
    return 1;
}


bool heavyhiggs::AnalysisCharged::GetWReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);

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

bool heavyhiggs::AnalysisCharged::GetTopLeptonicTag(analysis::Event &,  Tag)
{
    Print(kInformation, "leptonic top");
//     std::vector<TopLeptonicBranch> Tops = top_leptonic_tagger.GetBranches(event, Tag);
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) *static_cast<TopLeptonicBranch *>(Branch->NewEntry()) = Top;
    return 1;
}


bool heavyhiggs::AnalysisCharged::GetTopLeptonicReader(analysis::Event &, const Tag)
{
    Print(kInformation, "event semi");

//     Jets jets = event.hadrons().GetStructuredJets();
//     jets = BottomTagger.GetBdt(jets, BottomReader);
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     if (Leptons.size() < 2) return 0;
//
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doublets = top_leptonic_tagger.GetBdt(jets, Leptons, TopLeptonicReader);
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) *static_cast<TopLeptonicBranch *>(Branch->NewEntry()) = top_leptonic_tagger.GetBranch(doublet);
    return 1;
}

bool heavyhiggs::AnalysisCharged::GetTopHadronicTag(analysis::Event &event,  Tag Tag)
{
    Print(kInformation, "hadronic tops", Tag);
    std::vector<TopHadronicBranch> Tops = top_hadronic_tagger.GetBranches(event, Tag);
    if (Tops.empty()) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        TopHadronicBranch *TopTagger = static_cast<TopHadronicBranch *>(Branch->NewEntry());
        *TopTagger = Top;
    }
    return 1;
}



bool heavyhiggs::AnalysisCharged::GetTopHadronicReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);

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



bool heavyhiggs::AnalysisCharged::GetTopSemiTag(analysis::Event &event,  Tag Tag)
{
    Print(kInformation, "Tops", Tag);
    std::vector<TopSemiBranch> Tops = top_semi_tagger.GetBranches(event, Tag, PreCut());
    if (Tops.empty()) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}

bool heavyhiggs::AnalysisCharged::GetTopSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);

//     Jets jets = event.hadrons().GetStructuredJets();

    Jets jets = bottom_tagger_.GetJets(event);

    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> triplets = top_semi_tagger.GetBdt(doublets, jets, TopSemiReader);

    if (triplets.size() > 1) {
        std::sort(triplets.begin(), triplets.end());
        triplets.erase(triplets.begin() + 1, triplets.end());
    }

    for (const auto & triplet : triplets) {
        ++ObjectNumber;
        *static_cast<TopSemiBranch *>(Branch->NewEntry()) = top_semi_tagger.GetBranch(triplet);
    }

    return 1;
}



bool heavyhiggs::AnalysisCharged::GetJetPairTag(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "JetPair Tag", Tag);
    std::vector<TripletJetPairBranch> JetPairs = jet_pair_tagger.GetBranches(event, Tag);
    if (JetPairs.empty()) return 0;
    for (const auto & JetPair : JetPairs) {
        ++ObjectNumber;
        *static_cast<TripletJetPairBranch *>(Branch->NewEntry()) = JetPair;
    }
    return 1;
}


bool heavyhiggs::AnalysisCharged::GetJetPairReader(analysis::Event &event, const Tag Tag)
{
    Print(kDebug, "JetPair Reader", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
    std::vector<analysis::Quartet31> quartets = jet_pair_tagger.GetBdt(triplets, jets, JetPairReader);

    if (quartets.size() > 1) {
        std::sort(quartets.begin(), quartets.end());
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    for (const auto & quartet : quartets) {
        ++ObjectNumber;
        *static_cast<TripletJetPairBranch *>(Branch->NewEntry()) = jet_pair_tagger.GetBranch(quartet);
    }

    return 1;
}


bool heavyhiggs::AnalysisCharged::GetChargedHiggsSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "Semi HeavyHiggs Tag", Tag);
    std::vector<ChargedHiggsSemiBranch> Higgses = charged_higgs_semi_tagger.GetBranches(event, Tag);
    if (Higgses.empty()) return 0;
    for (const auto & Higgs : Higgses) {
        ++ObjectNumber;
        *static_cast<ChargedHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
    }
    return 1;
}

bool heavyhiggs::AnalysisCharged::GetChargdHiggsSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> triplets = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);

//     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());

    std::vector<analysis::Quartet31> quartets = charged_higgs_semi_tagger.GetBdt(triplets, jets, ChargedHiggsSemiReader);

    if (quartets.size() > 1) {
        std::sort(quartets.begin(), quartets.end());
        quartets.erase(quartets.begin() + 1, quartets.end());
    }

    for (const auto & quartet : quartets) {
        ++ObjectNumber;
        *static_cast<ChargedHiggsSemiBranch *>(Branch->NewEntry()) = charged_higgs_semi_tagger.GetBranch(quartet);
    }
    return 1;
}

bool heavyhiggs::AnalysisCharged::GetSignatureSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);
    std::vector<HChargedOctetBranch> Semievents = SignatureSemiTagger.GetBranches(event, Tag);
    if (Semievents.empty()) return 0;
    for (const auto & Semievent : Semievents) {
        ++ObjectNumber;
        *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = Semievent;
    }
    return 1;
}

bool heavyhiggs::AnalysisCharged::GetSignatureSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);

    Jets jets = bottom_tagger_.GetJets(event);
    jets = bottom_tagger_.GetJetBdt(jets, BottomReader);

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);

    std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
    //     triplets.insert(triplets.end(), tripletsHadronic.begin(), tripletsHadronic.end());

    std::vector<analysis::Quartet31> Higgsquartets = charged_higgs_semi_tagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);

    std::vector<analysis::Quartet31> Jetquartets = jet_pair_tagger.GetBdt(tripletsHadronic, jets, JetPairReader);

    std::vector<HOctet44> octets = SignatureSemiTagger.GetBdt(Higgsquartets, Jetquartets, SignatureSemiReader);
    if (octets.empty()) return 0;

    if (octets.size() > 1) {
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }
    octets.front().SetTag(Tag);

    for (const auto & octet : octets) {
        *static_cast<HChargedOctetBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(octet);
        ++ObjectNumber;
    }

    return 1;
}

bool heavyhiggs::AnalysisCharged::GeteventSemiTag(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);
    std::vector<heavyhiggs::HChargedSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
    if (Semievents.empty()) return 0;
    for (const auto & Semievent : Semievents) {
        ++ObjectNumber;
        static_cast<HChargedSemiBranch &>(*Branch->NewEntry()) = Semievent;
    }
    return 1;
}

bool heavyhiggs::AnalysisCharged::GeteventSemiReader(analysis::Event &event, const Tag Tag)
{
    Print(kInformation, "event semi", Tag);

    Jets PreJets = bottom_tagger_.GetJets(event);
    Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
    Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
    if (jets.empty()) return 0;
    if (SubJets.empty()) return 0;

    Jets Leptons = event.leptons().GetLeptonJets();
    fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
    std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
    std::vector<analysis::Quartet31> Higgsquartets = charged_higgs_semi_tagger.GetBdt(tripletsSemi, jets, ChargedHiggsSemiReader);


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
//       Jets Particles = event.partons().GenParticles();
//       Jets TopParticles = w_hadronic_tagger.RemoveIfWrongAbsFamily(Particles, TopId, GluonId);
//       if (TopParticles.size() != 1) Print(kError, "Where is the Top?");
//       else for (const auto & triplet : tripletsHadronic) if ((triplet.Jet().delta_R(TopParticles.at(0)) < w_hadronic_tagger.detector_geometry().JetConeSize)) Finaltriplets.emplace_back(triplet);
//     } else Finaltriplets = tripletsHadronic;


    std::vector<analysis::Quartet31> Jetquartets = jet_pair_tagger.GetBdt(tripletsHadronic, jets, JetPairReader);

    std::vector<HOctet44> octets = SignatureSemiTagger.GetBdt(Higgsquartets, Jetquartets, SignatureSemiReader);

    EventStruct global_observables;
    global_observables.LeptonNumber = Leptons.size();
    global_observables.JetNumber = jets.size();
    global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
    global_observables.ScalarHt = event.hadrons().GetScalarHt();
    global_observables.MissingEt = event.hadrons().GetMissingEt().pt();

    std::vector<MultipletEvent<HOctet44>> events = eventSemiTagger.GetBdt(octets, jets, SubJets, Leptons, global_observables, eventSemiReader);
    if (events.empty()) return 0;
    events.front().SetTag(Tag);

//     ++ObjectNumber; // this should be switched on otherwise the last step of the analysis takes very long
    static_cast<HChargedSemiBranch &>(*Branch->NewEntry()) = eventSemiTagger.GetBranch(events.front());
    return 1;
}*/
