/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "boca/generic/Vector.hh"
#include "boca/generic/Types.hh"
#include "boca/plotting/Significance.hh"
// #define INFORMATION
#include "boca/generic/DEBUG.hh"

namespace boca
{

std::vector< Significance > Constrained(std::vector<Significance> const& significances)
{
    INFO0;
    return Transform(significances, [](Significance significance) {
        return significance | Significance::experimental;
    });
}

std::vector< Significance > Exclusion(std::vector<Significance> const& significances)
{
    INFO0;
    return Transform(significances, [](Significance significance) {
        return significance | Significance::exclusion;
    });
}

std::vector< Significance > Discovery(std::vector<Significance> const& significances)
{
    INFO0;
    return Transform(significances, [](Significance significance) {
        return significance | Significance::discovery;
    });
}
std::vector< Significance > SignificancesSimple()
{
    INFO0;
    return {Significance::sum, Significance::background};
}

std::vector< Significance > SignificancesMD()
{
    INFO0;
    return Combine(SignificancesSimple(), Exclusion( {Significance::poisson}), Discovery( {Significance::poisson}));
}

std::vector< Significance > SignificancesBase()
{
    INFO0;
    return Combine(SignificancesSimple(), {Significance::poisson});
}

std::vector< Significance > SignificancesMI()
{
    INFO0;
    return Combine(Exclusion(SignificancesBase()), Discovery(SignificancesBase()));
}

std::vector< Significance > SignificancesMDI()
{
    INFO0;
    return Combine(SignificancesMI(), SignificancesSimple(), {Significance::experimental});
}

std::vector< Significance > Significances()
{
    INFO0;
    return Combine(Constrained(Combine(SignificancesMI(), SignificancesSimple())), SignificancesMDI());
}

std::string Name(Significance significance)
{
    INFO0;
    std::string name;
    FlagSwitch(significance, [&](Significance signific) {
        switch (signific) {
        case Significance::none : name += "None ";
            break;
        case Significance::experimental : name += "Experimental ";
            break;
        case Significance::background : name += "Background ";
            break;
        case Significance::sum : name += "Sum ";
            break;
        case Significance::discovery : name += "Discovery ";
            break;
        case Significance::exclusion : name += "Exclusion ";
            break;
        case Significance::poisson : name += "Poisson ";
            break;
            DEFAULT(to_int(signific));
        }
    });
    return name;
}

latex::String LatexName(Significance significance)
{
    INFO0;
    latex::String name;
    FlagSwitch(significance, [&](Significance signific) {
        switch (signific) {
        case Significance::experimental :
            name += name.empty() ? "" : " and " ;
            name += "\\frac{S}{B}";
            break;
        case Significance::background :
            name += name.empty() ? "" : " and " ;
            name += "\\frac{S}{\\sqrt{B}}";
            break;
        case Significance::sum :
            name += name.empty() ? "" : " and " ;
            name += "\\frac{S}{\\sqrt{S + B}}";
            break;
        case Significance::discovery :
//           name += name.empty() ? "" : " and " ;
            name += "|_{5}";
            break;
        case Significance::exclusion :
//           name += name.empty() ? "" : " and " ;
            name += "|_{2}";
            break;
        case Significance::poisson :
            name += name.empty() ? "" : " and " ;
            name += "\\sqrt{-2ln\\frac{L_{0}}{L_{1}}}";
            break;
            DEFAULT(to_int(signific));
        }
    });
    return name;
}

}

