#include "higgscpv/Analysis.hh"

#include "higgscpv/tagger/EventT.hh"
#include "higgscpv/tagger/EventLeptonT.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    higgscpv::Analysis<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    //     Run<standardmodel::tagger::WLeptonic>();
    Run<standardmodel::tagger::TopLeptonic>();
    //     Run<standardmodel::tagger::WHadronic>();
    //     Run<standardmodel::tagger::TopHadronic>();    Run<standardmodel::tagger::Higgs>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::TopLeptonicPairTagger>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::SignatureTagger>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::tagger::Global>(boca::Output::significance);
    Run<higgscpv::tagger::SignatureT>(boca::Output::efficiency);
    Run<higgscpv::tagger::EventT>(boca::Output::efficiency);
    //     Run<higgscpv::tagger::SignatureLepton>(boca::Output::efficiency);
    Run<higgscpv::tagger::SignatureLeptonT>(boca::Output::efficiency);
    Run<higgscpv::tagger::EventLeptonT>(boca::Output::significance);
}

