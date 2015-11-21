#include "exroot/ExRootAnalysis.hh"
#include "exroot/Hadrons.hh"
#include "Debug.hh"
#include "JetInfo.hh"

namespace boca {

namespace exroot {

 std::vector<Jet> Hadrons::Jets() const
{
    Info0;
    std::vector<Jet> jets;
    for (auto const& exroot_jet : tree_reader().Objects<::exroot::Jet>(Branch::jet)) {
        Jet jet(exroot_jet);
        jet.Info().SetBTag(exroot_jet.BTag);
        jets.emplace_back(jet);
    }
    return jets;
}

}

}
