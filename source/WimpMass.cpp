/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "WIMPMASS.h"

#include <map>
#include <boost/range/algorithm/transform.hpp>

#include "multiplets/Quartet.hh"
#include "physics/Math.hh"
#include "WimpMass.hh"
#include "Types.hh"
#include "Vector.hh"
#include "Particle.hh"
#include "DEBUG.hh"

namespace boca
{

namespace
{

void SetMomentum(double momentum[4], Jet const& jet)
{
    momentum[0] = jet.E();
    momentum[1] = jet.px();
    momentum[2] = jet.py();
    momentum[3] = jet.pz();
}

}

std::vector<boca::Sextet> WimpMass::Sextets(std::vector<Quartet22> const& quartets, Jet const& missing_et)
{
    std::vector<boca::Sextet> sextets;
    for (auto const & quartet : quartets) Insert(sextets, Sextets(quartet, missing_et));
    return sextets;
}

std::vector<boca::Sextet> WimpMass::Sextets(Quartet22 const& quartet, Jet const& missing_et)
{
    INFO0;
    event22 structure;
    SetMomentum(structure.p3, quartet.Doublet1().Singlet2());
    SetMomentum(structure.p4, quartet.Doublet2().Singlet2());
    SetMomentum(structure.p5, quartet.Doublet1().Singlet1());
    SetMomentum(structure.p6, quartet.Doublet2().Singlet1());
    SetMomentum(structure.pmiss, missing_et);
    double momentum_1[4][4], momentum_2[4][4];
    int solution_sum;
    solve22(structure, MassOf(Id::electron_neutrino) / GeV, MassOf(Id::W) / GeV, MassOf(Id::top) / GeV, solution_sum, momentum_1, momentum_2);
    DEBUG("Number solutions", solution_sum);
    std::vector<boca::Sextet> sextets;
    for (auto const & solution_number : IntegerRange(solution_sum)) {
        DEBUG("Solution ", solution_number);
        Doublet doublet_1(quartet.Doublet1().Singlet2(), Jet(momentum_1[solution_number]));
        if (doublet_1.Mass() <= massless) continue;
        Doublet doublet_2(quartet.Doublet2().Singlet2(), Jet(momentum_2[solution_number]));
        if (doublet_2.Mass() <= massless) continue;
        Triplet triplet_1(doublet_1, quartet.Doublet1().Singlet1());
        if (triplet_1.Mass() <= massless) continue;
        triplet_1.SetBdt(quartet.Doublet1().Bdt());
        Triplet triplet_2(doublet_2, quartet.Doublet2().Singlet1());
        if (triplet_2.Mass() <= massless) continue;
        triplet_2.SetBdt(quartet.Doublet2().Bdt());
        boca::Sextet sextet(triplet_1, triplet_2);
        if (sextet.Mass() <= massless) continue;
        sextet.SetTag(quartet.Tag());
        sextet.SetBdt(quartet.Bdt());
        sextets.emplace_back(sextet);
        DEBUG("TriplePair Bdt", sextet.Bdt(), quartet.Bdt());
    }
    if (solution_sum == 0) sextets.emplace_back(Fake(quartet));
    return sextets;
}

std::vector<boca::Sextet> WimpMass::Sextet(Quartet22 const& quartet, Jet const& missing_et, std::vector<Particle> const& neutrinos, Tag tag)
{
    INFO0;
    auto sextets = Sextets(quartet, missing_et);
    DEBUG(sextets.size());
    if (sextets.empty()) return sextets;
    for (auto const & neutrino : neutrinos) DEBUG(neutrino);
    DEBUG(missing_et);
    std::map<Mass, boca::Sextet> map;
    for (auto const & sextet : sextets) {
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
        DEBUG(sextet.Bdt());
    }
    for (auto const & pair : map) DEBUG(pair.first);
    if (tag == Tag::signal) map.erase(std::next(map.begin()), map.end());
    else map.erase(map.begin());
    std::vector<boca::Sextet> final_sextets;
    for (auto const & pair : map) final_sextets.emplace_back(pair.second);
    return final_sextets;
}

Sextet WimpMass::Fake(Quartet22 const& quartet) const
{
    boca::Sextet sextet;
    sextet.Enforce(quartet);
    return sextet;
}

}
