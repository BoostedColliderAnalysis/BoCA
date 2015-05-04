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
//     case  HBottomTagger :
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

std::vector<hanalysis::HFile> hbottomsumtagger::HAnalysis::Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", Tagger, tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;
    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::HFile> SignalSemiFiles;
    std::vector<hanalysis::HFile> BackgroundSemiFiles;


//     SignalSemiFiles.push_back(hanalysis::HFile(NameString(bb), SignalCrosssection()));
//     SignalSemiFiles.push_back(hanalysis::HFile(SignalName(Hbb), SignalCrosssection()));
//     SignalSemiFiles.push_back(BackgroundFile(ttbb));
    SignalSemiFiles.push_back(BackgroundFile(bb));
//     SignalSemiFiles.push_back(BackgroundFile(bbbb));

//     BackgroundSemiFiles.push_back(BackgroundFile(bb));
    BackgroundSemiFiles.push_back(BackgroundFile(cc));
    BackgroundSemiFiles.push_back(BackgroundFile(gg));
    BackgroundSemiFiles.push_back(BackgroundFile(qq));
//     BackgroundSemiFiles.push_back(BackgroundFile(bbjj));
//     BackgroundSemiFiles.push_back(BackgroundFile(bbcc));
//     BackgroundSemiFiles.push_back(BackgroundFile(bbgg));
//     BackgroundSemiFiles.push_back(BackgroundFile(bbqq));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttjj));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttqq));
//     BackgroundSemiFiles.push_back(BackgroundFile(ttgg));

    std::vector<hanalysis::HFile> SignalHadronicFiles;

    std::vector<hanalysis::HFile> BackgroundHadronicFiles;

    std::vector<hanalysis::HFile> LeptonicFiles = JoinFiles(SignalLeptonicFiles, BackgroundLeptonicFiles);
    std::vector<hanalysis::HFile> HadronicFiles = JoinFiles(SignalHadronicFiles, BackgroundHadronicFiles);
    std::vector<hanalysis::HFile> SemiFiles = JoinFiles(SignalSemiFiles, BackgroundSemiFiles);

    std::vector<hanalysis::HFile> NotLeptonicFiles = JoinFiles(HadronicFiles, SemiFiles);
    std::vector<hanalysis::HFile> CombinedFiles = JoinFiles(NotLeptonicFiles, LeptonicFiles);

    std::vector<hanalysis::HFile> NonLeptonicSignalFiles = JoinFiles(SignalLeptonicFiles, SignalSemiFiles);
    std::vector<hanalysis::HFile> CombinedSignalFiles = JoinFiles(SignalHadronicFiles, NonLeptonicSignalFiles);

    std::vector<hanalysis::HFile> NewFiles;

//     switch (Tagger) {
//     case  HBottomTagger :
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
    NewFiles.front().SetFileSuffix(".root");
    SetTrees(Tagger, tag);
    PrepareReader(Tagger, tag);
    return NewFiles;

}


void hbottomsumtagger::HAnalysis::SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::Tag Tag)
{

    HStrings SignalLeptonicTrees {};
    HStrings BackgroundLeptonicTrees {};



    HStrings SignalSemiTrees {
//         TreeName(bbbb)
//         TreeName(ttbb)
//         SignalTreeName(Hbb)
        TreeName(bb),
    };

    HStrings BackgroundSemiTrees {
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

    HStrings SignalHadronicTree {};
    HStrings BackgroundHadronicTrees {};

    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);

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
    tagger_.SetSignalTreeNames(SignalSemiTrees);
    tagger_.SetBackgroundTreeNames(BackgroundSemiTrees);
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
//         BottomReader.SetMva(BottomTagger);
//         break;
//     case HJetPairTagger :
//         EventBottomSumTagger.BottomTagger.SetTagger();
//         EventBottomSumTagger.BottomReader.SetMva(EventBottomSumTagger.BottomTagger);
//         break;
//     case HJetPairReader :
//         BottomReader.SetMva(BottomTagger);
//         EventBottomSumReader.SetMva(EventBottomSumTagger);
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
//     case HBottomTagger :
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

bool hbottomsumtagger::HAnalysis::Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
{
    Print(HInformation, "Analysis", Tagger);
    ++event_sum_;

    switch (Tagger) {
    case HBottomTagger :
        return GetBottomTag(Event, Tag);
    case HBottomReader:
        return GetBottomReader(Event, Tag);
    case HJetPairTagger :
        return GetEventSemiTag(Event, Tag);
    case HJetPairReader :
        return GetEventSemiReader(Event, Tag);
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool hbottomsumtagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(HDebug, "Get Bottom Tag", Tag);
    std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.size() < 1) {
        return 0;
    }
    for (const auto & Bottom : Bottoms) {
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
    }
    return 1;
}

bool hbottomsumtagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;


    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    int BNumber=0;
    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        if (Jets.front().delta_R(Particle) < BottomTagger.DetectorGeometry.JetConeSize) {
            static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
            ++BNumber;
        }
    }

//     if(Tag == HSignal && BNumber <4 )

    for (const auto & Jet : Jets) {
        if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) {
            continue;
        }
        if (std::abs(Jet.rap()) > BottomTagger.DetectorGeometry.TrackerEtaMax) {
            continue;
        }
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
    }
    return 1;
}


bool hbottomsumtagger::HAnalysis::GetEventSemiTag(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(HInformation, "Get Event semi", Tag);
    std::vector<HEventBottomTaggerBranch> SemiEvents = EventBottomSumTagger.GetBranches(Event, Tag);
    if (SemiEvents.size() < 1) return 0;
    for (const auto & SemiEvent : SemiEvents) {
        ++ObjectNumber;
        *static_cast<HEventBottomTaggerBranch *>(Branch->NewEntry()) = SemiEvent;
    }
    return 1;
}

bool hbottomsumtagger::HAnalysis::GetEventSemiReader(hanalysis::HEvent &Event, const Tag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    if (!EventBottomSumTagger.TruthLevelCheck(Jets,Event, Tag)) return 0;

//     if (Jets.size() < 4) return 0;
//
//     HJets BottomJets;
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles = BottomTagger.RemoveIfWrongAbsParticle(Particles,BottomId);
//     for (const auto & Particle : Particles) {
//       std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//       if (Jets.front().delta_R(Particle) < BottomTagger.DetectorGeometry.JetConeSize)
//         BottomJets.push_back(Jets.front());
//     }
//
//     if (Tag == HSignal && BottomJets.size() < 4) return 0;
//     if (Tag == HBackground && BottomJets.size() < 2) return 0;


    std::vector<HEventBottomMultiplet> Events = EventBottomSumTagger.GetBdt(Jets, EventBottomSumReader);
    if (Events.size() < 1) return 0;
    Events.front().SetTag(Tag);
    ++ObjectNumber;
    *static_cast<HEventBottomTaggerBranch *>(Branch->NewEntry()) = EventBottomSumTagger.GetBranch(Events.front());
    return 1;
}
