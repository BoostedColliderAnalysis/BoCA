#include "boca/exroot/Classes.hh"
#include "boca/exroot/Hadrons.hh"
#include "boca/generic/DEBUG.hh"

namespace boca
{

namespace exroot
{

Hadrons::Hadrons(boca::TreeReader const& tree_reader) :
    boca::Hadrons(tree_reader) {}

std::vector<Jet> Hadrons::Jets() const
{
    INFO0;
    std::vector<Jet> jets;
    for (auto const & exroot_jet : TreeReader().Array<::exroot::Jet>(Branch::jet)) {
        Jet jet(exroot_jet);
        jet.Info().SetBTag(exroot_jet.BTag);
        jets.emplace_back(jet);
    }
    return jets;
}

}

}
