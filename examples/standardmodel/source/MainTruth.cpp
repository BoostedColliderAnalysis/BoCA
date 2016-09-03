#include "standardmodel/AnalysisTop.hh"
#include "standardmodel/tagger/Truth.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
        Run<standardmodel::tagger::Truth>(boca::Output::fast);
}

