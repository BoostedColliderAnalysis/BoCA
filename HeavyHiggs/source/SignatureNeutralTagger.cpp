#include "SignatureNeutralTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace analysis {

namespace heavyhiggs {

SignatureNeutralTagger::SignatureNeutralTagger()
{
    Note();
    DefineVariables();
}

int SignatureNeutralTagger::Train(const Event& event, const PreCuts&, Tag tag) const
{
    Info();
    Jets higgs = heavy_higgs_semi_reader_.Tagger().HiggsParticle(event, tag);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    sextets = BestMatches(sextets, higgs, tag);
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    Jets bottoms = fastjet::sorted_by_pt(jet_pair_reader_.Tagger().BottomPair(event, tag));
    std::vector<Doublet> final_doublets;
    switch (tag) {
    case Tag::signal :
        if (bottoms.size() == 2) {
            for (const auto& doublet : doublets) {
                if ((Close(bottoms.at(0))(doublet.Singlet1().Jet()) && Close(bottoms.at(1))(doublet.Singlet2().Jet())) || (Close(bottoms.at(1))(doublet.Singlet1().Jet()) && Close(bottoms.at(0))(doublet.Singlet2().Jet()))) final_doublets.emplace_back(doublet);
            }
        }
        break;
    case Tag::background :
        final_doublets = doublets;
        break;
    }
    std::vector<Octet62> octets;
    for (const auto& doublet : final_doublets) {
        for (const auto& sextet : sextets) {
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
//     Error(octets.size(), doublets.size(), sextets.size());

    return SaveEntries(octets);
}


std::vector<Octet62> SignatureNeutralTagger::Multiplets(const Event& event, const PreCuts&, const TMVA::Reader& reader) const
{
    Info();
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    std::vector<Octet62> octets;
    for (const auto& doublet : doublets) {
        for (const auto& sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
//     if(octets.size()==0)Error(octets.size(), doublets.size(), sextets.size());
    return ReduceResult(octets);
}

}

}






