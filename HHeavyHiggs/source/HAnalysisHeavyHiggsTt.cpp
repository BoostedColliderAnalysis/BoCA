# include "HAnalysisHeavyHiggsTt.hh"

// hheavyhiggs::HAnalysisTt::HAnalysisTt()
// {
// //     DebugLevel = hanalysis::HObject::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
// //     JetPairTagger.SetAnalysisName(ProjectName());
//     WHadronicTagger.SetAnalysisName(ProjectName());
//     WSemiTagger.SetAnalysisName(ProjectName());
//     TopHadronicTagger.SetAnalysisName(ProjectName());
//     TopSemiTagger.SetAnalysisName(ProjectName());
//     HeavyHiggsSemiTagger.SetAnalysisName(ProjectName());
//     EventSemiTagger.SetAnalysisName(ProjectName());
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
//     case HEventSemiTagger:
//         return  "EventSemi";
//     case HEventLeptonicReader:
//         return  "EventLeptonicReader";
//     case HEventSemiReader:
//         return  "EventSemiReader";
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
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HHeavyHiggsSemiReader:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventLeptonicTagger:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HEventHadronicTagger:
//         if (tag == kSignal) NewFiles = SignalHadronicFiles;
//         else NewFiles = BackgroundHadronicFiles;
//         break;
//     case HEventSemiTagger:
//         if (tag == kSignal) NewFiles = SignalSemiFiles;
//         else NewFiles = BackgroundSemiFiles;
//         break;
//     case HEventLeptonicReader:
//         if (tag == kSignal) NewFiles = SignalLeptonicFiles;
//         else NewFiles = BackgroundLeptonicFiles;
//         break;
//     case HEventSemiReader:
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
//     case HEventSemiTagger :
//         if (Tag == kSignal) EventSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
//         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     case HEventSemiReader :
//         if (Tag == kSignal) EventSemiTagger.SetTagger(BottomTagger, WSemiTagger, WHadronicTagger, TopSemiTagger, TopHadronicTagger, HeavyHiggsSemiTagger);
//         EventSemiTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
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
//         break;
//     case HEventSemiReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         WSemiReader.set_tagger(WSemiTagger);
//         TopSemiReader.set_tagger(TopSemiTagger);
//         WHadronicReader.set_tagger(WHadronicTagger);
//         TopHadronicReader.set_tagger(TopHadronicTagger);
//         HeavyHiggsSemiReader.set_tagger(HeavyHiggsSemiTagger);
//         EventSemiReader.set_tagger(EventSemiTagger);
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
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventJetPairBranch::Class());
//         break;
//     case HWSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
//         break;
//     case HTopLeptonicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopLeptonicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonicBranch::Class());
//         break;
//     case HTopHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), TopHadronicBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopSemiBranch::Class());
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
//     case HEventLeptonicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventLeptonicBranch::Class());
//         break;
//     case HEventHadronicTagger :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventHadronicBranch::Class());
//         break;
//     case HEventSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventTtSemiBranch::Class());
//         break;
//     case HEventSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventTtSemiBranch::Class());
//         break;
//     case HEventLeptonicReader :
// //         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventLeptonicBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hheavyhiggs::HAnalysisTt::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{

    Print(kInformation, "Analysis");

    if (ObjectNumber > EventNumberMax()) return 0;

    Jets Particles = event.GetParticles()->Generator();
    Particles = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Particles.size() != 2) {
        Print(kError, "Not enough top quarks", Particles.size());
        return 0;
    } else {
        if (Particles.at(0).pt() < PreCut()) return 0;
        if (Particles.at(1).pt() < PreCut()) return 0;
    }


    if (event.GetJets()->GetMissingEt().pt() < MissingEt()) return 0;
    Jets Leptons = fastjet::sorted_by_pt(event.GetLeptons()->GetLeptonJets());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    Jets jets = bottom_tagger_.GetJets(event);
    if (jets.size() < 4) return 0;

//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     Jets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets());
//     if (Leptons.empty()) return 0;
//     if (MissingEt.pt() < 400) return 0;

    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(Event, Tag);
//     case HBottomReader:
//         return GetBottomReader(Event, Tag);
//     case HJetPairTagger :
//     case HJetPairReader :
//     case HWHadronicTagger :
//         return GetWTag(Event, Tag);
//     case HWHadronicReader :
//         return GetWReader(Event, Tag);
//     case HWSemiTagger :
//         return GetWSemiTag(Event, Tag);
//     case HWSemiReader :
//         return GetWSemiReader(Event, Tag);
//     case HTopLeptonicTagger :
//     case HTopHadronicTagger :
//         return GetTopHadronicTag(Event, Tag);
//     case HTopSemiTagger :
//         return GetTopSemiTag(Event, Tag);
//     case HTopHadronicReader :
//         return GetTopHadronicReader(Event, Tag);
//     case HTopLeptonicReader :
//     case HTopSemiReader :
//         return GetTopSemiReader(Event, Tag);
//     case HHeavyHiggsLeptonicTagger :
// //         return GetHeavyHiggsLeptonicTag(Event, Tag);
//     case HHeavyHiggsHadronicTagger :
// //         return GetHeavyHiggsHadronicTag(Event, Tag);
//     case HHeavyHiggsSemiTagger :
//         return GetHeavyHiggsSemiTag(Event, Tag);
//     case HHeavyHiggsSemiReader :
//         return GetHeavyHiggsSemiReader(Event, Tag);
//     case HHeavyHiggsLeptonicReader :
// //         return GetHeavyHiggsLeptonicReader(Event, Tag);
//     case HEventLeptonicTagger :
// //         return GetEventLeptonicTag(Event, Tag);
//     case HEventHadronicTagger :
// //         return GetEventHadronicTag(Event, Tag);
//     case HEventSemiTagger :
//         return GetEventSemiTag(Event, Tag);
//     case HEventSemiReader :
//         return GetEventSemiReader(Event, Tag);
//     case HEventLeptonicReader :
// //         return GetEventLeptonicReader(Event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
    //     }
    return tagger_.GetBranches(event, stage, tag);
}

// bool hheavyhiggs::HAnalysisTt::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Tag", Tag);
//     std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
//     if (Bottoms.empty()) return 0;
//     for (const auto & Bottom : Bottoms) {
//         ++ObjectNumber;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTt::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     Jets Particles = Event.GetParticles()->Generator();
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
// bool hheavyhiggs::HAnalysisTt::GetWSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get W Semi Tag", Tag);
//     std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
//     if (WSemis.empty()) return 0;
//     for (const auto & WSemi : WSemis) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTt::GetWSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get W Semi Reader", Tag);
//
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
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
// bool hheavyhiggs::HAnalysisTt::GetWTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get W Tag", Tag);
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
// bool hheavyhiggs::HAnalysisTt::GetWReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = Event.GetJets()->GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
// //     std::vector<hanalysis::Doublet> doublets = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Doublet> doublets = WHadronicTagger.GetBdt(jets, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(doublet);
//     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisTt::GetTopHadronicTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(kInformation, "Get hadronic tops", Tag);
//     std::vector<TopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
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
// bool hheavyhiggs::HAnalysisTt::GetTopHadronicReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = Event.GetJets()->GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
//     std::vector<hanalysis::Doublet> doublets = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(doublets, jets, TopHadronicReader);
//
//     if (triplets.size() > 1) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + 1, triplets.end());
//     }
//
//     for (const auto & triplet : triplets) {
//         ++ObjectNumber;
//         *static_cast<TopHadronicBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
//
// bool hheavyhiggs::HAnalysisTt::GetTopSemiTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(kInformation, "Get Tops", Tag);
//     std::vector<HTopSemiBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//       *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = Top;
//       ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTt::GetTopSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = Event.GetJets()->GetStructuredJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
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
//         *static_cast<HTopSemiBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
//
//
// bool hheavyhiggs::HAnalysisTt::GetHeavyHiggsSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Semi HeavyHiggs Tag", Tag);
//     std::vector<HHeavyHiggsSemiBranch> Higgses = HeavyHiggsSemiTagger.GetBranches(Event, Tag);
//     if (Higgses.empty()) return 0;
//     for (const auto & Higgs : Higgses) {
//         ++ObjectNumber;
//         *static_cast<HHeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
//     }
//     return 1;
// }
//
// bool hheavyhiggs::HAnalysisTt::GetHeavyHiggsSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<hanalysis::Doublet> doubletsHadronic = WHadronicTagger.GetBdt(jets, WHadronicReader);
// //     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
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
// bool hheavyhiggs::HAnalysisTt::GetEventSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//     std::vector<hheavyhiggs::HEventTtSemiBranch> SemiEvents = EventSemiTagger.GetBranches(Event, Tag);
//     if (SemiEvents.empty()) return 0;
//     for (const auto & SemiEvent : SemiEvents) {
//         *static_cast<HEventTtSemiBranch *>(Branch->NewEntry()) = SemiEvent;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
//
//
//
//
// bool hheavyhiggs::HAnalysisTt::GetEventSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::Doublet> doubletsSemi = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::Triplet> tripletsSemi = TopSemiTagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<hanalysis::Doublet> doubletsHadronic = WHadronicTagger.GetBdt(jets, WHadronicReader);
// //     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<hanalysis::Triplet> tripletsHadronic = TopHadronicTagger.GetBdt(jets, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::HSextet> Sextets = HeavyHiggsSemiTagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     HEventStruct EventStruct;
//     EventStruct.LeptonNumber = Leptons.size();
//     EventStruct.JetNumber = jets.size();
//     EventStruct.BottomNumber = Event.GetJets()->GetBottomJets().size();
//     EventStruct.ScalarHt = Event.GetJets()->GetScalarHt();
//
//     std::vector<HSextetEvent> SextetEvent = EventSemiTagger.GetBdt(Sextets, jets, Leptons, EventStruct, EventSemiReader);
//     if (SextetEvent.empty()) return 0;
//     SextetEvent.front().SetTag(Tag);
//     *static_cast<HEventTtSemiBranch *>(Branch->NewEntry()) = EventSemiTagger.GetBranch(SextetEvent.front());
// //     ++ObjectNumber;
//     return 1;
// }
