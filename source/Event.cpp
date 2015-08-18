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

namespace analysis {

Event::Event() {}

Event::Event(const Source source)
{
    Info();
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

Event::~Event()
{
    Info();
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
}

void Event::NewEvent(const ClonesArrays& clones_arrays)
{
    Info();
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
