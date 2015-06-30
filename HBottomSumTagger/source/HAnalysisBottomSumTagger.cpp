#include "HAnalysisBottomSumTagger.hh"

// hbottomsumtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = analysis::Severity::debug;
//     Print(Severity::notification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     eventBottomSumTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hbottomsumtagger::HAnalysis::StudyName(const analysis::HAnalysis::HTagger Tagger) const
// {
//     Print(Severity::notification, "Study Names", Tagger);
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
//         Print(Severity::error, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<analysis::File> hbottomsumtagger::HAnalysis::Files(const analysis::Tag tag)
{
  Print(analysis::Severity::notification, "Set File Vector", Name(tag));

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

    std::vector<analysis::File> LeptonicFiles = analysis::Join(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<analysis::File> HadronicFiles = analysis::Join(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<analysis::File> SemiFiles = analysis::Join(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<analysis::File> NotLeptonicFiles = analysis::Join(HadronicFiles, SemiFiles);
    std::vector<analysis::File> CombinedFiles = analysis::Join(NotLeptonicFiles, LeptonicFiles);

    std::vector<analysis::File> NonLeptonicSignalFiles = analysis::Join(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<analysis::File> CombinedSignalFiles = analysis::Join(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<analysis::File> NewFiles;

//     switch (Tagger) {
//     case  BottomTagger :
//         switch (Tag) {
//         case Tag::signal :
//             NewFiles = SemiFiles;
//             break;
//         case Tag::background :
//             NewFiles = SemiFiles;
//             break;
//         }
//         break;
//     case  HBottomReader :
//         switch (Tag) {
//         case Tag::signal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case Tag::background :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     case  JetPairTagger :
//         switch (Tag) {
//         case Tag::signal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case Tag::background :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     case  HJetPairReader :
//         switch (Tag) {
//         case Tag::signal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case Tag::background :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     default:
//         Print(Severity::error, "Files", "unknown tagger name", Tagger);
//     }

    switch (tag) {
      case analysis::Tag::signal :
        NewFiles = SignalSemiFiles;
        break;
      case analysis::Tag::background :
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

    analysis::Strings LeptonicTrees = analysis::Join(SignalLeptonicTrees, BackgroundLeptonicTrees);
    analysis::Strings HadronicTrees = analysis::Join(SignalHadronicTree, BackgroundHadronicTrees);
    analysis::Strings SemiTrees = analysis::Join(SignalSemiTrees, BackgroundSemiTrees);

    analysis::Strings NotLeptonicTrees = analysis::Join(HadronicTrees, SemiTrees);
    analysis::Strings CombinedTrees = analysis::Join(NotLeptonicTrees, LeptonicTrees);

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetSignalTreeNames(SemiTrees);
//         BottomTagger.SetBackgroundTreeNames(SemiTrees);
//         if (Tag == Tag::signal) {
//             BottomTagger.SetTagger();
//         }
//         break;
//     case HBottomReader:
//         if (Tag == Tag::signal) {
//             BottomTagger.SetTagger();
//         }
//         BottomTagger.SetSignalTreeNames(SemiTrees);
//         BottomTagger.SetBackgroundTreeNames(SemiTrees);
//         break;
//     case JetPairTagger :
//         eventBottomSumTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventBottomSumTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == Tag::signal) {
//             eventBottomSumTagger.SetTagger(BottomTagger);
//         }
//         break;
//     case HJetPairReader :
//         if (Tag == Tag::signal) {
//             eventBottomSumTagger.SetTagger(BottomTagger);
//         }
//         eventBottomSumTagger.SetSignalTreeNames(SignalSemiTrees);
//         eventBottomSumTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(Severity::error, "SetTrees", "unhandeled case");
    //     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
}

// void hbottomsumtagger::HAnalysis::PrepareReader(const analysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(Severity::information, "Prepare Reader", Tagger);
//     if (Tag == Tag::background) {
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
//         Print(Severity::error, "PrepareReader", "unhandled case");
//     }
// }

// void hbottomsumtagger::HAnalysis::NewBranches(exroot::TreeWriter &NewTreeWriter, const analysis::HAnalysis::HTagger Tagger)
// {
//     Print(Severity::notification, "New Branches", Tagger);
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
//         Print(Severity::error, "No Branch filled");
//     }
//
// }

// int hbottomsumtagger::HAnalysis::RunAnalysis(analysis::Event &, const analysis::Stage , const Tag )
// {
//     Print(Severity::information, "Analysis");
//     ++event_sum_;

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
//         Print(Severity::error, "unknown Tagger", Tagger);
//         return 0;
//     }
//     tagger_.GetBranches(event,stage,tag);
//     return 1;
// }


// bool hbottomsumtagger::HAnalysis::GetBottomTag(analysis::Event &event, const Tag Tag)
// {
//     Print(Severity::debug, "Bottom Tag", Tag);
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
//     Print(Severity::debug, "Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//
//     Jets Particles = event.Partons().GenParticles();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(Id::bottom)), Particles.end());
//
//     int BNumber=0;
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
//             static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(Signal);
//             ++BNumber;
//         }
//     }
//
// //     if(Tag == Tag::signal && BNumber <4 )
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
//     Print(Severity::information, "event semi", Tag);
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
//     Print(Severity::information, "event semi", Tag);
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
// //     Particles = BottomTagger.RemoveIfWrongAbsParticle(Particles,Id::bottom);
// //     for (const auto & Particle : Particles) {
// //       std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
// //       if (jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize)
// //         BottomJets.emplace_back(jets.front());
// //     }
// //
// //     if (Tag == Tag::signal && BottomJets.size() < 4) return 0;
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
