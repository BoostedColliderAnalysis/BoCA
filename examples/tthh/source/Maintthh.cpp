#include "tthh/Analysis.hh"
#include "tthh/tagger/Event.hh"

template<typename Tagger_>
void Run(boca::Output output = boca::Output::normal)
{
    tthh::Analysis<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>();
    Run<standardmodel::tagger::Global>(boca::Output::significance);
//    Run<standardmodel::tagger::WLeptonic>();
//    Run<standardmodel::tagger::WHadronic>();
//    Run<standardmodel::tagger::TopLeptonic>();
//    Run<standardmodel::tagger::TopHadronic>();
//    Run<standardmodel::tagger::Higgs>();
//    Run<tthh::tagger::HiggsSemiLeptonic>(boca::Output::efficiency);
//    Run<tthh::tagger::HiggsToHiggs>(boca::Output::efficiency);
//    Run<tthh::tagger::Signature>(boca::Output::significance);
//    Run<tthh::tagger::Event>(boca::Output::significance);
}
