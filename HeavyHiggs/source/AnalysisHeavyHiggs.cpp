#include "AnalysisHeavyHiggs.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

std::string Name(Collider collider)
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

std::string Name(Process process)
{
    switch (process) {
    case Process::Hbb:
        return "H0bb-ljbbbb";
    case Process::Htt:
      return "Htt-lljjbbbb";
    case Process::Htwb:
      return "Htwb-lljjbbbb";
    case Process::H0:
        return "H0-ljbb";
    case Process::Htb:
        return "H+tb-ljbbbb";
    case Process::tt:
        return "tt_inc";
    case Process::tttt:
      return "tttt";
    case Process::ttwwbb:
      return "ttwwbb";
    case Process::ttwbb:
      return "ttwbb";
    case Process::tt2:
        return "tt_inc+";
    default:
        Error("unhandled case");
        return "";
    }
}

std::string NiceName(Process process)
{
    switch (process) {
    case Process::Hbb:
        return "Hbb";
    case Process::Htt:
      return "Htt";
    case Process::Htwb:
      return "Htwb";
    case Process::ttwwbb:
      return "ttwwbb";
    case Process::ttwbb:
      return "ttwbb";
    case Process::H0:
        return "H";
    case Process::Htb:
        return "H+-tb";
    case Process::tt:
        return "tt";
    case Process::tttt:
        return "tttt";
    case Process::tt2:
        return "tt";
    default:
        Error("unhandled case");
        return "";
    }
}

}

}
