#include "boca/AnalysisHiggsCpv.hh"

#include "boca/EventTTagger.hh"
#include "boca/EventLeptonTTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::higgscpv::Analysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    //     Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    //     Run<boca::standardmodel::tagger::WHadronic>();
    //     Run<boca::standardmodel::tagger::TopHadronic>();    Run<boca::standardmodel::tagger::Higgs>(boca::Output::efficiency);
    //     Run<boca::higgscpv::TopLeptonicPairTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::SignatureTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::GlobalTagger>(boca::Output::significance);
    Run<boca::higgscpv::SignatureTTagger>(boca::Output::efficiency);
    Run<boca::higgscpv::EventTTagger>(boca::Output::efficiency);
    //     Run<boca::higgscpv::SignatureLeptonTagger>(boca::Output::efficiency);
    Run<boca::higgscpv::SignatureLeptonTTagger>(boca::Output::efficiency);
    Run<boca::higgscpv::EventLeptonTTagger>(boca::Output::significance);
}

