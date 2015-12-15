#include "AnalysisHeavyHiggs.hh"
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

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

std::string LatexName(Process process)
{
    switch (process) {
    case Process::Hbb : return "H/Ab#bar{b}";
    case Process::Htt : return "H/At#bar{t}";
    case Process::Htwb : return "H/AtW^{#pm}b";
    case Process::ttwwbb : return "t#bar{t}W^{#pm}W^{#mp}b#bar{b}";
    case Process::ttwbb : return "t#bar{t}W^{#pm}b#bar{b}";
    case Process::H0 : return "H/A";
    case Process::Htb : return "H^{#pm}tb";
    case Process::tt : return "t#bar{t}";
    case Process::tttt : return "t#bar{t}t#bar{t}";
    case Process::tt2 : return "t#bar{t}";
    default : Error("unhandled case");
        return "";
    }
}

}

}
