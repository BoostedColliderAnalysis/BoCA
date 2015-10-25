#include  "AnalysisTopPartner.hh"

namespace boca
{

namespace naturalness
{

std::string Name(Process process)
{
    Info();
    switch (process) {
    case Process::TthLep : return "Tth-lep";
    case Process::TthHad : return "Tth-had";
    case Process::TT : return "TT";
    case Process::ttBjj : return "ttBJJ";
    case Process::tthBjj : return "tthBjj";
    case Process::ttBBjj : return "ttBBjj";
    case Process::ttBB : return "ttBB";
    case Process::TThh : return "TThh";
    default: Error("no case");
    }
    return "";
}

std::string NiceName(Process process)
{
    Info();
    switch (process) {
    case Process::TT : return "T_{h}T_{l}";
    case Process::ttBjj : return "t_{l}t_{h}B^{0}jj";
    case Process::tthBjj : return "t_{l}t_{h}hB^{0}jj";
    case Process::TthLep : return "T_{l}t_{h}h";
    case Process::TthHad : return "T_{h}t_{l}h";
    case Process::TThh : return "T_{l}T_{h}hh";
    case Process::ttBB : return "t_{l}t_{h}B^{0}B^{0}";
    default: Error("no case");
    }
    return "";
}

bool MassDependent(Process process)
{
    Info();
    switch (process) {
    case Process::TthLep : return true;
    case Process::TthHad : return true;
    case Process::TT : return true;
    case Process::ttBjj : return false;
    case Process::tthBjj : return false;
    case Process::ttBBjj : return false;
    case Process::ttBB : return false;
    case Process::TThh : return true;
    default : Error("wrong process");
    }
    return false;
}

}

}
