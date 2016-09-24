/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "external/wimpmass/wimpmass/Invisible2.hh"
#include "boca/multiplets/Quartet.hh"
#include "boca/WimpMass.hh"
#include "boca/generic/DEBUG_MACROS.hh"

namespace boca
{

std::vector<boca::Sextet33> WimpMass::Sextets(std::vector<Quartet22> const& quartets, Jet const& missing_et)
{
    auto sextets = std::vector<boca::Sextet33>{};
    for (auto const & quartet : quartets) Insert(sextets, Sextets(quartet, missing_et));
    return sextets;
}

std::vector<boca::Sextet33> WimpMass::Sextets(Quartet22 const& quartet, Jet const& missing_et)
{
    INFO0;
    auto invisible = wimpmass::Invisible22{MassOf(Id::top), MassOf(Id::W), MassOf(MultiId::neutrino)};
    auto sextets = std::vector<boca::Sextet33>{};
    for (auto const & solution: invisible.Solve(quartet, missing_et.LorentzVector())){
        auto sextet = boca::Sextet33{Triplet(Doublet(quartet.Doublet1().Singlet2(), solution.first), quartet.Doublet1().Singlet1()), Triplet(Doublet(quartet.Doublet2().Singlet2(), solution.second), quartet.Doublet2().Singlet1())};
        sextet.Triplet1().SetBdt(quartet.Doublet1().Bdt());
        sextet.Triplet2().SetBdt(quartet.Doublet2().Bdt());
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);
    }
    if (sextets.size() == 0) sextets.emplace_back(Fake(quartet));
    return sextets;
}

std::vector<boca::Sextet33> WimpMass::Sextet(Quartet22 const& quartet, Jet const& missing_et, std::vector<Particle> const& neutrinos, Tag tag)
{
    INFO0;
    auto map = std::map<Mass, boca::Sextet33>{};
    for (auto const & sextet : Sextets(quartet, missing_et)) {
        auto neutrino_1 = sextet.Triplet1().Doublet().Singlet2();
        auto neutrino_2 = sextet.Triplet2().Doublet().Singlet2();
        auto errors_1 = std::vector<Mass>{};
        auto errors_2 = std::vector<Mass>{};
        for (auto const & neutrino : neutrinos) {
            errors_1.emplace_back((neutrino + neutrino_1).Mass());
            errors_2.emplace_back((neutrino + neutrino_2).Mass());
        }
        auto error = std::numeric_limits<Mass>::max();
        for (auto const & error_1 : errors_1)
            for (auto const & error_2 : errors_2) {
                if (Position(errors_1, error_1) == Position(errors_2, error_2)) continue;
                if (error_1 + error_2 < error) error = error_1 + error_2;
            }
        map[error] = sextet;
    }
    if (map.empty()) return {};
    if (tag == Tag::signal) map.erase(std::next(map.begin()), map.end());
    else map.erase(map.begin());
    return Transform(map,[](std::pair<Mass, boca::Sextet33> const& pair){
      return pair.second;
    });
}

Sextet33 WimpMass::Fake(Quartet22 const& quartet) const
{
    auto sextet = boca::Sextet33{};
    sextet.Enforce(quartet);
    return sextet;
}

}
