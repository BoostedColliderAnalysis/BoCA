#include "standardmodel/analysis/Top.hh"
#include "standardmodel/tagger/Truth.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::analysis::Top<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
        Run<standardmodel::tagger::Truth>(boca::Output::fast);
}

