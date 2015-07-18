#include "AnalysisHiggsCpv.hh"

#include "../include/EventTagger.hh"

int main()
{
    analysis::higgscpv::Analysis<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunFullEfficiency();

    analysis::higgscpv::Analysis<analysis::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunFullEfficiency();

    analysis::higgscpv::Analysis<analysis::HiggsTagger> higgs_analysis;
    higgs_analysis.RunFullEfficiency();

    analysis::higgscpv::Analysis<analysis::higgscpv::TopLeptonicPairTagger> jet_pair_analysis;
    jet_pair_analysis.RunFullEfficiency();

    analysis::higgscpv::Analysis<analysis::higgscpv::SignatureTagger> signature_leptonic_analysis;
    signature_leptonic_analysis.RunFullEfficiency();

    analysis::higgscpv::Analysis<analysis::higgscpv::EventTagger> event_leptonic_analysis;
    event_leptonic_analysis.RunFullEfficiency();
}

