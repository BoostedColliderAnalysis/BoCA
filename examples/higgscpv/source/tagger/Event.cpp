#include "boca/../boca/GlobalTagger.hh"
#include "boca/generic/DEBUG.hh"

namespace higgscpv
{

namespace tagger
{

int Global::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_reader_.Multiplets(event);
    INFO(octets.size());
    std::vector<MultipletEvent<Octet62>> multipletevents;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(multipletevents, 1);
}

std::vector<MultipletEvent<Octet62>> Global::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet62>> multiplet_events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet62> multiplet_event(octet.Multiplet(), event, jets);
        multiplet_event.SetBdt(Bdt(multiplet_event, reader));
        multiplet_events.emplace_back(multiplet_event);
    }
    return ReduceResult(multiplet_events, 1);
}
std::string Global::Name() const
{
    return "Event";
}

}

}
