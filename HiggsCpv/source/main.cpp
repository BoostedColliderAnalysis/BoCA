#include "AnalysisHiggsCpv.hh"

#include "EventTTagger.hh"
#include "EventLeptonTTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::higgscpv::Analysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    //     Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    //     Run<boca::standardmodel::WHadronicTagger>();
    //     Run<boca::standardmodel::TopHadronicTagger>();    Run<boca::standardmodel::HiggsTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::TopLeptonicPairTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::SignatureTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::GlobalTagger>(boca::Output::significance);
    Run<boca::higgscpv::SignatureTTagger>(boca::Output::efficiency);
    Run<boca::higgscpv::EventTTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::SignatureLeptonTagger>(boca::Output::efficiency);
    Run<boca::higgscpv::SignatureLeptonTTagger>(boca::Output::efficiency);
    Run<boca::higgscpv::EventLeptonTTagger>(boca::Output::significance);
}

