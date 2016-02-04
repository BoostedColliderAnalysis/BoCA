/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Constituent.hh"
#include "Debug.hh"

namespace boca
{

Constituent::Constituent()
{
    INFO0;
}

Constituent::Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position)
{
    INFO0;
    momentum_ = momentum;
    position_ = position;
}

Constituent::Constituent(TLorentzVector const& momentum, LorentzVector<Length> const& position, boca::DetectorPart detector_part, int charge)
{
    INFO0;
    momentum_ = momentum;
    position_ = position;
    detector_part_ = detector_part;
    charge_ = charge;
}

Constituent::Constituent(TLorentzVector const& momentum)
{
    INFO0;
    momentum_ = momentum;
}

Constituent::Constituent(TLorentzVector const& momentum, boca::DetectorPart detector_part, int charge)
{
    INFO0;
    momentum_ = momentum;
    detector_part_ = detector_part;
    charge_ = charge;
}

Constituent::Constituent(TLorentzVector const& momentum, boca::DetectorPart detector_part)
{
    INFO0;
    momentum_ = momentum;
    detector_part_ = detector_part;
}

void Constituent::SetMomentum(TLorentzVector const& momentum)
{
    INFO0;
    momentum_ = momentum;
}

LorentzVector<Length> const& Constituent::Position() const
{
    INFO0;
    return position_;
}

LorentzVector<Momentum> const& Constituent::Momentum() const
{
    INFO0;
    return momentum_;
}

LorentzVector<Length> & Constituent::Position()
{
  INFO0;
  return position_;
}

LorentzVector<Momentum> & Constituent::Momentum()
{
  INFO0;
  return momentum_;
}

Constituent Constituent::operator+(Constituent const& constituent)
{
    INFO0;
    position_ += constituent.position_;
    momentum_ += constituent.momentum_;
    charge_ += constituent.charge_;
    return *this;
}

void Constituent::SetDetectorPart(boca::DetectorPart detector_part)
{
    INFO0;
    detector_part_ = detector_part;
}

DetectorPart Constituent::DetectorPart() const
{
    INFO0;
    return detector_part_;
}

void Constituent::SetCharge(int charge)
{
    INFO0;
    charge_ = charge;
}

int Constituent::Charge() const
{
    INFO0;
    return charge_;
}

void Constituent::Smearing()
{
    INFO0;
    position_.Smearing(45_um);
}

}
