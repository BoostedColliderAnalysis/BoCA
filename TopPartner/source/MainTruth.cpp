#include "AnalysisTopPartnerEffective.hh"
#include "../include/TruthLevel.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::naturalness::AnalysisEffective<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::naturalness::TruthLevel>(boca::Output::fast);
}

