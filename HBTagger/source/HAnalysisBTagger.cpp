# include "HAnalysisBTagger.hh"

hbtagger::HAnalysis::HAnalysis()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    BottomTagger.SetAnalysisName(ProjectName());
    mkdir(ProjectName().c_str(), 0700);
}

std::string hbtagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
{
    Print(HNotification, "Get Study Names", Tagger);

    switch (Tagger) {
    case  HBottomTagger :
        return "Bottom";
    case  HBottomReader :
        return "BottomReader";
    default :
        Print(HError, "unexpected TaggerName", Tagger);
        return "";
    }
}

std::vector<hanalysis::HFile> hbtagger::HAnalysis::Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag)
{
    Print(HNotification, "Set File Vector", Tagger, Tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;
    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::HFile> SignalSemiFiles;
    std::vector<hanalysis::HFile> BackgroundSemiFiles;

//     SignalSemiFiles.push_back(hanalysis::HFile(FileName(bb), SignalCrosssection()));
//     SignalSemiFiles.push_back(hanalysis::HFile(FileName(Hbb), SignalCrosssection()));
//     SignalSemiFiles.push_back(hanalysis::HFile(FileName(ttbb), SignalCrosssection()));
    SignalSemiFiles.push_back(hanalysis::HFile(FileName(tt), SignalCrosssection()));

//     SignalSemiFiles.push_back(BackgroundFile(bb));
    BackgroundSemiFiles.push_back(BackgroundFile(bb));
    BackgroundSemiFiles.push_back(BackgroundFile(cc));
//     BackgroundSemiFiles.push_back(BackgroundFile(jj));
//     BackgroundSemiFiles.push_back(BackgroundFile(tt));
//         BackgroundSemiFiles.push_back(BackgroundFile(ttcc));
//         BackgroundSemiFiles.push_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.push_back(BackgroundFile(qq));
    BackgroundSemiFiles.push_back(BackgroundFile(gg));

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

    switch (Tagger) {
    case  HBottomTagger :
        switch (Tag) {
        case HObject::HSignal :
            NewFiles = SignalSemiFiles;
            break;
        case HObject::HBackground :
            NewFiles = BackgroundSemiFiles;
            break;
        }
        break;
    case  HBottomReader :
        switch (Tag) {
        case HObject::HSignal :
            NewFiles = SignalSemiFiles;
            break;
        case HObject::HBackground :
            NewFiles = BackgroundSemiFiles;
            break;
        }
        break;
    default:
        Print(HError, "Files", "unknown tagger name", Tagger);
    }

    NewFiles.front().SetBasePath("~/Projects/BTagging/");
    NewFiles.front().SetFileSuffix(".root");
    SetTrees(Tagger, Tag);
    PrepareReader(Tagger, Tag);
    return NewFiles;

}


void hbtagger::HAnalysis::SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag)
{

    HStrings SignalLeptonicTrees {};
    HStrings BackgroundLeptonicTrees {};

    HStrings SignalSemiTrees {
//         TreeName(bb)
//         TreeName(Hbb),
//         TreeName(ttbb),
        TreeName(tt),
    };

    HStrings BackgroundSemiTrees {
        TreeName(bb),
        TreeName(cc),
//         TreeName(jj),
//         TreeName(tt),
        TreeName(qq),
        TreeName(gg)
//         TreeName(ttcc),
//         TreeName(ttjj),
    };

    HStrings SignalHadronicTree {};
    HStrings BackgroundHadronicTrees {};

    HStrings LeptonicTrees = JoinHStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    HStrings HadronicTrees = JoinHStrings(SignalHadronicTree, BackgroundHadronicTrees);
    HStrings SemiTrees = JoinHStrings(SignalSemiTrees, BackgroundSemiTrees);

    HStrings NotLeptonicTrees = JoinHStrings(HadronicTrees, SemiTrees);
    HStrings CombinedTrees = JoinHStrings(NotLeptonicTrees, LeptonicTrees);

    switch (Tagger) {
    case HBottomTagger:
        BottomTagger.SetSignalTreeNames(SignalSemiTrees);
        BottomTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        if (Tag == HSignal)  BottomTagger.SetTagger();
        break;
    case HBottomReader:
        if (Tag == HSignal)  BottomTagger.SetTagger();
        BottomTagger.SetSignalTreeNames(SignalSemiTrees);
        BottomTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    default :
        Print(HError, "unhandeled case");
    }
}

void hbtagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HInformation, "Prepare Reader", Tagger);
    if (Tag == HBackground) return;
    switch (Tagger) {
    case HBottomTagger:
        break;
    case HBottomReader:
        BottomReader.SetMva(BottomTagger);
        break;
    default :
        Print(HError, "unhandled case");
    }
}

void hbtagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HBottomReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
        break;
    default :
        Print(HError, "No Branch filled");
    }

}

bool hbtagger::HAnalysis::Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HInformation, "Analysis", Tagger);
    ++EventSumM;

    switch (Tagger) {
    case HBottomTagger :
        return GetBottomTag(Event, Tag);
    case HBottomReader:
        return GetBottomReader(Event, Tag);
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool hbtagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Tag", Tag);
    std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) {
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
        ++ObjectNumber;
    }
    return 1;
}

bool hbtagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
    if (Jets.size() < 1) return 0;

//     HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         if (Jets.front().delta_R(Particle) < BottomTagger.DetectorGeometry.JetConeSize) static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
//     }

    Jets.erase(std::remove_if(Jets.begin(), Jets.end(), TooSmallPt(PreCut() / 2 * 3)), Jets.end());
    std::sort(Jets.begin(), Jets.end(), SortByBdt());

    for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.DetectorGeometry.TrackerEtaMax && ProductionChannel() == DYP) continue;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
        ++ObjectNumber;
        break;
    }
    return 1;
}

