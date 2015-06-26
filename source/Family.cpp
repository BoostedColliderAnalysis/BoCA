# include "Family.hh"

namespace analysis {

Family::Family() {
  particle_.Position = EmptyPosition;
  particle_.Id = to_int(Id::empty);
  mother_1_.Position = EmptyPosition;
  mother_1_.Id = to_int(Id::empty);
  marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const int id) {
  particle_.Id = id;
  mother_1_.Id = id;
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const Id id) {
  particle_.Id = int(id);
  mother_1_.Id = int(id);
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

// Family::Family(const int id, const int mother_id) {
//   particle_.Id = id;
//   mother_1_.Id = mother_id;
//   particle_.Position = EmptyPosition;
//   mother_1_.Position = EmptyPosition;
//   marker_ = false;
//   daughter_ids_.reserve(2);
// }

Family::Family(const Id id, const Id mother_id) {
  particle_.Id = int(id);
  mother_1_.Id = int(mother_id);
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const int id, const int mother_1_id, const int mother_2_id) {
  particle_.Id = id;
  mother_1_.Id = mother_1_id;
  mother_2_.Id = mother_2_id;
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const Id id, const Id mother_1_id, const Id mother_2_id) {
  particle_.Id = int(id);
  mother_1_.Id = int(mother_1_id);
  mother_2_.Id = int(mother_2_id);
  particle_.Position = EmptyPosition;
  mother_1_.Position = EmptyPosition;
  marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const int particle_position, const Id id, const int mother_position, const Id mother_id) {
  particle_.Position = particle_position;
  particle_.Id = int(id);
  mother_1_.Position = mother_position;
  mother_1_.Id = int(mother_id);
  marker_ = false;
  daughter_ids_.reserve(2);
}

Family::Family(const TLorentzVector &particle, const TLorentzVector &mother, const int particle_position, const int id, const int mother_position, const int mother_id) {
  particle_.Momentum = particle;
  mother_1_.Momentum = mother;
  particle_.Position = particle_position;
  particle_.Id = id;
  mother_1_.Position = mother_position;
  mother_1_.Id = mother_id;
  marker_ = false;
  daughter_ids_.reserve(2);
}

// Family::Family(const TLorentzVector &particle, const TLorentzVector &mother, const int particle_position, const Id id, const int mother_position, const Id mother_id) {
//   particle_.Momentum = particle;
//   mother_1_.Momentum = mother;
//   particle_.Position = particle_position;
//   particle_.Id = int(id);
//   mother_1_.Position = mother_position;
//   mother_1_.Id = int(mother_id);
//   marker_ = false;
//   daughter_ids_.reserve(2);
// }

bool Family::operator==(const Family &family) const {
  return (particle_.Id == family.particle().Id && mother_1_.Id == family.mother_1().Id && daughter_ids_ == family.daughter_ids_);
}

void Family::AddDaughter(const int daughter_id){
  daughter_ids_.emplace_back(daughter_id);
}


void Family::SetMarker() {
  marker_ = true;
}

void Family::UnSetMarker() {
  marker_ = false;
}

bool Family::Marker()const {
  return marker_;
}

}
