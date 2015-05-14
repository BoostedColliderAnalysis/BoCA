# include "HAnalysisPairTagger.hh"
# include "Predicate.hh"

// hpairtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = hanalysis::HObject::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     JetPairTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hpairtagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Get Study Names", Tagger);
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
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<hanalysis::File> hpairtagger::HAnalysis::Files(const hanalysis::HObject::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<hanalysis::File> SignalLeptonicFiles;
    std::vector<hanalysis::File> BackgroundLeptonicFiles;
    std::vector<hanalysis::File> SignalSemiFiles;
    std::vector<hanalysis::File> BackgroundSemiFiles;


    SignalSemiFiles.emplace_back(BackgroundFile(bb,VBF));
//     SignalSemiFiles.emplace_back(hanalysis::File(NameString(bb), SignalCrosssection()));
//     SignalSemiFiles.emplace_back(hanalysis::File(SignalName(Hbb), SignalCrosssection()));

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

    std::vector<hanalysis::File> SignalHadronicFiles;

    std::vector<hanalysis::File> BackgroundHadronicFiles;

    std::vector<hanalysis::File> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::File> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::File> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::File> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::File> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);

    std::vector<hanalysis::File> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::File> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::File> NewFiles;

        switch (tag) {
        case HObject::kSignal :
            NewFiles = SignalSemiFiles;
            break;
        case HObject::kBackground :
            NewFiles = BackgroundSemiFiles;
            break;
        }


//     NewFiles.front().SetBasePath("~/Projects/PairTagging/");
//     NewFiles.front().set_file_suffix(".root");
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
//         Print(kError, "SetTrees", "unhandeled case");
//     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
}

// void hpairtagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(kInformation, "Prepare Reader", Tagger);
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
//         Print(kError, "PrepareReader", "unhandled case");
//     }
// }

// void hpairtagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
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
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hpairtagger::HAnalysis::Analysis(hanalysis::Event &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Analysis", stage, tag);
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
//         Print(kError, "unknown Tagger", tagger);
//         return 0;
//     }

//     switch (stage) {
//       case hanalysis::Tagger::kTrainer :
        return tagger_.GetBranches(event, stage, tag);
//       case hanalysis::Tagger::kReader:
//         return tagger_.GetBdt(event, tag);
//     }
}


// bool hpairtagger::HAnalysis::GetTag(hanalysis::Event &event, const Tag tag)
// {
//   Print(kDebug, "Get Bottom Tag", tag);
//   return tagger_.GetBranches(event, tag);
// }
//
//
// bool hpairtagger::HAnalysis::GetBottomTag(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Tag", Tag);
//     std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(event, Tag);
//     if (Bottoms.empty()) {
//         return 0;
//     }
//     for (const auto & Bottom : Bottoms) {
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetBottomReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) {
//         return 0;
//     }
//
//     Jets Particles = event.Partons().Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
//             static_cast<hanalysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//         }
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<hanalysis::JetInfo>().Tag()) {
//             continue;
//         }
// //         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) {
// //             continue;
// //         }
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetJetPairTag(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get JetPair Tag", Tag);
//     std::vector<EventJetPairBranch> JetPairs = JetPairTagger.GetBranches(event, Tag, MotherId(ProductionChannel()));
//     if (JetPairs.empty()) {
//         return 0;
//     }
//     for (const auto & JetPair : JetPairs) {
//         *static_cast<EventJetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetJetPairReader(hanalysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get JetPair Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) {
//         Print(kInformation, "just one jet", jets.size());
//         return 0;
//     }
//     Print(kError, "jets", jets.size());
//
// //     Jets FilteredJets; // WRONG MUST BE REMOVED
//     Jets Particles = event.Partons().Generator();
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
// //         Print(kError, "where are the quarks?", Particles.size());
// //     }
//
// //     for (const auto & Particle : Particles) {
// //         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
// //         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
// //             static_cast<hanalysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
// //             FilteredJets.emplace_back(jets.front()); // WRONG MUST BE REMOVED
// //         }
// //     }
//
// //     std::vector<hanalysis::Doublet> doublets = JetPairTagger.GetBdt(FilteredJets, JetPairReader);
//     std::vector<hanalysis::Doublet> doublets = JetPairTagger.GetBdt(jets, JetPairReader);
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         static_cast<EventJetPairBranch &>(*Branch->NewEntry()) = JetPairTagger.GetBranch(doublet);
//     }
//     return 1;
// }
