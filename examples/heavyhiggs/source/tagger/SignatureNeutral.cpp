#include "boca/Event.hh"
#include "boca/fastjet/Particles.hh"

#include "heavyhiggs/tagger/SignatureNeutral.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs
{

namespace tagger
{

int SignatureNeutral::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto higgs = heavy_higgs_semi_reader_.Tagger().HiggsParticle(event, tag);
    auto sextets = heavy_higgs_semi_reader_.Multiplets(event);
    sextets = BestMatches(sextets, higgs, tag);

    auto doublets = jet_pair_reader_.Multiplets(event);
    auto bottoms = SortedByPt(jet_pair_reader_.Tagger().PairBottomQuarks(event, tag));

    auto particles = event.GenParticles();
    auto tops = CopyIfParticle(particles, Id::top);
    auto tops_even = CopyIfMother(tops, Id::heavy_higgs);
    auto tops_odd = CopyIfMother(tops, Id::CP_odd_higgs);
    auto top_higgs = Combine(tops_even, tops_odd);
    auto one_close_to_top = 0, two_close_to_top = 0;

    if (top_higgs.size() == 2) {

        for (auto const & doublet : doublets) {
            if ((Close<boca::Jet>(top_higgs.at(0))(doublet.Singlet1()) && Close<boca::Jet>(top_higgs.at(1))(doublet.Singlet2())) || (Close<boca::Jet>(top_higgs.at(1))(doublet.Singlet1()) && Close<boca::Jet>(top_higgs.at(0))(doublet.Singlet2()))) two_close_to_top++;
            if ((Close<boca::Jet>(top_higgs.at(0))(doublet.Singlet1()) || Close<boca::Jet>(top_higgs.at(1))(doublet.Singlet2())) || (Close<boca::Jet>(top_higgs.at(1))(doublet.Singlet1()) || Close<boca::Jet>(top_higgs.at(0))(doublet.Singlet2()))) one_close_to_top++;
        }
    }

//     ERROR(one_close_to_top, two_close_to_top);
    static auto close_to_top_ = 0;
    if (one_close_to_top == 6) {
        ++close_to_top_;
    }

    std::vector<Doublet> final_doublets;
    switch (tag) {
    case Tag::signal :
        if (bottoms.size() == 2) {

            for (auto const & doublet : doublets) {
                if ((Close<boca::Jet>(bottoms.at(0))(doublet.Singlet1()) && Close<boca::Jet>(bottoms.at(1))(doublet.Singlet2())) || (Close<boca::Jet>(bottoms.at(1))(doublet.Singlet1()) && Close<boca::Jet>(bottoms.at(0))(doublet.Singlet2()))) final_doublets.emplace_back(doublet);

            }
        } else ERROR(bottoms.size());
        break;
    case Tag::background :
        final_doublets = doublets;
        break;
    }

    static auto zero_doublets = 0;
    if (one_close_to_top < 6 && final_doublets.empty()) {
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
    static auto zero_octets = 0;
    if (one_close_to_top < 6 && !final_doublets.empty() && octets.empty()) {
        ++zero_octets;
    }
//     ERROR(close_to_top_, zero_doublets, zero_octets);

    if (tag == Tag::signal && octets.size() > 1) {
        INFO(octets.size());
        std::sort(octets.begin(), octets.end());
        octets.erase(octets.begin() + 1, octets.end());
    }

    return SaveEntries(octets);
}


std::vector<Octet62> SignatureNeutral::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto doublets = jet_pair_reader_.Multiplets(event);
    auto sextets = heavy_higgs_semi_reader_.Multiplets(event);
    std::vector<Octet62> octets;
    for (auto const & doublet : doublets) {
        for (auto const & sextet : sextets) {
            Octet62 octet(sextet, doublet);
            if (octet.Overlap()) continue;
            octet.SetBdt(Bdt(octet, reader));
            octets.emplace_back(octet);
        }
    }
//     if(octets.size()==0)ERROR(octets.size(), doublets.size(), sextets.size());
    return octets;
}

std::vector<Octet62> SignatureNeutral::CleanOctets(boca::Event const& event, std::vector<Octet62> const& octets, Tag tag) const
{
    std::vector<Octet62> final_octets;
    auto bottoms = jet_pair_reader_.Tagger().PairBottomQuarks(event, tag);
    //   CHECK((tag==Tag::signal && bottoms.size()==2) || (tag==Tag::background && bottoms.size() == 2), bottoms.size());
    auto higgses = heavy_higgs_semi_reader_.Tagger().HiggsParticle(event, tag);
    //   CHECK((tag==Tag::signal && higgses.size()==1) || (tag==Tag::background && higgses.empty()), higgses.size());
    //   ERROR(bottoms.size());
    for (auto const & octet : octets) {
        switch (tag) {
        case Tag::signal : for (const auto & higgs : higgses) if (!Close<boca::Jet>(higgs)(octet.Sextet())) continue;
            break;
        case Tag::background  :
            //         ERROR("What are we doing here?");
            break;
        }
        try {
            auto doublet = jet_pair_reader_.Tagger().TruthDoubletPair(octet.Doublet(), bottoms, tag);
        } catch (char const*) {
            continue;
        }
        final_octets.emplace_back(octet);
    }
    return final_octets;
}

std::string SignatureNeutral::Name() const
{
    return "SignatureNeutral";
}

}

}






