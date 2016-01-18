#include "AnalysisBoson.hh"
#include "BosonTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::AnalysisBoson<Tagger> analysis;
    analysis.Run(run);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    Run<boca::standardmodel::BosonTagger>(boca::Output::efficiency);
}

