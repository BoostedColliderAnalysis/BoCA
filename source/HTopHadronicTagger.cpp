# include "HTopHadronicTagger.hh"

hanalysis::HTopHadronicTagger::HTopHadronicTagger(HBottomTagger *const NewBottomTagger, HWTagger * const NewWTagger)
{
//     DebugLevel = hanalysis::HObject::HDebug;

    Print(HNotification, "Constructor");
    BottomTagger = NewBottomTagger;
    BottomReader = new HReader(BottomTagger);
    WTagger = NewWTagger;
    WReader = new HReader(WTagger);
    SetTaggerName("TopHadronic");
    Branch = new HTopHadronicBranch();
    JetTag = new HJetTag();
    DefineVariables();
    TopWindow = 50;
    JetRadiusParameter = 1;
// //     std::string TopCut = "TopHadronic.Mass>" + std::to_string(TopMass - TopWindow) + "&&TopHadronic.Mass<" + std:D:to_string(TopMass + TopWindow);
//     Cut = TopCut.c_str();
}

hanalysis::HTopHadronicTagger::~HTopHadronicTagger()
{
    Print(HNotification, "Destructor");
    delete Branch;
    delete JetTag;
//     delete BottomReader;
    delete WReader;
}


void hanalysis::HTopHadronicTagger::FillBranch(HTopHadronicBranch *const TopHadronicBranch, const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.GetBdt());

    TopHadronicBranch->Mass = Triplet.GetTripletJet().m();
    TopHadronicBranch->Pt = Triplet.GetTripletJet().pt();
    TopHadronicBranch->Rap = Triplet.GetTripletJet().rap();
    TopHadronicBranch->Phi = Triplet.GetTripletJet().phi();

    TopHadronicBranch->BottomPt = Triplet.GetSinglet().pt();
    TopHadronicBranch->WPt = Triplet.GetDoubletJet().pt();

    TopHadronicBranch->DeltaR = Triplet.GetDeltaR();
    TopHadronicBranch->DeltaRap = Triplet.GetDeltaRap();
    TopHadronicBranch->DeltaPhi = Triplet.GetDeltaPhi();

    TopHadronicBranch->Bdt = Triplet.GetBdt();
    TopHadronicBranch->Tag = Triplet.GetTag();
}

void hanalysis::HTopHadronicTagger::FillBranch(const hanalysis::HTriplet &Triplet)
{
    Print(HInformation, "Fill Top Tagger", Triplet.GetBdt());
    FillBranch(Branch, Triplet);
}

void hanalysis::HTopHadronicTagger::DefineVariables()
{

    Print(HNotification , "Define Variables");

    Observables.push_back(NewObservable(&Branch->Mass, "Mass"));
    Observables.push_back(NewObservable(&Branch->Pt, "Pt"));
    Observables.push_back(NewObservable(&Branch->Rap, "Rap"));
    Observables.push_back(NewObservable(&Branch->Phi, "Phi"));

    Observables.push_back(NewObservable(&Branch->BottomPt, "BottomPt"));
    Observables.push_back(NewObservable(&Branch->WPt, "WPt"));

    Observables.push_back(NewObservable(&Branch->DeltaPhi, "DeltaPhi"));
    Observables.push_back(NewObservable(&Branch->DeltaRap, "DeltaRap"));
    Observables.push_back(NewObservable(&Branch->DeltaR, "DeltaR"));

    Observables.push_back(NewObservable(&Branch->Bdt, "Bdt"));
    Spectators.push_back(NewObservable(&Branch->Tag, "Tag"));

    Print(HNotification, "Variables defined");

}

struct SortByTopMass {
    inline bool operator()(const hanalysis::HTriplet &Triplet1, const hanalysis::HTriplet &Triplet2) {
        return (std::abs(Triplet1.TopMass - Triplet1.GetTripletJet().m()) < std::abs(Triplet2.TopMass - Triplet2.GetTripletJet().m()));
    }
};


std::vector<HTopHadronicBranch *> hanalysis::HTopHadronicTagger::GetBranches(hanalysis::HEvent *const Event, const hanalysis::HObject::HTag Tag)
{

    Print(HInformation, "Get Top Tags");

    JetTag->HeavyParticles = {TopId};
    HJets Jets = Event->GetJets()->GetStructuredTaggedJets(JetTag);
    Print(HInformation, "Jet Number", Jets.size());

    Jets = WTagger->BottomTagger->GetBdt(Jets, WTagger->BottomReader);
    std::vector<HDoublet> Doublets = WTagger->GetBdt(Jets, WReader);

    std::vector<hanalysis::HTriplet>  Triplets;
    for (const auto & Jet : Jets)
        for (const auto & Doublet : Doublets) {
            if (Jet == Doublet.GetJet1()) continue;
            if (Jet == Doublet.GetJet2()) continue;
            HTriplet Triplet(Doublet, Jet);
            Triplet.SetTag(GetTag(Triplet));
            if (Triplet.GetTag() != Tag) continue;
            if (Tag == HSignal && std::abs(Triplet.GetTripletJet().m() - TopMass) > TopWindow) continue;
            Triplets.push_back(Triplet);
        }

        for (auto & Jet : Jets) {
          if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
            fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
            fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
            std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
            //         if (Jet.has_pieces()) {
            //             fastjet::JetDefinition JetDefinition(fastjet::cambridge_aachen_algorithm, JetSize);
            //             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
            //             std::vector<fastjet::PseudoJet> Pieces = fastjet::sorted_by_pt(ClusterSequence.inclusive_jets());
            Print(HInformation, "New Jet Number", Pieces.size());
            if (Pieces.size() > 1) {
              for (auto & Piece : Pieces) {
                hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                Piece.set_user_info(JetInfo);
              }
              Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
              std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
              for (auto Jet2 : Jets) {
                for (auto PiecesDoublet : PiecesDoublets) {
                  if (Jet2 == Jet) continue;
                  if (Jet2 == PiecesDoublet.GetJet1()) continue;
                  if (Jet2 == PiecesDoublet.GetJet2()) continue;
                  HTriplet Triplet(PiecesDoublet, Jet2);
                  Triplet.SetTag(GetTag(Triplet));
                  if (Triplet.GetTag() != Tag) continue;
                  if (Tag == HSignal && std::abs(Triplet.GetTripletJet().m() - TopMass) > TopWindow) continue;
                  Triplets.push_back(Triplet);
                }
              }
            }
          }
        }

        for (auto & Jet : Jets) {
          if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
            fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
            fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
            std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
//         if (Jet.has_pieces()) {
//             fastjet::JetDefinition JetDefinition(fastjet::cambridge_aachen_algorithm, JetSize);
//             fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
//             std::vector<fastjet::PseudoJet> Pieces = fastjet::sorted_by_pt(ClusterSequence.inclusive_jets());
            Print(HInformation, "New Jet Number", Pieces.size());
            if (Pieces.size() > 1) {
                for (auto & Piece : Pieces) {
                    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                    JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                    JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                    Piece.set_user_info(JetInfo);
                }
                Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
                std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
                for (auto Piece : Pieces) {
                    for (auto PiecesDoublet : PiecesDoublets) {
                        if (Piece == PiecesDoublet.GetJet1()) continue;
                        if (Piece == PiecesDoublet.GetJet2()) continue;
                        HTriplet Triplet(PiecesDoublet, Piece);
                        Triplet.SetTag(GetTag(Triplet));
                        if (Triplet.GetTag() != Tag) continue;
                        if (Tag == HSignal && std::abs(Triplet.GetTripletJet().m() - TopMass) > TopWindow) continue;
                        Triplets.push_back(Triplet);
                    }
                }
            }
        }
    }


    if (Tag == HSignal && Triplets.size() > 1) { // FIXME assuming maximal one hadronic W
        Print(HInformation, "Number of Jet Pairs", Triplets.size());
        std::sort(Triplets.begin(), Triplets.end(), SortByTopMass());
        Triplets.erase(Triplets.begin() + 1, Triplets.end());
    }


    std::vector<HTopHadronicBranch *> HadronicTopBranches;
    for (const auto & Triplet : Triplets) {
        HTopHadronicBranch *HadronicTopBranch = new HTopHadronicBranch();
        FillBranch(HadronicTopBranch, Triplet);
        HadronicTopBranches.push_back(HadronicTopBranch);
    }


    return HadronicTopBranches;

}

hanalysis::HObject::HTag hanalysis::HTopHadronicTagger::GetTag(const HTriplet &Triplet)
{
    Print(HInformation, "Get Triple Tag");

    HJetInfo BJetInfo = Triplet.GetSinglet().user_info<HJetInfo>();
    BJetInfo.ExtractFraction(BottomId);
    HJetInfo W1JetInfo = Triplet.GetDoublet().GetJet1().user_info<HJetInfo>();
    W1JetInfo.ExtractFraction(WId);
    HJetInfo W2JetInfo = Triplet.GetDoublet().GetJet2().user_info<HJetInfo>();
    W2JetInfo.ExtractFraction(WId);

    if (std::abs(W1JetInfo.GetMaximalId()) != WId) return HBackground;
    if (W1JetInfo.GetMaximalId() != W2JetInfo.GetMaximalId()) return HBackground;
    if (std::abs(BJetInfo.GetMaximalId()) != BottomId) return HBackground;
    if (sgn(BJetInfo.GetMaximalId()) != sgn(W1JetInfo.GetMaximalId())) return HBackground;
    return HSignal;
}

std::vector<hanalysis::HTriplet>  hanalysis::HTopHadronicTagger::GetBdt(const std::vector<HDoublet> &Doublets, const HJets &Jets, const HReader *const TopHadronicReader)
{

//   float DeltaRProtection = 0.02;
    std::vector<HTriplet>  Triplets;
    for (const auto & Doublet : Doublets)
        for (const auto & Jet : Jets) {
            if (Jet == Doublet.GetJet1()) continue;
            if (Jet == Doublet.GetJet2()) continue;
//             if (Doublet.GetDoubletJet().delta_R(Jet) < DeltaRProtection) continue;
            HTriplet Triplet(Doublet, Jet);
            FillBranch(Triplet);
            Triplet.SetBdt(TopHadronicReader->GetBdt());
            Triplets.push_back(Triplet);
        }

        for (const auto & Jet : Jets) {
          if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
            fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
            fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
            std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(2));
            if (Pieces.size() > 2) {
              for (auto & Piece : Pieces) {
                hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                Piece.set_user_info(JetInfo);
              }
              Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
              std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
              for (auto Jet2 : Jets) {
                for (auto PiecesDoublet : PiecesDoublets) {
                  if (Jet2 == Jet) continue;
                  if (Jet2 == PiecesDoublet.GetJet1()) continue;
                  if (Jet2 == PiecesDoublet.GetJet2()) continue;
//                   if (PiecesDoublet.GetDoubletJet().delta_R(Jet2) < DeltaRProtection) continue;
                  HTriplet Triplet(PiecesDoublet, Jet2);
                  FillBranch(Triplet);
                  Triplet.SetBdt(TopHadronicReader->GetBdt());
                  Triplets.push_back(Triplet);
                }
              }
            }
          }
        }

        for (const auto & Jet : Jets) {
          if (Jet.has_pieces()) if(Jet.pieces().size()>2) {
            fastjet::JetDefinition JetDefinition(fastjet::kt_algorithm, JetRadiusParameter);
            fastjet::ClusterSequence ClusterSequence(Jet.pieces(), JetDefinition);
            std::vector<fastjet::PseudoJet> Pieces = ClusterSequence.exclusive_jets_up_to(int(3));
            if (Pieces.size() > 2) {
                for (auto & Piece : Pieces) {
                    hanalysis::HJetInfo *JetInfo = new hanalysis::HJetInfo;
                    JetInfo->SetBTag(Jet.user_info<HJetInfo>().GetBTag());
                    JetInfo->SetVertices(Jet.user_info<HJetInfo>().GetVertices());
                    Piece.set_user_info(JetInfo);
                }
                Pieces = BottomTagger->GetBdt(Pieces, BottomReader);
                std::vector<HDoublet> PiecesDoublets = WTagger->GetBdt(Pieces, WReader);
                for (auto Piece : Pieces) {
                    for (auto PiecesDoublet : PiecesDoublets) {
                        if (Piece == PiecesDoublet.GetJet1()) continue;
                        if (Piece == PiecesDoublet.GetJet2()) continue;
//                         if (PiecesDoublet.GetDoubletJet().delta_R(Piece) < DeltaRProtection) continue;
                        HTriplet Triplet(PiecesDoublet, Piece);
                        FillBranch(Triplet);
                        Triplet.SetBdt(TopHadronicReader->GetBdt());
                        Triplets.push_back(Triplet);
                    }
                }
            }
        }
    }

    std::sort(Triplets.begin(), Triplets.end());
    Triplets.erase(Triplets.begin() + std::min(MaxCombi, int(Triplets.size())), Triplets.end());
    return Triplets;
}
