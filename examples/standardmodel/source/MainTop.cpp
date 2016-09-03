#include "standardmodel/AnalysisTop.hh"
#include "standardmodel/tagger/TopLeptonic.hh"
#include "standardmodel/tagger/TopHadronic.hh"
#include "standardmodel/tagger/TopHadronicHep.hh"
#include "standardmodel/tagger/TopHadronicHep2.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    switch (standardmodel::TopAnalysis<standardmodel::tagger::Bottom>::TopDecay()) {
    case boca::Decay::leptonic :
        Run<standardmodel::tagger::Bottom>() ;
        Run<standardmodel::tagger::WLeptonic>();
        Run<standardmodel::tagger::TopLeptonic>(boca::Output::efficiency | boca::Output::plot);
        break;
    case boca::Decay::hadronic :
        switch (standardmodel::TopAnalysis<standardmodel::tagger::Bottom>::TopTagger()) {
        case standardmodel::TopTagger::boca :
            Run<standardmodel::tagger::Bottom>() ;
            Run<standardmodel::tagger::WHadronic>();
            Run<standardmodel::tagger::TopHadronic>(boca::Output::efficiency | boca::Output::plot);
            break;
        case standardmodel::TopTagger::hep :
            Run<standardmodel::tagger::TopHadronicHep>(boca::Output::efficiency | boca::Output::plot);
            break;
        case standardmodel::TopTagger::hep2 :
            Run<standardmodel::tagger::TopHadronicHep2>(boca::Output::efficiency | boca::Output::plot);
            break;
        }
    }
}

