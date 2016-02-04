#include "SignatureEffectiveTagger.hh"
#include "Exception.hh"
#include "plotting/Font.hh"
#include "Debug.hh"

namespace boca {

namespace naturalness {

int SignatureEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Quattuordecuplets(event, [&](Quattuordecuplet554 &quattuordecuplet){
        quattuordecuplet.SetTag(tag);
        return quattuordecuplet;
    }));
}

std::vector<Quattuordecuplet554> SignatureEffectiveTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    return ReduceResult(Quattuordecuplets(event, [&](Quattuordecuplet554 & quattuordecuplet) {
      quattuordecuplet.SetBdt(Bdt(quattuordecuplet, reader));
      return quattuordecuplet;
    }));
}

std::vector<Quattuordecuplet554> SignatureEffectiveTagger::Quattuordecuplets(boca::Event const& event, std::function< Quattuordecuplet554(Quattuordecuplet554&)> const& function) const
{
  return triples(top_partner_hadronic_reader_.Multiplets(event), top_partner_leptonic_reader_.Multiplets(event), higgs_pair_reader_.Multiplets(event), [&](Quintet const & quintet_1, Quintet const & quintet_2, Quartet22 const & quartet) {
    Quattuordecuplet554 quattuordecuplet(quintet_1, quintet_2, quartet);
    if (quattuordecuplet.Overlap()) throw Overlap();
    return function(quattuordecuplet);
  });
}

std::string SignatureEffectiveTagger::Name() const
{
    return "Signature";
}

std::string SignatureEffectiveTagger::LatexName() const
{
    return Formula("T_{h} T_{l} h h");
}

}

}



