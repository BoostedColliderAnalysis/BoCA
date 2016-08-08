#include "boca/Event.hh"
#include "boca/generic/Exception.hh"
#include "boca/multiplets/Particles.hh"

#include "include/tagger/SignatureLepton.hh"

// #define DEBUGGING
#include "boca/generic/DEBUG.hh"

namespace higgscpv
{

namespace tagger
{

int SignatureLepton::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto leptons = event.Leptons();
    if (leptons.size() < 2) return 0;
    auto particles = event.GenParticles();
    auto lepton_particle = CopyIfParticles(particles, {Id::electron, Id::muon});
//     ERROR(lepton_particle);
    lepton_particle = CopyIfGrandMother(lepton_particle, Id::top);
//     ERROR(lepton_particle);
    auto final_leptons = CopyIfClose(leptons, lepton_particle);
//     ERROR(final_leptons);
    auto doublets = higgs_reader_.Multiplets(event);
    auto higgses = CopyIfParticles(particles, {Id::higgs, Id::CP_violating_higgs});
    auto final_doublets = BestMatches(doublets, higgses, tag);

    auto quartets = Triples(final_leptons, final_doublets, [&](Singlet const & singlet_1, Singlet const & singlet_2, Doublet const & doublet) {
        MultipletSignature<Quartet211> quartet = Signature(doublet, singlet_1, singlet_2);
        quartet.SetTag(tag);
        return quartet;
    });
    DEBUG(quartets.size());
    if (tag == Tag::signal) quartets = ReduceResult(quartets, 1);
    DEBUG(quartets.size());
    return  SaveEntries(quartets);
}

std::vector<MultipletSignature<Quartet211>> SignatureLepton::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto leptons = event.Leptons();
    if (leptons.size() < 2) return {};
    auto doublets = higgs_reader_.Multiplets(event);
    INFO(doublets.size());
    auto quartets = Triples(leptons, doublets, [&](Singlet const & singlet_1, Singlet const & singlet_2, Doublet const & doublet) {
        MultipletSignature<Quartet211> quartet = Signature(doublet, singlet_1, singlet_2);
        quartet.SetBdt(Bdt(quartet, reader));
        return quartet;
    });
    return ReduceResult(quartets);
}

MultipletSignature<Quartet211> SignatureLepton::Signature(Doublet const& doublet, Singlet const& singlet_1, Singlet const& singlet_2) const
{
    Quartet211 quartet;
    if (boca::Jet(doublet.Jet() + singlet_1.Jet()).Mass() > boca::Jet(doublet.Jet() + singlet_2.Jet()).Mass()) quartet.SetMultiplets(doublet, singlet_1, singlet_2);
    else quartet.SetMultiplets(doublet, singlet_2, singlet_1);
    if (quartet.Overlap()) throw Overlap();
    return MultipletSignature<Quartet211>(quartet);
}
std::string SignatureLepton::Name() const
{
    return "Leptons";
}

}

}
