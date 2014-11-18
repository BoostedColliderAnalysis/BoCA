#include "HAnalysisHiggsCpv.hh"

int main()
{
    hhiggscpv::HAnalysis *Analysis = new hhiggscpv::HAnalysis();

    Analysis->AnalysisLoop("BTagger");

    // TODO but conditional Factory here

    Analysis->AnalysisLoop("Event");

    delete Analysis;

    return 1;

}
