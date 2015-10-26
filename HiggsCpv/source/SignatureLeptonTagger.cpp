#include "../include/SignatureLeptonTagger.hh"
#include "Event.hh"
#include "Exception.hh"
// #define DEBUG
#include "Debug.hh"

namespace boca
{

namespace higgscpv
{

int SignatureLeptonTagger::Train(Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info();
    Jets leptons = event.Leptons().leptons();
    if (leptons.size() < 2) return 0;
    Jets particles = event.Partons().GenParticles();
    Jets lepton_particle = CopyIfParticles(particles, Id::electron, Id::muon);
//     Error(lepton_particle);
    lepton_particle = CopyIfGrandMother(lepton_particle, Id::top);
//     Error(lepton_particle);
    Jets final_leptons = CopyIfClose(leptons, lepton_particle);
//     Error(final_leptons);
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
    std::vector<Doublet> final_doublets = BestMatches(doublets, higgses, tag);

    std::vector<MultipletSignature<Quartet211>> quartets = triples(final_leptons, final_doublets, [&](auto const& singlet_1, auto const& singlet_2, auto const& doublet) {
        MultipletSignature<Quartet211> quartet = Signature(doublet, singlet_1, singlet_2);
        quartet.SetTag(tag);
        return quartet;
    });
    Debug(quartets.size());
    if (tag == Tag::signal) quartets = ReduceResult(quartets, 1);
    Debug(quartets.size());
    return  SaveEntries(quartets);
}

std::vector<MultipletSignature<Quartet211>> SignatureLeptonTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info();
    Jets leptons = event.Leptons().leptons();
    if (leptons.size() < 2) return {};
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    Info(doublets.size());
    std::vector<MultipletSignature<Quartet211>> quartets = triples(leptons, doublets, [&](auto const& singlet_1, auto const& singlet_2, auto const& doublet) {
        MultipletSignature<Quartet211> quartet = Signature(doublet, singlet_1, singlet_2);
        quartet.SetBdt(Bdt(quartet, reader));
        return quartet;
    });
    return ReduceResult(quartets);
}

MultipletSignature<Quartet211> SignatureLeptonTagger::Signature(Doublet const& doublet, Singlet const& singlet_1, Singlet const& singlet_2) const
{
    Quartet211 quartet;
    if ((doublet.Jet() + singlet_1.Jet()).m() > (doublet.Jet() + singlet_2.Jet()).m()) quartet.SetMultiplets(doublet, singlet_1, singlet_2);
    else quartet.SetMultiplets(doublet, singlet_2, singlet_1);
    if (quartet.Overlap()) throw Overlap();
    return MultipletSignature<Quartet211>(quartet);
}
std::string SignatureLeptonTagger::Name() const
{
    return "Leptons";
}

}

}
