# include "HAnalysisTopTagger.hh"

// htoptagger::HAnalysis::HAnalysis()
// {
// //         DebugLevel = hanalysis::HObject::HDebug;
//     Print(HNotification, "Constructor");
//     BottomTagger.SetAnalysisName(ProjectName());
//     WHadronicTagger.SetAnalysisName(ProjectName());
// //     WSemiTagger.SetAnalysisName(ProjectName());
//     TopHadronicTagger.SetAnalysisName(ProjectName());
//     TopLeptonTagger.SetAnalysisName(ProjectName());
//     mkdir(ProjectName().c_str(), 0700);
// }

// std::string htoptagger::HAnalysis::StudyName(const hanalysis::HAnalysis::HTagger Tagger) const
// {
//     Print(HNotification, "Get Study Names", Tagger);
//
//     switch (Tagger) {
//     case  HBottomTagger :
//         return "Bottom";
//     case  HBottomReader :
//         return "BottomReader";
//     case HWSemiTagger:
//         return  "WSemi";
//     case HWSemiReader:
//         return  "WSemiReader";
//     case HWHadronicTagger:
//         return  "WHadronic";
//     case HWHadronicReader:
//         return  "WHadronicReader";
//     case HJetPairTagger:
//         return  "JetPair";
//     case HJetPairReader:
//         return  "JetPairReader";
//     case HTopLeptonicTagger:
//         return  "TopLeptonic";
//     case HTopLeptonicReader:
//         return  "TopLeptonicReader";
//     case HTopHadronicTagger:
//         return  "TopHadronic";
//     case HTopSemiTagger:
//         return  "TopSemi";
//     case HTopHadronicReader:
//         return  "TopHadronicReader";
//     case HTopSemiReader:
//         return  "TopSemiReader";
//     case HHeavyHiggsLeptonicTagger:
//         return  "HeavyHiggsLeptonic";
//     case HHeavyHiggsHadronicTagger:
//         return  "HeavyHiggsHadronic";
//     case HHeavyHiggsSemiTagger:
//         return  "HeavyHiggsSemi";
//     case HHeavyHiggsSemiReader:
//         return  "HeavyHiggsSemiReader";
//     case HHeavyHiggsLeptonicReader:
//         return  "HeavyHiggsLeptonicReader";
//     case HEventLeptonicTagger:
//         return  "EventLeptonic";
//     case HEventHadronicTagger:
//         return  "EventHadronic";
//     case HEventLeptonicReader:
//         return  "EventLeptonicReader";
//     case HSignatureSemiTagger:
//         return  "SignatureSemi";
//     case HSignatureSemiReader:
//         return  "SignatureSemiReader";
//     case HEventSemiTagger:
//         return  "EventSemi";
//     case HEventSemiReader:
//         return  "EventSemiReader";
//     default :
//         Print(HError, "unexpected TaggerName", Tagger);
//         return "";
//     }
// }

std::vector<hanalysis::HFile> htoptagger::HAnalysis::Files(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);

    std::vector<hanalysis::HFile> SignalFiles;
    std::vector<hanalysis::HFile> BackgroundFiles;

    if (TopDecay() == Hadronic) SignalFiles.push_back(BackgroundFile(tthad));
    else if (TopDecay() == Leptonic) SignalFiles.push_back(BackgroundFile(ttlep));

//     std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV";
//   SignalSemiFiles.push_back(hanalysis::HFile(SignalName, SignalCrosssection(), Mass()));
    //     SignalSemiFiles.push_back(BackgroundFile(ttbb));
//     SignalSemiFiles.push_back(BackgroundFile(ttjj));
//     SignalFiles.push_back(BackgroundFile(tt));
//     SignalFiles.push_back(BackgroundFile(bb));
//     SignalSemiFiles.push_back(BackgroundFile(ttlep));

//   BackgroundSemiFiles.push_back(BackgroundFile(ttbb));
//   BackgroundSemiFiles.push_back(BackgroundFile(ttcc));
//   BackgroundSemiFiles.push_back(BackgroundFile(ttjj));
//     BackgroundSemiFiles.push_back(BackgroundFile(bbjj));
    BackgroundFiles.push_back(BackgroundFile(bb));
    BackgroundFiles.push_back(BackgroundFile(hh));
//     if (Tagger != HBottomTagger || tag == kBackground) {
        BackgroundFiles.push_back(BackgroundFile(cc));
        BackgroundFiles.push_back(BackgroundFile(qq));
        BackgroundFiles.push_back(BackgroundFile(gg));
        BackgroundFiles.push_back(BackgroundFile(ww));
        BackgroundFiles.push_back(BackgroundFile(zz));
//     }
    if (TopDecay() == Hadronic) BackgroundFiles.push_back(BackgroundFile(ttlep));
    else if (TopDecay() == Leptonic) BackgroundFiles.push_back(BackgroundFile(tthad));
//     BackgroundSemiFiles.push_back(BackgroundFile(wb));
//     BackgroundSemiFiles.push_back(BackgroundFile(wc));
//     BackgroundSemiFiles.push_back(BackgroundFile(wq));
//     BackgroundSemiFiles.push_back(BackgroundFile(wg));
//     BackgroundSemiFiles.push_back(BackgroundFile(wu));
//     BackgroundSemiFiles.push_back(BackgroundFile(wcb));
//     BackgroundSemiFiles.push_back(BackgroundFile(wbu));



    std::vector<hanalysis::HFile> Files = JoinFiles(SignalFiles, BackgroundFiles);


    std::vector<hanalysis::HFile> NewFiles;

//     switch (Tagger) {
//     case  HBottomTagger :
//         NewFiles = Files;
//         break;
//     case  HBottomReader :
//         NewFiles = Files;
//         break;
//     case HWSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HWSemiReader:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HWHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HWHadronicReader:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HTopHadronicTagger:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HTopSemiTagger:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HTopHadronicReader:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     case HTopSemiReader:
//         if (Tag == kSignal) NewFiles = SignalFiles;
//         else NewFiles = BackgroundFiles;
//         break;
//     default:
//         Print(HError, "unknown tagger name");
//     }

    switch (tag) {
      case HObject::kSignal :
        NewFiles = SignalFiles;
        break;
      case HObject::kBackground :
        NewFiles = BackgroundFiles;
        break;
    }

    NewFiles.front().SetBasePath("~/Projects/HTopTagger/");
    NewFiles.front().SetFileSuffix(".root");
    SetTrees();
//     PrepareReader(Tagger, tag);
    return NewFiles;

}


void htoptagger::HAnalysis::SetTrees()
{

//     std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(ColliderType()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    HStrings SignalTrees;
    if (TopDecay() == Hadronic) SignalTrees.push_back(BackgroundTree(tthad));
    else if (TopDecay() == Leptonic) SignalTrees.push_back(BackgroundTree(ttlep));


//     HStrings SignalTrees {
//     SignalTree
//         BackgroundTree(ttjj)
//         BackgroundTree(tt),
//         BackgroundTree(bb),
//         BackgroundTree(ttlep)
//     };

    HStrings BackgroundTrees {
//     BackgroundTree(ttbb),
//     BackgroundTree(ttcc),
//     BackgroundTree(ttjj)
//         BackgroundTree(bbjj)
        BackgroundTree(bb),
        BackgroundTree(cc),
        BackgroundTree(qq),
        BackgroundTree(gg),
        BackgroundTree(hh),
        BackgroundTree(ww),
        BackgroundTree(zz),
//         BackgroundTree(wb),
//         BackgroundTree(wc),
//         BackgroundTree(wq),
//         BackgroundTree(wg),
//         BackgroundTree(wcb),
//         BackgroundTree(wu),
//         BackgroundTree(wbu),
    };
    if (TopDecay() == Hadronic) BackgroundTrees.push_back(BackgroundTree(ttlep));
    else if (TopDecay() == Leptonic) BackgroundTrees.push_back(BackgroundTree(tthad));


    HStrings Trees = JoinHStrings(SignalTrees, BackgroundTrees);

//     switch (Tagger) {
//     case HBottomTagger:
//         BottomTagger.SetSignalTreeNames(Trees);
//         BottomTagger.SetBackgroundTreeNames(Trees);
//         if (Tag == kSignal)  BottomTagger.SetTagger();
//         break;
//     case HBottomReader:
//         break;
//     case HWHadronicTagger:
//         WHadronicTagger.SetSignalTreeNames(SignalTrees);
//         WHadronicTagger.SetBackgroundTreeNames(BackgroundTrees);
//         if (Tag == kSignal) WHadronicTagger.SetTagger(BottomTagger);
//         break;
//     case HWHadronicReader :
//         WHadronicTagger.SetSignalTreeNames(SignalTrees);
//         WHadronicTagger.SetBackgroundTreeNames(BackgroundTrees);
//         if (Tag == kSignal) WHadronicTagger.SetTagger(BottomTagger);
//         break;
//     case HWSemiTagger :
// //         if (Tag == kSignal) WSemiTagger.SetTagger();
// //         WSemiTagger.SetSignalTreeNames(SignalTrees);
// //         WSemiTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     case HWSemiReader :
// //         if (Tag == kSignal) WSemiTagger.SetTagger();
// //         WSemiTagger.SetSignalTreeNames(SignalTrees);
// //         WSemiTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     case HTopHadronicTagger :
//         if (Tag == kSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         TopHadronicTagger.SetSignalTreeNames(SignalTrees);
//         TopHadronicTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     case HTopHadronicReader :
//         if (Tag == kSignal) TopHadronicTagger.SetTagger(BottomTagger, WHadronicTagger);
//         TopHadronicTagger.SetSignalTreeNames(SignalTrees);
//         TopHadronicTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     case HTopSemiTagger :
//         if (Tag == kSignal) TopLeptonTagger.SetTagger(BottomTagger);
//         TopLeptonTagger.SetSignalTreeNames(SignalTrees);
//         TopLeptonTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     case HTopSemiReader :
//         if (Tag == kSignal) TopLeptonTagger.SetTagger(BottomTagger);
//         TopLeptonTagger.SetSignalTreeNames(SignalTrees);
//         TopLeptonTagger.SetBackgroundTreeNames(BackgroundTrees);
//         break;
//     default :
//         Print(HError, "unhandeled case");
//     }

    tagger_.SetSignalTreeNames(SignalTrees);
    tagger_.SetBackgroundTreeNames(BackgroundTrees);
}

// void htoptagger::HAnalysis::PrepareReader(const hanalysis::HAnalysis::HTagger Tagger, const Tag Tag)
// {
//     Print(HInformation, "Prepare Reader", Tagger);
//     if (Tag == kBackground) return;
//     switch (Tagger) {
//     case HBottomTagger:
//         break;
//     case HBottomReader:
//         BottomReader.SetMva(BottomTagger);
//         break;
//     case HWHadronicTagger:
//         WHadronicTagger.BottomTagger.SetTagger();
//         WHadronicTagger.BottomReader.SetMva(WHadronicTagger.BottomTagger);
//         break;
//     case HWHadronicReader:
//         BottomReader.SetMva(BottomTagger);
//         WHadronicReader.SetMva(WHadronicTagger);
//         break;
//     case HWSemiTagger :
//         break;
//     case HWSemiReader :
// //         WSemiReader.SetMva(WSemiTagger);
//         break;
//     case HTopHadronicTagger :
//         TopHadronicTagger.BottomTagger.SetTagger();
//         TopHadronicTagger.BottomReader.SetMva(TopHadronicTagger.BottomTagger);
//         TopHadronicTagger.WTagger.SetTagger(BottomTagger);
//         TopHadronicTagger.WReader.SetMva(TopHadronicTagger.WTagger);
//         break;
//     case HTopHadronicReader :
//         BottomReader.SetMva(BottomTagger);
//         WHadronicReader.SetMva(WHadronicTagger);
//         TopHadronicReader.SetMva(TopHadronicTagger);
//         break;
//     case HTopSemiTagger :
//         TopLeptonTagger.BottomTagger.SetTagger();
//         TopLeptonTagger.BottomReader.SetMva(TopLeptonTagger.BottomTagger);
// //         TopLeptonTagger.WSemiTagger.SetTagger();
// //         TopLeptonTagger.WSemiReader.SetMva(TopLeptonTagger.WSemiTagger);
//         break;
//     case HTopSemiReader :
//         BottomReader.SetMva(BottomTagger);
// //         WSemiReader.SetMva(WSemiTagger);
//         TopLeptonReader.SetMva(TopLeptonTagger);
//         break;
//     default :
//         Print(HError, "unhandled case");
//     }
// }

// void htoptagger::HAnalysis::NewBranches(ExRootTreeWriter &NewTreeWriter, const hanalysis::HAnalysis::HTagger Tagger)
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
//     case HWSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWSemiBranch::Class());
//         break;
//     case HWHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
//         break;
//     case HWHadronicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HWBranch::Class());
//         break;
//     case HTopHadronicTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronBranch::Class());
//         break;
//     case HTopSemiTagger :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonBranch::Class());
//         break;
//     case HTopHadronicReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopHadronBranch::Class());
//         break;
//     case HTopSemiReader :
//         Branch = NewTreeWriter.NewBranch(StudyName(Tagger).c_str(), HTopLeptonBranch::Class());
//         break;
//     default :
//         Print(HError, "No Branch filled");
//     }
//
// }

int htoptagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Analysis");

    if (ObjectNumber > EventNumberMax()) return 0;

    ++event_sum_;

//     switch (Tagger) {
//     case HBottomTagger :
//         return GetBottomTag(Event, Tag);
//     case HBottomReader:
//         return GetBottomReader(Event, Tag);
//     case HWHadronicTagger :
//         if (TopDecay() == Hadronic || TopDecay() == Semi) return GetWTag(Event, Tag);
//         else return 0;
//     case HWHadronicReader :
//         if (TopDecay() == Hadronic || TopDecay() == Semi) return GetWReader(Event, Tag);
//         else return 0;
//     case HWSemiTagger :
// //         if (TopDecay() == Leptonic || TopDecay() == Semi) return GetWSemiTag(Event, Tag);
// //         else
//         return 0;
//     case HWSemiReader :
// //         if (TopDecay() == Leptonic || TopDecay() == Semi) return GetWSemiReader(Event, Tag);
// //         else
//         return 0;
//     case HTopHadronicTagger :
//         if (TopDecay() == Hadronic || TopDecay() == Semi) return GetTopHadronicTag(Event, Tag);
//         else return 0;
//     case HTopSemiTagger :
//         if (TopDecay() == Leptonic || TopDecay() == Semi) return GetTopSemiTag(Event, Tag);
//         else return 0;
//     case HTopHadronicReader :
//         if (TopDecay() == Hadronic || TopDecay() == Semi) return GetTopHadronicReader(Event, Tag);
//         else return 0;
//     case HTopSemiReader :
//         if (TopDecay() == Leptonic || TopDecay() == Semi) return GetTopSemiReader(Event, Tag);
//         else return 0;
//     default :
//         Print(HError, "unknown Tagger", Tagger);
//         return 0;
//     }

    return tagger_.GetBranches(event, stage, tag);
}


// bool htoptagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Tag", Tag);
//     std::vector<HBottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
//     if (Bottoms.empty()) {
//         Print(HDebug, "No Bottoms");
//         return 0;
//     }
//     for (const auto & Bottom : Bottoms) {
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = Bottom;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool htoptagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get Bottom Reader", Tag);
//     HJets Jets = BottomTagger.GetJets(Event);
//     Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
//     if (Jets.empty()) return 0;
//
//     //     Jets = static_cast<hanalysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(Jets);
//
//     HJets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(Jets.begin(), Jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::HJetInfo *>(Jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : Jets) {
//         if (Tag != Jet.user_info<hanalysis::HJetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.DetectorGeometry.TrackerEtaMax) continue;
//         *static_cast<HBottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// // // bool htoptagger::HAnalysis::GetWSemiTag(hanalysis::HEvent &Event, const HTag Tag)
// // // {
// // //     Print(HDebug, "Get W Semi Tag", Tag);
// // //     std::vector<HWSemiBranch> WSemis = WSemiTagger.GetBranches(Event, Tag);
// // //     if (WSemis.empty()) return 0;
// // //     for (const auto & WSemi : WSemis) {
// // //         ++ObjectNumber;
// // //         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
// // //     }
// // //     return 1;
// // // }
//
// // bool htoptagger::HAnalysis::GetWSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HDebug, "Get W Semi Reader", Tag);
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //
// //     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //
// //     if (Doublets.empty()) return 0;
// //
// //     if (Doublets.size() > 1) {
// //         std::sort(Doublets.begin(), Doublets.end());
// //         Doublets.erase(Doublets.begin() + 1, Doublets.end());
// //     }
// //
// //     for (const auto & Doublet : Doublets) {
// //         ++ObjectNumber;
// //         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(Doublet);
// //     }
// //     return 1;
// // }
//
// bool htoptagger::HAnalysis::GetWTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HDebug, "Get W Tag", Tag);
//     std::vector<HWBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
//     if (Ws.empty()) return 0;
//     for (const auto & W : Ws) {
//         ++ObjectNumber;
//         *static_cast<HWBranch *>(Branch->NewEntry()) = W;
//     }
//     return 1;
// }
//
//
// bool htoptagger::HAnalysis::GetWReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = BottomTagger.GetJets(Event);
//     Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
//
// //     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
//     std::vector<hanalysis::HDoublet> Doublets;
//     // W is in 2 of 3 subjets
//     for (const auto & Jet : Jets) {
//         HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
//         Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
//         for (const auto & Piece1 : Pieces)
//             for (const auto & Piece2 : Pieces) {
//                 if (Piece1 == Piece2)continue;
//                 hanalysis::HDoublet Doublet(Piece1, Piece2);
// //                 if (Tag == kSignal && std::abs(Doublet.Jet().m() - WMass) > 50) continue;
//                 Doublet = WHadronicTagger.GetBdt(Doublet, WHadronicReader);
//                 Doublets.push_back(Doublet);
//             }
//     }
//
//     if (Doublets.size() > 2) {
//         std::sort(Doublets.begin(), Doublets.end());
//         Doublets.erase(Doublets.begin() + 2, Doublets.end());
//     }
//
//     for (const auto & Doublet : Doublets) {
//         *static_cast<HWBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(Doublet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool htoptagger::HAnalysis::GetTopHadronicTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(HInformation, "Get hadronic tops", Tag);
//     std::vector<HTopHadronBranch> Tops = TopHadronicTagger.GetBranches(Event, Tag);
//
//     std::vector<HTopHadronBranch> FinalTops;
//     for (const auto & Top : Tops) {
//         if (Top.Pt < PreCut()) continue;
//         if (Top.Pt > UpperCut()) continue;
//         FinalTops.push_back(Top);
//     }
//     if (FinalTops.empty()) return 0;
//     for (const auto & Top : FinalTops) {
//         *static_cast<HTopHadronBranch *>(Branch->NewEntry()) = Top;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
//
//
// bool htoptagger::HAnalysis::GetTopHadronicReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = BottomTagger.GetJets(Event);
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
//
// //     std::vector<hanalysis::HTriplet> Triplets;
// //     for (const auto Jet : Jets) {
// //         HJets Pieces = TopHadronicTagger.GetSubJets(Jet, 3);
// //         Pieces = BottomTagger.GetJetBdt(Pieces, BottomReader);
// //         for (const auto & Piece1 : Pieces) {
// //             for (const auto & Piece2 : Pieces) {
// //                 hanalysis::HDoublet Doublet(Piece1, Piece2);
// //                 Doublet = WHadronicTagger.GetBdt(Doublet, WHadronicReader);
// //                 for (const auto & Piece3 : Pieces) {
// //                     hanalysis::HTriplet Triplet(Doublet, Piece3);
// //                     Triplet = TopHadronicTagger.GetBdt(Triplet, TopHadronicReader);
// //                     Triplets.push_back(Triplet);
// //                 }
// //             }
// //         }
// //     }
//
//
//     std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Jets,Leptons, TopHadronicReader, WHadronicTagger, WHadronicReader, BottomTagger, BottomReader);
//
//     std::vector<hanalysis::HTriplet> FinalTriplets;
//     for (const auto & Triplet : Triplets) {
// //         if (Triplet.DeltaR() < 0.5) continue;
//         if (Triplet.Jet().pt() < PreCut()) continue;
//         if (Triplet.Jet().pt() > UpperCut()) continue;
//         FinalTriplets.push_back(Triplet);
//     }
//
//     const int MaxTopSize = 1;
//     if (FinalTriplets.size() > MaxTopSize) {
//         std::sort(FinalTriplets.begin(), FinalTriplets.end());
//         FinalTriplets.erase(FinalTriplets.begin() + MaxTopSize, FinalTriplets.end());
//     }
//
//     if (FinalTriplets.empty()) return 0;
//     for (const auto & FinalTriplet : FinalTriplets) {
//         *static_cast<HTopHadronBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(FinalTriplet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
//
//
// bool htoptagger::HAnalysis::GetTopSemiTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(HInformation, "Get Tops", Tag);
//     std::vector<HTopLeptonBranch> Tops = TopLeptonTagger.GetBranches(Event, Tag);
//
//     std::vector<HTopLeptonBranch> FinalTops;
//     for (const auto & Top : Tops) {
//         if (Top.Pt < PreCut()) continue;
//         if (Top.Pt > UpperCut()) continue;
//         FinalTops.push_back(Top);
//     }
//     if (FinalTops.empty()) return 0;
//     for (const auto & Top : FinalTops) {
//         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = Top;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool htoptagger::HAnalysis::GetTopSemiReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(HInformation, "Get Event semi", Tag);
//
//     HJets Jets = BottomTagger.GetJets(Event);
//     Jets = fastjet::sorted_by_pt(BottomTagger.GetJetBdt(Jets, BottomReader));
//
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //   fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //   std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::HDoublet> Doublets = TopLeptonTagger.GetBdt(Jets, Leptons, TopLeptonReader);
//
//     std::vector<hanalysis::HDoublet> FinalTriplets;
//     for (const auto & Triplet : Doublets) {
//         //         if (Triplet.DeltaR() < 0.5) continue;
//         if (Triplet.Jet().pt() < PreCut()) continue;
//         if (Triplet.Jet().pt() > UpperCut()) continue;
//         FinalTriplets.push_back(Triplet);
//     }
//
//     const int MaxTopSize = 2;
//     if (FinalTriplets.size() > MaxTopSize) {
//         std::sort(FinalTriplets.begin(), FinalTriplets.end());
//         FinalTriplets.erase(FinalTriplets.begin() + MaxTopSize, FinalTriplets.end());
//     }
//
//     for (const auto & Doublet : FinalTriplets) {
//         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = TopLeptonTagger.GetBranch(Doublet);
//         ++ObjectNumber;
//         break;
//     }
//     return 1;
// }
//
//
// // bool htoptagger::HAnalysis::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
// // {
// //     Print(HInformation, "Get Tops", Tag);
// //     std::vector<HTopLeptonBranch> Tops = TopSemiTagger.GetBranches(Event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) {
// //         ++ObjectNumber;
// //         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = Top;
// //     }
// //     return 1;
// // }
// //
// // bool htoptagger::HAnalysis::GetTopSemiReader(hanalysis::HEvent &Event, const HTag Tag)
// // {
// //     Print(HInformation, "Get Event semi", Tag);
// //
// //     HJets Jets = Event.GetJets()->GetStructuredJets();
// //     Jets = BottomTagger.GetJetBdt(Jets, BottomReader);
// //
// //     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::HDoublet> Doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<hanalysis::HTriplet> Triplets = TopSemiTagger.GetBdt(Doublets, Jets, TopSemiReader);
// //
// //     if (Triplets.size() > 2) {
// //         std::sort(Triplets.begin(), Triplets.end());
// //         Triplets.erase(Triplets.begin() + 2, Triplets.end());
// //     }
// //
// //     for (const auto & Triplet : Triplets) {
// // //         ++ObjectNumber;
// //         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(Triplet);
// //     }
// //     return 1;
// // }
