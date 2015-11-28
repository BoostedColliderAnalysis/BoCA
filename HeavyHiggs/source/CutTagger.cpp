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

std::vector<Lepton> Signed(std::vector<Lepton> leptons, int charge)
{
    std::vector<Lepton> chosen;
    boost::range::copy(leptons | boost::adaptors::filtered([charge](Jet const & jet_1) {
        return sgn(jet_1.Info().Charge()) == sgn(charge);
    }), std::back_inserter(chosen));
    return chosen;
}

std::vector<Lepton> Window(std::vector<Lepton> leptons)
{
    if (leptons.size() < 2) return leptons;
    if (boost::units::abs(Lepton(leptons.at(0) + leptons.at(1)).Mass() - MassOf(Id::Z)) < 10. * GeV) return {};
    return leptons;
}

boost::optional<CutPlet> CutTagger::CutMethod(Event const& event) const
{
    Info0;
    CutPlet cut_plet;

    std::vector<Lepton> electrons = event.Leptons().Electrons();
    std::vector<Lepton> muons = event.Leptons().Muons();
    if (electrons.size() + muons.size() != 2) return boost::none;

    electrons = Window(electrons);

    std::vector<Jet> leptons = RemoveIfSoft(Join(electrons, muons), 15. * GeV);
    if (electrons.size() + muons.size() != 2) return boost::none;

    std::vector<Lepton> positive = Signed(leptons, 1);
    std::vector<Lepton> negative = Signed(leptons, -1);

    if (positive.size() != 2 && negative.size() != 2) return boost::none;

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
