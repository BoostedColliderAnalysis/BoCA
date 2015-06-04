# include "AnalysisNeutral.hh"

std::vector<analysis::File> heavyhiggs::AnalysisNeutral::Files(const analysis::Object::Tag tag)
{
    Print(kNotification, "Set File Vector", tag);

    std::vector<analysis::File> SignalLeptonicFiles;
    std::vector<analysis::File> BackgroundLeptonicFiles;
    std::vector<analysis::File> SignalSemiFiles;
    std::vector<analysis::File> BackgroundSemiFiles;

    std::string SignalName = ProcessName(Hbb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV";
    SignalSemiFiles.emplace_back(analysis::File(SignalName, SignalCrosssection(), Mass()));
//     SignalSemiFiles.emplace_back(BackgroundFile(ttbb));

//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttbb));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttcc));
//     BackgroundSemiFiles.emplace_back(BackgroundFile(ttjj));
    BackgroundSemiFiles.emplace_back(BackgroundFile(tt));

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

    switch (tag) {
    case Object::kSignal :
        NewFiles = SignalSemiFiles;
        break;
    case Object::kBackground :
        NewFiles = BackgroundSemiFiles;
        break;
    }

    SetTrees();
    return NewFiles;

}


void heavyhiggs::AnalysisNeutral::SetTrees()
{

  analysis::Strings SignalLeptonicTrees {};
  analysis::Strings BackgroundLeptonicTrees {};

    std::string SignalTree = ProcessName(Hbb) + "-" + ColliderName(collider_type()) + "-" + std::to_string(Mass()) + "GeV-run_01";

    analysis::Strings SignalSemiTrees {
        SignalTree
//         BackgroundTree(ttbb)
    };

    analysis::Strings BackgroundSemiTrees {
//         BackgroundTree(ttbb),
//         BackgroundTree(ttcc),
//         BackgroundTree(ttjj)
        BackgroundTree(tt)
    };

    analysis::Strings SignalHadronicTree {};
    analysis::Strings BackgroundHadronicTrees {};

    analysis::Strings LeptonicTrees = JoinStrings(SignalLeptonicTrees, BackgroundLeptonicTrees);
    analysis::Strings HadronicTrees = JoinStrings(SignalHadronicTree, BackgroundHadronicTrees);
    analysis::Strings SemiTrees = JoinStrings(SignalSemiTrees, BackgroundSemiTrees);

    analysis::Strings NotLeptonicTrees = JoinStrings(HadronicTrees, SemiTrees);
    analysis::Strings CombinedTrees = JoinStrings(NotLeptonicTrees, LeptonicTrees);

//     case HHeavyHiggsLeptonicReader:
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HeavyHiggsLeptonicBranch::Class());
//         break;
//     case HHeavyHiggsHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HHeavyHiggsHadronicBranch::Class());
//         break;
//     case HeavyHiggsSemiTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HeavyHiggsSemiBranch::Class());
//         break;
//     case HHeavyHiggsSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), HeavyHiggsSemiBranch::Class());
//         break;
//     case EventLeptonicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case EventHadronicTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventHadronicBranch::Class());
//         break;
//     case EventLeptonicReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventLeptonicBranch::Class());
//         break;
//     case SignatureNeutralTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), OctetNeutralBranch::Class());
//         break;
//     case HSignatureSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), OctetNeutralBranch::Class());
//         break;
//     case EventNeutralTagger :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventSemiBranch::Class());
//         break;
//     case EventSemiReader :
//         Branch = tree_writer.NewBranch(StudyName(tagger).c_str(), EventSemiBranch::Class());
//         break;
//     default :
//         Print(kError, "No Branch filled");
//     }
//
}

int heavyhiggs::AnalysisNeutral::RunAnalysis(analysis::Event &event, const analysis::Tagger::Stage stage, const Tag tag)
{
    Print(kInformation, "Analysis");

    analysis::Jets Particles = event.partons().GenParticles();
    analysis::Jets Tops = RemoveIfWrongAbsParticle(Particles, TopId);
    if (Tops.size() != 2) {
        Print(kError, "Not enough top quarks", Tops.size());
        return 0;
    } else {
        if (Tops.at(0).pt() < PreCut()) return 0;
        if (Tops.at(1).pt() < PreCut()) return 0;
    }

    if (event.hadrons().MissingEt().pt() < MissingEt()) return 0;
    analysis::Jets Leptons = fastjet::sorted_by_pt(event.leptons().leptons());
    if (Leptons.empty()) return 0;
    if (Leptons.front().pt() < LeptonPt()) return 0;
    analysis::Jets jets = event.hadrons().Jets();
    if (jets.size() < 4) return 0;


    ++event_sum_;

    tagger_.GetBranches(event, stage, tag);

//     switch (Tagger) {
//     case BottomTagger :
//         return GetBottomTag(event, Tag);
//     case HBottomReader:
//         return GetBottomReader(event, Tag);
//     case JetPairTagger :
//         return GetJetPairTag(event, Tag);
//     case HJetPairReader :
//         return GetJetPairReader(event, Tag);
//     case WHadronicTagger :
//         return GetWTag(event, Tag);
//     case HWHadronicReader :
//         return GetWReader(event, Tag);
//     case HWSemiTagger :
//         return GetWSemiTag(event, Tag);
//     case HWSemiReader :
//         return GetWSemiReader(event, Tag);
//     case TopLeptonicTagger :
//         return GetTopLeptonicTag(event, Tag);
//     case TopHadronicTagger :
//         return GetTopHadronicTag(event, Tag);
//     case HTopSemiTagger :
//         return GetTopSemiTag(event, Tag);
//     case HTopHadronicReader :
//         return GetTopHadronicReader(event, Tag);
//     case HTopLeptonicReader :
//         return GetTopLeptonicReader(event, Tag);
//     case HTopSemiReader :
//         return GetTopSemiReader(event, Tag);
//     case HeavyHiggsLeptonicTagger :
//         return GetHeavyHiggsLeptonicTag(event, Tag);
//     case HHeavyHiggsHadronicTagger :
//         return GetHeavyHiggsHadronicTag(event, Tag);
//     case HeavyHiggsSemiTagger :
//         return GetHeavyHiggsSemiTag(event, Tag);
//     case HHeavyHiggsSemiReader :
//         return GetHeavyHiggsSemiReader(event, Tag);
//     case HHeavyHiggsLeptonicReader :
//         return GetHeavyHiggsLeptonicReader(event, Tag);
//     case EventLeptonicTagger :
//         return GeteventLeptonicTag(event, Tag);
//     case EventHadronicTagger :
//         return GeteventHadronicTag(event, Tag);
//     case EventLeptonicReader :
//         return GeteventLeptonicReader(event, Tag);
//     case SignatureNeutralTagger :
//         return GetSignatureSemiTag(event, Tag);
//     case HSignatureSemiReader :
//         return GetSignatureSemiReader(event, Tag);
//     case EventNeutralTagger :
//         return GeteventSemiTag(event, Tag);
//     case EventSemiReader :
//         return GeteventSemiReader(event, Tag);
//     default :
//         Print(kError, "unknown Tagger", Tagger);
//         return 0;
//     }
}


// bool heavyhiggs::AnalysisNeutral::GetBottomTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Tag", Tag);
//     std::vector<BottomBranch> Bottoms = BottomTagger.GetBranches(event, Tag);
//     if (Bottoms.empty()) return 0;
//     for (const auto & Bottom : Bottoms) {
//         ++ObjectNumber;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = Bottom;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetBottomReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "Bottom Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//
//     if (jets.empty()) return 0;
//
// //     jets = static_cast<analysis::HBottomTagger>(BottomReader.Tagger()).GetJetBdt(jets);
//
//     Jets Particles = event.partons().GenParticles();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsId(BottomId)), Particles.end());
//
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     for (const auto & Jet : jets)  {
//         if (Tag != Jet.user_info<analysis::JetInfo>().Tag()) continue;
//         if (std::abs(Jet.rap()) > BottomTagger.detector_geometry().TrackerEtaMax) continue;
//         *static_cast<BottomBranch *>(Branch->NewEntry()) = BottomTagger.GetBranch(Jet);
//         ++ObjectNumber;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetJetPairTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "JetPair Tag", Tag);
//     std::vector<JetPairBranch> JetPairs = jet_pair_tagger.GetBranches(event, Tag);
//     if (JetPairs.empty()) return 0;
//     for (const auto & JetPair : JetPairs) {
//         ++ObjectNumber;
//         *static_cast<JetPairBranch *>(Branch->NewEntry()) = JetPair;
//     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetJetPairReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "JetPair Reader", Tag);
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
//     if (jets.empty()) return 0;
//
//     Jets Particles = event.partons().GenParticles();
//     Particles.erase(std::remove_if(Particles.begin(), Particles.end(), WrongAbsFamily(BottomId, GluonId)), Particles.end());
//     for (const auto & Particle : Particles) {
//         std::sort(jets.begin(), jets.end(), MinDeltaR(Particle));
//         static_cast<analysis::JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
//     }
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<JetPairBranch *>(Branch->NewEntry()) = jet_pair_tagger.GetBranch(doublet);
//     }
//     return 1;
//
// }
//
// bool heavyhiggs::AnalysisNeutral::GetWSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "W Semi Tag", Tag);
//     std::vector<HWSemiBranch> WSemis = w_semi_tagger.GetBranches(event, Tag);
//     if (WSemis.empty()) return 0;
//     for (const auto & WSemi : WSemis) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = WSemi;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetWSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "W Semi Reader", Tag);
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//
//     std::vector<analysis::Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//
//     if (doublets.empty()) return 0;
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<HWSemiBranch *>(Branch->NewEntry()) = w_semi_tagger.GetBranch(doublet);
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetWTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kDebug, "W Tag", Tag);
//     std::vector<WHadronicBranch> Ws = w_hadronic_tagger.GetBranches(event, Tag);
//     if (Ws.empty()) return 0;
//     for (const auto & W : Ws) {
//         ++ObjectNumber;
//         *static_cast<WHadronicBranch *>(Branch->NewEntry()) = W;
//     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetWReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (doublets.size() > 1) {
//         std::sort(doublets.begin(), doublets.end());
//         doublets.erase(doublets.begin() + 1, doublets.end());
//     }
//
//     for (const auto & doublet : doublets) {
//         ++ObjectNumber;
//         *static_cast<WHadronicBranch *>(Branch->NewEntry()) = w_hadronic_tagger.GetBranch(doublet);
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetTopLeptonicTag(analysis::Event &, const analysis::Object::Tag)
// {
// //     Print(kInformation, "leptonic top", Tag);
// //     std::vector<TopLeptonicBranch> Tops = top_leptonic_tagger.GetBranches(event, Tag);
// //     if (Tops.empty()) return 0;
// //     for (const auto & Top : Tops) {
// //         ++ObjectNumber;
// //         *static_cast<TopLeptonicBranch *>(Branch->NewEntry()) = Top;
// //     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetTopLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event semi", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = top_leptonic_tagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     if (doublets.size() > 1) {
// //         std::sort(doublets.begin(), doublets.end());
// //         doublets.erase(doublets.begin() + 1, doublets.end());
// //     }
// //
// //     for (const auto & doublet : doublets)  {
// //         ++ObjectNumber;
// //         *static_cast<TopLeptonicBranch *>(Branch->NewEntry()) = top_leptonic_tagger.GetBranch(doublet);
// //     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetTopHadronicTag(analysis::Event &event,  Tag Tag)
// {
//     Print(kInformation, "hadronic tops", Tag);
//     std::vector<TopHadronicBranch> Tops = top_hadronic_tagger.GetBranches(event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<TopHadronicBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
//
//
// bool heavyhiggs::AnalysisNeutral::GetTopHadronicReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//
// //     std::vector<analysis::Doublet> doublets = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(doublets, jets, TopHadronicReader);
//
//
//     std::vector<analysis::Triplet> triplets = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     if (triplets.size() > 1) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + 1, triplets.end());
//     }
//
//     for (const auto & triplet : triplets) {
//         ++ObjectNumber;
//         *static_cast<TopHadronicBranch *>(Branch->NewEntry()) = top_hadronic_tagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
//
// bool heavyhiggs::AnalysisNeutral::GetTopSemiTag(analysis::Event &event, const analysis::Object::Tag Tag)
// {
//     Print(kInformation, "Tops", Tag);
//     std::vector<TopSemiBranch> Tops = top_semi_tagger.GetBranches(event, Tag, PreCut());
//     if (Tops.empty()) return 0;
//     for (const auto & Top : Tops) {
//         ++ObjectNumber;
//         *static_cast<TopSemiBranch *>(Branch->NewEntry()) = Top;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetTopSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doublets = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> triplets = top_semi_tagger.GetBdt(doublets, jets, TopSemiReader);
//
//     if (triplets.size() > 1) {
//         std::sort(triplets.begin(), triplets.end());
//         triplets.erase(triplets.begin() + 1, triplets.end());
//     }
//
//     for (const auto & triplet : triplets) {
//         ++ObjectNumber;
//         *static_cast<TopSemiBranch *>(Branch->NewEntry()) = top_semi_tagger.GetBranch(triplet);
//     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsLeptonicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Leptonic Heavy Higgs Tag", Tag);
// //     std::vector<HeavyHiggsLeptonicBranch> Higgses = heavy_higgs_leptonic_tagger.GetBranches(event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) {
// //         ++ObjectNumber;
// //         *static_cast<HeavyHiggsLeptonicBranch *>(Branch->NewEntry()) = Higgs;
// //     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event semi", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> doublets = top_leptonic_tagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<analysis::Hsextet> sextets = heavy_higgs_leptonic_tagger.GetBdt(doublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     if (sextets.size() > 1) {
// //         std::sort(sextets.begin(), sextets.end());
// //         sextets.erase(sextets.begin() + 1, sextets.end());
// //     }
// //
// //     for (const auto & sextet : sextets)  {
// //         ++ObjectNumber;
// //         *static_cast<HeavyHiggsLeptonicBranch *>(Branch->NewEntry())  = heavy_higgs_leptonic_tagger.GetBranch(sextet);
// //     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsHadronicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Hadronic HeavyHiggs Tag", Tag);
// //     std::vector<HHeavyHiggsHadronicBranch> Higgses = HeavyHiggsHadronicTagger.GetBranches(event, Tag);
// //     if (Higgses.empty()) return 0;
// //     for (const auto & Higgs : Higgses) {
// //         ++ObjectNumber;
// //         *static_cast<HHeavyHiggsHadronicBranch *>(Branch->NewEntry()) = Higgs;
// //     }
//     return 1;
// }
//
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Semi HeavyHiggs Tag", Tag);
//     std::vector<HeavyHiggsSemiBranch> Higgses = heavy_higgs_semi_tagger.GetBranches(event, Tag);
//     if (Higgses.empty()) return 0;
//     for (const auto & Higgs : Higgses) {
//         ++ObjectNumber;
//         *static_cast<HeavyHiggsSemiBranch *>(Branch->NewEntry()) = Higgs;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetHeavyHiggsSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::Hsextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     if (sextets.size() > 1) {
//         std::sort(sextets.begin(), sextets.end());
//         sextets.erase(sextets.begin() + 1, sextets.end());
//     }
//
//     for (const auto & sextet : sextets) {
//         ++ObjectNumber;
//         *static_cast<HeavyHiggsSemiBranch *>(Branch->NewEntry()) = heavy_higgs_semi_tagger.GetBranch(sextet);
//     }
//
//     return 1;
// }
//
//
//
//
// bool heavyhiggs::AnalysisNeutral::GeteventLeptonicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event leptonic", Tag);
// //     std::vector<heavyhiggs::EventLeptonicBranch *> LeptoniceventBranches = eventLeptonicTagger.GetBranches(event, Tag);
// //     if (LeptoniceventBranches.empty()) return 0;
// //     for (const auto & Leptonicevent : LeptoniceventBranches) {
// //         ++ObjectNumber;
// //         *static_cast<EventLeptonicBranch *>(Branch->NewEntry()) = *Leptonicevent;
// //     }
//     return 1;
// }
//
//
//
// bool heavyhiggs::AnalysisNeutral::GeteventHadronicTag(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "event hadronic", Tag);
// //     std::vector<heavyhiggs::EventHadronicBranch *> Hadronicevents = eventHadronicTagger.GetBranches(event, Tag);
// //     if (Hadronicevents.empty()) return 0;
// //     for (const auto & Hadronicevent : Hadronicevents) {
// //         ++ObjectNumber;
// //         *static_cast<EventHadronicBranch *>(Branch->NewEntry()) = *Hadronicevent;
// //     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GeteventLeptonicReader(analysis::Event &, const Tag)
// {
// //     Print(kInformation, "Leptonic reader", Tag);
// //
// //     Jets jets = bottom_tagger_.GetJets(event);
// //     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
// //     if (jets.empty()) return 0;
// //
// //     Print(kInformation, "Jet Pair");
// //
// //     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
// //
// //     Print(kInformation, "Top");
// //     Jets Leptons = event.leptons().GetLeptonJets();
// //     if (Leptons.size() < 2) return 0;
// //     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
// //     std::vector<analysis::Doublet> Leptonicdoublets = top_leptonic_tagger.GetBdt(jets, Leptons, TopLeptonicReader);
// //
// //     std::vector<analysis::Hsextet> sextets = heavy_higgs_leptonic_tagger.GetBdt(Leptonicdoublets, MissingEt, HeavyHiggsLeptonicReader);
// //
// //     EventStruct global_observables;
// //     global_observables.LeptonNumber = Leptons.size();
// //     global_observables.JetNumber = jets.size();
// //     global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
// //     global_observables.ScalarHt = event.hadrons().GetScalarHt();
// //
// //     std::vector<HOctet> octets = eventLeptonicTagger.GetBdt(sextets, doublets, jets, global_observables, eventLeptonicReader);
// //     if (octets.empty()) return 0;
// //     octets.front().SetTag(Tag);
// //
// //     heavyhiggs::EventLeptonicBranch *Leptonicevent = new heavyhiggs::EventLeptonicBranch();
// //     eventLeptonicTagger.FillBranch(Leptonicevent, octets.front());
// //
// //     ++ObjectNumber;
// //     EventLeptonicBranch *NeweventBranch = static_cast<EventLeptonicBranch *>(Branch->NewEntry());
// //     *NeweventBranch = *Leptonicevent;
// //
//     return 1;
// }
//
//
//
// bool heavyhiggs::AnalysisNeutral::GetSignatureSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Signature semi", Tag);
//     std::vector<heavyhiggs::OctetNeutralBranch> Signatures = SignatureSemiTagger.GetBranches(event, Tag);
//     if (Signatures.empty()) return 0;
//     for (const auto & Signature : Signatures) {
//         ++ObjectNumber;
//         *static_cast<OctetNeutralBranch *>(Branch->NewEntry()) = Signature;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GetSignatureSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "Signature Semi Reader", Tag);
//
//     Jets jets = bottom_tagger_.GetJets(event);
//     jets = bottom_tagger_.GetJetBdt(jets, BottomReader);
//     if (jets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
//     //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
//
//     std::vector<analysis::Hsextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
//
//     std::vector<HOctet> octets = SignatureSemiTagger.GetBdt(sextets, doublets, SignatureSemiReader);
//     if (octets.empty()) return 0;
//
//     if (octets.size() > 1) {
//         std::sort(octets.begin(), octets.end());
//         octets.erase(octets.begin() + 1, octets.end());
//     }
//     octets.front().SetTag(Tag);
//     ++ObjectNumber;
//     *static_cast<OctetNeutralBranch *>(Branch->NewEntry()) = SignatureSemiTagger.GetBranch(octets.front());
//     return 1;
// }
//
//
//
// bool heavyhiggs::AnalysisNeutral::GeteventSemiTag(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//     std::vector<heavyhiggs::EventSemiBranch> Semievents = eventSemiTagger.GetBranches(event, Tag);
//     if (Semievents.empty()) return 0;
//     for (const auto & Semievent : Semievents) {
//         ++ObjectNumber;
//         *static_cast<EventSemiBranch *>(Branch->NewEntry()) = Semievent;
//     }
//     return 1;
// }
//
// bool heavyhiggs::AnalysisNeutral::GeteventSemiReader(analysis::Event &event, const Tag Tag)
// {
//     Print(kInformation, "event semi", Tag);
//     //must be in the beginning to get the counting right
//
//     Jets PreJets = bottom_tagger_.GetJets(event);
//     Jets jets = bottom_tagger_.GetJetBdt(PreJets, BottomReader);
//     Jets SubJets = bottom_tagger_.GetMultiJetBdt(PreJets, BottomReader);
//     if (jets.empty()) return 0;
//     if (SubJets.empty()) return 0;
//
//     std::vector<analysis::Doublet> doublets = jet_pair_tagger.GetBdt(jets, JetPairReader);
// //     Print(kError, "doublets", doublets.size());
//
//     Jets Leptons = event.leptons().GetLeptonJets();
//     fastjet::PseudoJet MissingEt = event.hadrons().GetMissingEt();
//     std::vector<analysis::Doublet> doubletsSemi = w_semi_tagger.GetBdt(Leptons, MissingEt, WSemiReader);
//     std::vector<analysis::Triplet> tripletsSemi = top_semi_tagger.GetBdt(doubletsSemi, jets, TopSemiReader);
// //     Print(kError, "triplets Semi", tripletsSemi.size());
//
// //     std::vector<analysis::Doublet> doubletsHadronic = w_hadronic_tagger.GetBdt(jets, WHadronicReader);
// //     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(doubletsHadronic, jets, TopHadronicReader);
//     std::vector<analysis::Triplet> tripletsHadronic = top_hadronic_tagger.GetBdt(jets, TopHadronicReader, w_hadronic_tagger, WHadronicReader, bottom_tagger_, BottomReader);
// //     Print(kError, "triplets Hadronic", tripletsHadronic.size());
//
//     std::vector<analysis::Hsextet> sextets = heavy_higgs_semi_tagger.GetBdt(tripletsSemi, tripletsHadronic, HeavyHiggsSemiReader);
// //     Print(kError, "sextets", sextets.size());
//
//     std::vector<HOctet> octets = SignatureSemiTagger.GetBdt(sextets, doublets, SignatureSemiReader);
// //     Print(kError, "Octets", octets.size());
//
//     EventStruct global_observables;
//     global_observables.LeptonNumber = Leptons.size();
//     global_observables.JetNumber = jets.size();
//     global_observables.BottomNumber = event.hadrons().GetBottomJets().size();
//     global_observables.ScalarHt = event.hadrons().GetScalarHt();
//     global_observables.MissingEt = event.hadrons().GetMissingEt().pt();
// //   if (global_observables.LeptonNumber > 0) global_observables.LeptonPt = fastjet::sorted_by_pt(event.leptons().GetLeptonJets()).front().pt();
//
//     std::vector<MultipletEvent<HOctet>> events = eventSemiTagger.GetBdt(octets, jets, SubJets, Leptons,  global_observables, eventSemiReader);
//     if (events.empty()) return 0;
//     events.front().SetTag(Tag);
// //     ++ObjectNumber; // FIXME should be switched on to avoid long duration of last step
//     *static_cast<EventSemiBranch *>(Branch->NewEntry()) = eventSemiTagger.GetBranch(events.front());
//     return 1;
// }
