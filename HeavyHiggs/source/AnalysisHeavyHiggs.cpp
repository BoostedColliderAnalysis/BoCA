#include "AnalysisHeavyHiggs.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

std::string Name(const Collider collider)
{
    switch (collider) {
    case Collider::LHC :
        return "14TeV";
    case Collider::FHC:
        return "100TeV";
    case Collider::LE:
        return "LE";
    default:
        Error("unhandled case");
        return "";
    }
}

std::string Name(const Process process)
{
    switch (process) {
    case Process::Hbb:
      return "H0bb-ljbbbb";
    case Process::H0:
      return "H0-ljbb";
    case Process::Htb:
      return "H+tb-ljbbbb";
    case Process::tt:
      return "tt_inc";
    case Process::tt2:
      return "tt_inc+";
    default:
        Error("unhandled case");
        return "";
    }
}

std::string NiceName(const Process process)
{
  switch (process) {
    case Process::Hbb:
      return "Hbb";
    case Process::H0:
      return "H";
    case Process::Htb:
      return "H+-tb";
    case Process::tt:
      return "tt";
    case Process::tt2:
      return "tt";
    default:
      Error("unhandled case");
      return "";
  }
}

}

}
