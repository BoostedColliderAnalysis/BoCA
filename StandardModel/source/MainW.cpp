#include "AnalysisWTagger.hh"
#include "WHadronicTagger.hh"
#include "WSemiTagger.hh"

int main()
{

    analysis::BottomTagger bottom_tagger;
    analysis::standardmodel::AnalysisW bottom_analysis(bottom_tagger);
    bottom_analysis.RunFast();

    switch (bottom_analysis.WDecay()) {
      case analysis::standardmodel::Decay::hadronic : {
        analysis::WHadronicTagger w_hadronic_tagger;
        analysis::standardmodel::AnalysisW w_hadronic_analysis(w_hadronic_tagger);
        w_hadronic_analysis.RunFullEfficiency();
        break;
    }
      case analysis::standardmodel::Decay::semi : {
        analysis::WSemiTagger w_semi_tagger;
        analysis::standardmodel::AnalysisW w_semi_analysis(w_semi_tagger);
        w_semi_analysis.RunFullEfficiency();
        break;
    }
    }
}

