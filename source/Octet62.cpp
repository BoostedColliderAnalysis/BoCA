# include "Octet62.hh"

namespace analysis {

Sextet Octet62::Sextet()const {
  return multiplet_1_;
}

Doublet Octet62::Doublet() const {
  return multiplet_2_;
}

}
