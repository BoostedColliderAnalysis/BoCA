#include "CutTagger.hh"
#include "Event.hh"
#include "boost/range.hpp"
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptors.hpp>
// #define INFORMATION
#include "Debug.hh"

namespace boca
{

namespace heavyhiggs
{

int CutTagger::Train(Event const& event, PreCuts const&, Tag) const
{
    Info0;
    std::vector<CutPlet> octets;
    if (boost::optional<CutPlet> optional = CutMethod(event)) octets.emplace_back(*optional);
    return SaveEntries(octets);
}

std::vector<CutPlet> CutTagger::Multiplets(Event const& event, PreCuts const&, TMVA::Reader const& reader) const
{
    Info0;
    std::vector<CutPlet> octets;
    if (boost::optional<CutPlet> optional = CutMethod(event)) octets.emplace_back(*optional);
    for (auto & octet : octets) octet.SetPassed(Cuts(octet, reader));
    return ReduceResult(octets);
}

boost::optional<CutPlet> CutTagger::CutMethod(Event const& event) const
{
    Info0;
    CutPlet cut_plet;

    std::vector<Lepton> leptons = event.Leptons().leptons();

    for (auto const & lepton : leptons) if (lepton.Pt() < 10. * GeV) Error(lepton.Pt());

    if (leptons.size() > 2) return boost::none;

    leptons = RemoveIfSoft(leptons, 15. * GeV);

    std::vector<Lepton> positive;
    boost::range::copy(leptons | boost::adaptors::filtered([](Jet const & jet_1) {
        return jet_1.Info().Charge() > 0;
    }), std::back_inserter(positive));
    positive = SortedByPt(positive);

    std::vector<Lepton> negative;
    boost::range::copy(leptons | boost::adaptors::filtered([](Jet const & jet_1) {
        return jet_1.Info().Charge() < 0;
    }), std::back_inserter(negative));
    negative = SortedByPt(negative);

    if (positive.size() < 2 && negative.size() < 2) return boost::none;

    std::vector<Jet> jets = event.Hadrons().Jets();
    if (jets.size() < 4) return boost::none;
    cut_plet.jet_number_ = jets.size();

    std::vector<Jet> bottoms;
    boost::range::copy(jets | boost::adaptors::filtered([](Jet const & jet) {
        return jet.Info().BTag();
    }), std::back_inserter(bottoms));
    if (bottoms.size() < 4) return boost::none;
    cut_plet.bottom_number_ = bottoms.size();

    boca::MissingEt missing_et = event.Hadrons().MissingEt();
    if (missing_et.Pt() < 30. * GeV) return boost::none;
    cut_plet.et_miss_ = missing_et.Pt();

    Momentum scalar_ht = event.Hadrons().ScalarHt();
    cut_plet.ht_ = scalar_ht;

    if (cut_plet.IsNaN()) return boost::none;
    return cut_plet;
}

std::string CutTagger::Name() const
{
    return "Cut";
}

}

}
