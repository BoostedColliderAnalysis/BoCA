#include "AnalysisBoson.hh"
#include "BosonTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::AnalysisBoson<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::BottomTagger>(boca::Output::fast) ;
    Run<boca::BosonTagger>(boca::Output::efficiency);
}

