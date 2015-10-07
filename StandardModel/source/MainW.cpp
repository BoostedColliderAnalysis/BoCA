#include "AnalysisW.hh"
#include "WHadronicTagger.hh"
#include "WLeptonicTagger.hh"

int main()
{
    boca::standardmodel::AnalysisW<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunFast();
    switch (bottom_analysis.WDecay()) {
    case boca::Decay::hadronic : {
        boca::standardmodel::AnalysisW<boca::WHadronicTagger> w_hadronic_analysis;
        w_hadronic_analysis.RunFullEfficiency();
        break;
    }
    case boca::Decay::leptonic : {
        boca::standardmodel::AnalysisW<boca::WLeptonicTagger> w_leptonic_analysis;
        w_leptonic_analysis.RunFullEfficiency();
        break;
    }
    }
}

