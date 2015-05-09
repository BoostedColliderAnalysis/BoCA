# include "HAnalysisTopTagger.hh"


htoptagger::HAnalysis::HAnalysis(hanalysis::Tagger &tagger) : hanalysis::HAnalysis::HAnalysis(tagger)
{
  Print(HNotification, "Constructor");
  event_sum_ = 0;
  tagger_.set_analysis_name(ProjectName());
}

void htoptagger::HAnalysis::SetFiles(const hanalysis::HObject::Tag tag)
{
    Print(HNotification, "Set File Vector", tag);
    switch (tag) {
    case kSignal :
        if (TopDecay() == kHadronic) NewSignalFile(tthad);
        else if (TopDecay() == kLeptonic) NewSignalFile(ttlep);

        //     NewSignalFile(ttbb);
//     NewSignalFile(ttjj);
//     NewSignalFile(tt);
//     NewSignalFile(bb);
//     NewSignalFile(ttlep);

//   NewBackgroundFile(ttbb);
//   NewBackgroundFile(ttcc);
//   NewBackgroundFile(ttjj);
//     NewBackgroundFile(bbjj);
//     NewBackgroundFile(bb);
//     NewBackgroundFile(hh);

//     NewBackgroundFile(cc);
//         NewBackgroundFile(qq);
//         NewBackgroundFile(gg);
//         NewBackgroundFile(ww);
//         NewBackgroundFile(zz);
        break;
    case kBackground :
        if (TopDecay() == kHadronic) NewBackgroundFile(ttlep);
        else if (TopDecay() == kLeptonic) NewBackgroundFile(tthad);
//     NewBackgroundFile(wb);
//     NewBackgroundFile(wc);
//     NewBackgroundFile(wq);
//     NewBackgroundFile(wg);
//     NewBackgroundFile(wu);
//     NewBackgroundFile(wcb);
//     NewBackgroundFile(wbu);
        break;
    }

}


int htoptagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Analysis");

//     if (ObjectNumber > EventNumberMax()) return 0;

    ++event_sum_;
    switch (stage) {
    case hanalysis::Tagger::kTrainer :
        return tagger_.Train(event, tag);
    case hanalysis::Tagger::kReader :
        return reader_.GetBdt(event);
    }

//     return tagger_.GetBranches(event, stage, tag);
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
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
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
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
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
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//
// //     std::vector<hanalysis::HDoublet> Doublets = WHadronicTagger.GetBdt(Jets, WHadronicReader);
//     std::vector<hanalysis::HDoublet> Doublets;
//     // W is in 2 of 3 subjets
//     for (const auto & Jet : Jets) {
//         HJets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         for (const auto & Piece1 : Pieces)
//             for (const auto & Piece2 : Pieces) {
//                 if (Piece1 == Piece2)continue;
//                 hanalysis::HDoublet Doublet(Piece1, Piece2);
// //                 if (Tag == kSignal && std::abs(Doublet.Jet().m() - WMass) > 50) continue;
//                 Doublet = WHadronicTagger.GetBdt(Doublet, WHadronicReader);
//                 Doublets.emplace_back(Doublet);
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
//         FinalTops.emplace_back(Top);
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
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     HJets Leptons = Event.GetLeptons()->GetLeptonJets();
//     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
//
// //     std::vector<hanalysis::HTriplet> Triplets;
// //     for (const auto Jet : Jets) {
// //         HJets Pieces = TopHadronicTagger.GetSubJets(Jet, 3);
// //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// //         for (const auto & Piece1 : Pieces) {
// //             for (const auto & Piece2 : Pieces) {
// //                 hanalysis::HDoublet Doublet(Piece1, Piece2);
// //                 Doublet = WHadronicTagger.GetBdt(Doublet, WHadronicReader);
// //                 for (const auto & Piece3 : Pieces) {
// //                     hanalysis::HTriplet Triplet(Doublet, Piece3);
// //                     Triplet = TopHadronicTagger.GetBdt(Triplet, TopHadronicReader);
// //                     Triplets.emplace_back(Triplet);
// //                 }
// //             }
// //         }
// //     }
//
//
//     std::vector<hanalysis::HTriplet> Triplets = TopHadronicTagger.GetBdt(Jets,Leptons, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::HTriplet> FinalTriplets;
//     for (const auto & Triplet : Triplets) {
// //         if (Triplet.DeltaR() < 0.5) continue;
//         if (Triplet.Jet().pt() < PreCut()) continue;
//         if (Triplet.Jet().pt() > UpperCut()) continue;
//         FinalTriplets.emplace_back(Triplet);
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
//         FinalTops.emplace_back(Top);
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
//     HJets Jets = bottom_tagger_.GetJets(Event);
//     Jets = fastjet::sorted_by_pt(bottom_tagger_.GetJetBdt(Jets, BottomReader));
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
//         FinalTriplets.emplace_back(Triplet);
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
// //     Jets = bottom_tagger_.GetJetBdt(Jets, BottomReader);
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
