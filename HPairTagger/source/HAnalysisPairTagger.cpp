# include "HAnalysisPairTagger.hh"
# include "Predicate.hh"

// hpairtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = analysis::Object::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     jet_pair_tagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hpairtagger::HAnalysis::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  BottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case  JetPairTagger :
//         return "JetPair";
//     case  HJetPairReader :
//         return "JetPairReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<analysis::File> hpairtagger::HAnalysis::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;
    std::vector<analysis::File> BackgroundLeptonicFiles;
    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;


    SignalSemiFiles.emplace_back(BackgroundFile(bb,VBF));
//     SignalSemiFiles.emplace_back(analysis::File(NameString(bb), SignalCrosssection()));
//     SignalSemiFiles.emplace_back(analysis::File(SignalName(Hbb), SignalCrosssection()));

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
//     case JetPairTagger :
//         jet_pair_tagger.SetSignalTreeNames(SignalSemiTrees);
//         jet_pair_tagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) {
//             jet_pair_tagger.SetTagger(BottomTagger);
//         }
//         break;
//     case HJetPairReader :
//         if (Tag == kSignal) {
//             jet_pair_tagger.SetTagger(BottomTagger);
//         }
//         jet_pair_tagger.SetSignalTreeNames(SignalSemiTrees);
//         jet_pair_tagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "SetTrees", "unhandeled case");
//     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
}

// void hpairtagger::HAnalysis::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//     case JetPairTagger :
//         jet_pair_tagger.BottomTagger.SetTagger();
//         jet_pair_tagger.BottomReader.set_tagger(jet_pair_tagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         JetPairReader.set_tagger(jet_pair_tagger);
//         break;
//     default :
//         Print(kError, "PrepareReader", "unhandled case");
//     }
// }

// void hpairtagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger)
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
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hpairtagger::HAnalysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const analysis::Object::Tag tag)
{
    Print(kInformation, "Analysis", stage, tag);
    ++event_sum_;

//     switch (stage) {
//     case BottomTagger :
//         return GetBottomTag(event, tag);
//     case HBottomReader:
//         return GetBottomReader(event, tag);
//     case JetPairTagger :
//         return GetJetPairTag(event, tag);
//     case HJetPairReader :
//         return GetJetPairReader(event, tag);
//     default :
//         Print(kError, "unknown Tagger", tagger);
//         return 0;
//     }

//     switch (stage) {
//       case analysis::Tagger::kTrainer :
        return tagger_.GetBranches(event, stage, tag);
//       case analysis::Tagger::kReader:
//         return tagger_.GetBdt(event, tag);
//     }
}


// bool hpairtagger::HAnalysis::GetTag(analysis::Event &event, const Tag tag)
// {
//   Print(kDebug, "Get Bottom Tag", tag);
//   return tagger_.GetBranches(event, tag);
// }
//
//
// bool hpairtagger::HAnalysis::GetBottomTag(analysis::Event &event, const Tag Tag)
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
// bool hpairtagger::HAnalysis::GetBottomReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) {
//         return 0;
//     }
//
//     Jets Particles = event.partons().Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
//             static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//         }
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) {
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
// bool hpairtagger::HAnalysis::GetJetPairTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Get JetPair Tag", Tag);
//     std::vector<JetPairBranch> JetPairs = jet_pair_tagger.GetBranches(event, Tag, MotherId(ProductionChannel()));
//     if (JetPairs.empty()) {
//         return 0;
//     }
//     for (const auto & JetPair : JetPairs) {
//         *static_cast<JetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
// bool hpairtagger::HAnalysis::GetJetPairReader(analysis::Event &event, const Tag Tag)
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
//     Jets Particles = event.partons().Generator();
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
// //             static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
// //             FilteredJets.emplace_back(jets.front()); // WRONG MUST BE REMOVED
// //         }
// //     }
//
// //     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(FilteredJets, JetPairReader);
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         static_cast<JetPairBranch &>(*Branch->NewEntry()) = jet_pair_tagger.GetBranch(doublet);
//     }
//     return 1;
// }
