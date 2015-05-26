# include "BottomTagger.hh"

analysis::BottomTagger::BottomTagger()
{
//     DebugLevel = kDebug;
    Print(kInformation, "Constructor");
    set_tagger_name("Bottom");
    DefineVariables();
}

void analysis::BottomTagger::DefineVariables()
{
    Print(kInformation , "Define Variables");
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

int analysis::BottomTagger::Train(analysis::Event &event, PreCuts &pre_cuts, const analysis::Object::Tag tag)
{
    Print(kInformation, "Get Bottom Tag", tag);

    Jets particles = event.partons().Generator();
    Jets bottoms = copy_if_abs_particle(particles, BottomId);
    Print(kInformation, "Particle size", bottoms.size());

    Jets jets = event.hadrons().ClusteredJets();
    Print(kInformation, "Number Jets", jets.size());
    if (jets.empty()) return 0;

    Jets final_jets = CleanJets(jets, bottoms, pre_cuts, tag);

    Jets doublet_pieces = GetSubJets(jets, bottoms, pre_cuts, tag, 2);
    final_jets = JoinVectors(final_jets, doublet_pieces);

    Jets triplet_pieces = GetSubJets(jets, bottoms, pre_cuts, tag, 3);
    final_jets = JoinVectors(final_jets, triplet_pieces);

    std::vector<Singlet> singlets;
    for(const auto &jet : final_jets) singlets.emplace_back(Singlet(jet));
    SaveEntries<BottomBranch>(singlets);
    Print(kInformation, "Final jet Number", final_jets.size());
    return final_jets.size();
}

Jets analysis::BottomTagger::GetSubJets(const Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Tag tag, const int sub_jet_number)
{
    Print(kInformation, "Get Sub Jets");
    Jets pieces = GetSubJets(jets,sub_jet_number);
    return CleanJets(pieces, particles, pre_cuts, tag);
}


Jets analysis::BottomTagger::CleanJets(Jets &jets, const Jets &particles, PreCuts &pre_cuts, const Tag tag)
{
    Print(kInformation, "Clean Jets", jets.size(), particles.size());

    if (jets.empty()) return jets;
    for (const auto & particle : particles) {
        std::sort(jets.begin(), jets.end(), MinDeltaRTo(particle));
        if (jets.front().delta_R(particle) < detector_geometry().JetConeSize) static_cast<JetInfo &>(*jets.front().user_info_shared_ptr().get()).SetTag(kSignal);
    }

    Jets clean_jets;
    for (const auto & jet : jets) {
        if (!jet.has_user_info<JetInfo>()) {
            Print(kError, "Clean Jets", "No Jet Info");
            continue;
        }
        if (pre_cuts.PtLowerCut(BottomId) > 0 && jet.pt() < pre_cuts.PtLowerCut(BottomId)) continue;
        if (pre_cuts.PtUpperCut(BottomId) > 0 && jet.pt() > pre_cuts.PtUpperCut(BottomId)) continue;
        if (std::abs(jet.rap()) > detector_geometry().TrackerEtaMax) {
            Print(kInformation, "Clean Jets", "too large rap");
            continue;
        }
        if (jet.m() < 0) {
            Print(kInformation, "Clean Jets", "negative mass");
            continue;
        }
        if (tag == kSignal && jet.user_info<JetInfo>().SumDisplacement() == 0) {
            Print(kInformation, "Clean Jets", "no displacment");
            continue;
        }
        if (jet.user_info<JetInfo>().Tag() != tag) {
            Print(kDebug, "Clean Jets", "Not a b quark", jet.user_info<JetInfo>().Tag());
            continue;
        }
        clean_jets.emplace_back(jet);
    }
    Print(kInformation, "Jets", clean_jets.size(), particles.size());
    return clean_jets;
}

Jets analysis::BottomTagger::GetMultiJetBdt(const Jets &jets, const TMVA::Reader &reader)
{

    Jets final_jets = GetJetBdt(jets, reader);

    Jets di_sub_jets = GetSubBdt(jets, reader, 2);
    final_jets.insert(final_jets.end(), di_sub_jets.begin(), di_sub_jets.end());

    Jets tri_sub_jets = GetSubBdt(jets, reader, 3);
    final_jets.insert(final_jets.end(), tri_sub_jets.begin(), tri_sub_jets.end());

    return final_jets;
}

Jets analysis::BottomTagger::GetSubBdt(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{
    Print(kInformation, "Get Sub Bdt");
    return GetJetBdt(GetSubJets(jets,sub_jet_number), reader);
}

Jets analysis::BottomTagger::GetJetBdt(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "Get Jet Bdt");
    return GetJetBdt(event.hadrons().ClusteredJets(), pre_cuts, reader);
}

Jets analysis::BottomTagger::GetJetBdt(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Jets final_jets;
    for (const auto jet : jets) {
        if (!jet.has_user_info<JetInfo>()) continue;
        if (jet.m() <= 0) continue;
        if (pre_cuts.PtLowerCut(BottomId) > 0 && jet.pt() < pre_cuts.PtLowerCut(BottomId)) continue;
        if (pre_cuts.PtUpperCut(BottomId) > 0 && jet.pt() > pre_cuts.PtUpperCut(BottomId)) continue;
        if (pre_cuts.TrackerMaxEta(BottomId) > 0 && std::abs(jet.rap()) > pre_cuts.TrackerMaxEta(BottomId)) continue;
        final_jets.emplace_back(GetJetBdt(jet, reader));
    }
    return final_jets;
}

fastjet::PseudoJet analysis::BottomTagger::GetJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
  branch_ = branch<BottomBranch>(Singlet(jet));
    static_cast<JetInfo &>(*jet.user_info_shared_ptr().get()).SetBdt(Bdt(reader));
    return jet;
}

Jets analysis::BottomTagger::GetSubJetBdt(const fastjet::PseudoJet &jet, const TMVA::Reader &reader, const int sub_jet_number)
{
    Jets jets;
    for (const auto sub_jet : Tagger::GetSubJets(jet, sub_jet_number)) {
        if (!sub_jet.has_user_info<JetInfo>()) continue;
        if (sub_jet.m() <= 0) continue;
        jets.emplace_back(GetJetBdt(sub_jet, reader));
    }
    return jets;
}
