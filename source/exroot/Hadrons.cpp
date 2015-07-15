#include "exroot/Hadrons.hh"
#include "Debug.hh"
#include "JetInfo.hh"

namespace analysis
{

namespace exroot
{

Jets Hadrons::Jets() const
{
    Info(clones_arrays().JetSum());
    analysis::Jets jets;
    for (const int jet_number : Range(clones_arrays().JetSum())) {
        ::exroot::Jet &jet = static_cast<::exroot::Jet &>(clones_arrays().Jet(jet_number));
        fastjet::PseudoJet pseudo_jet = PseudoJet(jet);
        pseudo_jet.set_user_info(new JetInfo(bool(jet.BTag)));
        jets.emplace_back(pseudo_jet);
    }
    return jets;
}

}

}
