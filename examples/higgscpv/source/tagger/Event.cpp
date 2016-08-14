<<<<<<< HEAD
#include "boca/tagger/Global.hh"
#include "boca/generic/DEBUG.hh"
=======
#include "boca/../boca/GlobalTagger.hh"
#include "boca/generic/DEBUG_MACROS.hh"
>>>>>>> afafcdd580b052b73489f960bd21b9a272ac24b6

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
    std::vector<EventMultiplet<Octet62>> multipletevents;
    for (auto const & octet : octets) {
        EventMultiplet<Octet62> multipletevent(octet.Multiplet(), event, jets);
        multipletevent.SetTag(tag);
        multipletevents.emplace_back(multipletevent);
    }
    return SaveEntries(multipletevents, 1);
}

std::vector<EventMultiplet<Octet62>> Global::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto jets = bottom_reader_.Jets(event);
    auto octets = signature_reader_.Multiplets(event);
    std::vector<EventMultiplet<Octet62>> multiplet_events;
    for (auto const & octet : octets) {
        EventMultiplet<Octet62> multiplet_event(octet.Multiplet(), event, jets);
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
