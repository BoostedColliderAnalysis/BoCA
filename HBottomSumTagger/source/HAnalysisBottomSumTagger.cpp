# include "HAnalysisBottomSumTagger.hh"

// hbottomsumtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = analysis::Object::kDebug;
//     Print(kNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     eventBottomSumTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hbottomsumtagger::HAnalysis::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(kNotification, "Study Names", Tagger);
//
//     switch (Tagger) {
//     case  BottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case  JetPairTagger :
//         return "eventBottom";
//     case  HJetPairReader :
//         return "eventBottomReader";
//     default :
//         Print(kError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<analysis::File> hbottomsumtagger::HAnalysis::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;
    std::vector<analysis::File> BackgroundLeptonicFiles;
    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;


//     SignalSemiFiles.emplace_back(analysis::File(NameString(bb), SignalCrosssection()));
//     SignalSemiFiles.emplace_back(analysis::File(SignalName(Hbb), SignalCrosssection()));
//     SignalSemiFiles.emplace_back(BackgroundFile(ttbb));
    SignalSemiFiles.emplace_back(BackgroundFile(bb));
//     SignalSemiFiles.emplace_back(BackgroundFile(bbbb));

//     BackgroundSemiFiles.emplace_back(BackgroundFile(bb));
    BackgroundSemiFiles.emplace_back(BackgroundFile(cc));
    BackgroundSemiFiles.emplace_back(BackgroundFile(gg));
    BackgroundSemiFiles.emplace_back(BackgroundFile(qq));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(bbjj));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(bbcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(bbgg));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(bbqq));
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

//     switch (Tagger) {
//     case  BottomTagger :
//         switch (Tag) {
//         case Object::kSignal :
//             NewFiles = SemiFiles;
//             break;
//         case Object::kBackground :
//             NewFiles = SemiFiles;
//             break;
//         }
//         break;
//     case  HBottomReader :
//         switch (Tag) {
//         case Object::kSignal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case Object::kBackground :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     case  JetPairTagger :
//         switch (Tag) {
//         case Object::kSignal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case Object::kBackground :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     case  HJetPairReader :
//         switch (Tag) {
//         case Object::kSignal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case Object::kBackground :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     default:
//         Print(kError, "Files", "unknown tagger name", Tagger);
//     }

    switch (tag) {
      case Object::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case Object::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

//     NewFiles.front().SetBasePath("~/Projects/MultiBTagging/");
//     NewFiles.front().set_file_suffix(".root");
    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;

}


void hbottomsumtagger::HAnalysis::SetTrees()
{

  analysis::Strings SignalLeptonicTrees {};
  analysis::Strings BackgroundLeptonicTrees {};



  analysis::Strings SignalSemiTrees {
//         TreeName(bbbb)
//         TreeName(ttbb)
//         SignalTreeName(Hbb)
        TreeName(bb),
    };

    analysis::Strings BackgroundSemiTrees {
//         TreeName(bb),
        TreeName(cc),
        TreeName(qq),
        TreeName(gg),
//         TreeName(bbjj)
//         TreeName(bbcc),
//         TreeName(bbqq),
//         TreeName(bbgg)
//         TreeName(ttbb),
//         TreeName(ttcc),
//         TreeName(ttjj)
//         TreeName(ttgg),
//         TreeName(ttqq)
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
//         eventBottomSumTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventBottomSumTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) {
//             eventBottomSumTagger.SetTagger(BottomTagger);
//         }
//         break;
//     case HJetPairReader :
//         if (Tag == kSignal) {
//             eventBottomSumTagger.SetTagger(BottomTagger);
//         }
//         eventBottomSumTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventBottomSumTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(kError, "SetTrees", "unhandeled case");
    //     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
}

// void hbottomsumtagger::HAnalysis::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         eventBottomSumTagger.BottomTagger.SetTagger();
//         eventBottomSumTagger.BottomReader.set_tagger(eventBottomSumTagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         eventBottomSumReader.set_tagger(eventBottomSumTagger);
//         break;
//     default :
//         Print(kError, "PrepareReader", "unhandled case");
//     }
// }

// void hbottomsumtagger::HAnalysis::NewBranches(exroot::TreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger)
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
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventBottomTaggerBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), EventBottomTaggerBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
// }

int hbottomsumtagger::HAnalysis::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{
    Print(kInformation, "Analysis");
    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, Tag);
//     case HBottomReader:
//         return GetBottomReader(event, Tag);
//     case JetPairTagger :
//         return GeteventSemiTag(event, Tag);
//     case HJetPairReader :
//         return GeteventSemiReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
//     }
    tagger_.GetBranches(event,stage,tag);
}


// bool hbottomsumtagger::HAnalysis::GetBottomTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Tag", Tag);
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
// bool hbottomsumtagger::HAnalysis::GetBottomReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//
//     Jets Particles = event.Partons().GenParticles();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     int BNumber=0;
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
//             static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//             ++BNumber;
//         }
//     }
//
// //     if(Tag == kSignal && BNumber <4 )
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) {
//             continue;
//         }
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) {
//             continue;
//         }
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
//
// bool hbottomsumtagger::HAnalysis::GeteventSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//     std::vector<EventBottomTaggerBranch> Semievents = eventBottomSumTagger.GetBranches(event, Tag);
//     if (Semievents.empty()) return 0;
//     for (const auto & Semievent : Semievents) {
//         ++ObjectNumber;
//         *static_cast<EventBottomTaggerBranch *>(Branch->NewEntry()) = Semievent;
//     }
//     return 1;
// }
//
// bool hbottomsumtagger::HAnalysis::GeteventSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     if (!eventBottomSumTagger.TruthLevelCheck(jets,event, Tag)) return 0;
//
// //     if (jets.size() < 4) return 0;
// //
// //     Jets BottomJets;
// //     Jets Particles = event.Partons().GenParticles();
// //     Particles = BottomTagger.RemoveIfWrongAbsParticle(Particles,BottomId);
// //     for (const auto & Particle : Particles) {
// //       std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
// //       if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize)
// //         BottomJets.emplace_back(jets.front());
// //     }
// //
// //     if (Tag == kSignal && BottomJets.size() < 4) return 0;
// //     if (Tag == HBackground && BottomJets.size() < 2) return 0;
//
//
//     std::vector<EventBottomMultiplet> events = eventBottomSumTagger.GetBdt(jets, eventBottomSumReader);
//     if (events.empty()) return 0;
//     events.front().SetTag(Tag);
//     ++ObjectNumber;
//     *static_cast<EventBottomTaggerBranch *>(Branch->NewEntry()) = eventBottomSumTagger.GetBranch(events.front());
//     return 1;
// }
