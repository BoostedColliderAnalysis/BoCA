#include "AnalysisHiggsCpv.hh"

#include "../include/EventTagger.hh"
#include "../include/EventTTagger.hh"
#include "SignatureLeptonTagger.hh"
#include "Types.hh"
#include "FourVector.hh"
#include "Debug.hh"

int main()
{
    analysis::higgscpv::Analysis<analysis::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

//     analysis::higgscpv::Analysis<analysis::WLeptonicTagger> w_leptonic_analysis;
//     w_leptonic_analysis.RunNormal();

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

//     analysis::higgscpv::Analysis<analysis::higgscpv::TopLeptonicPairTagger> jet_pair_analysis;
//     jet_pair_analysis.RunFullEfficiency();
//     jet_pair_analysis.RunPlots();

//     analysis::higgscpv::Analysis<analysis::higgscpv::SignatureTagger> signature_leptonic_analysis;
//     signature_leptonic_analysis.RunFullEfficiency();
//     signature_leptonic_analysis.RunPlots();

//     analysis::higgscpv::Analysis<analysis::higgscpv::EventTagger> event_leptonic_analysis;
//     event_leptonic_analysis.RunFullSignificance();

    analysis::higgscpv::Analysis<analysis::higgscpv::SignatureTTagger> signature_t_analysis;
    signature_t_analysis.RunFullEfficiency();
    signature_t_analysis.RunPlots();

    analysis::higgscpv::Analysis<analysis::higgscpv::EventTTagger> event_t_analysis;
    event_t_analysis.RunFullSignificance();

//     analysis::higgscpv::Analysis<analysis::higgscpv::SignatureLeptonTagger> signature_l_analysis;
//     signature_l_analysis.RunFullEfficiency();
//     signature_l_analysis.RunPlots();


}

