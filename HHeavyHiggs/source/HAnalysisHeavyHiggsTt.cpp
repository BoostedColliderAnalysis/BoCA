# include "HAnalysisHeavyHiggsTt.hh"

// hheavyhiggs::HAnalysisTt::HAnalysisTt()
// {
// //     DebugLevel = hanalysis::HObject::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
// //     JetPairTagger.SetAnalysisName(ProjectName());
//     w_hadronic_tagger.SetAnalysisName(ProjectName());
//     WSemiTagger.SetAnalysisName(ProjectName());
//     top_hadronic_tagger.SetAnalysisName(ProjectName());
//     TopSemiTagger.SetAnalysisName(ProjectName());
//     HeavyHiggsSemiTagger.SetAnalysisName(ProjectName());
//     eventSemiTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hheavyhiggs::HAnalysisTt::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
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
//     case EventSemiTagger:
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

std::vector<hanalysis::RootFile> hheavyhiggs::HAnalysisTt::Files(const Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<hanalysis::RootFile> SignalLeptonicFiles;
    std::vector<hanalysis::RootFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::RootFile> SignalSemiFiles;
    std::vector<hanalysis::RootFile> BackgroundSemiFiles;


    std::string SignalName = ProcessName(H0) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(hanalysis::RootFile(SignalName, SignalCrosssection(), Mass()));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

//     BackgroundSemiFiles.emplace_back(hanalysis::RootFile( {"tt_semi_400_0", "tt_semi_400_1", "tt_semi_400_2", "tt_semi_400_3", "tt_semi_400_4", "tt_semi_400_5", "tt_semi_400_6"}, 3100.));

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
//     case EventSemiTagger:
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
      case HObject::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case HObject::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

    NewFiles.front().SetBasePath("~/Projects/HeavyHiggs/Mass/");
    NewFiles.front().set_file_suffix(".root");

    Print(kNotification, "Files prepared");

    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;
}


void hheavyhiggs::HAnalysisTt::SetTrees()
{

    Strings SignalLeptonicTrees {
    };
    Strings BackgroundLeptonicTrees {
    };

    std::string SignalTree = ProcessName(H0) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV-run_01";

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

    Strings SignalHadronicTree {
    };
    Strings BackgroundHadronicTrees {
    };

    Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

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
//     case EventSemiTagger :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, HeavyHiggsSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case EventSemiReader :
//         if (Tag == kSignal) eventSemiTagger.SetTagger(BottomTagger, WSemiTagger, w_hadronic_tagger, TopSemiTagger, top_hadronic_tagger, HeavyHiggsSemiTagger);
//         eventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "unhandled case");
    //     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);

}



// void hheavyhiggs::HAnalysisTt::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         break;
//     case EventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(w_hadronic_tagger);
//         TopHadronicReader.set_tagger(top_hadronic_tagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         eventSemiReader.set_tagger(eventSemiTagger);
//         break;
//     default :
//         Print(kError, "unhandled case");
//     }
//
// }

// void hheavyhiggs::HAnalysisTt::ResetBranch()
// {
// //         Branch.reset();
// }

// void hheavyhiggs::HAnalysisTt::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
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
//     case HJetPairTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventJetPairBranch::Class());
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
//     case HHeavyHiggsSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HHeavyHiggsSemiBranch::Class());
//         break;
//     case EventLeptonicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case EventHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventHadronicBranch::Class());
//         break;
//     case EventSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventTtSemiBranch::Class());
//         break;
//     case EventSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventTtSemiBranch::Class());
//         break;
//     case EventLeptonicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hheavyhiggs::HAnalysisTt::Analysis(hanalysis::Event &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{

    Print(kInformation, "Analysis");

    if (object_number_ > EventNumberMax()) return 0;

    Jets Particles = event.Partons().Generator();
    Particles = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Particles.size() != 2) {
        Print(kError, "Not enough top quarks", Particles.size());
        return 0;
    } else {
        if (Particles.at(0).pt() < PreCut()) return 0;
        if (Particles.at(1).pt() < PreCut()) return 0;
    }


    if (event.Hadrons().GetMissingEt().pt() < MissingEt()) return 0;
    Jets Leptons = fastjet::sorted_by_pt(event.Leptons().GetLeptonJets());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    Jets jets = bottom_tagger_.GetJets(event);
    if (jets.size() < 4) return 0;

//     fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
//     Jets Leptons = fastjet::sorted_by_pt(event.Leptons().GetLeptonJets());
//     if (Leptons.empty()) return 0;
//     if (MissingEt.pt() < 400) return 0;

    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, Tag);
//     case HBottomReader:
//         return GetBottomReader(event, Tag);
//     case HJetPairTagger :
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
//     case HHeavyHiggsSemiTagger :
//         return GetHeavyHiggsSemiTag(event, Tag);
//     case HHeavyHiggsSemiReader :
//         return GetHeavyHiggsSemiReader(event, Tag);
//     case HHeavyHiggsLeptonicReader :
// //         return GetHeavyHiggsLeptonicReader(event, Tag);
//     case EventLeptonicTagger :
// //         return GeteventLeptonicTag(event, Tag);
//     case EventHadronicTagger :
// //         return GeteventHadronicTag(event, Tag);
//     case EventSemiTagger :
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

// bool hheavyhiggs::HAnalysisTt::GetBottomTag(hanalysis::Event &event, const Tag Tag)
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
// bool hheavyhiggs::HAnalysisTt::GetBottomReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     Jets Particles = event.Partons().Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<hanalysis::JetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
//         ++ObjectNumber;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTt::GetWSemiTag(hanalysis::Event &event, const Tag Tag)
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
// bool hheavyhiggs::HAnalysisTt::GetWSemiReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get W Semi Reader", Tag);
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
//
//     std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
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
// bool hheavyhiggs::HAnalysisTt::GetWTag(hanalysis::Event &event, const Tag Tag)
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
// bool hheavyhiggs::HAnalysisTt::GetWReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = event.Hadrons().GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
// //     std::vector<hanalysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader, bottom_tagger_, BottomReader);
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
// bool hheavyhiggs::HAnalysisTt::GetTopHadronicTag(hanalysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "Get hadronic tops", Tag);
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
// bool hheavyhiggs::HAnalysisTt::GetTopHadronicReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = event.Hadrons().GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
//     std::vector<hanalysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
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
// bool hheavyhiggs::HAnalysisTt::GetTopSemiTag(hanalysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "Get Tops", Tag);
//     std::vector<TopSemiBranch> Tops = TopSemiTagger.GetBranches(event, Tag);
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//       *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
//       ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTt::GetTopSemiReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = event.Hadrons().GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
//     std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);
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
//
//
// bool hheavyhiggs::HAnalysisTt::GetHeavyHiggsSemiTag(hanalysis::Event &event, const Tag Tag)
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
// bool hheavyhiggs::HAnalysisTt::GetHeavyHiggsSemiReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
//     std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<hanalysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<hanalysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
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
// bool hheavyhiggs::HAnalysisTt::GeteventSemiTag(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//     std::vector<hheavyhiggs::EventTtSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
//     if (Semievents.empty()) return 0;
//     for (const auto & Semievent : Semievents) {
//         *static_cast<EventTtSemiBranch *>(Branch->NewEntry()) = Semievent;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
//
//
//
//
// bool hheavyhiggs::HAnalysisTt::GeteventSemiReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Get event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
//     Jets Leptons = event.Leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.Hadrons().GetMissingEt();
//     std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<hanalysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<hanalysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     EventStruct eventStruct;
//     eventStruct.LeptonNumber = Leptons.size();
//     eventStruct.JetNumber = jets.size();
//     eventStruct.BottomNumber = event.Hadrons().GetBottomJets().size();
//     eventStruct.ScalarHt = event.Hadrons().GetScalarHt();
//
//     std::vector<HSextetevent> Sextetevent = eventSemiTagger.GetBdt(Sextets, jets, Leptons, eventStruct, eventSemiReader);
//     if (Sextetevent.empty()) return 0;
//     Sextetevent.front().SetTag(Tag);
//     *static_cast<EventTtSemiBranch *>(Branch->NewEntry()) = eventSemiTagger.GetBranch(Sextetevent.front());
// //     ++ObjectNumber;
//     return 1;
// }
