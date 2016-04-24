/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/Constituent.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

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

Constituent::Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position, boca::DetectorPart detector_part, int charge)
{
    DEBUG0;
    momentum_ = momentum;
    position_ = position;
    detector_part_ = detector_part;
    charge_ = charge;
}

Constituent::Constituent(TLorentzVector const& momentum)
{
    DEBUG0;
    momentum_ = momentum;
}

Constituent::Constituent(TLorentzVector const& momentum, boca::DetectorPart detector_part, int charge)
{
    DEBUG0;
    momentum_ = momentum;
    detector_part_ = detector_part;
    charge_ = charge;
}

Constituent::Constituent(TLorentzVector const& momentum, boca::DetectorPart detector_part)
{
    DEBUG0;
    momentum_ = momentum;
    detector_part_ = detector_part;
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
    DEBUG0;
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

}
