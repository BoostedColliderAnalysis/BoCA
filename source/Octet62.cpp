# include "Octet62.hh"

namespace analysis {

Sextet &Octet62::Sextet() const
{
  return Multiplet1();
}

Doublet &Octet62::Doublet() const
{
  return Multiplet2();
}

}
