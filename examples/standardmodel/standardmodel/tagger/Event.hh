#pragma once

#include "boca/multiplets/EventMultiplet.hh"
#include "boca/branch/Event.hh"
#include "standardmodel/tagger/Global.hh"

namespace standardmodel
{

namespace tagger
{

/**
*
* @brief event BDT for semi leptonic heavy higgs
*
*/
template<typename Signature_, typename Multiplet_, typename Branch_>
class Event : public Tagger<EventMultiplet<Multiplet_>, Branch_>
{

  using Tagger_ = Tagger<EventMultiplet<Multiplet_>, Branch_>;

public:

    int Train(boca::Event const& event, PreCuts const& , Tag tag) override {
        return Tagger_::SaveEntries(Events(event, [&](boca::EventMultiplet<Multiplet_>& event_multiplet) {
            event_multiplet.SetTag(tag);
            return event_multiplet;
        }), tag);
    }

    std::vector<EventMultiplet<Multiplet_>> Multiplets(boca::Event const& event, PreCuts const& , TMVA::Reader const& reader) override {
        return Tagger_::ReduceResult(Events(event, [&](boca::EventMultiplet<Multiplet_>& event_multiplet) {
            event_multiplet.SetBdt(Tagger_::Bdt(event_multiplet, reader));
            return event_multiplet;
        }), 1);
    }

    std::string Name() const override {
        return "Event";
    }

protected:

    std::vector<EventMultiplet<Multiplet_>> Events(boca::Event const& event, std::function<EventMultiplet<Multiplet_>(boca::EventMultiplet<Multiplet_> &)> const& function) {
        auto global = global_reader_.Multiplets(event).front();
        std::vector<EventMultiplet<Multiplet_>> events;
        for (auto const & signature : signature_reader_.Multiplets(event)) {
            EventMultiplet<Multiplet_> event_multiplet(signature, global);
            events.emplace_back(function(event_multiplet));
        }
        return events;
    }

private:

    Reader<Signature_> signature_reader_;

    Reader<tagger::Global> global_reader_;

};

}

}
