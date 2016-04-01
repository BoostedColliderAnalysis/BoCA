#include "EventSingleLeptonicTagger.hh"
#include "plotting/Font.hh"
#include "generic/DEBUG.hh"

namespace boca {

namespace naturalness {

int EventSingleLeptonicTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
  INFO0;
  return SaveEntries(Events(event, [&](EventMultiplet<Decuplet532>& multiplet_event) {
    multiplet_event.SetTag(tag);
    return multiplet_event;
  }), tag);
}

std::vector<EventMultiplet<Decuplet532>> EventSingleLeptonicTagger::Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const
{
  INFO0;
  return ReduceResult(Events(event, [&](EventMultiplet<Decuplet532>& multiplet_event) {
    multiplet_event.SetBdt(Bdt(multiplet_event, reader));
    return multiplet_event;
  }), 1);
}

std::vector<EventMultiplet<Decuplet532>> EventSingleLeptonicTagger::Events(Event const& event, std::function<EventMultiplet<Decuplet532>(EventMultiplet<Decuplet532> &)> const& function) const
{
  INFO0;
  auto global_observables = global_reader_.Multiplets(event).front();
  std::vector<EventMultiplet<Decuplet532>> events;
  for (auto const & decuplet : signature_reader_.Multiplets(event)) {
    EventMultiplet<Decuplet532> multiplet_event(decuplet, global_observables);
    events.emplace_back(function(multiplet_event));
  }
  return events;
}


std::string EventSingleLeptonicTagger::Name() const
{
    return "EventSingleLep";
}
std::string EventSingleLeptonicTagger::LatexName() const
{
  return Formula("T_{l}t_{h}h");
}

}

}
