#include "Constituent.hh"

namespace analysis {

Constituent::Constituent() {};

Constituent::Constituent(const TLorentzVector& momentum, const analysis::LorentzVector& position, const analysis::Family& family)
{
    momentum_ = momentum;
    position_ = position;
    family_ = family;
}

Constituent::Constituent(const TLorentzVector& momentum, const analysis::LorentzVector& position)
{
    momentum_ = momentum;
    position_ = position;
}

Constituent::Constituent(const TLorentzVector& momentum, const analysis::LorentzVector& position, const analysis::SubDetector sub_detector, float charge)
{
    momentum_ = momentum;
    position_ = position;
    sub_detector_ = sub_detector;
    charge_ = charge;
}

Constituent::Constituent(const TLorentzVector& momentum, const Family& family)
{
    momentum_ = momentum;
    family_ = family;
}

Constituent::Constituent(const LorentzVector& momentum, const Family& family)
{
    momentum_ = momentum;
    family_ = family;
}

Constituent::Constituent(const TLorentzVector& momentum)
{
    momentum_ = momentum;
}

Constituent::Constituent(const TLorentzVector& momentum, const SubDetector sub_detector, float charge)
{
    momentum_ = momentum;
    sub_detector_ = sub_detector;
    charge_ = charge;
}

Constituent::Constituent(const TLorentzVector& momentum, const SubDetector sub_detector)
{
    momentum_ = momentum;
    sub_detector_ = sub_detector;
}

void Constituent::SetPosition(const TLorentzVector& position)
{
    position_ = position;
}

void Constituent::SetPosition(float x, float y, float z, float t)
{
    position_.SetXYZT(x, y, z, t);
}

void Constituent::SetMomentum(const TLorentzVector& momentum)
{
    momentum_ = momentum;
}

void Constituent::SetFamily(const Family& family)
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

Constituent Constituent::operator+(const Constituent& constituent)
{
    position_ += constituent.position_;
    momentum_ += constituent.momentum_;
    charge_ += constituent.charge_;
    return *this;
}

void Constituent::SetDetector(const SubDetector detector)
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
