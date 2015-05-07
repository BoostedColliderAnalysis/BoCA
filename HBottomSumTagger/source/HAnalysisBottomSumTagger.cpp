# include "HAnalysisBottomSumTagger.hh"

// hbottomsumtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = hanalysis::HObject::HDebug;
//     Print(HNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     EventBottomSumTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hbottomsumtagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(HNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  BottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case  HJetPairTagger :
//         return "EventBottom";
//     case  HJetPairReader :
//         return "EventBottomReader";
//     default :
//         Print(HError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<hanalysis::RootFile> hbottomsumtagger::HAnalysis::Files(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

    std::vector<hanalysis::RootFile> SignalLeptonicFiles;
    std::vector<hanalysis::RootFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::RootFile> SignalSemiFiles;
    std::vector<hanalysis::RootFile> BackgroundSemiFiles;


//     SignalSemiFiles.emplace_back(hanalysis::RootFile(NameString(bb), SignalCrosssection()));
//     SignalSemiFiles.emplace_back(hanalysis::RootFile(SignalName(Hbb), SignalCrosssection()));
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
//         switch (Tag) {
//         case HObject::kSignal :
//             NewFiles = SemiFiles;
//             break;
//         case HObject::kBackground :
//             NewFiles = SemiFiles;
//             break;
//         }
//         break;
//     case  HBottomReader :
//         switch (Tag) {
//         case HObject::kSignal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case HObject::kBackground :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     case  HJetPairTagger :
//         switch (Tag) {
//         case HObject::kSignal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case HObject::kBackground :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     case  HJetPairReader :
//         switch (Tag) {
//         case HObject::kSignal :
//             NewFiles = SignalSemiFiles;
//             break;
//         case HObject::kBackground :
//             NewFiles = BackgroundSemiFiles;
//             break;
//         }
//         break;
//     default:
//         Print(HError, "Files", "unknown tagger name", Tagger);
//     }

    switch (tag) {
      case HObject::kSignal :
        NewFiles = SignalSemiFiles;
        break;
      case HObject::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

    NewFiles.front().SetBasePath("~/Projects/MultiBTagging/");
    NewFiles.front().set_file_suffix(".root");
    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;

}


void hbottomsumtagger::HAnalysis::SetTrees()
{

    Strings SignalLeptonicTrees {};
    Strings BackgroundLeptonicTrees {};



    Strings SignalSemiTrees {
//         TreeName(bbbb)
//         TreeName(ttbb)
//         SignalTreeName(Hbb)
        TreeName(bb),
    };

    Strings BackgroundSemiTrees {
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
//         EventBottomSumTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventBottomSumTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         if (Tag == kSignal) {
//             EventBottomSumTagger.SetTagger(BottomTagger);
//         }
//         break;
//     case HJetPairReader :
//         if (Tag == kSignal) {
//             EventBottomSumTagger.SetTagger(BottomTagger);
//         }
//         EventBottomSumTagger.SetSignalTreeNames(SignalSemiTrees);
//         EventBottomSumTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
//         break;
//     default :
//         Print(HError, "SetTrees", "unhandeled case");
    //     }
//     tagger_.SetSignalTreeNames(SignalSemiTrees);
//     tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
}

// void hbottomsumtagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
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
//         EventBottomSumTagger.BottomTagger.SetTagger();
//         EventBottomSumTagger.BottomReader.set_tagger(EventBottomSumTagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.set_tagger(bottom_tagger_);
//         EventBottomSumReader.set_tagger(EventBottomSumTagger);
//         break;
//     default :
//         Print(HError, "PrepareReader", "unhandled case");
//     }
// }

// void hbottomsumtagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
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
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventBottomTaggerBranch::Class());
//         break;
//     case HJetPairReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HEventBottomTaggerBranch::Class());
//         break;
//     default :
//         Print(HError, "No Branch filled");
//     }
//
// }

int hbottomsumtagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{
    Print(HInformation, "Analysis");
    ++event_sum_;

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(Event, Tag);
//     case HBottomReader:
//         return GetBottomReader(Event, Tag);
//     case HJetPairTagger :
//         return GetEventSemiTag(Event, Tag);
//     case HJetPairReader :
//         return GetEventSemiReader(Event, Tag);
//     default :
//         Print(HError, "unknown Tagger", Tagger);
//         return 0;
//     }
    tagger_.GetBranches(event,stage,tag);
}


// bool hbottomsumtagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
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
// bool hbottomsumtagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Reader", Tag);
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     int BNumber=0;
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         if (Jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize) {
//             static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//             ++BNumber;
//         }
//     }
//
// //     if(Tag == kSignal && BNumber <4 )
//
//     for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) {
//             continue;
//         }
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) {
//             continue;
//         }
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//     }
//     return 1;
// }
//
//
// bool hbottomsumtagger::HAnalysis::GetEventSemiTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//     std::vector<HEventBottomTaggerBranch> SemiEvents = EventBottomSumTagger.GetBranches(Event, Tag);
//     if (SemiEvents.empty()) return 0;
//     for (const auto & SemiEvent : SemiEvents) {
//         ++ObjectNumber;
//         *static_cast<HEventBottomTaggerBranch *>(Branch->NewEntry()) = SemiEvent;
//     }
//     return 1;
// }
//
// bool hbottomsumtagger::HAnalysis::GetEventSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//
//     if (!EventBottomSumTagger.TruthLevelCheck(Jets,Event, Tag)) return 0;
//
// //     if (Jets.size() < 4) return 0;
// //
// //     HJets BottomJets;
// //     HJets Particles = Event.GetParticles()->Generator();
// //     Particles = BottomTagger.RemoveIfWrongAbsParticle(Particles,BottomId);
// //     for (const auto & Particle : Particles) {
// //       std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
// //       if (Jets.front().delta_R(Particle) < BottomTagger.detector_geometry().JetConeSize)
// //         BottomJets.emplace_back(Jets.front());
// //     }
// //
// //     if (Tag == kSignal && BottomJets.size() < 4) return 0;
// //     if (Tag == HBackground && BottomJets.size() < 2) return 0;
//
//
//     std::vector<HEventBottomMultiplet> Events = EventBottomSumTagger.GetBdt(Jets, EventBottomSumReader);
//     if (Events.empty()) return 0;
//     Events.front().SetTag(Tag);
//     ++ObjectNumber;
//     *static_cast<HEventBottomTaggerBranch *>(Branch->NewEntry()) = EventBottomSumTagger.GetBranch(Events.front());
//     return 1;
// }
