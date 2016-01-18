#include "AnalysisZ.hh"
#include "ZHadronicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::AnalysisZ<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    Run<boca::standardmodel::ZHadronicTagger>(boca::Output::efficiency);
}
