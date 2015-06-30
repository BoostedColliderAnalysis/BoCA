#include "SignatureNeutralTagger.hh"
#include "Debug.hh"

namespace analysis
{

namespace heavyhiggs
{

SignatureNeutralTagger::SignatureNeutralTagger()
{
    //   DebugLevel = Severity::debug;
    Note("Constructor");
    set_tagger_name("SignatureNeutral");
    heavy_higgs_semi_reader_.SetTagger(heavy_higgs_semi_tagger_);
    jet_pair_reader_.SetTagger(jet_pair_tagger_);
    DefineVariables();
}

int SignatureNeutralTagger::Train(Event &event, PreCuts &pre_cuts, const Tag tag)
{
    Info("event Tags");
    float Mass = event.mass();
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);
    if (sextets.empty())Info("No sextets", sextets.size());

    Jets HiggsParticles = event.Partons().GenParticles();
    Jets Even = RemoveIfWrongAbsFamily(HiggsParticles, Id::heavy_higgs, Id::gluon);
    Jets Odd = RemoveIfWrongAbsFamily(HiggsParticles, Id::CP_odd_higgs, Id::gluon);
    HiggsParticles = Even;
    HiggsParticles.insert(HiggsParticles.end(), Odd.begin(), Odd.end());
    fastjet::PseudoJet HiggsBoson;
    if (tag == Tag::signal) {
        if (HiggsParticles.size() == 1) HiggsBoson = HiggsParticles.front();
        else Error("Where is the Higgs?", HiggsParticles.size());
        std::sort(sextets.begin(), sextets.end(), MinDeltaRTo(HiggsParticles.front()));
        if (sextets.size() > 1) sextets.erase(sextets.begin() + 1, sextets.end());
    }

    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets<JetPairTagger>(event);

    std::vector<Doublet> Finaldoublets;
    Jets Particles = event.Partons().GenParticles();
    if (tag == Tag::signal) {
        Particles = RemoveIfWrongAbsFamily(Particles, Id::bottom, Id::gluon);
        if (Particles.size() == 2) {
            for (const auto & doublet : doublets) {
              if ((doublet.SingletJet1().delta_R(Particles.at(0)) < DetectorGeometry().JetConeSize && doublet.SingletJet2().delta_R(Particles.at(1)) < DetectorGeometry().JetConeSize) || (doublet.SingletJet1().delta_R(Particles.at(1)) < DetectorGeometry().JetConeSize && doublet.SingletJet2().delta_R(Particles.at(0)) < DetectorGeometry().JetConeSize)) Finaldoublets.emplace_back(doublet);
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


std::vector<Octet62> SignatureNeutralTagger::Multiplets(Event &event, PreCuts &pre_cuts, const TMVA::Reader &reader)
{
    Info("event Tags");

    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets<JetPairTagger>(event);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets<HeavyHiggsSemiTagger>(event);
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
