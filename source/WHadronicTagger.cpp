# include "WHadronicTagger.hh"

namespace analysis {

WHadronicTagger::WHadronicTagger()
{
//     DebugLevel = Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WHadronic");
    w_mass_window_ = 20;
    bottom_reader_.set_tagger(bottom_tagger_);
    DefineVariables();
}

int WHadronicTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "W Tags");

    Jets w_hadronic_daughters = WDaughters(event);

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kInformation, "Bottom Tagger Number", jets.size());

    // 2 Jets form 1 W
    std::vector<Doublet> doublets;
    for (auto jet1 = jets.begin(); jet1 != jets.end(); ++jet1) {
        for (const auto & w_hadronic_daughter : w_hadronic_daughters) {
            switch (tag) {
            case kSignal :
                if ((*jet1).delta_R(w_hadronic_daughter) > detector_geometry().JetConeSize) continue;
                break;
            case kBackground :
                if ((*jet1).delta_R(w_hadronic_daughter) < detector_geometry().JetConeSize) continue;
                break;
            }
        }
        for (auto jet2 = jet1 + 1; jet2 != jets.end(); ++jet2) {
            if (tag == kSignal) {
                bool tagged = false;
                for (const auto & w_hadronic_daughter : w_hadronic_daughters) if ((*jet2).delta_R(w_hadronic_daughter) < detector_geometry().JetConeSize) tagged = true;
                if (!tagged) continue;
            }
            Doublet doublet(*jet1, *jet2);
            if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) continue;
            doublets.emplace_back(doublet);
        }
    }

    int w_hadronic_id = WHadronicId(w_hadronic_daughters);
    Jets w_particles = event.Partons().GenParticles();
    w_particles = RemoveIfWrongParticle(w_particles, w_hadronic_id);

    Jets w_jets;
    switch (tag) {
    case kSignal :
        w_jets = CopyIfClose(jets, w_particles);
        break;
    case kBackground :
        w_jets = RemoveIfClose(jets, w_particles);
        break;
    }

//  1 Jet (2 subjets) form(s) 1 W
    for (const auto & jet : w_jets) {
        const int sub_jet_number = 2;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) continue;
        doublets.emplace_back(doublet);
    }

// W is in 2 of 3 subjets
    for (const auto & jet : jets) {
        const int sub_jet_number = 3;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            for (auto piece2 = piece1 + 1; piece2 != pieces.end(); ++piece2) {
                Doublet doublet(*piece1, *piece2);
                if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) continue;
                doublets.emplace_back(doublet);
            }
        }
    }

// W is in 1 of 2 subjet
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (const auto & piece : pieces) {
            Doublet doublet(piece);
            if (tag == kSignal && std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) continue;
            doublets.emplace_back(doublet);
        }
    }

    if (tag == kSignal && doublets.size() > w_particles.size()) {
        std::sort(doublets.begin(), doublets.end(), SortByMassTo(Mass(WId)));
        doublets.erase(doublets.begin() + w_particles.size(), doublets.end());
    }
    return SaveEntries(doublets);
}


Jets WHadronicTagger::WDaughters(Event &event) const
{
    Jets w_daughters = event.Partons().GenParticles();
    w_daughters = RemoveIfWrongAbsMother(w_daughters, WId);
    Print(kInformation, "W daughters", w_daughters.size());

    w_daughters = RemoveIfLetpons(w_daughters);
    Print(kInformation, "hadronic W daughters", w_daughters.size());
    return w_daughters;
}

int WHadronicTagger::WHadronicId(const Jets &jets) const
{
    if (jets.empty()) return WId;
    else return jets.front().user_info<JetInfo>().constituents().front().family().mother_1().Id;
}

std::vector<Doublet> WHadronicTagger::Multiplets(analysis::Event &event, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);

    // 2 jets form a W
    std::vector<Doublet> doublets = Multiplets(jets,pre_cuts, reader);

    // 1 jet (2 subjets) form a W
    Multiplets(jets, reader, 2);

    // 2 of 3 subjets form a W
    Multiplets(jets, reader, 3);

    // 1 of 2 subjets forms a W
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), 2);
        for (const auto & piece : pieces) doublets = Join(doublets, Multiplet(piece, reader));
    }

    return ReduceResult(doublets);
}

std::vector<Doublet> WHadronicTagger::Multiplets(const analysis::Jets &jets, analysis::PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");

    // W in 2 jets
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            doublets = Join(doublets, Multiplet(*Jet1, *Jet2, reader));
        }

    return ReduceResult(doublets);
}

std::vector<Doublet> WHadronicTagger::Multiplets(const Jets &jets, const TMVA::Reader &reader, const int sub_jet_number)
{
    Print(kInformation, "doublet Bdt");

    std::vector<Doublet>  doublets;
    for (const auto & jet : jets) {
        Jets pieces = static_cast<BottomTagger &>(bottom_reader_.tagger()).SubMultiplet(jet, bottom_reader_.reader(), sub_jet_number);
        for (const auto & piece : pieces) doublets = Join(doublets, Multiplet(piece, reader));
    }

//     std::sort(doublets.begin(), doublets.end());
//     doublets.erase(doublets.begin() + std::min(max_combi(), int(doublets.size())), doublets.end());
    return doublets;
}

std::vector<Doublet> WHadronicTagger::Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Doublet doublet(jet_1, jet_2);
    if (doublet.DeltaR() < detector_geometry().MinCellResolution) return std::vector<Doublet> {};
    return Multiplet(doublet, reader);
}

std::vector<Doublet> WHadronicTagger::Multiplet(const fastjet::PseudoJet &jet, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Jets subjets = SubJets(jet, 2);
    if (subjets.empty()) return std::vector<Doublet> {};
    Doublet doublet;
    if (subjets.size() == 1) doublet.SetJet(jet);
    else doublet.SetMultiplets(subjets.at(0), subjets.at(1));
    return Multiplet(doublet, reader);
}

std::vector<Doublet> WHadronicTagger::Multiplet(Doublet &doublet, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    std::vector<Doublet>  doublets;
    if (std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) return doublets;
    doublet.SetBdt(Bdt(doublet,reader));
    doublets.emplace_back(doublet);
    return doublets;
}

}
