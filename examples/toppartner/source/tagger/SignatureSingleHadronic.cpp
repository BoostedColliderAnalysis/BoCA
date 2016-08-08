/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "include/tagger/SignatureSingleHadronic.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace toppartner
{

namespace tagger
{

int SignatureSingleHadronic::Train(boca::Event const& event, PreCuts const& , Tag tag)
{
    INFO0;
    return SaveEntries(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }), tag);
}

std::vector<Decuplet532> SignatureSingleHadronic::Multiplets(boca::Event const& event, boca::PreCuts const& , TMVA::Reader const& reader)
{
    INFO0;
    return ReduceResult(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

std::vector<Decuplet532> SignatureSingleHadronic::Decuplets(boca::Event const& event, std::function<Decuplet532(Decuplet532&)> const& function)
{
    INFO0;
    auto triplets = top_reader_.Multiplets(event);
    auto quintets = partner_reader_.Multiplets(event);
    std::vector<Decuplet532> decuplets;
    for (auto const & doublet : higgs_reader_.Multiplets(event)) {
        for (auto const & triplet : triplets) {
            Quintet veto(triplet, doublet);
            if (veto.Overlap()) continue;
            veto.SetBdt(veto_reader_.Bdt(veto));
            for (auto const & quintet : quintets) {
                Decuplet532 decuplet(quintet, triplet, doublet);
                if (decuplet.Overlap()) continue;
                decuplet.SetVetoBdt(veto.Bdt());
                decuplets.emplace_back(function(decuplet));
            }
        }
    }
    return decuplets;
}

std::string SignatureSingleHadronic::Name() const
{
    return "SignatureSingleHadronic";
}

latex::String SignatureSingleHadronic::LatexName() const
{
    return "T_{h}t_{l}h";
}

}

}
