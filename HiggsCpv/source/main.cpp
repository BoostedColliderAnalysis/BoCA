#include "AnalysisHiggsCpv.hh"

#include "../include/EventTagger.hh"
#include "EventTTagger.hh"
#include "EventLeptonTTagger.hh"
#include "SignatureLeptonTTagger.hh"
#include "Types.hh"
#include "FourVector.hh"
#include "Debug.hh"

int main()
{

    boca::higgscpv::Analysis<boca::BottomTagger> bottom_analysis;
    bottom_analysis.RunNormal();

//     boca::higgscpv::Analysis<boca::WLeptonicTagger> w_leptonic_analysis;
//     w_leptonic_analysis.RunNormal();

    boca::higgscpv::Analysis<boca::TopLeptonicTagger> top_leptonic_analysis;
    top_leptonic_analysis.RunNormal();

//     boca::higgscpv::Analysis<boca::WHadronicTagger> w_hadronic_analysis;
    //     w_hadronic_analysis.RunNormal();
//
//     boca::higgscpv::Analysis<boca::TopHadronicTagger> top_hadronic_analysis;
    //     top_hadronic_analysis.RunNormal();

    boca::higgscpv::Analysis<boca::HiggsTagger> higgs_analysis;
    higgs_analysis.RunFullEfficiency();
//     higgs_analysis.RunPlots();

//     boca::higgscpv::Analysis<boca::higgscpv::TopLeptonicPairTagger> jet_pair_analysis;
//     jet_pair_analysis.RunFullEfficiency();
//     jet_pair_analysis.RunPlots();

//     boca::higgscpv::Analysis<boca::higgscpv::SignatureTagger> signature_leptonic_analysis;
//     signature_leptonic_analysis.RunFullEfficiency();
//     signature_leptonic_analysis.RunPlots();

//     boca::higgscpv::Analysis<boca::higgscpv::EventTagger> event_leptonic_analysis;
//     event_leptonic_analysis.RunFullSignificance();

    boca::higgscpv::Analysis<boca::higgscpv::SignatureTTagger> signature_t_analysis;
    signature_t_analysis.RunFullEfficiency();
//     signature_t_analysis.RunPlots();

    boca::higgscpv::Analysis<boca::higgscpv::EventTTagger> event_t_analysis;
    event_t_analysis.RunFullSignificance();

//     boca::higgscpv::Analysis<boca::higgscpv::SignatureLeptonTagger> signature_l_analysis;
//     signature_l_analysis.RunFullEfficiency();
    //     signature_l_analysis.RunPlots();

    boca::higgscpv::Analysis<boca::higgscpv::SignatureLeptonTTagger> signature_lepton_t_analysis;
    signature_lepton_t_analysis.RunFullEfficiency();
        signature_t_analysis.RunPlots();

    boca::higgscpv::Analysis<boca::higgscpv::EventLeptonTTagger> event_lepton_t_analysis;
    event_lepton_t_analysis.RunFullSignificance();


}

