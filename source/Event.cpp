/**
 * Copyright (C) 2015-2016 Jan Hajer
 *
 * YingYing Li: Lepton Isolation
 *
 */
#include "boca/generic/Vector.hh"
#include "boca/generic/Types.hh"
#include "boca/Settings.hh"
#include "boca/Event.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

std::string Name(Decay decay)
{
    switch (decay) {
    case Decay::hadronic : return "hadronic";
    case Decay::leptonic : return "leptonic";
        DEFAULT(to_int(decay), "");
    }
}

std::string Name(JetDetail jet_detail)
{
    std::string name;
    FlagSwitch(jet_detail, [&](JetDetail detail) {
        switch (detail) {
        case JetDetail::none : name += "None ";
            break;
        case JetDetail::plain : name += "Plain ";
            break;
        case JetDetail::isolation : name += "Isolation ";
            break;
        case JetDetail::structure : name += "Structure ";
            break;
            DEFAULT(to_int(detail));
        }
    });
    return name;
}

Event::Event(boca::TreeReader const& tree_reader) : tree_reader_(&tree_reader)
{
    INFO0;
}

std::vector< Lepton > Event::Leptons() const
{
    INFO0;
    if (!Settings::Isolation()) return Combine(Electrons(), Muons());
    auto leptons = std::vector<Lepton>{};
    for (auto const & lepton : Combine(Electrons(), Muons())) {
        if (lepton.Pt() > Settings::HardLeptonMomentum()) {
            leptons.emplace_back(lepton);
            continue;
        }
        auto isolated = true;
        for (auto const & jet : Jets())
            if (Close<Lepton>(lepton, Settings::IsolationConeSize())(jet) && jet.Pt() / lepton.Pt() > Settings::IsolationFraction()) {
                isolated = false;
                break;
            }
        if (isolated) leptons.emplace_back(lepton);
    }
    return leptons;
}

std::vector<Particle> Event::Particles() const
{
    return Particles(Status::stable);
}

std::vector<Particle> Event::GenParticles() const
{
    return Particles(Status::generator);
}

Momentum Event::ScalarHt() const
{
    Error("No scalar Ht");
    return at_rest;
}

boca::MissingEt Event::MissingEt() const
{
    Error("No missing Et");
    return {};
}

std::vector<Jet> Event::EFlow(JetDetail) const
{
    Error("No EFlow Jets");
    return {};
}

boca::TreeReader const& Event::TreeReader() const
{
    return *tree_reader_;
}

}

