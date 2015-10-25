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
    Run<boca::BottomTagger>(boca::Output::fast) ;
    switch (boca::standardmodel::AnalysisW<boca::BottomTagger>::WDecay()) {
    case boca::Decay::hadronic : {
        Run<boca::WHadronicTagger>(boca::Output::efficiency);
        break;
    }
    case boca::Decay::leptonic : {
        Run<boca::WLeptonicTagger>(boca::Output::efficiency);
        break;
    }
    }
}
