#include "boca/AnalysisFusion.hh"
#include "boca/EventFusionTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::heavyhiggs::AnalysisFusion<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::heavyhiggs::HeavyHiggsSemiTagger>();
    Run<boca::heavyhiggs::EventFusionTagger>(boca::Output::significance);
}
