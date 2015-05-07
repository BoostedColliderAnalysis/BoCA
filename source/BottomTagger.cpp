# include "BottomTagger.hh"

// # include "HBranch.hh"
// # include "HEvent.hh"
// # include "HJetTag.hh"
# include "Reader.hh"
# include "HEvent.hh"
// # include "HAnalysis.hh"

hanalysis::BottomTagger::BottomTagger()
{
//     DebugLevel = HDebug;
  Print(HInformation, "Constructor");
  set_tagger_name("Bottom");
  DefineVariables();
}

void hanalysis::BottomTagger::DefineVariables()
{
    Print(HInformation , "Define Variables");
    ClearVectors();
    AddVariable(branch_.VertexMass, "VertexMass");
    AddVariable(branch_.Pt, "Pt");
    AddSpectator(branch_.Rap, "Rap");
    AddSpectator(branch_.Phi, "Phi");
    AddVariable(branch_.MaxDisplacement, "MaxDisplacement");
    AddVariable(branch_.MeanDisplacement, "MeanDisplacement");
    AddVariable(branch_.SumDisplacement, "SumDisplacement");
    AddVariable(branch_.Multipliticity, "Multipliticity");
    AddVariable(branch_.DeltaR, "DeltaR");
    AddVariable(branch_.Spread, "Spread");
    AddVariable(branch_.VertexDeltaR, "VertexDeltaR");
    AddVariable(branch_.VertexSpread, "VertexSpread");
    AddVariable(branch_.EnergyFraction, "EnergyFraction");
    AddSpectator(branch_.BTag, "BTag");
    AddVariable(branch_.Mass, "Mass");
    AddSpectator(branch_.Tag, "Tag");
    AddSpectator(branch_.Bdt, "Bdt");
}

HBottomBranch hanalysis::BottomTagger::GetBranch(const fastjet::PseudoJet &jet) const
{
    Print(HInformation, "Fill Branch");
    HBottomBranch branch;
    if (!jet.has_user_info<HJetInfo>()) {
        Print(HError, "BJet without user info");
        return branch;
    }
    branch.VertexMass = jet.user_info<HJetInfo>().VertexMass();
    branch.Mass = jet.m();
    branch.Pt = jet.pt();
    branch.Rap = jet.rap();
    branch.Phi = jet.phi();
    float MaxDisp = jet.user_info<HJetInfo>().MaxDisplacement();
    if (MaxDisp > 0) branch.MaxDisplacement = std::log(MaxDisp);
    else branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<HJetInfo>().MeanDisplacement();
    if (MeanDisp > 0) branch.MeanDisplacement = std::log(MeanDisp);
    else branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<HJetInfo>().SumDisplacement();
    if (SumDisp > 0) branch.SumDisplacement = std::log(SumDisp);
    else branch.SumDisplacement = -3;
    branch.Multipliticity = jet.user_info<HJetInfo>().VertexNumber();
    branch.DeltaR = GetDeltaR(jet);
    branch.Spread = GetSpread(jet);
    branch.VertexDeltaR = GetDeltaR(jet.user_info<HJetInfo>().VertexJet());
    branch.VertexSpread = GetSpread(jet.user_info<HJetInfo>().VertexJet());
    branch.EnergyFraction = jet.user_info<HJetInfo>().VertexEnergy() / jet.e();
    branch.BTag = jet.user_info<HJetInfo>().BTag();
    branch.Tag = jet.user_info<HJetInfo>().Tag();
    branch.Bdt = jet.user_info<HJetInfo>().Bdt();
    return branch;
}

int hanalysis::BottomTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(HInformation, "Get Bottom Tag", tag);

    HJets particles = event.GetParticles()->Generator();
    particles = RemoveIfWrongAbsParticle(particles,BottomId);
    Print(HInformation, "Particle size", particles.size());

    HJets jets = GetJets(event);
    Print(HInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;

    HJets final_jets = CleanJets(jets, particles, tag);

    HJets doublet_pieces = GetSubJets(jets, particles, tag, 2);
    final_jets.insert(final_jets.end(), doublet_pieces.begin(), doublet_pieces.end());

    HJets triplet_pieces = GetSubJets(jets, particles, tag, 3);
    final_jets.insert(final_jets.end(), triplet_pieces.begin(), triplet_pieces.end());

    SaveEntries(final_jets);
    return final_jets.size();
}

HJets hanalysis::BottomTagger::GetSubJets(const HJets &jets, const HJets &particles, const Tag tag, const int sub_jet_number)
{
    Print(HInformation, "Get Sub Jets");
    HJets final_pieces;
    for (const auto & jet : jets) {
        if (!jet.has_constituents()) {
            Print(HError, "Pieceless jet");
            continue;
        }
        if (!jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Sub Jets", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(jet.constituents(), detector_geometry().SubJetDefinition);
        HJets pieces = ClusterSequence->exclusive_jets_up_to(sub_jet_number);
        ClusterSequence->delete_self_when_unused();


        for (auto & piece : pieces) {
            std::vector<HConstituent> Constituents;
            for (const auto & PieceConstituent : piece.constituents()) {
                if (!PieceConstituent.has_user_info<HJetInfo>()) {
                    Print(HError, "Get Sub Jets", "No Piece Constituent Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = PieceConstituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            piece.set_user_info(new HJetInfo(Constituents, jet.user_info<HJetInfo>().BTag()));
            final_pieces.emplace_back(piece);
        }
    }
    return CleanJets(final_pieces, particles, tag);
}


HJets hanalysis::BottomTagger::CleanJets(HJets &jets, const HJets &particles, const Tag tag)
{
    Print(HInformation, "Clean Jets");

    for (const auto & Particle : particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize) static_cast<HJetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    HJets NewCleanJets;
    for (const auto & Jet : jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (std::abs(Jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (Jet.m() < 0) continue;
//         static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         Jet.user_info<HJetInfo>().PrintAllInfos(HDebug);
//         if (Tag == kSignal && Jet.user_info<HJetInfo>().MaximalFraction() < .8) {
//             continue;
//         }
//         if (Tag == kSignal && Jet.user_info<HJetInfo>().MeanDisplacement() < .1) {
//             continue;
//         }
        if (tag == kSignal && Jet.user_info<HJetInfo>().SumDisplacement() == 0) {
            continue;
        }
//         if (Tag == HBackground && Jet.user_info<HJetInfo>().Fraction(BottomId) > .2) {
//             continue;
//         }
// for (const auto &Particle : Particles) if (Tag == HBackground && Jet.delta_R(Particle) < std::min(GetDeltaR(Jet), float(0.4))) continue;
//         static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        Print(HDebug, "Jet Tag", Jet.user_info<HJetInfo>().Tag());
        if (Jet.user_info<HJetInfo>().Tag() != tag) continue;
        NewCleanJets.emplace_back(Jet);
    }
    return NewCleanJets;
}

HJets hanalysis::BottomTagger::GetMultiJetBdt(HJets &jets, const TMVA::Reader &reader)
{

    HJets NewJets = GetJetBdt(jets, reader);

    HJets DiJets = GetSubBdt(jets, reader, 2);
    NewJets.insert(NewJets.end(), DiJets.begin(), DiJets.end());

    HJets TriJets = GetSubBdt(jets, reader, 3);
    NewJets.insert(NewJets.end(), TriJets.begin(), TriJets.end());

    return NewJets;
}

HJets hanalysis::BottomTagger::GetSubBdt(const HJets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{
    Print(HInformation, "Get Sub Bdt");
    HJets Pieces;
    for (const auto & Jet : jets) {
        if (!Jet.has_pieces()) {
            Print(HInformation, "pieceless jet");
            continue;
        }
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Sub Bdt", "No Jet Info");
            continue;
        }
        fastjet::ClusterSequence *ClusterSequence = new fastjet::ClusterSequence(Jet.pieces(), detector_geometry().SubJetDefinition);
        HJets SubPieces = ClusterSequence->exclusive_jets_up_to(sub_jet_number);
        ClusterSequence->delete_self_when_unused();

        std::vector<HConstituent> Constituents;
        for (auto & Piece : SubPieces) {
            for (const auto & Constituent : Piece.constituents()) {
                if (!Constituent.has_user_info<HJetInfo>()) {
                    Print(HInformation, "Get Constituent Bdt", "No Jet Info");
                    continue;
                }
                std::vector<HConstituent> NewConstituents = Constituent.user_info<HJetInfo>().Constituents();
                Constituents.insert(Constituents.end(), NewConstituents.begin(), NewConstituents.end());
            }
            Piece.set_user_info(new HJetInfo(Constituents/*, Jet.user_info<HJetInfo>().BTag()*/));
            Pieces.emplace_back(Piece);
        }
    }
    return GetJetBdt(Pieces, reader);
}

HJets hanalysis::BottomTagger::GetJetBdt(const HJets &jets, const TMVA::Reader &reader)
{
    HJets NewJets;
    Print(HInformation, "Get Jet Bdt");
    for (const auto Jet : jets) {
        if (!Jet.has_user_info<HJetInfo>()) {
            Print(HError, "Get Jet Bdt", "No Jet Info");
            continue;
        }
        if (Jet.m() <= 0) {
            Print(HInformation, "Empty Piece");
            continue;
        }
        branch_ = GetBranch(Jet);
        static_cast<HJetInfo *>(Jet.user_info_shared_ptr().get())->SetBdt(Bdt(reader));
        NewJets.emplace_back(Jet);
    }
    return NewJets;
}

float hanalysis::BottomTagger::GetDeltaR(const fastjet::PseudoJet &jet) const
{
    Print(HInformation, "Get Delta R");
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        Print(HDebug, "Delta R", constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float hanalysis::BottomTagger::GetSpread(const fastjet::PseudoJet &jet) const
{
    Print(HInformation, "Get spread");
    if (!jet.has_constituents()) return 0;
    float delta_r = GetDeltaR(jet);
    if (delta_r == 0) return 0;
    float spread = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        spread += constituent_delta_r * constituent.pt();
    }
    return spread / jet.pt() / delta_r;
}
