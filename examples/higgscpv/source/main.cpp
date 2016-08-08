#include "include/AnalysisHiggsCpv.hh"

#include "include/tagger/EventT.hh"
#include "include/tagger/EventLeptonT.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    higgscpv::Analysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::tagger::Bottom>();
    //     Run<boca::standardmodel::tagger::WLeptonic>();
    Run<boca::standardmodel::tagger::TopLeptonic>();
    //     Run<boca::standardmodel::tagger::WHadronic>();
    //     Run<boca::standardmodel::tagger::TopHadronic>();    Run<boca::standardmodel::tagger::Higgs>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::TopLeptonicPairTagger>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::SignatureTagger>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::GlobalTagger>(boca::Output::significance);
    Run<higgscpv::tagger::SignatureT>(boca::Output::efficiency);
    Run<higgscpv::tagger::EventT>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::SignatureLepton>(boca::Output::efficiency);
    Run<higgscpv::tagger::SignatureLeptonT>(boca::Output::efficiency);
    Run<higgscpv::tagger::EventLeptonT>(boca::Output::significance);
}

