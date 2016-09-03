#include "heavyhiggs/analysis/Neutral.hh"
#include "heavyhiggs/tagger/CutNeutral.hh"

template<typename Tagger_>
void Run(boca::Output output)
{
    heavyhiggs::analysis::Neutral<Tagger_> analysis;
    analysis.Run(output);
}

int main()
{
    Run<standardmodel::tagger::Bottom>(boca::Output::fast);
    Run<heavyhiggs::tagger::CutNeutral>(boca::Output::cut);
}
