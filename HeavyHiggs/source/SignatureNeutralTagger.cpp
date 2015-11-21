#include "SignatureNeutralTagger.hh"
#include "Event.hh"
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

int SignatureNeutralTagger::Train(Event const& event, PreCuts const&, Tag tag) const
{
    Info0;
    std::vector<Particle> higgs = heavy_higgs_semi_reader_.Tagger().HiggsParticle(event, tag);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    sextets = BestMatches(sextets, higgs, tag);

    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    std::vector<Particle> bottoms = SortedByPt(jet_pair_reader_.Tagger().BottomPair(event, tag));

    std::vector<Particle> particles = event.Partons().GenParticles();
    std::vector<Particle> tops = CopyIfParticle(particles, Id::top);
    std::vector<Particle> tops_even = CopyIfMother(tops, Id::heavy_higgs);
    std::vector<Particle> tops_odd = CopyIfMother(tops, Id::CP_odd_higgs);
    std::vector<Particle> top_higgs = Join(tops_even, tops_odd);
    int  one_close_to_top = 0, two_close_to_top = 0;

    if (top_higgs.size() == 2) {

        for (auto const & doublet : doublets) {
            if ((Close(top_higgs.at(0))(doublet.Singlet1().Jet()) && Close(top_higgs.at(1))(doublet.Singlet2().Jet())) || (Close(top_higgs.at(1))(doublet.Singlet1().Jet()) && Close(top_higgs.at(0))(doublet.Singlet2().Jet()))) two_close_to_top++;
            if ((Close(top_higgs.at(0))(doublet.Singlet1().Jet()) || Close(top_higgs.at(1))(doublet.Singlet2().Jet())) || (Close(top_higgs.at(1))(doublet.Singlet1().Jet()) || Close(top_higgs.at(0))(doublet.Singlet2().Jet()))) one_close_to_top++;
        }
    }

//     Error(one_close_to_top, two_close_to_top);
    static int close_to_top_ = 0;
    if (one_close_to_top == 6) {
        ++close_to_top_;
    }

    std::vector<Doublet> final_doublets;
    switch (tag) {
    case Tag::signal :
        if (bottoms.size() == 2) {

            for (auto const & doublet : doublets) {
                if ((Close(bottoms.at(0))(doublet.Singlet1().Jet()) && Close(bottoms.at(1))(doublet.Singlet2().Jet())) || (Close(bottoms.at(1))(doublet.Singlet1().Jet()) && Close(bottoms.at(0))(doublet.Singlet2().Jet()))) final_doublets.emplace_back(doublet);

            }
        } else Error(bottoms.size());
        break;
    case Tag::background :
        final_doublets = doublets;
        break;
    }

    static int zero_doublets = 0;
    if (one_close_to_top < 6 && final_doublets.size() == 0) {
        ++zero_doublets;
    }

    std::vector<Octet62> octets;
    for (auto const & doublet : final_doublets) {
        for (auto const & sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetTag(tag);
            octets.emplace_back(octet);
        }
    }
    static int zero_octets = 0;
    if (one_close_to_top < 6 && final_doublets.size() > 0 && octets.size() == 0) {
        ++zero_octets;
    }
//     Error(close_to_top_, zero_doublets, zero_octets);

    if (tag == Tag::signal && octets.size() > 1) {
        INFO(octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    return SaveEntries(octets);
}


std::vector<Octet62> SignatureNeutralTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<Doublet> doublets = jet_pair_reader_.Multiplets(event);
    std::vector<Sextet> sextets = heavy_higgs_semi_reader_.Multiplets(event);
    std::vector<Octet62> octets;
    for (auto const & doublet : doublets) {
        for (auto const & sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
//     if(octets.size()==0)Error(octets.size(), doublets.size(), sextets.size());
    return ReduceResult(octets);
}
std::string SignatureNeutralTagger::Name() const
{
    return "SignatureNeutral";
}

}

}






