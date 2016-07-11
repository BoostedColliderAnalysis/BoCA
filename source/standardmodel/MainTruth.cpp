#include "boca/standardmodel/AnalysisTop.hh"
#include "boca/standardmodel/tagger/Truth.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
        Run<boca::standardmodel::tagger::Truth>(boca::Output::fast);
}

