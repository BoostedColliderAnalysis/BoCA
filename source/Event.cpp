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
    }
}

Event::Event() {}

Event::Event(Source source)
{
    Info0;
    source_ = source;
    switch (source_) {
    case Source::delphes :
        partons_ = new delphes::Partons();
        hadrons_ = new delphes::Hadrons();
        leptons_ = new delphes::Leptons();
        break;
    case Source::pgs :
        leptons_ = new exroot::Leptons();
        hadrons_ = new exroot::Hadrons();
        break;
    case Source::parton :
        partons_ = new exroot::Partons();
        break;
    }
}

Event::Event(ClonesArrays const& clones_arrays, Source source)
{

    Info0;
    source_ = source;
    switch (source_) {
    case Source::delphes :
        partons_ = new delphes::Partons();
        hadrons_ = new delphes::Hadrons();
        leptons_ = new delphes::Leptons();
        break;
    case Source::pgs :
        leptons_ = new exroot::Leptons();
        hadrons_ = new exroot::Hadrons();
        break;
    case Source::parton :
        partons_ = new exroot::Partons();
        break;
    }
    NewEvent(clones_arrays);
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

void Event::NewEvent(ClonesArrays const& clones_arrays)
{
    Info0;
    switch (source_) {
    case Source::delphes :
        partons_->NewEvent(clones_arrays);
        hadrons_->NewEvent(clones_arrays);
        leptons_->NewEvent(clones_arrays);
        break;
    case Source::pgs :
        hadrons_->NewEvent(clones_arrays);
        leptons_->NewEvent(clones_arrays);
        break;
    case Source::parton:
        partons_->NewEvent(clones_arrays);
        break;
    }
}

}
