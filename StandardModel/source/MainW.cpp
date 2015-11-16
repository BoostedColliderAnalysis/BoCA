#include "AnalysisW.hh"
#include "WHadronicTagger.hh"
#include "WLeptonicTagger.hh"

template<typename Tagger>
void Run(boca::Output run = boca::Output::normal)
{
    boca::standardmodel::AnalysisW<Tagger> analysis;
    boca::Run(analysis, run);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast) ;
    switch (boca::standardmodel::AnalysisW<boca::standardmodel::BottomTagger>::WDecay()) {
    case boca::Decay::hadronic : {
        Run<boca::standardmodel::WHadronicTagger>(boca::Output::efficiency);
        break;
    }
    case boca::Decay::leptonic : {
        Run<boca::standardmodel::WLeptonicTagger>(boca::Output::efficiency);
        break;
    }
    }
}
