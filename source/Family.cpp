# include "Family.hh"

analysis::Family::Family() {
  particle_.Position = EmptyPosition;
  particle_.Id = EmptyId;
  mother_1_.Position = EmptyPosition;
  mother_1_.Id = EmptyId;
  marker_ = false;
  daughter_ids_.reserve(2);
}

analysis::Family::Family(const int particle_id) {
  particle_.Id = particle_id;
  mother_1_.Id = particle_id;
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

analysis::Family::Family(const int particle_id, const int mother_id) {
  particle_.Id = particle_id;
  mother_1_.Id = mother_id;
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

analysis::Family::Family(const int particle_id, const int mother_1_id, const int mother_2_id) {
  particle_.Id = particle_id;
  mother_1_.Id = mother_1_id;
  mother_2_.Id = mother_2_id;
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

analysis::Family::Family(const int particle_position, const int particle_id, const int mother_position, const int mother_id) {
  particle_.Position = particle_position;
  particle_.Id = particle_id;
  mother_1_.Position = mother_position;
  mother_1_.Id = mother_id;
  marker_ = false;
  daughter_ids_.reserve(2);
}

analysis::Family::Family(const TLorentzVector &particle, const TLorentzVector &mother, const int particle_position, const int particle_id, const int mother_position, const int mother_id) {
  particle_.Momentum = particle;
  mother_1_.Momentum = mother;
  particle_.Position = particle_position;
  particle_.Id = particle_id;
  mother_1_.Position = mother_position;
  mother_1_.Id = mother_id;
  marker_ = false;
  daughter_ids_.reserve(2);
}

bool analysis::Family::operator==(const Family &family) const {
  return (particle_.Id == family.particle().Id && mother_1_.Id == family.mother_1().Id && daughter_ids_ == family.daughter_ids_);
}

void analysis::Family::AddDaughter(const int daughter_id){
  daughter_ids_.emplace_back(daughter_id);
}


void analysis::Family::SetMarker() {
  marker_ = true;
}

void analysis::Family::UnSetMarker() {
  marker_ = false;
}

bool analysis::Family::Marker()const {
  return marker_;
}
