/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#include "Hadrons.hh"
#include "Types.hh"
#include "DEBUG.hh"

namespace boca
{

std::string Name(JetDetail jet_detail)
{
    std::string name;
    FlagSwitch(jet_detail, [&](JetDetail jet_detail) {
        switch (jet_detail) {
        case JetDetail::none : name += "None";
            break;
        case JetDetail::plain : name += "Plain";
            break;
        case JetDetail::isolation : name += "Isolation";
            break;
        case JetDetail::structure : name += "Structure";
            break;
            DEFAULT(to_int(jet_detail));
        }
    });
    return name;
}

Hadrons::Hadrons(boca::TreeReader const& tree_reader) :
    FourVector(tree_reader) {}

Momentum Hadrons::ScalarHt() const
{
    ERROR("No Scalar Ht");
    return at_rest;
}

boca::MissingEt Hadrons::MissingEt() const
{
    ERROR("No Mising Et");
    return {};
}

}
