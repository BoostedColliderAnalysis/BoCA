/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "Constituent.hh"

namespace boca {

Constituent::Constituent() {};

Constituent::Constituent(TLorentzVector const& momentum, const boca::LorentzVector& position, const boca::Family& family)
{
    momentum_ = momentum;
    position_ = position;
    family_ = family;
}

Constituent::Constituent(TLorentzVector const& momentum, const boca::LorentzVector& position)
{
    momentum_ = momentum;
    position_ = position;
}

Constituent::Constituent(TLorentzVector const& momentum, const boca::LorentzVector& position, const boca::SubDetector sub_detector, float charge)
{
    momentum_ = momentum;
    position_ = position;
    sub_detector_ = sub_detector;
    charge_ = charge;
}

Constituent::Constituent(TLorentzVector const& momentum, Family const& family)
{
    momentum_ = momentum;
    family_ = family;
}

Constituent::Constituent(LorentzVector const& momentum, Family const& family)
{
    momentum_ = momentum;
    family_ = family;
}

Constituent::Constituent(TLorentzVector const& momentum)
{
    momentum_ = momentum;
}

Constituent::Constituent(TLorentzVector const& momentum, SubDetector sub_detector, float charge)
{
    momentum_ = momentum;
    sub_detector_ = sub_detector;
    charge_ = charge;
}

Constituent::Constituent(TLorentzVector const& momentum, SubDetector sub_detector)
{
    momentum_ = momentum;
    sub_detector_ = sub_detector;
}

void Constituent::SetPosition(TLorentzVector const& position)
{
    position_ = position;
}

void Constituent::SetPosition(float x, float y, float z, float t)
{
    position_.SetXYZT(x, y, z, t);
}

void Constituent::SetMomentum(TLorentzVector const& momentum)
{
    momentum_ = momentum;
}

void Constituent::SetFamily(Family const& family)
{
    family_ = family;
}

LorentzVector Constituent::Position() const
{
    return position_;
}

LorentzVector Constituent::Momentum() const
{
    return momentum_;
}

Family Constituent::family() const
{
    return family_;
}

Constituent Constituent::operator+(Constituent const& constituent)
{
    position_ += constituent.position_;
    momentum_ += constituent.momentum_;
    charge_ += constituent.charge_;
    return *this;
}

void Constituent::SetDetector(SubDetector detector)
{
    sub_detector_ = detector;
}

SubDetector Constituent::sub_detector() const
{
    return sub_detector_;
}

void Constituent::set_charge(int charge)
{
    charge_ = charge;
}

int Constituent::charge() const
{
    return charge_;
}

}
