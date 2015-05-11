# include "BottomTagger.hh"

# include "Reader.hh"
# include "HEvent.hh"

hanalysis::BottomTagger::BottomTagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    set_tagger_name("Bottom");
    DefineVariables();
}

void hanalysis::BottomTagger::DefineVariables()
{
    Print(kInformation , "Define Variables");
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
    AddVariable(branch_.Mass, "Mass");
    AddSpectator(branch_.Tag, "Tag");
    AddSpectator(branch_.Bdt, "Bdt");
}

BottomBranch hanalysis::BottomTagger::GetBranch(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "Fill Branch");
    BottomBranch branch;
    if (!jet.has_user_info<JetInfo>()) {
        Print(kError, "BJet without user info");
        return branch;
    }
    branch.VertexMass = jet.user_info<JetInfo>().VertexMass();
    branch.Mass = jet.m();
    branch.Pt = jet.pt();
    branch.Rap = jet.rap();
    branch.Phi = jet.phi();
    float MaxDisp = jet.user_info<JetInfo>().MaxDisplacement();
    if (MaxDisp > 0) branch.MaxDisplacement = std::log10(MaxDisp);
    else branch.MaxDisplacement = -3;
    float MeanDisp = jet.user_info<JetInfo>().MeanDisplacement();
    if (MeanDisp > 0) branch.MeanDisplacement = std::log10(MeanDisp);
    else branch.MeanDisplacement = -3;
    float SumDisp = jet.user_info<JetInfo>().SumDisplacement();
    if (SumDisp > 0) branch.SumDisplacement = std::log10(SumDisp);
    else branch.SumDisplacement = -3;
    branch.Multipliticity = jet.user_info<JetInfo>().VertexNumber();
    branch.DeltaR = GetDeltaR(jet);
    branch.Spread = GetSpread(jet);
    branch.VertexDeltaR = GetDeltaR(jet.user_info<JetInfo>().VertexJet());
    branch.VertexSpread = GetSpread(jet.user_info<JetInfo>().VertexJet());
    branch.EnergyFraction = jet.user_info<JetInfo>().VertexEnergy() / jet.e();
    branch.Tag = jet.user_info<JetInfo>().Tag();
    branch.Bdt = jet.user_info<JetInfo>().Bdt();
    return branch;
}

int hanalysis::BottomTagger::Train(hanalysis::HEvent &event, const hanalysis::HObject::Tag tag)
{
    Print(kInformation, "Get Bottom Tag", tag);


    Jets particles = event.GetParticles()->Generator();
    particles = RemoveIfWrongAbsParticle(particles, BottomId);
    Print(kInformation, "Particle size", particles.size());

    Jets jets = GetJets(event);
    Print(kInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;

    Jets final_jets = CleanJets(jets, particles, tag);

    Jets doublet_pieces = GetSubJets(jets, particles, tag, 2);
    final_jets.insert(final_jets.end(), doublet_pieces.begin(), doublet_pieces.end());

    Jets triplet_pieces = GetSubJets(jets, particles, tag, 3);
    final_jets.insert(final_jets.end(), triplet_pieces.begin(), triplet_pieces.end());

    SaveEntries(final_jets);
    return final_jets.size();
}

Jets hanalysis::BottomTagger::GetSubJets(const Jets &jets, const Jets &particles, const Tag tag, const int sub_jet_number)
{
    Print(kInformation, "Get Sub Jets");
    Jets final_pieces;
    for (const auto & jet : jets) {
        if (!jet.has_constituents()) continue;
        if (!jet.has_user_info<JetInfo>()) continue;
        fastjet::ClusterSequence *cluster_sequence = new fastjet::ClusterSequence(jet.constituents(), detector_geometry().SubJetDefinition);
        Jets pieces = cluster_sequence->exclusive_jets_up_to(sub_jet_number);
        cluster_sequence->delete_self_when_unused();

        for (auto & piece : pieces) {
            std::vector<Constituent> constituents;
            for (const auto & piece_constituent : piece.constituents()) {
                if (!piece_constituent.has_user_info<JetInfo>()) {
                    Print(kError, "Get Sub Jets", "No Piece constituent Info");
                    continue;
                }
                std::vector<Constituent> piece_constituents = piece_constituent.user_info<JetInfo>().constituents();
                constituents.insert(constituents.end(), piece_constituents.begin(), piece_constituents.end());
            }
            piece.set_user_info(new JetInfo(constituents/*, jet.user_info<JetInfo>().BTag()*/));
            final_pieces.emplace_back(piece);
        }
    }
    return CleanJets(final_pieces, particles, tag);
}


Jets hanalysis::BottomTagger::CleanJets(Jets &jets, const Jets &particles, const Tag tag)
{
    Print(kInformation, "Clean Jets");

    for (const auto & Particle : particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(Particle));
        if (jets.front().delta_R(Particle) < detector_geometry().JetConeSize) static_cast<JetInfo *>(jets.front().user_info_shared_ptr().get())->SetTag(kSignal);
    }

    Jets clean_jets;
    for (const auto & jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Print(kError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (std::abs(jet.rap()) > detector_geometry().TrackerEtaMax) continue;
        if (jet.m() < 0) continue;
//         static_cast<JetInfo *>(Jet.user_info_shared_ptr().get())->ExtractAbsFraction(BottomId);
//         Jet.user_info<JetInfo>().PrintAllInfos(kDebug);
//         if (Tag == kSignal && Jet.user_info<JetInfo>().MaximalFraction() < .8) {
//             continue;
//         }
//         if (Tag == kSignal && Jet.user_info<JetInfo>().MeanDisplacement() < .1) {
//             continue;
//         }
        if (tag == kSignal && jet.user_info<JetInfo>().SumDisplacement() == 0) continue;
//         if (Tag == HBackground && Jet.user_info<JetInfo>().Fraction(BottomId) > .2) {
//             continue;
//         }
// for (const auto &Particle : Particles) if (Tag == HBackground && Jet.delta_R(Particle) < std::min(GetDeltaR(Jet), float(0.4))) continue;
//         static_cast<JetInfo *>(Jet.user_info_shared_ptr().get())->SetTag(GetTag(Jet));
        Print(kDebug, "Jet Tag", jet.user_info<JetInfo>().Tag());
        if (jet.user_info<JetInfo>().Tag() != tag) continue;
        clean_jets.emplace_back(jet);
    }
    return clean_jets;
}

Jets hanalysis::BottomTagger::GetMultiJetBdt(Jets &jets, const TMVA::Reader &reader)
{

    Jets final_jets = GetJetBdt(jets, reader);

    Jets di_sub_jets = GetSubBdt(jets, reader, 2);
    final_jets.insert(final_jets.end(), di_sub_jets.begin(), di_sub_jets.end());

    Jets tri_sub_jets = GetSubBdt(jets, reader, 3);
    final_jets.insert(final_jets.end(), tri_sub_jets.begin(), tri_sub_jets.end());

    return final_jets;
}

Jets hanalysis::BottomTagger::GetSubBdt(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{

    Print(kInformation, "Get Sub Bdt");
    Jets pieces;
    for (const auto & jet : jets) {
        if (!jet.has_pieces()) continue;
        if (!jet.has_user_info<JetInfo>()) continue;
        fastjet::ClusterSequence *cluster_sequence = new fastjet::ClusterSequence(jet.pieces(), detector_geometry().SubJetDefinition);
        Jets pieces = cluster_sequence->exclusive_jets_up_to(sub_jet_number);
        cluster_sequence->delete_self_when_unused();

        std::vector<Constituent> constituents;
        for (auto & piece : pieces) {
            for (const auto & constituent : piece.constituents()) {
                if (!constituent.has_user_info<JetInfo>()) continue;
                std::vector<Constituent> piece_constituents = constituent.user_info<JetInfo>().constituents();
                constituents.insert(constituents.end(), piece_constituents.begin(), piece_constituents.end());
            }
            piece.set_user_info(new JetInfo(constituents/*, Jet.user_info<JetInfo>().BTag()*/));
            pieces.emplace_back(piece);
        }
    }
    return GetJetBdt(pieces, reader);
}

Jets hanalysis::BottomTagger::GetJetBdt(HEvent &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get Jet Bdt");
    return GetJetBdt(GetJets(event), reader);
//     for (const auto jet : GetJets(event)){
//       if (!jet.has_user_info<JetInfo>()) continue;
//       if (jet.m() <= 0) continue;
//       jets.emplace_back(GetJetBdt(jet, reader));
//     }
//     return jets;
}

Jets hanalysis::BottomTagger::GetJetBdt(const Jets &jets, const TMVA::Reader &reader)
{
    Jets final_jets;
    for (const auto jet : jets) {
        if (!jet.has_user_info<JetInfo>()) continue;
        if (jet.m() <= 0) continue;
        final_jets.emplace_back(GetJetBdt(jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet hanalysis::BottomTagger::GetJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    branch_ = GetBranch(jet);
    static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(reader));
    return jet;
}

Jets hanalysis::BottomTagger::GetSubJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number)
{
    Jets jets;
    for (const auto sub_jet : Tagger::GetSubJets(jet, sub_jet_number)) {
      if (!sub_jet.has_user_info<JetInfo>()) continue;
      if (sub_jet.m() <= 0) continue;
      jets.emplace_back(GetJetBdt(sub_jet, reader));
    }
    return jets;
}

float hanalysis::BottomTagger::GetDeltaR(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "Get Delta R");
    if (!jet.has_constituents()) return 0;
    float delta_r = 0;
    for (const auto & constituent : jet.constituents()) {
        const float constituent_delta_r = jet.delta_R(constituent);
        if (constituent_delta_r > 100) continue;
        Print(kDebug, "Delta R", constituent_delta_r);
        if (constituent_delta_r > delta_r) delta_r = constituent_delta_r;
    }
    return delta_r;
}

float hanalysis::BottomTagger::GetSpread(const fastjet::PseudoJet &jet) const
{
    Print(kInformation, "Get spread");
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
