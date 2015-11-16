#include "AnalysisZ.hh"
#include "ZHadronicTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::AnalysisZ<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    Run<boca::standardmodel::ZHadronicTagger>(boca::Output::efficiency);
}
