/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Event.hh"
#include "delphes/Partons.hh"
#include "delphes/Leptons.hh"
#include "delphes/Hadrons.hh"
#include "exroot/Leptons.hh"
#include "exroot/Hadrons.hh"
#include "exroot/Partons.hh"
#include "Debug.hh"

namespace boca
{

std::string Name(Decay decay)
{
    switch (decay) {
    case Decay::hadronic : return "hadronic";
    case Decay::leptonic : return "leptonic";
    case Decay::other : return "other";
        Default("decay", "");
    }
}

Event::Event(TreeReader const& tree_reader, Source source)
{
    Info0;
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
    }
}

Event::~Event()
{
    Info0;
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
    }
    partons_ = nullptr;
    leptons_ = nullptr;
    hadrons_ = nullptr;
}

Hadrons const& Event::Hadrons() const
{
    return *hadrons_;
}

Leptons const& Event::Leptons() const
{
    return *leptons_;
}

Partons const& Event::Partons() const
{
    return *partons_;
}

}

