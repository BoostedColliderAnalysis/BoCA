#include "boca/AnalysisCharged.hh"
#include "boca/EventChargedTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::fast)
{
    boca::heavyhiggs::AnalysisCharged<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>();
    Run<boca::standardmodel::WHadronicTagger>();
    Run<boca::standardmodel::WLeptonicTagger>();
    Run<boca::standardmodel::TopHadronicTagger>();
    Run<boca::standardmodel::TopLeptonicTagger>();
    Run<boca::heavyhiggs::ChargedHiggsSemiTagger>();
    Run<boca::heavyhiggs::SignatureChargedTagger>();
    Run<boca::heavyhiggs::EventChargedTagger>(boca::Output::significance);
}
