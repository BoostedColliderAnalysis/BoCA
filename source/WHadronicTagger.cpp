# include "WHadronicTagger.hh"

namespace analysis
{

WHadronicTagger::WHadronicTagger()
{
//     debug_level_ = Object::kDebug;
    Print(kNotification, "Constructor");
    set_tagger_name("WHadronic");
    w_mass_window_ = 20;
    bottom_reader_.SetTagger(bottom_tagger_);
    DefineVariables();
}

int WHadronicTagger::Train(Event &event, PreCuts &pre_cuts, const Object::Tag tag)
{
    Print(kInformation, "W Tags");
    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);
    Print(kInformation, "Bottom Tagger Number", jets.size());

    // 2 Jets form 1 W
    std::vector<Doublet> doublets;
    for (auto jet1 = jets.begin(); jet1 != jets.end(); ++jet1) {
        for (auto jet2 = jet1 + 1; jet2 != jets.end(); ++jet2) {
            Doublet doublet(*jet1, *jet2);
            if (Problematic(doublet, pre_cuts, tag)) continue;
            doublets.emplace_back(doublet);
        }
    }

//  1 Jet (2 subjets) form(s) 1 W
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        Doublet doublet(pieces.at(0), pieces.at(1));
        if (Problematic(doublet, pre_cuts, tag)) continue;
        doublets.emplace_back(doublet);
    }

// W is in 2 of 3 subjets
    for (const auto & jet : jets) {
        const int sub_jet_number = 3;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            for (auto piece2 = piece1 + 1; piece2 != pieces.end(); ++piece2) {
                Doublet doublet(*piece1, *piece2);
                if (Problematic(doublet, pre_cuts, tag)) continue;
                doublets.emplace_back(doublet);
            }
        }
    }

// W is in 1 of 2 subjet
    for (const auto & jet : jets) {
        const int sub_jet_number = 2;
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        for (const auto & piece : pieces) {
            Doublet doublet(piece);
            if (Problematic(doublet, pre_cuts, tag)) continue;
            doublets.emplace_back(doublet);
        }
    }

    Jets w_hadronic_daughters = WDaughters(event);
    int w_hadronic_id = WHadronicId(w_hadronic_daughters);
    Jets particles = event.Partons().GenParticles();
    Jets w_particles = copy_if_abs_particle(particles, w_hadronic_id);
    return SaveEntries(BestMatches(doublets, w_particles, tag));
}


Jets WHadronicTagger::WDaughters(Event &event) const
{
    Jets w_daughters = event.Partons().GenParticles();
    w_daughters = CopyIfAbsMother(w_daughters, WId);
    Print(kInformation, "W daughters", w_daughters.size());

    w_daughters = CopyIfQuark(w_daughters);
    Print(kInformation, "hadronic W daughters", w_daughters.size());
    return w_daughters;
}

int WHadronicTagger::WHadronicId(const Jets &jets) const
{
    if (jets.empty()) return WId;
    else return jets.front().user_info<JetInfo>().constituents().front().family().mother_1().Id;
}

bool WHadronicTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts, const Tag tag)
{
    if (Problematic(doublet, pre_cuts)) return true;
    switch (tag) {
    case kSignal :
        if (std::abs(doublet.Jet().m() - Mass(WId)) > w_mass_window_) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5)) return true;
        if (doublet.Singlet1().Bdt() > 1) return true;
        if (doublet.Singlet2().Bdt() > 1) return true;
        break;
    case kBackground :
        break;
    }
    return false;
}

bool WHadronicTagger::Problematic(const Doublet &doublet, PreCuts &pre_cuts)
{
    if (pre_cuts.PtLowerCut(WId) > 0 && pre_cuts.PtLowerCut(WId) > doublet.Jet().pt()) return true;
    if (pre_cuts.PtUpperCut(WId) > 0 && pre_cuts.PtUpperCut(WId) < doublet.Jet().pt()) return true;
    if (pre_cuts.MassUpperCut(WId) > 0 && pre_cuts.MassUpperCut(WId) < doublet.Jet().m()) return true;
//     if (doublet.DeltaR() < detector_geometry().MinCellResolution) return std::vector<Doublet> {};
    return false;
}

std::vector<Doublet> WHadronicTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");

    Jets jets = bottom_reader_.Multiplets<BottomTagger>(event);

    // 2 jets form a W
    std::vector<Doublet> doublets = Multiplets(jets, pre_cuts, reader);

    // 1 jet (2 subjets) form a W
    doublets = Join(doublets, SubMultiplets(jets, pre_cuts, reader, 2));

    // 2 of 3 subjets form a W
    doublets = Join(doublets, SubMultiplets(jets, pre_cuts, reader, 3));

    // 1 of 2 subjets forms a W
    for (const auto & jet : jets) {
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, 2);
        for (const auto & piece : pieces) {
            Doublet doublet(piece);
            doublets.emplace_back(Multiplet(doublet, pre_cuts, reader));
        }

    }
    return ReduceResult(doublets);
}

std::vector<Doublet> WHadronicTagger::Multiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    std::vector<Doublet>  doublets;
    for (auto Jet1 = jets.begin(); Jet1 != jets.end(); ++Jet1)
        for (auto Jet2 = Jet1 + 1; Jet2 != jets.end(); ++Jet2) {
            doublets.emplace_back(Multiplet(*Jet1, *Jet2, pre_cuts, reader));
        }
    return ReduceResult(doublets);
}

std::vector<Doublet> WHadronicTagger::SubMultiplets(const Jets &jets, PreCuts &pre_cuts, const TMVA::Reader &reader, const int sub_jet_number)
{
    Print(kInformation, "doublet Bdt");
    std::vector<Doublet>  doublets;
    for (const auto & jet : jets) {
        Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, sub_jet_number);
        for (auto piece1 = pieces.begin(); piece1 != pieces.end(); ++piece1) {
            for (auto piece2 = piece1 + 1; piece2 != pieces.end(); ++piece2) {
                doublets.emplace_back(Multiplet(*piece1, *piece2, pre_cuts, reader));
            }
        }
    }
    return ReduceResult(doublets);
}

Doublet WHadronicTagger::Multiplet(const fastjet::PseudoJet &jet_1, const fastjet::PseudoJet &jet_2, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Doublet doublet(jet_1, jet_2);
    return Multiplet(doublet, pre_cuts, reader);
}

Doublet WHadronicTagger::SubMultiplet(const fastjet::PseudoJet &jet, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Jets pieces = bottom_reader_.SubMultiplet<BottomTagger>(jet, 2);
    Doublet doublet;
    if (pieces.empty()) return doublet;
    if (pieces.size() == 1) doublet.SetJet(jet);
    else doublet.SetMultiplets(pieces.at(0), pieces.at(1));
    return Multiplet(doublet, pre_cuts, reader);
}

Doublet WHadronicTagger::Multiplet(const fastjet::PseudoJet &jet, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
  Print(kInformation, "doublet Bdt");
  Doublet doublet(jet);
  return Multiplet(doublet, pre_cuts, reader);
}

Doublet WHadronicTagger::Multiplet(Doublet &doublet, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Print(kInformation, "doublet Bdt");
    Doublet EmptyDoublet; // FIXME this is evil must be removed from the results
    if (Problematic(doublet, pre_cuts)) return EmptyDoublet;
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

}
