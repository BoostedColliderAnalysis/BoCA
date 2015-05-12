# include "HAnalysisTopTagger.hh"


htoptagger::HAnalysis::HAnalysis(hanalysis::Tagger &tagger) : hanalysis::HAnalysis::HAnalysis(tagger)
{
    Print(kNotification, "Constructor");
    event_sum_ = 0;
    tagger_.set_analysis_name(ProjectName());
}

void htoptagger::HAnalysis::SetFiles(const hanalysis::HObject::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);
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


int htoptagger::HAnalysis::PassPreCut(hanalysis::HEvent &event)
{
    Print(kInformation, "paas pre cut");
    Jets particles = event.GetParticles()->Generator();
    Jets tops = fastjet::sorted_by_pt(copy_if_abs_particle(particles, TopId));
    remove_if_not_in_pt_window(tops, PreCut(), UpperCut());
    return tops.size();
}

int htoptagger::HAnalysis::Analysis(hanalysis::HEvent &event, const hanalysis::Tagger::Stage stage, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Analysis");
    ++event_sum_;
    switch (stage) {
      case hanalysis::Tagger::kTrainer :
        Print(kInformation, "Analysis");
//         return tagger_.Train(event, tag);
      case hanalysis::Tagger::kReader :
        Print(kInformation, "Analysis");
//         return reader_.GetBdt(event);
    }
}


// bool htoptagger::HAnalysis::GetBottomTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Tag", Tag);
//     std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(Event, Tag);
//     if (Bottoms.empty()) {
//         Print(kDebug, "No Bottoms");
//         return 0;
//     }
//     for (const auto & Bottom : Bottoms) {
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool htoptagger::HAnalysis::GetBottomReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     //     jets = static_cast<hanalysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(jets);
//
//     Jets Particles = Event.GetParticles()->Generator();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<hanalysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<hanalysis::JetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// // // bool htoptagger::HAnalysis::GetWSemiTag(hanalysis::HEvent &Event, const HTag Tag)
// // // {
// // //     Print(kDebug, "Get W Semi Tag", Tag);
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
// //     Print(kDebug, "Get W Semi Reader", Tag);
// //
// //     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //
// //     std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //
// //     if (doublets.empty()) return 0;
// //
// //     if (doublets.size() > 1) {
// //         std::sort(doublets.begin(), doublets.end());
// //         doublets.erase(doublets.begin() + 1, doublets.end());
// //     }
// //
// //     for (const auto & doublet : doublets) {
// //         ++ObjectNumber;
// //         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemiTagger.GetBranch(doublet);
// //     }
// //     return 1;
// // }
//
// bool htoptagger::HAnalysis::GetWTag(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kDebug, "Get W Tag", Tag);
//     std::vector<WHadronicBranch> Ws = WHadronicTagger.GetBranches(Event, Tag);
//     if (Ws.empty()) return 0;
//     for (const auto & W : Ws) {
//         ++ObjectNumber;
//         *static_cast<WHadronicBranch *>(Branch->NewEntry()) = W;
//     }
//     return 1;
// }
//
//
// bool htoptagger::HAnalysis::GetWReader(hanalysis::HEvent &Event, const Tag Tag)
// {
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
// //     std::vector<hanalysis::Doublet> doublets = WHadronicTagger.GetBdt(jets, WHadronicReader);
//     std::vector<hanalysis::Doublet> doublets;
//     // W is in 2 of 3 subjets
//     for (const auto & Jet : jets)  {
//         Jets Pieces = WHadronicTagger.GetSubJets(Jet, 3);
//         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
//         for (const auto & Piece1 : Pieces)
//             for (const auto & Piece2 : Pieces) {
//                 if (Piece1 == Piece2)continue;
//                 hanalysis::Doublet doublet(Piece1, Piece2);
// //                 if (Tag == kSignal && std::abs(doublet.Jet().m() - WMass) > 50) continue;
//                 doublet = WHadronicTagger.GetBdt(doublet, WHadronicReader);
//                 doublets.emplace_back(doublet);
//             }
//     }
//
//     if (doublets.size() > 2) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 2, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         *static_cast<WHadronicBranch *>(Branch->NewEntry()) = WHadronicTagger.GetBranch(doublet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool htoptagger::HAnalysis::GetTopHadronicTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(kInformation, "Get hadronic tops", Tag);
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
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(Event);
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
// //     std::vector<hanalysis::Triplet> triplets;
// //     for (const auto Jet : jets)  {
// //         Jets Pieces = TopHadronicTagger.GetSubJets(Jet, 3);
// //         Pieces = bottom_tagger_.GetJetBdt(Pieces, BottomReader);
// //         for (const auto & Piece1 : Pieces) {
// //             for (const auto & Piece2 : Pieces) {
// //                 hanalysis::Doublet doublet(Piece1, Piece2);
// //                 doublet = WHadronicTagger.GetBdt(doublet, WHadronicReader);
// //                 for (const auto & Piece3 : Pieces) {
// //                     hanalysis::Triplet triplet(doublet, Piece3);
// //                     triplet = TopHadronicTagger.GetBdt(triplet, TopHadronicReader);
// //                     triplets.emplace_back(triplet);
// //                 }
// //             }
// //         }
// //     }
//
//
//     std::vector<hanalysis::Triplet> triplets = TopHadronicTagger.GetBdt(jets,Leptons, TopHadronicReader, WHadronicTagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<hanalysis::Triplet> Finaltriplets;
//     for (const auto & triplet : triplets) {
// //         if (triplet.DeltaR() < 0.5) continue;
//         if (triplet.Jet().pt() < PreCut()) continue;
//         if (triplet.Jet().pt() > UpperCut()) continue;
//         Finaltriplets.emplace_back(triplet);
//     }
//
//     const int MaxTopSize = 1;
//     if (Finaltriplets.size() > MaxTopSize) {
//         std::sort(Finaltriplets.begin(), Finaltriplets.end());
//         Finaltriplets.erase(Finaltriplets.begin() + MaxTopSize, Finaltriplets.end());
//     }
//
//     if (Finaltriplets.empty()) return 0;
//     for (const auto & Finaltriplet : Finaltriplets) {
//         *static_cast<HTopHadronBranch *>(Branch->NewEntry()) = TopHadronicTagger.GetBranch(Finaltriplet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
//
//
// bool htoptagger::HAnalysis::GetTopSemiTag(hanalysis::HEvent &Event,  Tag Tag)
// {
//     Print(kInformation, "Get Tops", Tag);
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
//     Print(kInformation, "Get Event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(Event);
//     jets = fastjet::sorted_by_pt(bottom_tagger_.GetJetBdt(jets, BottomReader));
//
//     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
// //   fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //   std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<hanalysis::Doublet> doublets = TopLeptonTagger.GetBdt(jets, Leptons, TopLeptonReader);
//
//     std::vector<hanalysis::Doublet> Finaltriplets;
//     for (const auto & triplet : doublets) {
//         //         if (triplet.DeltaR() < 0.5) continue;
//         if (triplet.Jet().pt() < PreCut()) continue;
//         if (triplet.Jet().pt() > UpperCut()) continue;
//         Finaltriplets.emplace_back(triplet);
//     }
//
//     const int MaxTopSize = 2;
//     if (Finaltriplets.size() > MaxTopSize) {
//         std::sort(Finaltriplets.begin(), Finaltriplets.end());
//         Finaltriplets.erase(Finaltriplets.begin() + MaxTopSize, Finaltriplets.end());
//     }
//
//     for (const auto & doublet : Finaltriplets) {
//         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = TopLeptonTagger.GetBranch(doublet);
//         ++ObjectNumber;
//         break;
//     }
//     return 1;
// }
//
//
// // bool htoptagger::HAnalysis::GetTopSemiTag(hanalysis::HEvent &Event,  HTag Tag)
// // {
// //     Print(kInformation, "Get Tops", Tag);
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
// //     Print(kInformation, "Get Event semi", Tag);
// //
// //     Jets jets = Event.GetJets()->GetStructuredJets();
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //
// //     Jets Leptons = Event.GetLeptons()->GetLeptonJets();
// //     fastjet::PseudoJet MissingEt = Event.GetJets()->GetMissingEt();
// //     std::vector<hanalysis::Doublet> doublets = WSemiTagger.GetBdt(Leptons, MissingEt, WSemiReader);
// //     std::vector<hanalysis::Triplet> triplets = TopSemiTagger.GetBdt(doublets, jets, TopSemiReader);
// //
// //     if (triplets.size() > 2) {
// //         std::sort(triplets.begin(), triplets.end());
// //         triplets.erase(triplets.begin() + 2, triplets.end());
// //     }
// //
// //     for (const auto & triplet : triplets) {
// // //         ++ObjectNumber;
// //         *static_cast<HTopLeptonBranch *>(Branch->NewEntry()) = TopSemiTagger.GetBranch(triplet);
// //     }
// //     return 1;
// // }
