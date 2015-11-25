#include "AnalysisNeutral.hh"
#include "EventNeutralTagger.hh"

template<typename Tagger>
void Run(boca::Output output = boca::Output::normal)
{
    boca::heavyhiggs::AnalysisNeutral<Tagger> analysis;
    analysis.Run(output);
}

int main()
{
    Run<boca::standardmodel::BottomTagger>(boca::Output::fast);
    Run<boca::standardmodel::WHadronicTagger>(boca::Output::fast);
    Run<boca::standardmodel::WLeptonicTagger>(boca::Output::fast);
    Run<boca::standardmodel::TopHadronicTagger>(boca::Output::fast);
    Run<boca::standardmodel::TopLeptonicTagger>(boca::Output::fast);
    Run<boca::JetPairTagger>(boca::Output::fast);
    Run<boca::heavyhiggs::HeavyHiggsSemiTagger>(boca::Output::fast);
    Run<boca::heavyhiggs::SignatureNeutralTagger>(boca::Output::fast);
    Run<boca::heavyhiggs::EventNeutralTagger>(boca::Output::significance);
}
