# include "HAnalysisTopTagger.hh"

htoptagger::HAnalysis::HAnalysis()
{
    //     DebugLevel = hanalysis::HObject::HDebug;
    Print(HNotification, "Constructor");
    BottomTagger.SetAnalysisName(ProjectName());
    WHadronicTagger.SetAnalysisName(ProjectName());
    WSemiTagger.SetAnalysisName(ProjectName());
    TopHadronicTagger.SetAnalysisName(ProjectName());
    TopLeptonTagger.SetAnalysisName(ProjectName());
    mkdir(ProjectName().c_str(), 0700);
}

std::string htoptagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
{
    Print(HNotification, "Get Study Names", Tagger);

    switch (Tagger) {
    case  HBottomTagger :
        return "Bottom";
    case  HBottomReader :
        return "BottomReader";
    case HWSemiTagger:
        return  "WSemi";
    case HWSemiReader:
        return  "WSemiReader";
    case HWHadronicTagger:
        return  "WHadronic";
    case HWHadronicReader:
        return  "WHadronicReader";
    case HJetPairTagger:
        return  "JetPair";
    case HJetPairReader:
        return  "JetPairReader";
    case HTopLeptonicTagger:
        return  "TopLeptonic";
    case HTopLeptonicReader:
        return  "TopLeptonicReader";
    case HTopHadronicTagger:
        return  "TopHadronic";
    case HTopSemiTagger:
        return  "TopSemi";
    case HTopHadronicReader:
        return  "TopHadronicReader";
    case HTopSemiReader:
        return  "TopSemiReader";
    case HHeavyHiggsLeptonicTagger:
        return  "HeavyHiggsLeptonic";
    case HHeavyHiggsHadronicTagger:
        return  "HeavyHiggsHadronic";
    case HHeavyHiggsSemiTagger:
        return  "HeavyHiggsSemi";
    case HHeavyHiggsSemiReader:
        return  "HeavyHiggsSemiReader";
    case HHeavyHiggsLeptonicReader:
        return  "HeavyHiggsLeptonicReader";
    case HEventLeptonicTagger:
        return  "EventLeptonic";
    case HEventHadronicTagger:
        return  "EventHadronic";
    case HEventLeptonicReader:
        return  "EventLeptonicReader";
    case HSignatureSemiTagger:
        return  "SignatureSemi";
    case HSignatureSemiReader:
        return  "SignatureSemiReader";
    case HEventSemiTagger:
        return  "EventSemi";
    case HEventSemiReader:
        return  "EventSemiReader";
    default :
        Print(HError, "unexpected TaggerName", Tagger);
        return "";
    }
}

std::vector<hanalysis::HFile> htoptagger::HAnalysis::Files(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HObject::HTag Tag)
{
    Print(HNotification, "Set File Vector", Tagger, Tag);

    std::vector<hanalysis::HFile> SignalLeptonicFiles;
    std::vector<hanalysis::HFile> BackgroundLeptonicFiles;
    std::vector<hanalysis::HFile> SignalSemiFiles;
    std::vector<hanalysis::HFile> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
//   SignalSemiFiles.push_back(hanalysis::HFile(SignalName, SignalCrosssection(), Mass()));
    //     SignalSemiFiles.push_back(BackgroundFile(ttbb));
//     SignalSemiFiles.push_back(BackgroundFile(ttjj));
    SignalSemiFiles.push_back(BackgroundFile(tt));

//   BackgroundSemiFiles.push_back(BackgroundFile(ttbb));
//   BackgroundSemiFiles.push_back(BackgroundFile(ttcc));
//   BackgroundSemiFiles.push_back(BackgroundFile(ttjj));
//     BackgroundSemiFiles.push_back(BackgroundFile(bbjj));
    BackgroundSemiFiles.push_back(BackgroundFile(bb));
    BackgroundSemiFiles.push_back(BackgroundFile(cc));
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
        NewFiles = CombinedFiles;
        break;
    case  HBottomReader :
        NewFiles = CombinedFiles;
        break;
    case HWSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HWSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HWHadronicTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HWHadronicReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HTopHadronicTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HTopSemiTagger:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HTopHadronicReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    case HTopSemiReader:
        if (Tag == HSignal) NewFiles = SignalSemiFiles;
        else NewFiles = BackgroundSemiFiles;
        break;
    default:
        Print(HError, "unknown tagger name");
    }

    NewFiles.front().SetBasePath("~/Projects/HTopTagger/");
    NewFiles.front().SetFileSuffix(".root");
    SetTrees(Tagger, Tag);
    PrepareReader(Tagger, Tag);
    return NewFiles;

}


void htoptagger::HAnalysis::SetTrees(const hanalysis::HAnalysis::HTagger Tagger, const hanalysis::HAnalysis::HTag Tag)
{

    HStrings SignalLeptonicTrees {};
    HStrings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    HStrings SignalSemiTrees {
//     SignalTree
//         BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    HStrings BackgroundSemiTrees {
//     BackgroundTree(ttbb),
//     BackgroundTree(ttcc),
//     BackgroundTree(ttjj)
//         BackgroundTree(bbjj)
        BackgroundTree(bb),
        BackgroundTree(cc),
        BackgroundTree(qq),
        BackgroundTree(gg)
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
        BottomTagger.SetSignalTreeNames(CombinedTrees);
        BottomTagger.SetBackgroundTreeNames(CombinedTrees);
        if (Tag == HSignal)  BottomTagger.SetTagger();
        break;
    case HBottomReader:
        break;
    case HWHadronicTagger:
        WHadronicTagger.SetSignalTreeNames(SignalSemiTrees);
        WHadronicTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
        break;
    case HWHadronicReader :
        WHadronicTagger.SetSignalTreeNames(SignalSemiTrees);
        WHadronicTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        if (Tag == HSignal) WHadronicTagger.SetTagger(BottomTagger);
        break;
    case HWSemiTagger :
        if (Tag == HSignal) WSemiTagger.SetTagger();
        WSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        WSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HWSemiReader :
        if (Tag == HSignal) WSemiTagger.SetTagger();
        WSemiTagger.SetSignalTreeNames(SignalSemiTrees);
        WSemiTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HTopHadronicTagger :
        if (Tag == HSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        TopHadronicTagger.SetSignalTreeNames(SignalSemiTrees);
        TopHadronicTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HTopHadronicReader :
        if (Tag == HSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
        TopHadronicTagger.SetSignalTreeNames(SignalSemiTrees);
        TopHadronicTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HTopSemiTagger :
        if (Tag == HSignal) TopLeptonTagger.SetTagger(BottomTagger);
        TopLeptonTagger.SetSignalTreeNames(SignalSemiTrees);
        TopLeptonTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    case HTopSemiReader :
        if (Tag == HSignal) TopLeptonTagger.SetTagger(BottomTagger);
        TopLeptonTagger.SetSignalTreeNames(SignalSemiTrees);
        TopLeptonTagger.SetBackgroundTreeNames(BackgroundSemiTrees);
        break;
    default :
        Print(HError, "unhandeled case");
    }
}

void htoptagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HInformation, "Prepare Reader", Tagger);
    if (Tag == HBackground) return;
    switch (Tagger) {
    case HBottomTagger:
        break;
    case HBottomReader:
        BottomReader.SetMva(BottomTagger);
        break;
    case HWHadronicTagger:
        WHadronicTagger.BottomTagger.SetTagger();
        WHadronicTagger.BottomReader.SetMva(WHadronicTagger.BottomTagger);
        break;
    case HWHadronicReader:
        BottomReader.SetMva(BottomTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        break;
    case HWSemiTagger :
        break;
    case HWSemiReader :
//         WSemiReader.SetMva(WSemiTagger);
        break;
    case HTopHadronicTagger :
        TopHadronicTagger.BottomTagger.SetTagger();
        TopHadronicTagger.BottomReader.SetMva(TopHadronicTagger.BottomTagger);
        TopHadronicTagger.WTagger.SetTagger(BottomTagger);
        TopHadronicTagger.WReader.SetMva(TopHadronicTagger.WTagger);
        break;
    case HTopHadronicReader :
        BottomReader.SetMva(BottomTagger);
        WHadronicReader.SetMva(WHadronicTagger);
        TopHadronicReader.SetMva(TopHadronicTagger);
        break;
    case HTopSemiTagger :
        TopLeptonTagger.BottomTagger.SetTagger();
        TopLeptonTagger.BottomReader.SetMva(TopLeptonTagger.BottomTagger);
//         TopLeptonTagger.WSemiTagger.SetTagger();
//         TopLeptonTagger.WSemiReader.SetMva(TopLeptonTagger.WSemiTagger);
        break;
    case HTopSemiReader :
        BottomReader.SetMva(BottomTagger);
//         WSemiReader.SetMva(WSemiTagger);
        TopLeptonReader.SetMva(TopLeptonTagger);
        break;
    default :
        Print(HError, "unhandled case");
    }
}

void htoptagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
{
    Print(HNotification, "New Branches", Tagger);

    switch (Tagger) {
    case HBottomTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HBottomReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HBottomBranch::Class());
        break;
    case HWSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
        break;
    case HWHadronicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
        break;
    case HWHadronicReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
        break;
    case HTopHadronicTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiTagger :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonBranch::Class());
        break;
    case HTopHadronicReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronicBranch::Class());
        break;
    case HTopSemiReader :
        Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonBranch::Class());
        break;
    default :
        Print(HError, "No Branch filled");
    }

}

bool htoptagger::HAnalysis::Analysis(hanalysis::HEvent &Event, const hanalysis::HAnalysis::HTagger Tagger, const HTag Tag)
{
    Print(HInformation, "Analysis", Tagger);

    //     const int NumberofBackgroundFiles = 3;
    //     int ObjectMax;
    //     switch(Tag){
    //       case HSignal : ObjectMax = EventNumberMax();
    //       case HBackground : ObjectMax = EventNumberMax() / NumberofBackgroundFiles; // might be stupid
    //     }

    if (ObjectNumber > EventNumberMax()) {
        //         if (Tag == HSignal) Print(HError, "more signals than events", "doesnt have to be bad");
        return 0;
    }

//     const float TopPtCut = 500;

//     HJets Particles = Event.GetParticles()->Generator();
//     Particles = BottomTagger.RemoveIfWrongAbsParticle(Particles, TopId);
//     if (Tag == HSignal && Particles.size() != 2) {
// //     Print(HError, "Not enough tops", Particles.size());
// //     return 0;
//     } else if (Particles.size() > 1) {
//         if (Particles.at(0).pt() < TopPtCut) return 0;
//         if (Particles.at(1).pt() < TopPtCut) return 0;
//         Print(HInformation, "Top pt", Particles.at(0).pt(), Particles.at(1).pt());
//     }


//     HJets Leptons = fastjet::sorted_by_pt(Event.GetLeptons()->GetLeptonJets());
//     if (Leptons.size() < 1) return 0;
//     if (Leptons.front().pt() < PreCut()) return 0;

    //     HJets Bottoms = Event.GetJets()->GetBottomJets();
    //     if (Bottoms.size() < 3) return 0;
    ++EventSumM;

    switch (Tagger) {
    case HBottomTagger :
        return GetBottomTag(Event, Tag);
    case HBottomReader:
        return GetBottomReader(Event, Tag);
    case HWHadronicTagger :
        if (TopDecay() == Hadronic || TopDecay() == Semi) return GetWTag(Event, Tag);
        else return 0;
    case HWHadronicReader :
        if (TopDecay() == Hadronic || TopDecay() == Semi) return GetWReader(Event, Tag);
        else return 0;
    case HWSemiTagger :
//         if (TopDecay() == Leptonic || TopDecay() == Semi) return GetWSemiTag(Event, Tag);
//         else
      return 0;
    case HWSemiReader :
//         if (TopDecay() == Leptonic || TopDecay() == Semi) return GetWSemiReader(Event, Tag);
//         else
      return 0;
    case HTopHadronicTagger :
        if (TopDecay() == Hadronic || TopDecay() == Semi) return GetTopHadronicTag(Event, Tag);
        else return 0;
    case HTopSemiTagger :
        if (TopDecay() == Leptonic || TopDecay() == Semi) return GetTopSemiTag(Event, Tag);
        else return 0;
    case HTopHadronicReader :
        if (TopDecay() == Hadronic || TopDecay() == Semi) return GetTopHadronicReader(Event, Tag);
        else return 0;
    case HTopSemiReader :
        if (TopDecay() == Leptonic || TopDecay() == Semi) return GetTopSemiReader(Event, Tag);
        else return 0;
    default :
        Print(HError, "unknown Tagger", Tagger);
        return 0;
    }
}


bool htoptagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Tag", Tag);
    std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
    if (Bottoms.size() < 1) return 0;
    for (const auto & Bottom : Bottoms) {
        ++ObjectNumber;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
    }
    return 1;
}

bool htoptagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get Bottom Reader", Tag);
    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    //     Jets = static_cast<hanalysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(Jets);

    HJets Particles = Event.GetParticles()->Generator();
    Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());

    for (const auto & Particle : Particles) {
        std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
        static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(HSignal);
    }

    for (const auto & Jet : Jets) {
        if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
        if (std::abs(Jet.rap()) > BottomTagger.DetectorGeometry.TrackerEtaMax) continue;
        *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
    }
    return 1;
}

// // bool htoptagger::HAnalysis::GetWSemiTag(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HDebug, "Get W Semi Tag", Tag);
// //     std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
// //     if (WSemis.size() < 1) return 0;
// //     for (const auto & WSemi : WSemis) {
// //         ++ObjectNumber;
// //         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
// //     }
// //     return 1;
// // }

// bool htoptagger::HAnalysis::GetWSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// {
//     Print(HDebug, "Get W Semi Reader", Tag);
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//
//     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//
//     if (Doublets.size() < 1) return 0;
//
//     if (Doublets.size() > 1) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 1, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(Doublet);
//     }
//     return 1;
// }

bool htoptagger::HAnalysis::GetWTag(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HDebug, "Get W Tag", Tag);
    std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
    if (Ws.size() < 1) return 0;
    for (const auto & W : Ws) {
        ++ObjectNumber;
        *static_cast<HWBranch *>(Branch->NewEntry()) = W;
    }
    return 1;
}


bool htoptagger::HAnalysis::GetWReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

//     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
    std::vector<hanalysis::HDoublet> Doublets;
    // W is in 2 of 3 subjets
    for (const auto & Jet : Jets) {
        HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
        for (const auto & Piece1 : Pieces)
            for (const auto & Piece2 : Pieces) {
                if (Piece1 == Piece2)continue;
                hanalysis::HDoublet Doublet(Piece1, Piece2);
//                 if (Tag == HSignal && std::abs(Doublet.Jet().m() - WMass) > 50) continue;
                Doublet = WHadronicTagger.GetBdt(Doublet, WHadronicReader);
                Doublets.push_back(Doublet);
            }
    }

    if (Doublets.size() > 2) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 2, Doublets.end());
    }

    for (const auto & Doublet : Doublets) {
        *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);
    }
    return 1;
}

bool htoptagger::HAnalysis::GetTopHadronicTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get hadronic tops", Tag);
    std::vector<HTopHadronicBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
//         ++ObjectNumber;
        *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}



bool htoptagger::HAnalysis::GetTopHadronicReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    std::vector<hanalysis::HTriplet> Triplets;
    for (const auto Jet : Jets) {
        HJets Pieces = TopHadronicTagger.GetSubJets(Jet, 3);
        Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);

        for (const auto & Piece1 : Pieces) {
            for (const auto & Piece2 : Pieces) {
                hanalysis::HDoublet Doublet(Piece1, Piece2);
                Doublet = WHadronicTagger.GetBdt(Doublet, WHadronicReader);
//                 if (Doublet.Jet().m()  > (TopMass + WMass) / 2) continue;
//                 if (Doublet.Jet().m()  < 10) continue;
                for (const auto & Piece3 : Pieces) {
                    hanalysis::HTriplet Triplet(Doublet, Piece3);
//                     if (Triplet.Jet().m()  < (TopMass + WMass) / 2) continue;
                    Triplet = TopHadronicTagger.GetBdt(Triplet, TopHadronicReader);
                    Triplets.push_back(Triplet);
                }
            }
        }
    }

    if (Triplets.size() > 2) {
        std::sort(Triplets.begin(), Triplets.end());
        Triplets.erase(Triplets.begin() + 2, Triplets.end());
    }

    for (const auto & Triplet : Triplets) {
        *static_cast<HTopHadronicBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(Triplet);
    }
    return 1;
}



bool htoptagger::HAnalysis::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
{
    Print(HInformation, "Get Tops", Tag);
    std::vector<HTopLeptonBranch> Tops = TopLeptonTagger.GetBranches(Event, Tag);
    if (Tops.size() < 1) return 0;
    for (const auto & Top : Tops) {
        ++ObjectNumber;
        *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = Top;
    }
    return 1;
}

bool htoptagger::HAnalysis::GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag)
{
    Print(HInformation, "Get Event semi", Tag);

    HJets Jets = BottomTagger.GetJets(Event);
    Jets = BottomTagger.GetJetBdt(Jets, BottomReader);

    HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//   fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//   std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
    std::vector<hanalysis::HDoublet> Doublets = TopLeptonTagger.GetBdt(Jets, Leptons, TopLeptonReader);

    if (Doublets.size() > 2) {
        std::sort(Doublets.begin(), Doublets.end());
        Doublets.erase(Doublets.begin() + 2, Doublets.end());
    }

    for (const auto & Triplet : Doublets) {
        //         ++ObjectNumber;
        *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = TopLeptonTagger.GetBranch(Triplet);
    }
    return 1;
}


// bool htoptagger::HAnalysis::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
// {
//     Print(HInformation, "Get Tops", Tag);
//     std::vector<HTopLeptonBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
//     if (Tops.size() < 1) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
// bool htoptagger::HAnalysis::GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = Event.GetJets()->GetStructuredJets();
//     Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
//     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);
//
//     if (Triplets.size() > 2) {
//         std::sort(Triplets.begin(), Triplets.end());
//         Triplets.erase(Triplets.begin() + 2, Triplets.end());
//     }
//
//     for (const auto & Triplet : Triplets) {
// //         ++ObjectNumber;
//         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);
//     }
//     return 1;
// }
