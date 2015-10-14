/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "WHadronicTagger.hh"

#include "ParticleInfo.hh"
#include "Event.hh"
#include "Math.hh"
#include "Exception.hh"
// #define NOTIFICATION
#include "Debug.hh"

namespace boca
{

WHadronicTagger::WHadronicTagger()
{
    Info();
    w_mass_window_ = 40. * GeV;
}

int WHadronicTagger::Train(Event const& event, boca::PreCuts const& pre_cuts, Tag tag) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    Info(jets.size());

    Info("2 jets form one W");
    std::vector<Doublet> doublets = Doublets(jets, pre_cuts, tag);

    for (auto const & jet : jets) {

        Info("1 jet forms one W");
        try {
            doublets.emplace_back(CheckDoublet(Doublet(jet), pre_cuts, tag));
        } catch (std::exception const&) {}

        Info("2 of 2 sub jets form one W");
        Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
        try {
            doublets.emplace_back(CheckDoublet(Doublet(pieces.at(0), pieces.at(1)), pre_cuts, tag));
        } catch (std::exception const&) {}

        Info("1 of 2 sub jets forms one W");
        for (auto const & piece : pieces) {
            try {
                doublets.emplace_back(CheckDoublet(Doublet(piece), pre_cuts, tag));
            } catch (std::exception const&) {}
        }

        Info("2 of 3 sub jets forms one W");
        pieces = bottom_reader_.SubMultiplet(jet, 3);
        doublets = Join(doublets, Doublets(pieces, pre_cuts, tag));

    }

    Jets particles = event.Partons().GenParticles();
    int w_hadronic_id = WHadronicId(event);
    Jets w_particles;
    if (w_hadronic_id != 0) w_particles = CopyIfExactParticle(particles, w_hadronic_id);
    else w_particles = CopyIfParticle(particles, Id::W);
    w_particles = RemoveIfSoft(w_particles, DetectorGeometry::JetMinPt());
    Info(doublets.size(), w_particles.size());
    return SaveEntries(BestMatches(doublets, w_particles, tag, Id::W));
}

Doublet WHadronicTagger::CheckDoublet(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts, tag)) throw boca::Problematic();
    doublet.SetTag(tag);
    return doublet;
}

Jets WHadronicTagger::WDaughters(boca::Event const& event) const
{
    Jets particles = event.Partons().GenParticles();
    Jets w_daughters = CopyIfMother(particles, Id::W);
    Info(w_daughters.size());
    w_daughters = CopyIfQuark(w_daughters);
    Info(w_daughters.size());
    return w_daughters;
}

int WHadronicTagger::WHadronicId(Jets const& daughters) const
{
    if (daughters.empty()) return 0;
    int sign;
    bool first = true;
    bool just_one = true;
    for (auto const & daughter : daughters) {
        int id = daughter.user_info<ParticleInfo>().Family().mother_1().id();
        if (first) sign = sgn(id);
        else if (sign != sgn(id)) just_one = false;
        first = false;
    }
    if (just_one) return sign * to_int(Id::W);
    return 0;
}

std::vector<Doublet> WHadronicTagger::Doublets(boca::Jets const& jets, boca::PreCuts const& pre_cuts, boca::Tag tag) const
{
    return unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        Doublet doublet(jet_1, jet_2);
        if (Problematic(doublet, pre_cuts, tag)) throw boca::Problematic();
        return doublet;
    });
}

bool WHadronicTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts, Tag tag) const
{
    if (Problematic(doublet, pre_cuts))
        return true;
    switch (tag) {
    case Tag::signal :
        if (boost::units::abs(doublet.Mass() - MassOf(Id::W)) > w_mass_window_) return true;
        if ((doublet.Rho() > 2 || doublet.Rho() < 0.5) && doublet.Rho() > 0) return true;
//         if (doublet.Singlet1().Bdt() > 1) return true;
//         if (doublet.Singlet2().Bdt() > 1) return true;
        break;
    case Tag::background :
        break;
    }
    return false;
}

bool WHadronicTagger::Problematic(Doublet const& doublet, PreCuts const& pre_cuts) const
{
    if (pre_cuts.PtLowerCut(Id::W) > at_rest && pre_cuts.PtLowerCut(Id::W) > doublet.Pt()) return true;
    if (pre_cuts.PtUpperCut(Id::W) > at_rest && pre_cuts.PtUpperCut(Id::W) < doublet.Pt()) return true;
    if (pre_cuts.MassUpperCut(Id::W) > massless && pre_cuts.MassUpperCut(Id::W) < doublet.Mass()) return true;
    if (doublet.DeltaR() < DetectorGeometry::MinCellResolution() && doublet.DeltaR() > 0) return true;
    return false;
}

std::vector<Doublet> WHadronicTagger::Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets jets = bottom_reader_.Multiplets(event);
    std::vector<Doublet> doublets;
    Info("2 jets form one W");
    doublets = Join(doublets, Multiplets(jets, pre_cuts, reader));
    Info("2 of 2 sub jets form one W");
    doublets = Join(doublets, SubMultiplets(jets, pre_cuts, reader, 2));
    Info("2 of 3 sub jets forms one W");
    doublets = Join(doublets, SubMultiplets(jets, pre_cuts, reader, 3));
    Info("1 of 2 sub jets form one W");
    doublets = Join(doublets, SubMultiplets2(jets, pre_cuts, reader));
    Info("1 jets form one W");
    doublets = Join(doublets, Multiplets3(jets, pre_cuts, reader));
    return ReduceResult(doublets);
}

std::vector<Doublet> WHadronicTagger::Multiplets(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    std::vector<Doublet>  doublets = unordered_pairs(jets, [&](fastjet::PseudoJet const & jet_1, fastjet::PseudoJet const & jet_2) {
        return Multiplet(jet_1, jet_2, pre_cuts, reader);
    });
    return doublets;
}

std::vector<Doublet> WHadronicTagger::Multiplets3(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    std::vector<Doublet>  doublets;
    for (auto const & jet : jets) {
        try {
            doublets.emplace_back(Multiplet(jet, pre_cuts, reader));
        } catch (std::exception const&) {}
    }
    return doublets;
}

std::vector<Doublet> WHadronicTagger::SubMultiplets(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader, size_t sub_jet_number) const
{
    Info();
    std::vector<Doublet>  doublets;
    for (auto const & jet : jets) {
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        if (pieces.size() < sub_jet_number) continue;
        doublets = Join(doublets, unordered_pairs(pieces, [&](fastjet::PseudoJet const & piece_1, fastjet::PseudoJet const & piece_2) {
            return Multiplet(piece_1, piece_2, pre_cuts, reader);
        }));
    }
    return doublets;
}

std::vector<Doublet> WHadronicTagger::SubMultiplets2(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    size_t sub_jet_number = 2;
    std::vector<Doublet>  doublets;
    for (auto const & jet : jets) {
        Jets pieces = bottom_reader_.SubMultiplet(jet, sub_jet_number);
        for (auto const & piece : pieces) {
            try {
                doublets.emplace_back(Multiplet(piece, pre_cuts, reader));
            }  catch (std::exception const&) {}
        }
    }
    return doublets;
}

Doublet WHadronicTagger::SubMultiplet(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Jets pieces = bottom_reader_.SubMultiplet(jet, 2);
    Doublet doublet;
    if (pieces.empty()) return doublet;
    if (pieces.size() == 1) doublet.SetJet(jet);
    else doublet.SetMultiplets(pieces.at(0), pieces.at(1));
    try {
        return Multiplet(doublet, pre_cuts, reader);
    } catch (std::exception const&) {
        throw;
    }
}

Doublet WHadronicTagger::Multiplet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Doublet doublet(jet_1, jet_2);
    try {
        return Multiplet(doublet, pre_cuts, reader);
    } catch (std::exception const&) {
        throw;
    }
}

Doublet WHadronicTagger::Multiplet(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    Doublet doublet(jet);
    try {
        return Multiplet(doublet, pre_cuts, reader);
    } catch (std::exception const&) {
        throw;
    }
}

Doublet WHadronicTagger::Multiplet(Doublet& doublet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    Info();
    if (Problematic(doublet, pre_cuts)) throw boca::Problematic();
    doublet.SetBdt(Bdt(doublet, reader));
    return doublet;
}

Doublet WHadronicTagger::Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    try {
        return Multiplet(jet, pre_cuts, reader);
    } catch (std::exception const&) {
        throw;
    }
}

int WHadronicTagger::WHadronicId(boca::Event const& event) const
{
    return WHadronicId(WDaughters(event));
}

Doublet WHadronicTagger::SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    try {
        return SubMultiplet(jet, pre_cuts, reader);
    } catch (std::exception const&) {
        throw;
    }
}

Doublet WHadronicTagger::Multiplet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2, TMVA::Reader const& reader) const
{
    PreCuts pre_cuts;
    try {
        return Multiplet(jet_1, jet_2, pre_cuts, reader);
    } catch (std::exception const&) {
        throw;
    }
}

int WHadronicTagger::SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const
{
    return SaveEntries(Multiplets(event, pre_cuts, reader), 2);
}

}

