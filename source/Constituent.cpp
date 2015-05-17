# include "Constituent.hh"

analysis::Constituent::Constituent() {};

analysis::Constituent::Constituent(const TLorentzVector &momentum, const TLorentzVector &position, const analysis::Family &family) {
  momentum_ = momentum;
  position_ = position;
  family_ = family;
}

analysis::Constituent::Constituent(const TLorentzVector &momentum, const TLorentzVector &position) {
  momentum_ = momentum;
  position_ = position;
}

analysis::Constituent::Constituent(const TLorentzVector &momentum, const TLorentzVector &position, const SubDetector sub_detector) {
  momentum_ = momentum;
  position_ = position;
  sub_detector_ = sub_detector;
}

analysis::Constituent::Constituent(const TLorentzVector &momentum, const analysis::Family &family) {
  momentum_ = momentum;
  family_ = family;
}

analysis::Constituent::Constituent(const TLorentzVector &momentum) {
  momentum_ = momentum;
}

analysis::Constituent::Constituent(const TLorentzVector &momentum, const SubDetector sub_detector) {
  momentum_ = momentum;
  sub_detector_ = sub_detector;
}

void analysis::Constituent::SetPosition(const TLorentzVector &position) {
  position_ = position;
}

void analysis::Constituent::SetPosition(const float x, const float y, const float z, const float t) {
  position_.SetXYZT(x, y, z, t);
}

void analysis::Constituent::SetMomentum(const TLorentzVector &momentum) {
  momentum_ = momentum;
}

void analysis::Constituent::SetFamily(const Family & family) {
  family_ = family;
}

TLorentzVector analysis::Constituent::Position() const {
  return position_;
}

TLorentzVector analysis::Constituent::Momentum() const {
  return momentum_;
}

analysis::Family analysis::Constituent::family() const {
  return family_;
}

analysis::Constituent analysis::Constituent::operator+(Constituent &constituent) {
    constituent.position_ += this->position_;
    constituent.momentum_ += this->momentum_;
  return constituent;
}

void analysis::Constituent::SetDetector(const SubDetector detector) {
  sub_detector_ = detector;
}

analysis::Constituent::SubDetector analysis::Constituent::sub_detector() const {
  return sub_detector_;
}
