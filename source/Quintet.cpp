# include "Quintet.hh"

namespace analysis {

Doublet Quintet::Doublet()const {
  return multiplet_2_;
}

Triplet Quintet::Triplet()const {
  return multiplet_1_;
}

}
