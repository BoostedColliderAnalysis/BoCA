# include "HAnalysisPairTagger.hh"
# include "Predicate.hh"

// hpairtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = hanalysis::HObject::HDebug;
//     Print(HNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     JetPairTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hpairtagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(HNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  BottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case  HJetPairTagger :
//         return "JetPair";
//     case  HJetPairReader :
//         return "JetPairReader";
//     default :
//         Print(HError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<hanalysis::RootFile> hpairtagger::HAnalysis::Files(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

    std::vector<hanalysis::RootFile> SignalLeptonicFiles;
    std::vector<hanalysis::RootFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::RootFile> SignalSemiFiles;
    std::vector<hanalysis::RootFile> BackgroundSemiFiles;


    SignalSemiFiles.emplace_back(BackgroundFile(bb,VBF));
//     SignalSemiFiles.emplace_back(hanalysis::RootFile(NameString(bb), SignalCrosssection()));
//     SignalSemiFiles.emplace_back(hanalysis::RootFile(SignalName(Hbb), SignalCrosssection()));

    BackgroundSemiFiles.emplace_back(BackgroundFile(bb,DYP));
    BackgroundSemiFiles.emplace_back(BackgroundFile(cc,DYP));
    BackgroundSemiFiles.emplace_back(BackgroundFile(cc,VBF));
    BackgroundSemiFiles.emplace_back(BackgroundFile(jj,DYP));
    BackgroundSemiFiles.emplace_back(BackgroundFile(jj,VBF));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttjj));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttqq));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttgg));

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


    NewFiles.front().SetBasePath("~/Projects/PairTagging/");
    NewFiles.front().set_file_suffix(".root");
    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;

}


void hpairtagger::HAnalysis::SetTrees()
{

    Strings SignalLeptonicTrees {};
    Strings BackgroundLeptonicTrees {};



    Strings SignalSemiTrees {
      TreeName(bb,VBF),
//       SignalTreeName(Hbb)
    };

    Strings BackgroundSemiTrees {
        TreeName(bb,DYP),
        TreeName(cc,VBF),
        TreeName(cc,DYP),
        TreeName(jj,VBF),
        TreeName(jj,DYP),
//         TreeName(ttbb),
//         TreeName(ttcc),
//         TreeName(ttjj),
//         TreeName(ttgg),
//         TreeName(ttqq)
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
//         BottomTagger.SetSignalTreeNames(SemiTrees);
//         BottomTagger.SetBackgroundTreeNames(SemiTrees);
//         if (Tag == kSignal) {
//             BottomTagger.SetTagger();
//         }
//         break;
//     case HBottomReader:
//         if (Tag == kSignal) {
//             BottomTagger.SetTagger();
//         }
//         BottomTagger.SetSignalTreeNames(SemiTrees);
//         BottomTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case HJetPairTagger :
//         JetPairTagger.SetSignalTreeNames(SignalSemiTrees);
//         JetPairTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) {
//             JetPairTagger.SetTagger(BottomTagger);
//         }
//         break;
//     case HJetPairReader :
//         if (Tag == kSignal) {
//             JetPairTagger.SetTagger(BottomTagger);
//         }
//         JetPairTagger.SetSignalTreeNames(SignalSemiTrees);
//         JetPairTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(HError, "SetTrees", "unhandeled case");
//     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
}

// void hpairtagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(HInformation, "Prepare Reader", Tagger);
//     if (Tag == kBackground) {
//         return;
//     }
//     switch (Tagger) {
//     case HBottomTagger:
//         break;
//     case HBottomReader:
//         BottomReader.set_tagger(bottom_tagger_);
//         break;
//     case HJetPairTagger :
//         JetPairTagger.BottomTagger.SetTagger();
//         JetPairTagger.BottomReader.set_tagger(JetPairTagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         JetPairReader.set_tagger(JetPairTagger);
//         break;
//     default :
//         Print(HError, "PrepareReader", "unhandled case");
//     }
// }

// void hpairtagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
// {
//     Print(HNotification, "New Branches", Tagger);
//
//     switch (Tagger) {
//     case BottomTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
//         break;
//     case HBottomReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
//         break;
//     case HJetPairTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventJetPairBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventJetPairBranch::Class());
//         break;
//     default :
//         Print(HError, "No Branch filled");
//     }
//
// }

int hpairtagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Analysis", stage, tag);
    ++event_sum_;

//     switch (stage) {
//     case BottomTagger :
//         return GetBottomTag(event, tag);
//     case HBottomReader:
//         return GetBottomReader(event, tag);
//     case HJetPairTagger :
//         return GetJetPairTag(event, tag);
//     case HJetPairReader :
//         return GetJetPairReader(event, tag);
//     default :
//         Print(HError, "unknown Tagger", tagger);
//         return 0;
//     }

//     switch (stage) {
//       case hanalysis::Tagger::kTrainer :
        return tagger_.GetBranches(event, stage, tag);
//       case hanalysis::Tagger::kReader:
//         return tagger_.GetBdt(Event, tag);
//     }
}


// bool hpairtagger::HAnalysis::GetTag(hanalysis::HEvent &Event, const Tag tag)
// {
//   Print(HDebug, "Get Bottom Tag", tag);
//   return tagger_.GetBranches(Event, tag);
// }
//
//
// bool hpairtagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Tag", Tag);
//     std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
//     if (Bottoms.empty()) {
//         return 0;
//     }
//     for (const auto & Bottom : Bottoms) {
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) {
//         return 0;
//     }
//
//     Jets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
//             static_cast<hanalysis::HJetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//         }
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) {
//             continue;
//         }
// //         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) {
// //             continue;
// //         }
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetJetPairTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get JetPair Tag", Tag);
//     std::vector<HEventJetPairBranch> JetPairs = JetPairTagger.GetBranches(Event, Tag, MotherId(ProductionChannel()));
//     if (JetPairs.empty()) {
//         return 0;
//     }
//     for (const auto & JetPair : JetPairs) {
//         *static_cast<HEventJetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetJetPairReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get JetPair Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) {
//         Print(HInformation, "just one jet", jets.size());
//         return 0;
//     }
//     Print(HError, "jets", jets.size());
//
// //     Jets FilteredJets; // WRONG MUST BE REMOVED
//     Jets Particles = Event.GetParticles()->Generator();
//     if (Tag == kSignal) {
// //         Particles = BottomTagger.RemoveIfWrongAbsFamily(Particles, BottomId, MotherId(ProductionChannel()));
//     }
//     if (
// // ProductionChannel() == Associated &&
//         Tag == kBackground) {
// //         Particles = RemoveIfWrongAbsStepMother(Particles, TopId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
// //         Particles = BottomTagger.RemoveIfWrongParticle(Particles, GluonId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
// //         Particles = BottomTagger.RemoveIfWrongAbsMother(Particles, ZId); // THIS IS WRONG AND SHOULD BE REMOVED AGAIN
//     }
//
// //     if (
// //         Tag == kSignal &&
// //         Particles.size() != 2) {
// //         Print(HError, "where are the quarks?", Particles.size());
// //     }
//
// //     for (const auto & Particle : Particles) {
// //         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
// //         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
// //             static_cast<hanalysis::HJetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
// //             FilteredJets.emplace_back(jets.front()); // WRONG MUST BE REMOVED
// //         }
// //     }
//
// //     std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(FilteredJets, JetPairReader);
//     std::vector<hanalysis::HDoublet> Doublets = JetPairTagger.GetBdt(jets, JetPairReader);
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) {
//         static_cast<HEventJetPairBranch &>(*Branch->NewEntry()) = JetPairTagger.GetBranch(Doublet);
//     }
//     return 1;
// }
