/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/multiplets/Global.hh"
#include "toppartner/tagger/CompleteSingleHadronic.hh"
// #define INFORMATION
#include "boca/generic/DEBUG_MACROS.hh"

namespace toppartner
{

namespace tagger
{

int CompleteSingleHadronic::Train(boca::Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    return SaveEntries(Decuplets(event, [&](boca::EventMultiplet<Decuplet532>& decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }), tag);
}

std::vector<EventMultiplet<Decuplet532>> CompleteSingleHadronic::Multiplets(boca::Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Decuplets(event, [&](boca::EventMultiplet<Decuplet532>& decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

std::vector<EventMultiplet<Decuplet532>> CompleteSingleHadronic::Decuplets(boca::Event const& event, std::function<EventMultiplet<Decuplet532>(boca::EventMultiplet<Decuplet532>&)> const& function)
{
    INFO0;
    boca::Global global(event, bottom_reader_.Jets(event));
    auto triplets = top_reader_.Multiplets(event);
    auto quintets = partner_reader_.Multiplets(event);
    std::vector<EventMultiplet<Decuplet532>> decuplets;
    for (auto const & doublet : higgs_reader_.Multiplets(event)) {
        for (auto const & triplet : triplets) {
            Quintet veto(triplet, doublet);
            if (veto.Overlap()) continue;
            veto.SetBdt(veto_reader_.Bdt(veto));
            for (auto const & quintet : quintets) {
                Decuplet532 decuplet(quintet, triplet, doublet);
                if (decuplet.Overlap()) continue;
                decuplet.SetExtraInfo(veto.Bdt());
                EventMultiplet<Decuplet532> event(decuplet, global);
                decuplets.emplace_back(function(event));
            }
        }
    }
    DEBUG(decuplets.size());
    return decuplets;
}

std::string CompleteSingleHadronic::Name() const
{
    return "CompleteSingleHadronic";
}

latex::String CompleteSingleHadronic::LatexName() const
{
    return "T_{h}t_{l}h";
}

}

}
