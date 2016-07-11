/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Types.hh"
#include "boca/Constituent.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

std::string Name(DetectorPart detector_part)
{
    switch (detector_part) {
    case DetectorPart::none : return "None";
    case DetectorPart::gen_particle : return "gen_particle";
    case DetectorPart::track : return "track";
    case DetectorPart::photon : return "photon";
    case DetectorPart::tower : return "tower";
    case DetectorPart::muon : return "muon";
        DEFAULT(to_int(detector_part), "");
    }
}


Constituent::Constituent()
{
    DEBUG0;
}

Constituent::Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position)
{
    DEBUG0;
    momentum_ = momentum;
    position_ = position;
}

Constituent::Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position, boca::Family const& family, boca::DetectorPart detector_part, int charge)
{
    DEBUG0;
    momentum_ = momentum;
    position_ = position;
    detector_part_ = detector_part;
    charge_ = charge;
    families_.emplace_back(family);
}

Constituent::Constituent(TLorentzVector const& momentum)
{
    DEBUG0;
    momentum_ = momentum;
}

Constituent::Constituent(TLorentzVector const& momentum, boca::Family const& family, boca::DetectorPart detector_part, int charge)
{
    DEBUG0;
    momentum_ = momentum;
    detector_part_ = detector_part;
    charge_ = charge;
    families_.emplace_back(family);
}

Constituent::Constituent(TLorentzVector const& momentum, std::vector<boca::Family> const& families, boca::DetectorPart detector_part)
{
    DEBUG0;
    momentum_ = momentum;
    detector_part_ = detector_part;
    families_ = families;
}

void Constituent::SetMomentum(TLorentzVector const& momentum)
{
    DEBUG0;
    momentum_ = momentum;
}

LorentzVector<Length> const& Constituent::Position() const
{
    DEBUG0;
    return position_;
}

LorentzVector<Momentum> const& Constituent::Momentum() const
{
    DEBUG0;
    return momentum_;
}

LorentzVector<Length>& Constituent::Position()
{
    DEBUG0;
    return position_;
}

LorentzVector<Momentum>& Constituent::Momentum()
{
    DEBUG0;
    return momentum_;
}

Constituent Constituent::operator+(Constituent const& constituent)
{
    DEBUG0;
    position_ += constituent.position_;
    momentum_ += constituent.momentum_;
    charge_ += constituent.charge_;
    return *this;
}

void Constituent::SetDetectorPart(boca::DetectorPart detector_part)
{
    DEBUG0;
    detector_part_ = detector_part;
}

DetectorPart Constituent::DetectorPart() const
{
    DEBUG(Name(detector_part_));
    return detector_part_;
}

void Constituent::SetCharge(int charge)
{
    DEBUG0;
    charge_ = charge;
}

int Constituent::Charge() const
{
    DEBUG0;
    return charge_;
}

void Constituent::Smearing()
{
    DEBUG0;
    position_.Smearing(45_um); // TODO make this momentum dependent
}

std::vector< Family > Constituent::Families() const
{
    DEBUG0;
    return families_;
}


}
