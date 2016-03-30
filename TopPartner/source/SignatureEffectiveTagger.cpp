#include "SignatureEffectiveTagger.hh"
#include "Exception.hh"
#include "EventShapesOld.hh"
#include "plotting/Font.hh"
#include "DEBUG.hh"

namespace boca
{

namespace naturalness
{

int SignatureEffectiveTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    INFO0;
    return SaveEntries(Quattuordecuplets(event, [&](Quattuordecuplet554 & quattuordecuplet) {
        quattuordecuplet.SetTag(tag);
        return quattuordecuplet;
    }), tag);
}

std::vector<Quattuordecuplet554> SignatureEffectiveTagger::Multiplets(Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
    INFO0;
    return ReduceResult(Quattuordecuplets(event, [&](Quattuordecuplet554 & quattuordecuplet) {
        quattuordecuplet.SetBdt(Bdt(quattuordecuplet, reader));
        return quattuordecuplet;
    }), 1);
}

std::vector<Quattuordecuplet554> SignatureEffectiveTagger::Quattuordecuplets(boca::Event const& event, std::function< Quattuordecuplet554(Quattuordecuplet554&)> const& function) const
{
    INFO0;
    auto hadronic = top_partner_hadronic_reader_.Multiplets(event, 8);
    auto leptonic = top_partner_leptonic_reader_.Multiplets(event, 8);
    auto higgs_pairs = higgs_pair_reader_.Multiplets(event, 8);
    auto signatures = Triples(hadronic, leptonic, higgs_pairs, [&](Quintet const & quintet_1, Quintet const & quintet_2) {
        Decuplet55 decuplet(quintet_1, quintet_2);
        if (decuplet.Overlap()) throw Overlap();
        return decuplet;
    }, [&](Decuplet55 const & decuplet, Quartet22 const & quartet) {
        Quattuordecuplet554 quattuordecuplet;
        quattuordecuplet.SetMultiplets12(decuplet, quartet);
        if (quattuordecuplet.Overlap()) throw Overlap();
        return function(quattuordecuplet);
    });
    static int sig = 0;
    static int eve = 0;
    ++eve;
    if (!signatures.empty()) ++sig;
    double fraction = double(sig) / eve;

    ERROR(signatures.size(), hadronic.size(), leptonic.size(), higgs_pairs.size(), fraction);
    return signatures;
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



