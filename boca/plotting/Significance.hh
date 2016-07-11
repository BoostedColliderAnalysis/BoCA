/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/generic/Flag.hh"
#include "boca/latex/String.hh"

namespace boca
{

enum class Significance
{
    none = 0,
    experimental = 1 << 0, //< experimental error $s/b$
    sum = 1 << 1, //< simple significance estimator $s / sqrt b$
    background = 1 << 2, //< slighly more complicated estimator for significance $s/sqrt{s+b}$
    poisson = 1 << 3, //< poisson estimator for significance $sqrt{-2 ln L1 / L 0}$
    discovery = 1 << 4, //< discovery hypothesis and requirement
    exclusion = 1 << 5, //< exclusion hypothesis and requirement
};

std::string Name(Significance significance);

latex::String LatexName(Significance significance);

template<>
struct Flag<Significance> {
    static const bool enable = true;
};

std::vector<Significance> Constrained(std::vector<Significance> const& significances);
std::vector<Significance> Exclusion(std::vector<Significance> const& significances);
std::vector<Significance> Discovery(std::vector<Significance> const& significances);
std::vector<Significance> SignificancesSimple();
std::vector<Significance> SignificancesBase();
std::vector<Significance> SignificancesMD();
std::vector<Significance> SignificancesMI();
std::vector<Significance> Significances();

}
