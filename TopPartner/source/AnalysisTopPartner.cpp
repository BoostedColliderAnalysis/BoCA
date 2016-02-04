#include  "AnalysisTopPartner.hh"
#include  "plotting/Font.hh"

namespace boca
{

namespace naturalness
{

std::string Name(Process process)
{
    INFO0;
    switch (process) {
    case Process::TthLep : return "Tth-lep";
    case Process::TthHad : return "Tth-had";
    case Process::TT : return "TT";
    case Process::ttBjj : return "ttBJJ";
    case Process::tthBjj : return "tthBjj";
    case Process::ttBBjj : return "ttBBjj";
    case Process::ttBB : return "ttBB";
    case Process::TThh : return "TThh";
    case Process::ttWWWW : return "ttWWWW";
    case Process::ttWWWB : return "ttWWWB";
    case Process::ttWWBB : return "ttWWBB";
    case Process::ttWBBB : return "ttWBBB";
    case Process::ttBBBB : return "ttBBBB";
    DEFAULT("Process","");
    }
}

std::string LatexName(Process process)
{
    INFO0;
    switch (process) {
    case Process::TT : return Formula("T_{h}T_{l}");
    case Process::ttBjj : return Formula("t_{l}t_{h}Bjj");
    case Process::tthBjj : return Formula("t_{l}t_{h}hBjj");
    case Process::TthLep : return Formula("T_{l}t_{h}h");
    case Process::TthHad : return Formula("T_{h}t_{l}h");
    case Process::TThh : return Formula("T_{l}T_{h}hh");
    case Process::ttBB : return Formula("t_{l}t_{h}BB");
    case Process::ttWWWW : return Formula("t_{l}t_{h}WWWW");
    case Process::ttWWWB : return Formula("t_{l}t_{h}WWB");
    case Process::ttWWBB : return Formula("t_{l}t_{h}WWBB");
    case Process::ttWBBB : return Formula("t_{l}t_{h}WBBB");
    case Process::ttBBBB : return Formula("t_{l}t_{h}BBBB");
    DEFAULT("Process","");
    }
}

bool MassDependent(Process process)
{
    INFO0;
    switch (process) {
    case Process::TthLep : return true;
    case Process::TthHad : return true;
    case Process::TT : return true;
    case Process::ttBjj : return false;
    case Process::tthBjj : return false;
    case Process::ttBBjj : return false;
    case Process::ttBB : return false;
    case Process::TThh : return true;
    case Process::ttWWWW : return false;
    case Process::ttWWWB : return false;
    case Process::ttWWBB : return false;
    case Process::ttWBBB : return false;
    case Process::ttBBBB : return false;
    DEFAULT("Process",false);
    }
}

}

}
