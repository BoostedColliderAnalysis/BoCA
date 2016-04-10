/**
 * Copyright (C) 2015-2016 Jan Hajer
 */

#include "external/Invisible2.hh"
#include "multiplets/Quartet.hh"
#include "WimpMass.hh"
#include "generic/DEBUG.hh"

namespace boca
{

std::vector<boca::Sextet> WimpMass::Sextets(std::vector<Quartet22> const& quartets, Jet const& missing_et)
{
    std::vector<boca::Sextet> sextets;
    for (auto const & quartet : quartets) Insert(sextets, Sextets(quartet, missing_et));
    return sextets;
}

std::vector<boca::Sextet> WimpMass::Sextets(Quartet22 const& quartet, Jet const& missing_et)
{
    INFO0;
    wimpmass::Invisible22 invisible(quartet, missing_et.Vector());
    std::vector<boca::Sextet> sextets;
    for (auto const & solution: invisible.Solve(MassOf(Id::top), MassOf(Id::W), MassOf(MultiId::neutrino))){
        boca::Sextet sextet(Triplet(Doublet(quartet.Doublet1().Singlet2(), solution.first), quartet.Doublet1().Singlet1()), Triplet(Doublet(quartet.Doublet2().Singlet2(), solution.second), quartet.Doublet2().Singlet1()));
        sextet.Triplet1().SetBdt(quartet.Doublet1().Bdt());
        sextet.Triplet2().SetBdt(quartet.Doublet2().Bdt());
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);
    }
    if (sextets.size() == 0) sextets.emplace_back(Fake(quartet));
    return sextets;
}

std::vector<boca::Sextet> WimpMass::Sextet(Quartet22 const& quartet, Jet const& missing_et, std::vector<Particle> const& neutrinos, Tag tag)
{
    INFO0;
    std::map<Mass, boca::Sextet> map;
    for (auto const & sextet : Sextets(quartet, missing_et)) {
        Jet neutrino_1 = sextet.Triplet1().Doublet().Singlet2();
        Jet neutrino_2 = sextet.Triplet2().Doublet().Singlet2();
        std::vector<Mass> errors_1, errors_2;
        for (auto const & neutrino : neutrinos) {
            errors_1.emplace_back(Particle(neutrino + Particle(neutrino_1)).Mass());
            errors_2.emplace_back(Particle(neutrino + Particle(neutrino_2)).Mass());
        }
        Mass error = std::numeric_limits<Mass>::max();
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
    return Transform(map,[](std::pair<Mass, boca::Sextet> const& pair){
      return pair.second;
    });
}

Sextet WimpMass::Fake(Quartet22 const& quartet) const
{
    boca::Sextet sextet;
    sextet.Enforce(quartet);
    return sextet;
}

}
