#include "SignatureNeutralTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

SignatureNeutralTagger::SignatureNeutralTagger()
{
    Note();
    DefineVariables();
}

int SignatureNeutralTagger::Train(const Event &event, PreCuts &pre_cuts, const Tag tag) const
{
    Info();
    Jets higgs = heavy_higgs_semi_reader_.tagger().HiggsParticle(event, tag);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    sextets = BestMatches(sextets, higgs, tag);

    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    Jets bottoms = jet_pair_reader_.tagger().BottomPair(event, tag);  //Write a function to get the jet pair
    std::vector<Doublet> final_doublets;

    switch (tag) {
    case Tag::signal :
        if (bottoms.size() == 2) {
            for (const auto & doublet : doublets) {
                if ((doublet.SingletJet1().delta_R(Particles.at(0)) < DetectorGeometry::JetConeSize() && doublet.SingletJet2().delta_R(Particles.at(1)) < DetectorGeometry::JetConeSize()) || (doublet.SingletJet1().delta_R(Particles.at(1)) < DetectorGeometry::JetConeSize() && doublet.SingletJet2().delta_R(Particles.at(0)) < DetectorGeometry::JetConeSize())) final_doublets.emplace_back(doublet);
            }
        }
        break;
    case Tag::background :
        final_doublets = doublets;
        break;
    }

    std::vector<Octet62> octets;
    for (const auto & doublet : final_doublets) {
        for (const auto & sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }

    if (tag == Tag::signal && octets.size() > 1) {
        Info(octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }
    return SaveEntries(octets);
}


std::vector<Octet62> SignatureNeutralTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info();
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    std::vector<Octet62> octets;
    for (const auto & doublet : doublets) {
        for (const auto & sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
    return ReduceResult(octets);
}

}

}
