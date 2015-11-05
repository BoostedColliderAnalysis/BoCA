#include "exroot/ExRootAnalysis.hh"
#include "exroot/Hadrons.hh"
#include "Debug.hh"
#include "JetInfo.hh"

namespace boca {

namespace exroot {

Jets Hadrons::Jets() const
{
//     Info(tree_reader().JetSum());
    boca::Jets jets;
    for (auto const& jet : tree_reader().Objects<::exroot::Jet>(Branch::jet)) {
//         ::exroot::Jet& jet = static_cast<::exroot::Jet&>(tree_reader().Jet(jet_number));
        fastjet::PseudoJet pseudo_jet = PseudoJet(jet);
        pseudo_jet.set_user_info(new JetInfo(bool(jet.BTag)));
        jets.emplace_back(pseudo_jet);
    }
    return jets;
}

}

}
