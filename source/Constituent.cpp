#include "Constituent.hh"

namespace analysis {

Constituent::Constituent() {};

Constituent::Constituent(const TLorentzVector &momentum, const TLorentzVector &position, const Family &family)
{
    momentum_ = momentum;
    position_ = position;
    family_ = family;
}

Constituent::Constituent(const TLorentzVector &momentum, const TLorentzVector &position)
{
    momentum_ = momentum;
    position_ = position;
}

Constituent::Constituent(const TLorentzVector &momentum, const TLorentzVector &position, const SubDetector sub_detector, const float charge)
{
    momentum_ = momentum;
    position_ = position;
    sub_detector_ = sub_detector;
    charge_ = charge;
}

Constituent::Constituent(const TLorentzVector &momentum, const Family &family)
{
    momentum_ = momentum;
    family_ = family;
}

Constituent::Constituent(const TLorentzVector &momentum)
{
    momentum_ = momentum;
}

Constituent::Constituent(const TLorentzVector &momentum, const SubDetector sub_detector, const float charge)
{
    momentum_ = momentum;
    sub_detector_ = sub_detector;
    charge_ = charge;
}

Constituent::Constituent(const TLorentzVector &momentum, const SubDetector sub_detector)
{
  momentum_ = momentum;
  sub_detector_ = sub_detector;
}

void Constituent::SetPosition(const TLorentzVector &position)
{
    position_ = position;
}

void Constituent::SetPosition(const float x, const float y, const float z, const float t)
{
    position_.SetXYZT(x, y, z, t);
}

void Constituent::SetMomentum(const TLorentzVector &momentum)
{
    momentum_ = momentum;
}

void Constituent::SetFamily(const Family &family)
{
    family_ = family;
}

TLorentzVector Constituent::Position() const
{
    return position_;
}

TLorentzVector Constituent::Momentum() const
{
    return momentum_;
}

Family Constituent::family() const
{
    return family_;
}

Constituent Constituent::operator+(Constituent &constituent)
{
    constituent.position_ += this->position_;
    constituent.momentum_ += this->momentum_;
    constituent.charge_ += this->charge_;
    return constituent;
}

void Constituent::SetDetector(const SubDetector detector)
{
    sub_detector_ = detector;
}

SubDetector Constituent::sub_detector() const
{
    return sub_detector_;
}

void Constituent::set_charge(const int charge)
{
    charge_ = charge;
}

int Constituent::charge() const
{
    return charge_;
}

}
