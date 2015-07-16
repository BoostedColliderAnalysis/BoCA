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
    Info("event Tags");
    float Mass = event.mass();
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    if (sextets.empty())Info("No sextets", sextets.size());

    Jets HiggsBoson = heavy_higgs_semi_reader_.tagger().Particle_Higgs(event, tag);
    sextets=BestMatches(sextets, HiggsBoson, tag);
    
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);

    std::vector<Doublet> Finaldoublets;
    Jets Particles = jet_pair_reader_.tagger().Particle_2Bottom(event, tag);  //Write a function to get the jet pair
    if (tag == Tag::signal) {
        if (Particles.size() == 2) {
            for (const auto & doublet : doublets) {
              if ((doublet.SingletJet1().delta_R(Particles.at(0)) < DetectorGeometry::JetConeSize() && doublet.SingletJet2().delta_R(Particles.at(1)) < DetectorGeometry::JetConeSize()) || (doublet.SingletJet1().delta_R(Particles.at(1)) < DetectorGeometry::JetConeSize() && doublet.SingletJet2().delta_R(Particles.at(0)) < DetectorGeometry::JetConeSize())) Finaldoublets.emplace_back(doublet);
            }
        }
    }
    if (tag == Tag::background) Finaldoublets = doublets;

    std::vector<Octet62> octets;
    for (const auto & doublet : Finaldoublets) {
        for (const auto & sextet : sextets) {
            if (tag == Tag::signal && sextet.Jet().m() < Mass / 2)continue;
            if (tag == Tag::signal && sextet.Jet().m() > Mass * 3 / 2)continue;
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    if (octets.empty())Info("No octets", octets.size());

    if (tag == Tag::signal && octets.size() > 1) {
        Info("more than one event", octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    return SaveEntries(octets);

}


std::vector<Octet62> SignatureNeutralTagger::Multiplets(const Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader) const
{
    Info("event Tags");

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
