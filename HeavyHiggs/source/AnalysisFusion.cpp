# include "AnalysisFusion.hh"

// heavyhiggs::AnalysisFusion::AnalysisFusion()
// {
// //     DebugLevel = analysis::Object::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
// //     jet_pair_tagger.SetAnalysisName(ProjectName());
//     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     w_semi_tagger.SetAnalysisName(ProjectName());
//     top_hadronic_tagger.SetAnalysisName(ProjectName());
//     top_semi_tagger.SetAnalysisName(ProjectName());
//     heavy_higgs_semi_tagger.SetAnalysisName(ProjectName());
//     eventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string heavyhiggs::AnalysisFusion::StudyName(const analysis::HAnalysis::HTagger Tagger) const
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
//     case EventNeutralTagger:
//         return  "eventSemi";
//     case EventLeptonicReader:
//         return  "eventLeptonicReader";
//     case EventSemiReader:
//         return  "eventSemiReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
//
// }

std::vector<analysis::File> heavyhiggs::AnalysisFusion::Files(const Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;
    std::vector<analysis::File> BackgroundLeptonicFiles;
    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;


    std::string SignalName = ProcessName(H0) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(analysis::File(SignalName, SignalCrosssection(), Mass()));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

//     BackgroundSemiFiles.emplace_back(analysis::File( {"tt_semi_400_0", "tt_semi_400_1", "tt_semi_400_2", "tt_semi_400_3", "tt_semi_400_4", "tt_semi_400_5", "tt_semi_400_6"}, 3100.));

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
//     case HeavyHiggsSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HHeavyHiggsSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventLeptonicTagger:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case EventHadronicTagger:
//         if (tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case EventNeutralTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case EventLeptonicReader:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case EventSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     default:
//         Print(kError, "unknown tagger name");
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

    Print(kNotification, "Files prepared");

    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;
}


void heavyhiggs::AnalysisFusion::SetTrees()
{

  analysis::Strings SignalLeptonicTrees {
    };
    analysis::Strings BackgroundLeptonicTrees {
    };

    std::string SignalTree = ProcessName(H0) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

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

    analysis::Strings SignalHadronicTree {
    };
    analysis::Strings BackgroundHadronicTrees {
    };

    analysis::Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    analysis::Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    analysis::Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    analysis::Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    analysis::Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetSignalTreeNames(CombinedTrees);
//         BottomTagger.SetBackgroundTreeNames(CombinedTrees);
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         break;
//     case HBottomReader:
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
//     case EventNeutralTagger :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, heavy_higgs_semi_tagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiReader :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, w_semi_tagger, w_hadronic_tagger, top_semi_tagger, top_hadronic_tagger, heavy_higgs_semi_tagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandled case");
    //     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void heavyhiggs::AnalysisFusion::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         break;
//     case EventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(w_semi_tagger);
//         TopSemiReader.set_tagger(top_semi_tagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         HeavyHiggsSemiReader.set_tagger(heavy_higgs_semi_tagger);
//         eventSemiReader.set_tagger(eventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
//
// }

// void heavyhiggs::AnalysisFusion::ResetBranch()
// {
// //         Branch.reset();
// }

// void heavyhiggs::AnalysisFusion::NewBranches(exroot::TreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger)
// {
//     Print(kNotification, "New Branches", Tagger);
//
//     switch (Tagger) {
//     case BottomTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), BottomBranch::Class());
//         break;
//     case HBottomReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), BottomBranch::Class());
//         break;
//     case JetPairTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), JetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), JetPairBranch::Class());
//         break;
//     case HWSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case WHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), WHadronicBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), WHadronicBranch::Class());
//         break;
//     case HTopLeptonicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case TopHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopSemiBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopSemiBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsLeptonicReader:
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
//         break;
//     case HeavyHiggsSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HeavyHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HeavyHiggsSemiBranch::Class());
//         break;
//     case EventLeptonicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case EventHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventHadronicBranch::Class());
//         break;
//     case EventNeutralTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventFusionBranch::Class());
//         break;
//     case EventSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventFusionBranch::Class());
//         break;
//     case EventLeptonicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int heavyhiggs::AnalysisFusion::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{

    Print(kInformation, "Analysis");

    if (object_number_ > EventNumberMax()) return 0;

    analysis::Jets Particles = event.partons().GenParticles();
    Particles = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Particles.size() != 2) {
        Print(kError, "Not enough top quarks", Particles.size());
        return 0;
    } else {
        if (Particles.at(0).pt() < PreCut()) return 0;
        if (Particles.at(1).pt() < PreCut()) return 0;
    }


    if (event.hadrons().MissingEt().pt() < MissingEt()) return 0;
    analysis::Jets Leptons = fastjet::sorted_by_pt(event.leptons().leptons());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    analysis::Jets jets = event.hadrons().Jets();
    if (jets.size() < 4) return 0;

//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     Jets Leptons = fastjet::sorted_by_pt(event.leptons().GetLeptonJets());
//     if (Leptons.empty()) return 0;
//     if (MissingEt.pt() < 400) return 0;

    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, Tag);
//     case HBottomReader:
//         return GetBottomReader(event, Tag);
//     case JetPairTagger :
//     case HJetPairReader :
//     case WHadronicTagger :
//         return GetWTag(event, Tag);
//     case HWHadronicReader :
//         return GetWReader(event, Tag);
//     case HWSemiTagger :
//         return GetWSemiTag(event, Tag);
//     case HWSemiReader :
//         return GetWSemiReader(event, Tag);
//     case HTopLeptonicTagger :
//     case TopHadronicTagger :
//         return GetTopHadronicTag(event, Tag);
//     case HTopSemiTagger :
//         return GetTopSemiTag(event, Tag);
//     case HTopHadronicReader :
//         return GetTopHadronicReader(event, Tag);
//     case HTopLeptonicReader :
//     case HTopSemiReader :
//         return GetTopSemiReader(event, Tag);
//     case HHeavyHiggsLeptonicTagger :
// //         return GetHeavyHiggsLeptonicTag(event, Tag);
//     case HHeavyHiggsHadronicTagger :
// //         return GetHeavyHiggsHadronicTag(event, Tag);
//     case HeavyHiggsSemiTagger :
//         return GetHeavyHiggsSemiTag(event, Tag);
//     case HHeavyHiggsSemiReader :
//         return GetHeavyHiggsSemiReader(event, Tag);
//     case HHeavyHiggsLeptonicReader :
// //         return GetHeavyHiggsLeptonicReader(event, Tag);
//     case EventLeptonicTagger :
// //         return GeteventLeptonicTag(event, Tag);
//     case EventHadronicTagger :
// //         return GeteventHadronicTag(event, Tag);
//     case EventNeutralTagger :
//         return GeteventSemiTag(event, Tag);
//     case EventSemiReader :
//         return GeteventSemiReader(event, Tag);
//     case EventLeptonicReader :
// //         return GeteventLeptonicReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
    //     }
    return tagger_.GetBranches(event, stage, tag);
}

// bool heavyhiggs::AnalysisFusion::GetBottomTag(analysis::Event &event, const Tag Tag)
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
// bool heavyhiggs::AnalysisFusion::GetBottomReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     Jets Particles = event.partons().GenParticles();
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
//         ++ObjectNumber;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisFusion::GetWSemiTag(analysis::Event &event, const Tag Tag)
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
// bool heavyhiggs::AnalysisFusion::GetWSemiReader(analysis::Event &event, const Tag Tag)
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
// bool heavyhiggs::AnalysisFusion::GetWTag(analysis::Event &event, const Tag Tag)
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
// bool heavyhiggs::AnalysisFusion::GetWReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = event.hadrons().GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
// //     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
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
//
//
// bool heavyhiggs::AnalysisFusion::GetTopHadronicTag(analysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "hadronic tops", Tag);
//     std::vector<TopHadronicBranch> Tops = top_hadronic_tagger.GetBranches(event, Tag);
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
// bool heavyhiggs::AnalysisFusion::GetTopHadronicReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = event.hadrons().GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
//     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
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
// bool heavyhiggs::AnalysisFusion::GetTopSemiTag(analysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "Tops", Tag);
//     std::vector<TopSemiBranch> Tops = top_semi_tagger.GetBranches(event, Tag);
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//       *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
//       ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisFusion::GetTopSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = event.hadrons().GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
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
//
//
// bool heavyhiggs::AnalysisFusion::GetHeavyHiggsSemiTag(analysis::Event &event, const Tag Tag)
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
// bool heavyhiggs::AnalysisFusion::GetHeavyHiggsSemiReader(analysis::Event &event, const Tag Tag)
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
// bool heavyhiggs::AnalysisFusion::GeteventSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//     std::vector<heavyhiggs::EventFusionBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
//     if (Semievents.empty()) return 0;
//     for (const auto & Semievent : Semievents) {
//         *static_cast<EventFusionBranch *>(Branch->NewEntry()) = Semievent;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
//
//
//
//
// bool heavyhiggs::AnalysisFusion::GeteventSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
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
//     EventStruct global_observables;
//     global_observables.LeptonNumber = Leptons.size();
//     global_observables.JetNumber = jets.size();
//     global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
//     global_observables.ScalarHt = event.hadrons().GetScalarHt();
//
//     std::vector<Hsextet_event> sextet_event = eventSemiTagger.GetBdt(sextets, jets, Leptons, global_observables, eventSemiReader);
//     if (sextet_event.empty()) return 0;
//     sextet_event.front().SetTag(Tag);
//     *static_cast<EventFusionBranch *>(Branch->NewEntry()) = eventSemiTagger.GetBranch(sextet_event.front());
// //     ++ObjectNumber;
//     return 1;
// }
