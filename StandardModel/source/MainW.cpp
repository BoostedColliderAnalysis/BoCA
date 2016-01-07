#include "AnalysisW.hh"
#include "WHadronicTagger.hh"
#include "WLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::AnalysisW<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    switch (boca::standardmodel::AnalysisW<boca::standardmodel::BottomTagger>::WDecay()) {
    case boca::Decay::hadronic :
        Run<boca::standardmodel::WHadronicTagger>(boca::Output::efficiency);
        break;
    case boca::Decay::leptonic :
        Run<boca::standardmodel::WLeptonicTagger>(boca::Output::efficiency);
        break;
    defaul : break;
    }
}
