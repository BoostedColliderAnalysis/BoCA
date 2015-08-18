#include "AnalysisStandardModel.hh"
#include "Debug.hh"

namespace boca {

namespace standardmodel {

std::string Name(Process process)
{
    switch (process) {
    case Process::tt:
        return "tt";
    case Process::tt_lep:
        return "tt_leptonic";
    case Process::tt_had:
        return "tt_hadronic";
    case Process::bb:
        return "bb";
    case Process::cc:
        return "cc";
    case Process::qq:
        return "qq";
    case Process::gg:
        return "gg";
    case Process::hh:
        return "hh";
    case Process::hh_bb:
        return "hh_bb";
    case Process::ww:
        return "ww";
    case Process::zz:
        return "zz";
    case Process::zz_bb:
        return "zz_bb";
    default:
        Error("unhandled case", to_int(process));
        return "";
    }
}

std::string Name(Collider collider)
{
    switch (collider) {
    case Collider::LHC :
        return "14TeV";
    case Collider::FHC:
        return "100TeV";
    case Collider::LE:
        return "100TeV";
    default:
        Error("unhandled case", to_int(collider));
        return "";
    }
}

std::string NiceName(Process process)
{
    switch (process) {
    case Process::bb:
        return "b";
    case Process::cc:
        return "c";
    case Process::qq:
        return "q";
    case Process::gg:
        return "g";
    case Process::hh:
        return "h";
    case Process::hh_bb:
        return "h|_{b}";
    case Process::ww:
        return "W";
    case Process::zz:
        return "Z";
    case Process::zz_bb:
        return "Z|_{b}";
    case Process::tt_had:
        return "t_{h}";
    case Process::tt_lep:
        return "t_{l}";
    default:
        Error("unhandled case", Name(process));
        return "";
    }
}

}

}
