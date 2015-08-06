#include "Types.hh"

#include <sys/stat.h>

#include "TLorentzVector.h"

#include "JetInfo.hh"
#include "Debug.hh"

namespace analysis {

fastjet::PseudoJet PseudoJet(const TLorentzVector& vector)
{
    // construct a pseudojet from explicit components
    // PseudoJet(double px, double py, double pz, double E);
    return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}

fastjet::PseudoJet PseudoJet(const LorentzVector& vector)
{
    // construct a pseudojet from explicit components
    // PseudoJet(double px, double py, double pz, double E);
    return fastjet::PseudoJet(vector.Px(), vector.Py(), vector.Pz(), vector.E());
}

bool Exists(const std::string& name)
{
  Note(name);
  struct stat buffer;
  return (stat(name.c_str(), &buffer) == 0);
}

}

