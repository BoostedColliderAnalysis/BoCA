/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "CompleteSingleHadronicTagger.hh"
#include "GlobalObservables.hh"
// #define INFORMATION
#include "generic/DEBUG.hh"

namespace boca
{

namespace naturalness
{

int CompleteSingleHadronicTagger::Train(Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    return SaveEntries(Decuplets(event, [&](EventMultiplet<Decuplet532> & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }), tag);
}

std::vector<EventMultiplet<Decuplet532>> CompleteSingleHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Decuplets(event, [&](EventMultiplet<Decuplet532> & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

std::vector<EventMultiplet<Decuplet532>> CompleteSingleHadronicTagger::Decuplets(Event const& event, std::function<EventMultiplet<Decuplet532>(EventMultiplet<Decuplet532>&)> const& function)
{
    INFO0;
    boca::GlobalObservables global_observables(event, bottom_reader_.Jets(event));
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
                decuplet.SetVetoBdt(veto.Bdt());
                EventMultiplet<Decuplet532> event(decuplet, global_observables);
                decuplets.emplace_back(function(event));
            }
        }
    }
    DEBUG(decuplets.size());
    return decuplets;
}

std::string CompleteSingleHadronicTagger::Name() const
{
    return "CompleteSingleHadronic";
}

std::string CompleteSingleHadronicTagger::LatexName() const
{
    return "T_{h}t_{l}h";
}

}

}
