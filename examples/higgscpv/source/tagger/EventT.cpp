#include "include/tagger/EventT.hh"
#include "boca/generic/DEBUG.hh"

namespace higgscpv
{

namespace tagger
{

int EventT::Train(boca::Event const& event, boca::PreCuts const&, Tag tag)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_reader_.Multiplets(event);
    INFO(octets.size());
    std::vector<MultipletEvent<Octet332>> multipletevents;
    for (auto const & octet : octets) {
        MultipletEvent<Octet332> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
//     return SaveEntries(multipletevents, 1); //FIXME reanble this
}

std::vector<MultipletEvent<Octet332>> EventT::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_reader_.Multiplets(event);
    std::vector<MultipletEvent<Octet332>> multiplet_events;
    for (auto const & octet : octets) {
        MultipletEvent<Octet332> multiplet_event(octet.Multiplet(), event, jets);
        //         multiplet_event.SetBdt(Bdt(multiplet_event, reader)); //FIXME reanble this
        multiplet_events.emplace_back(multiplet_event);
    }
    //     return ReduceResult(multiplet_events,1); //FIXME reanble this
}

std::string EventT::Name() const
{
    return "EventTChannel";
}

}

}
