# include "Quintet.hh"

namespace analysis {

Triplet &Quintet::Triplet() const {
  return Multiplet1();
}

Doublet &Quintet::Doublet() const
{
  return Multiplet2();
}

}
