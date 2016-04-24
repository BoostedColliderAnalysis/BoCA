#include "boca/standardmodel/AnalysisTop.hh"
#include "boca/standardmodel/TruthLevel.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
        Run<boca::standardmodel::TruthLevel>(boca::Output::fast);
}

