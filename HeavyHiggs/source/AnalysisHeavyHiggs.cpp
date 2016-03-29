#include "AnalysisHeavyHiggs.hh"
#include "plotting/Font.hh"
#include "DEBUG.hh"

namespace boca
{

namespace heavyhiggs
{

std::string Name(Collider collider)
{
    switch (collider) {
    case Collider::LHC : return "14TeV";
    case Collider::FHC : return "100TeV";
    case Collider::LE : return "LE";
        DEFAULT(Name(collider), "");
    }
}

std::string Name(Process process)
{
    switch (process) {
    case Process::Hbb : return "H0bb-ljbbbb";
    case Process::Htt : return "Htt-lljjbbbb";
    case Process::Htwb : return "Htwb-lljjbbbb";
    case Process::H0 : return "H0-ljbb";
    case Process::Htb : return "H+tb-ljbbbb";
    case Process::tt : return "tt_inc";
    case Process::tttt : return "tttt";
    case Process::tttwb : return "tttwb";
    case Process::ttwwbb : return "ttwwbb";
    case Process::ttwbb : return "ttwbb";
    case Process::tt2 : return "tt_inc+";
    case Process::hbb : return "Hbb";
        DEFAULT("Process", "");
    }
}

std::string LatexName(Process process)
{
    switch (process) {
    case Process::Hbb : return Formula("H/Ab\\bar{b}");
    case Process::Htt : return Formula("H/At\\bar{t}");
    case Process::Htwb : return Formula("H/AtW^{#pm}b");
    case Process::ttwwbb : return Formula("t\\bar{t}W^{#pm}W^{\\mp}b\\bar{b}");
    case Process::ttwbb : return Formula("t\\bar{t}W^{#pm}b\\bar{b}");
    case Process::H0 : return Formula("H/A");
    case Process::Htb : return Formula("H^{#pm}tb");
    case Process::tt : return Formula("t\\bar{t}");
    case Process::tttt : return Formula("t\\bar{t}t\\bar{t}");
    case Process::tttwb : return Formula("t\\bar{t}W^{#pm}b");
    case Process::tt2 : return Formula("t\\bar{t}");
    case Process::hbb : return Formula("H/Ab\\bar{b}");
        DEFAULT(Name(process), "");
    }
}

}

}
