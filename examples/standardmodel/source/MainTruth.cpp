#include "standardmodel/analysis/Top.hh"
#include "standardmodel/tagger/Truth.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::analysis::Top<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
        Run<standardmodel::tagger::Truth>(boca::Output::fast);
}

