/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/GlobalObservables.hh"
#include "boca/multiplets/TwoBody.hh"

namespace boca
{

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_>
class EventMultiplet : public boca::TwoBody<Multiplet_, boca::GlobalObservables>
{

public:

    using TwoBody<Multiplet_, boca::GlobalObservables>::TwoBody;

    EventMultiplet(Multiplet_ const& multiplet_, Event const& event) :
        TwoBody<Multiplet_, boca::GlobalObservables>::TwoBody(multiplet_, boca::GlobalObservables(event)) {};


    EventMultiplet(Multiplet_ const& multiplet_, Event const& event, std::vector<Jet> const& jets) :
        TwoBody<Multiplet_, boca::GlobalObservables>::TwoBody(multiplet_, boca::GlobalObservables(event, jets)) {};

    Multiplet_ const& Signature() const {
        return boca::TwoBody<Multiplet_, boca::GlobalObservables>::Multiplet1();
    }

    boca::GlobalObservables const& GlobalObservables() const {
        return boca::TwoBody<Multiplet_, boca::GlobalObservables>::Multiplet2();
    }
};

}


