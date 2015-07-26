#include "AnalysisHiggsCpv.hh"

#include "../include/EventTagger.hh"
#include "Predicate.hh"
#include "Flag.hh"
#include "Debug.hh"
#include "FourVector.hh"

int main()
{
    analysis::higgscpv::Analysis<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

    analysis::higgscpv::Analysis<analysis::WLeptonicTagger> w_leptonic_analysis;
    w_leptonic_analysis.RunNormal();

    analysis::higgscpv::Analysis<analysis::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

//     analysis::higgscpv::Analysis<analysis::WHadronicTagger> w_hadronic_analysis;
    //     w_hadronic_analysis.RunNormal();
//
//     analysis::higgscpv::Analysis<analysis::TopHadronicTagger> top_hadronic_analysis;
    //     top_hadronic_analysis.RunNormal();

    analysis::higgscpv::Analysis<analysis::HiggsTagger> higgs_analysis;
    higgs_analysis.RunFullEfficiency();
    higgs_analysis.RunPlots();

    analysis::higgscpv::Analysis<analysis::higgscpv::TopLeptonicPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFullEfficiency();
    jet_pair_analysis.RunPlots();

    analysis::higgscpv::Analysis<analysis::higgscpv::SignatureTagger> signature_leptonic_analysis;
    signature_leptonic_analysis.RunFullEfficiency();
    signature_leptonic_analysis.RunPlots();

    analysis::higgscpv::Analysis<analysis::higgscpv::EventTagger> event_leptonic_analysis;
    event_leptonic_analysis.RunFullSignificance();
}

