# include "AnalysisTopTagger.hh"
# include "TopHadronicTagger.hh"
# include "TopSemiTagger.hh"
# include "TopLeptonicTagger.hh"

int main()
{
    analysis::BottomTagger bottom_tagger;
    analysis::standardmodel::TopAnalysis bottom_analysis(bottom_tagger);
    bottom_analysis.RunFast();

    switch (bottom_analysis.TopDecay()) {
    case analysis::standardmodel::Decay::hadronic : {
        analysis::WHadronicTagger w_hadronic_tagger;
        analysis::standardmodel::TopAnalysis w_hadronic_analysis(w_hadronic_tagger);
        w_hadronic_analysis.RunFast();

        analysis::TopHadronicTagger top_hadronic_tagger;
        analysis::standardmodel::TopAnalysis top_hadronic_analysis(top_hadronic_tagger);
        top_hadronic_analysis.RunFull();
        break;
    }
    case analysis::standardmodel::Decay::semi : {
        analysis::WSemiTagger w_semi_tagger;
        analysis::standardmodel::TopAnalysis w_semi_analysis(w_semi_tagger);
        w_semi_analysis.RunFast();

        analysis::TopSemiTagger tops_semi_tagger;
        analysis::standardmodel::TopAnalysis top_semi_analysis(tops_semi_tagger);
        top_semi_analysis.RunFull();
        break;
    }
    case analysis::standardmodel::Decay::leptonic : {
        analysis::TopLeptonicTagger tops_leptonic_tagger;
        analysis::standardmodel::TopAnalysis top_leptonic_analysis(tops_leptonic_tagger);
        top_leptonic_analysis.RunFull();
        break;
    }
    }
}

