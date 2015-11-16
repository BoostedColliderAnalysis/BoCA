#include "EventLeptonTTagger.hh"
#include "Debug.hh"

namespace boca
{

namespace higgscpv
{

int EventLeptonTTagger::Train(boca::Event const& event, boca::PreCuts const&, Tag tag) const
{
    Info0;
    Jets jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    Jets particles = event.Partons().GenParticles();
    Jets higgses = CopyIfParticles(particles, Id::higgs, Id::CP_violating_higgs);
    Jets leptons = signature_reader_.Tagger().Leptons(event);

    std::vector<MultipletSignature<Octet332>> final_octets;
    if (tag == Tag::signal) {
        for (auto const & octet : octets) {
            int match = 0;
            for (auto const & lepton : leptons) {
                if (Close(octet.Multiplet().Triplet1().Jet())(lepton)) match |= 1 << 0;
                if (Close(octet.Multiplet().Triplet2().Jet())(lepton)) match |= 1 << 1;
            }
            for (auto const & higgs : higgses) if (Close(octet.Multiplet().Doublet().Jet())(higgs)) match |= 1 << 2;
            if (match == 7) final_octets.emplace_back(octet);
        }
    } else final_octets = octets;

    Info(final_octets.size());
    std::vector<MultipletEvent<Octet332>> multipletevents;
    for (auto const & octet : final_octets) {
        MultipletEvent<Octet332> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(ReduceResult(multipletevents, 1));
}

std::vector<MultipletEvent<Octet332>> EventLeptonTTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    Jets jets = bottom_reader_.Jets(event);
    std::vector<MultipletSignature<Octet332>> octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet332>> multiplet_events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet332> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events);
}
std::string EventLeptonTTagger::Name() const
{
    return "EventLeptonTChannel";
}

}

}
