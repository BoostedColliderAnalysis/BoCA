# include "TopSemiTagger.hh"

analysis::TopSemiTagger::TopSemiTagger()
{
    //     DebugLevel = analysis::Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("TopSemi");
    top_mass_window_ = (TopMass - WMass) / 2;
    bottom_reader_.set_tagger(bottom_tagger_);
    w_semi_reader_.set_tagger(w_semi_tagger_);
    DefineVariables();
}

void analysis::TopSemiTagger::DefineVariables()
{
    Print(kNotification , "Define Variables");

    AddVariable(branch_.Mass, "Mass");
    AddVariable(branch_.Rap, "Rap");
    AddVariable(branch_.Phi, "Phi");
    AddVariable(branch_.Pt, "Pt");
    AddVariable(branch_.Ht, "Ht");

    AddVariable(branch_.BottomPt, "BottomPt");
    AddVariable(branch_.WPt, "WPt");

    AddVariable(branch_.DeltaPt, "DeltaPt");
    AddVariable(branch_.DeltaM, "DeltaM");
    AddVariable(branch_.DeltaHt, "DeltaHt");
    AddVariable(branch_.DeltaPhi, "DeltaPhi");
    AddVariable(branch_.DeltaRap, "DeltaRap");
    AddVariable(branch_.DeltaR, "DeltaR");

    AddVariable(branch_.WBdt, "WBdt");
    AddVariable(branch_.BBdt, "BBdt");
    AddVariable(branch_.Bdt, "Bdt");
    AddSpectator(branch_.Tag, "Tag");

    Print(kNotification, "Variables defined");
}

analysis::TopSemiBranch analysis::TopSemiTagger::GetBranch(const analysis::Triplet &triplet) const
{
    Print(kInformation, "Fill Top Tagger", triplet.Bdt());

    TopSemiBranch branch;
    branch.FillBranch(triplet);
    return branch;
}


int analysis::TopSemiTagger::Train(analysis::Event &event, const analysis::Object::Tag tag)
{
    Print(kInformation, "Get Top Tags");

    float pre_cut = 0;

    int WSemiId = w_semi_tagger_.WSemiId(event);
    Jets TopParticles = event.partons().Generator();
    int TopSemiId = sgn(WSemiId) * std::abs(TopId);
    TopParticles = RemoveIfWrongParticle(TopParticles, TopSemiId);
    fastjet::PseudoJet TopQuark;
    if (TopParticles.size() == 1) TopQuark = TopParticles.front();
    else Print(kError, "Where is the Top?", TopParticles.size());


    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<analysis::Doublet> doublets = static_cast<WSemiTagger &>(w_semi_reader_.tagger()).GetDoublets(event, w_semi_reader_.reader());

    Jets Leptons = event.leptons().GetLeptonJets();
    Print(kInformation, "Lepton Number", Leptons.size());

    std::vector<Triplet> triplets;
    if (!boost_) {

        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue; // should be enabled again
                if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
                if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
                if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
                triplet.SetTag(tag);
                triplets.emplace_back(triplet);
            }
        }

    }

    for (const auto & Jet : jets) {
        for (const auto & Lepton : Leptons) {
            Doublet doublet(Lepton);
            Triplet triplet(doublet, Jet);
            if (tag == kSignal && std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue; // should be enabled again
            if (tag == kSignal && triplet.Jet().pt() <  pre_cut / 2) continue;
            if (tag == kSignal && triplet.Jet().delta_R(TopQuark) > detector_geometry().JetConeSize) continue;
            if (tag == kBackground && triplet.Jet().delta_R(TopQuark) < detector_geometry().JetConeSize) continue;
            triplet.SetTag(tag);
            triplets.emplace_back(triplet);
        }
    }

    std::vector<TopSemiBranch> top_semi_branches;
    int SemiLeptonicTopNumber = 1; // Must be 1 for the analysis!!;
    if (tag == kSignal &&
            triplets.size() > SemiLeptonicTopNumber) {
        std::sort(triplets.begin(), triplets.end(), SortByMass(TopMass));
        triplets.erase(triplets.begin() + SemiLeptonicTopNumber, triplets.end());
    }
    Print(kInformation, "Number triplets", triplets.size());

    return SaveEntries(triplets);
}



std::vector<analysis::Triplet>  analysis::TopSemiTagger::GetTriplets(Event &event, const TMVA::Reader &reader)
{
    Print(kInformation, "Get Bdt");

    Jets jets = static_cast<BottomTagger &>(bottom_reader_.tagger()).GetJetBdt(event, bottom_reader_.reader());
    std::vector<analysis::Doublet> doublets = static_cast<WSemiTagger &>(w_semi_reader_.tagger()).GetDoublets(event, w_semi_reader_.reader());

    std::vector<Triplet> triplets;
    if (!boost_) {

        for (const auto & Jet : jets) {
            for (const auto & doublet : doublets) {
                Triplet triplet(doublet, Jet);
                if (std::abs(triplet.Jet().m() - TopMass) > top_mass_window_) continue;
                branch_ = GetBranch(triplet);
                triplet.SetBdt(Bdt(reader));
                triplets.emplace_back(triplet);
            }
        }
    }

    for (const auto & Jet : jets) {
        for (const auto & Predoublet : doublets) {
            Doublet doublet(Predoublet.Singlet1());
            Triplet triplet(doublet, Jet);
//             if (std::abs(triplet.Jet().m() - TopMass) > TopWindow) continue; // reactivate this check
            branch_ = GetBranch(triplet);
            triplet.SetBdt(Bdt(reader));
            triplets.emplace_back(triplet);
        }
    }

    std::sort(triplets.begin(), triplets.end());
    triplets.erase(triplets.begin() + std::min(max_combi(), int(triplets.size())), triplets.end());

    return triplets;
}



float analysis::TopSemiTagger::GetDeltaR(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Delta R");

    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Print(kDebug, "Delta R", TempDeltaR);
        if (TempDeltaR > DeltaR) {
            DeltaR = TempDeltaR;
        }
    }
    return DeltaR;
}

float analysis::TopSemiTagger::GetSpread(const fastjet::PseudoJet &Jet) const
{
    Print(kInformation, "Get Centrality");
    if (!Jet.has_constituents()) {
        return 0;
    }

    float DeltaR = GetDeltaR(Jet);
    if (DeltaR == 0) {
        return 0;
    }
    float Spread = 0;
    for (const auto & constituent : Jet.constituents()) {
        const float TempDeltaR = Jet.delta_R(constituent);
        if (TempDeltaR > 100) {
            continue;
        }
        Spread += TempDeltaR * constituent.pt();
    }
    return (Spread / Jet.pt() / DeltaR);
}

