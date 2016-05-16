/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Event.hh"
#include "boca/delphes/Partons.hh"

#include "boca/generic/Vector.hh"
#include "boca/generic/Types.hh"
#include "boca/delphes/Leptons.hh"
#include "boca/delphes/Hadrons.hh"
#include "boca/exroot/Leptons.hh"
#include "boca/exroot/Hadrons.hh"
#include "boca/exroot/Partons.hh"
#include "boca/Settings.hh"
#include "boca/generic/DEBUG.hh"

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

Event::Event(TreeReader const& tree_reader, Source source) : isolation_(*this, tree_reader)
{
    INFO0;
    source_ = source;
    switch (source_) {
    case Source::delphes :
        partons_ = new delphes::Partons(tree_reader);
        hadrons_ = new delphes::Hadrons(tree_reader);
        leptons_ = new delphes::Leptons(tree_reader);
        break;
    case Source::pgs :
        leptons_ = new exroot::Leptons(tree_reader);
        hadrons_ = new exroot::Hadrons(tree_reader);
        break;
    case Source::parton :
        partons_ = new exroot::Partons(tree_reader);
        break;
        DEFAULT(Name(source_));
    }
}

Event::~Event()
{
    INFO0;
    switch (source_) {
    case Source::delphes :
        delete partons_;
        delete leptons_;
        delete hadrons_;
        break;
    case Source::pgs :
        delete leptons_;
        delete hadrons_;
        break;
    case Source::parton:
        delete partons_;
        break;
        DEFAULT(Name(source_));
    }
    partons_ = nullptr;
    leptons_ = nullptr;
    hadrons_ = nullptr;
}

Hadrons const& Event::Hadrons() const
{
    return *hadrons_;
}

Leptons const& Event::Leptons_() const
{
    INFO(Name(Settings::Collider()));
    switch (Settings::Collider()) {
    case Collider::lhc :
        return isolation_;
        return *leptons_;
    case Collider::future :
        return isolation_;
        return *leptons_;
        DEFAULT(Name(Settings::Collider()), *leptons_)
    }
}

Partons const& Event::Partons() const
{
    return *partons_;
}

std::vector<Lepton> Event::IsolatedLeptons()
{
    INFO0;
    std::vector<Lepton> leptons;
    for (auto const & lepton : leptons_->leptons()) {
        if (lepton.Pt() > Settings::HardLeptonMomentum()) {
            leptons.emplace_back(lepton);
            continue;
        }
        auto isolated = true;
        for (auto const & jet : hadrons_->Jets())
            if (Close<Lepton>(lepton, Settings::IsolationConeSize())(jet) && jet.Pt() / lepton.Pt() > Settings::IsolationFraction()) {
                isolated = false;
                break;
            }
        if (isolated) leptons.emplace_back(lepton);
    }
    return leptons;
}

}

