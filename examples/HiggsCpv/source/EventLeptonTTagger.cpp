#include "boca/EventLeptonTTagger.hh"
#include "boca/multiplets/Particles.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace higgscpv
{

int EventLeptonTTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
   std::vector<Particle> particles = event.GenParticles();
   std::vector<Particle> higgses = CopyIfParticles(particles, {Id::higgs, Id::CP_violating_higgs});
   std::vector<Particle> leptons = signature_reader_.Tagger().Leptons(event);

    std::vector<MultipletSignature<Octet332>> final_octets;
    if (tag == Tag::signal) {
        for (auto const & octet : octets) {
            int match = 0;
            for (auto const & lepton : leptons) {
                if (Close<Particle>(lepton)(octet.Multiplet().Triplet1())) match |= 1 << 0;
                if (Close<Particle>(lepton)(octet.Multiplet().Triplet2())) match |= 1 << 1;
            }
            for (auto const & higgs : higgses) if (Close<Particle>(higgs)(octet.Multiplet().Doublet())) match |= 1 << 2;
            if (match == 7) final_octets.emplace_back(octet);
        }
    } else final_octets = octets;

    INFO(final_octets.size());
    std::vector<MultipletEvent<Octet332>> multipletevents;
    for (auto const & octet : final_octets) {
        MultipletEvent<Octet332> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(multipletevents, 1);
}

std::vector<MultipletEvent<Octet332>> EventLeptonTTagger::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
   std::vector<Jet> jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet332>> multiplet_events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet332> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events,1);
}

std::string EventLeptonTTagger::Name() const
{
    return "EventLeptonTChannel";
}

}

}
