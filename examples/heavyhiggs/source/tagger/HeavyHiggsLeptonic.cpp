#include "boca/multiplets/WimpMass.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/generic/Types.hh"
#include "boca/event/Event.hh"
#include "boca/fastjet/Particles.hh"

#include "heavyhiggs/tagger/HeavyHiggsLeptonic.hh"

#include "boca/generic/DEBUG_MACROS.hh"

namespace heavyhiggs {

namespace tagger {

int HeavyHiggsLeptonic::Train(boca::Event const& event, PreCuts const&, Tag tag)
{
    INFO0;
    auto triplets = top_leptonic_reader_.Multiplets(event);
    auto missing_et = event.MissingEt();
    auto particles = event.GenParticles();
    auto neutrinos = CopyIfNeutrino(particles);
    INFO(triplets.size());
    std::vector<Sextet33> sextets;
    for (auto const& triplet_1 : triplets) {
        for (auto const& triplet_2 : triplets) {
            Quartet22 quartet(Doublet(triplet_1.Singlet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet(), triplet_2.Doublet().Jet()));
            if (quartet.Overlap()) continue;
            std::vector<Sextet33> Presextets;
            WimpMass wimp_mass;
            Presextets = wimp_mass.Sextet(quartet, missing_et, neutrinos, tag);
            for (auto const& sextet : Presextets) {
                sextets.emplace_back(sextet);
            }
        }
    }
    INFO(sextets.size());
//     if (tag == Tag::signal) sextets = BestMass(sextets, mass);
    return SaveEntries(sextets);
}

std::vector<Sextet33>  HeavyHiggsLeptonic::Multiplets(boca::Event const& event, PreCuts const&, TMVA::Reader const& reader)
{
    INFO0;
    auto triplets = top_leptonic_reader_.Multiplets(event);
    auto missing_et = event.MissingEt();
    std::vector<Sextet33> sextets;
    for (auto const& triplet_1 : triplets) {
        for (auto const& triplet_2 : triplets) {
            Quartet22 quartet(Doublet(triplet_1.Singlet(), triplet_1.Doublet().Jet()), Doublet(triplet_2.Singlet(), triplet_2.Doublet().Jet()));
            if (quartet.Overlap())
                continue;
            std::vector<Sextet33> pre_sextets;
            WimpMass wimp_mass;
            pre_sextets = wimp_mass.Sextets(quartet, missing_et);
            for (auto& sextet : pre_sextets) {
                sextet.SetBdt(Bdt(sextet, reader));
                sextets.emplace_back(sextet);
            }
        }
    }
    return sextets;
}
std::string HeavyHiggsLeptonic::Name() const
{
    return "HeavyHiggsLeptonic";
}

}

}
