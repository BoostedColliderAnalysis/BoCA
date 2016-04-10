#include "../include/SignatureLeptonTagger.hh"
#include "Event.hh"
#include "generic/Exception.hh"
// #define DEBUGGING
#include "generic/DEBUG.hh"

namespace boca
{

namespace higgscpv
{

int SignatureLeptonTagger::Train(Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
   std::vector<Lepton> leptons = event.Leptons().leptons();
    if (leptons.size() < 2) return 0;
   std::vector<Particle> particles = event.Partons().GenParticles();
   std::vector<Particle> lepton_particle = CopyIfParticles(particles, {Id::electron, Id::muon});
//     ERROR(lepton_particle);
    lepton_particle = CopyIfGrandMother(lepton_particle, Id::top);
//     ERROR(lepton_particle);
    std::vector<Lepton> final_leptons = CopyIfClose(leptons, lepton_particle);
//     ERROR(final_leptons);
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    std::vector<Particle> higgses = CopyIfParticles(particles, {Id::higgs, Id::CP_violating_higgs});
    std::vector<Doublet> final_doublets = BestMatches(doublets, higgses, tag);

    std::vector<MultipletSignature<Quartet211>> quartets = Triples(final_leptons, final_doublets, [&](Singlet const& singlet_1, Singlet const& singlet_2, Doublet const& doublet) {
        MultipletSignature<Quartet211> quartet = Signature(doublet, singlet_1, singlet_2);
        quartet.SetTag(tag);
        return quartet;
    });
    DEBUG(quartets.size());
    if (tag == Tag::signal) quartets = ReduceResult(quartets, 1);
    DEBUG(quartets.size());
    return  SaveEntries(quartets);
}

std::vector<MultipletSignature<Quartet211>> SignatureLeptonTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
   std::vector<Lepton> leptons = event.Leptons().leptons();
    if (leptons.size() < 2) return {};
    std::vector<Doublet> doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    std::vector<MultipletSignature<Quartet211>> quartets = Triples(leptons, doublets, [&](Singlet const& singlet_1, Singlet const& singlet_2, Doublet const& doublet) {
        MultipletSignature<Quartet211> quartet = Signature(doublet, singlet_1, singlet_2);
        quartet.SetBdt(Bdt(quartet, reader));
        return quartet;
    });
    return ReduceResult(quartets);
}

MultipletSignature<Quartet211> SignatureLeptonTagger::Signature(Doublet const& doublet, Singlet const& singlet_1, Singlet const& singlet_2) const
{
    Quartet211 quartet;
    if ((doublet.Jet() + singlet_1.Jet()).Mass() > (doublet.Jet() + singlet_2.Jet()).Mass()) quartet.SetMultiplets(doublet, singlet_1, singlet_2);
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
