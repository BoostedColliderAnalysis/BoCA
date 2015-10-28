/**
 * Copyright (C) 2015 Jan Hajer
 */
#include "SignatureSingleHadronicTagger.hh"
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace naturalness
{

int SignatureSingleHadronicTagger::Train(Event const& event, PreCuts const& , Tag tag) const
{
    Info();
    return SaveEntries(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetTag(tag);
        return decuplet;
    }), tag);
}

std::vector<Decuplet532> SignatureSingleHadronicTagger::Multiplets(Event const& event, boca::PreCuts const& , TMVA::Reader const& reader) const
{
    Info();
    return ReduceResult(Decuplets(event, [&](Decuplet532 & decuplet) {
        decuplet.SetBdt(Bdt(decuplet, reader));
        return decuplet;
    }), 1);
}

std::vector<Decuplet532> SignatureSingleHadronicTagger::Decuplets(Event const& event, std::function<Decuplet532(Decuplet532&)> const& function) const
{
    Info();
    std::vector<Triplet> triplets = top_reader_.Multiplets(event);
    std::vector<Quintet> quintets = partner_reader_.Multiplets(event);
    std::vector<Decuplet532> decuplets;
    for (auto const & doublet : higgs_reader_.Multiplets(event)) {
        for (auto const & triplet : triplets) {
            Quintet veto(triplet, doublet);
            if (veto.Overlap()) continue;
            float veto_bdt = veto_reader_.Bdt(veto);
            for (auto const & quintet : quintets) {
                Decuplet532 decuplet(quintet, triplet, doublet);
                if (decuplet.Overlap()) continue;
                decuplet.SetVetoBdt(veto_bdt);
                decuplets.emplace_back(function(decuplet));
            }
        }
    }
    Debug(decuplets.size());
    return decuplets;
}

std::string SignatureSingleHadronicTagger::Name() const
{
    return "SignatureSingleHadronic";
}

std::string SignatureSingleHadronicTagger::NiceName() const
{
    return "T_{h}t_{l}h";
}

}

}
