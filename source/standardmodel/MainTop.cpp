#include "boca/standardmodel/AnalysisTop.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/standardmodel/tagger/TopHadronic.hh"
#include "boca/standardmodel/TopHadronicHep.hh"
#include "boca/standardmodel/TopHadronicHep2.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::standardmodel::TopAnalysis<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    switch (boca::standardmodel::TopAnalysis<boca::standardmodel::tagger::Bottom>::TopDecay()) {
    case boca::Decay::leptonic :
        Run<boca::standardmodel::tagger::Bottom>() ;
        Run<boca::standardmodel::tagger::WLeptonic>();
        Run<boca::standardmodel::tagger::TopLeptonic>(boca::Output::efficiency | boca::Output::plot);
        break;
    case boca::Decay::hadronic :
        switch (boca::standardmodel::TopAnalysis<boca::standardmodel::tagger::Bottom>::TopTagger()) {
        case boca::standardmodel::TopTagger::boca :
            Run<boca::standardmodel::tagger::Bottom>() ;
            Run<boca::standardmodel::tagger::WHadronic>();
            Run<boca::standardmodel::tagger::TopHadronic>(boca::Output::efficiency | boca::Output::plot);
            break;
        case boca::standardmodel::TopTagger::hep :
            Run<boca::standardmodel::TopHadronicHep>(boca::Output::efficiency | boca::Output::plot);
            break;
        case boca::standardmodel::TopTagger::hep2 :
            Run<boca::standardmodel::TopHadronicHep2>(boca::Output::efficiency | boca::Output::plot);
            break;
        }
    }
}

