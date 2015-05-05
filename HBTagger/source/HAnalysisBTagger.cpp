# include "HAnalysisBTagger.hh"

// hbtagger::HAnalysis::HAnalysis()
// {
//     //     DebugLevel = hanalysis::HObject::HDebug;
//     Print(HNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string hbtagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(HNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  HBottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     default :
//         Print(HError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<hanalysis::HFile> hbtagger::HAnalysis::Files(const hanalysis::HObject::Tag Tag)
{
    Print(HNotification, "Set File Vector", Tag);

    std::vector<hanalysis::HFile> SignalFiles;
    std::vector<hanalysis::HFile> BackgroundFiles;

    SignalFiles.push_back(hanalysis::HFile(FileName(bb), SignalCrosssection()));
//     SignalFiles.push_back(hanalysis::HFile(FileName(Hbb), SignalCrosssection()));
//     SignalFiles.push_back(hanalysis::HFile(FileName(ttbb), SignalCrosssection()));
//     SignalFiles.push_back(hanalysis::HFile(FileName(ttlep), SignalCrosssection()));
//     SignalFiles.push_back(hanalysis::HFile(FileName(tthad), SignalCrosssection()));
//     SignalFiles.push_back(hanalysis::HFile(FileName(tt), SignalCrosssection()));

//     SignalFiles.push_back(BackgroundFile(bb));
//     BackgroundFiles.push_back(BackgroundFile(bb));
    BackgroundFiles.push_back(BackgroundFile(cc));
//     BackgroundFiles.push_back(BackgroundFile(jj));
//     BackgroundFiles.push_back(BackgroundFile(tt));
//         BackgroundFiles.push_back(BackgroundFile(ttcc));
//         BackgroundFiles.push_back(BackgroundFile(ttjj));
    BackgroundFiles.push_back(BackgroundFile(qq));
    BackgroundFiles.push_back(BackgroundFile(gg));
//     BackgroundFiles.push_back(BackgroundFile(hh));
//     BackgroundFiles.push_back(BackgroundFile(ww));

    std::vector<hanalysis::HFile> NewFiles;

//     switch (Tagger) {
//     case  HBottomTagger :
        switch (Tag) {
        case HObject::kSignal :
            NewFiles = SignalFiles;
            break;
        case HObject::kBackground :
            NewFiles = BackgroundFiles;
            break;
        }
//         break;
//     case  HBottomReader :
//         switch (Tag) {
//         case HObject::kSignal :
//             NewFiles = SignalFiles;
//             break;
//         case HObject::kBackground :
//             NewFiles = BackgroundFiles;
//             break;
//         }
//         break;
//     default:
//         Print(HError, "Files", "unknown tagger name", Tagger);
//     }

    NewFiles.front().SetBasePath("~/Projects/BTagging/");
    NewFiles.front().SetFileSuffix(".root");
    SetTrees();
//     PrepareReader(Tagger, Tag);
    return NewFiles;

}


void hbtagger::HAnalysis::SetTrees()
{

    HStrings SignalTrees {
        TreeName(bb),
//         TreeName(Hbb),
//         TreeName(ttbb),
//         TreeName(ttlep),
//         TreeName(tthad),
    };

    HStrings BackgroundTrees {
//         TreeName(bb),
        TreeName(cc),
//         TreeName(jj),
//         TreeName(tt),
        TreeName(qq),
        TreeName(gg),
//         TreeName(hh),
//         TreeName(ww),
//         TreeName(ttcc),
//         TreeName(ttjj),
    };

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetSignalTreeNames(SignalTrees);
//         BottomTagger.SetBackgroundTreeNames(BackgroundTrees);
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         break;
//     case HBottomReader:
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         BottomTagger.SetSignalTreeNames(SignalTrees);
//         BottomTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     default :
//         Print(HError, "unhandeled case");
//     }

    tagger_.SetSignalTreeNames(SignalTrees);
    tagger_.SetBackgroundTreeNames(BackgroundTrees);

}

// void hbtagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(HInformation, "Prepare Reader", Tagger);
//     if (Tag == kBackground) return;
//     switch (Tagger) {
//     case HBottomTagger:
//         break;
//     case HBottomReader:
//         BottomReader.SetMva(BottomTagger);
//         break;
//     default :
//         Print(HError, "unhandled case");
//     }
// }

// void hbtagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
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
//     default :
//         Print(HError, "No Branch filled");
//     }
//
// }

bool hbtagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const Tag tag)
{
    Print(HInformation, "Analysis");
    ++event_sum_;

//     switch (Tagger) {
//     case HBottomTagger :
//         return GetBottomTag(Event, Tag);
//     case HBottomReader:
//         return GetBottomReader(Event, Tag);
//     default :
//         Print(HError, "unknown Tagger", Tagger);
//         return 0;
//     }
    return tagger_.GetBranches(event, stage, tag);
}


// bool hbtagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Tag", Tag);
//     std::vector<HBottomBranch> bottoms = BottomTagger.GetBranches(Event, Tag);
//     std::vector<HBottomBranch> final_bottoms;
//
//     for (const auto & bottom : bottoms) if (bottom.Pt > PreCut() || bottom.Pt < 1.5 * PreCut()) final_bottoms.push_back(bottom);
//     if (bottoms.size() < 1) return 0;
//
//     for (const auto & bottom : final_bottoms) {
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = bottom;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool hbtagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Reader", Tag);
//     HJets Jets = BottomTagger.GetJets(Event);
//     Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
//     if (Jets.size() < 1) return 0;
//
// //     HJets Particles = Event.GetParticles()->Generator();
// //     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
// //
// //     for (const auto & Particle : Particles) {
// //         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
// //         if (Jets.front().delta_R(Particle) < BottomTagger.DetectorGeometry.JetConeSize) static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
// //     }
//
//     Jets.erase(std::remove_if(Jets.begin(), Jets.end(), TooSmallPt(PreCut())), Jets.end());
//     Jets.erase(std::remove_if(Jets.begin(), Jets.end(), TooBigPt(1.5 * PreCut())), Jets.end());
//     std::sort(Jets.begin(), Jets.end(), SortByBdt());
//
//     for (const auto & Jet : Jets) {
// //         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
// //         if (std::abs(Jet.rap()) > BottomTagger.DetectorGeometry.TrackerEtaMax && ProductionChannel() == DYP) continue;
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//         ++ObjectNumber;
//         break;
//     }
//     return 1;
// }
//
