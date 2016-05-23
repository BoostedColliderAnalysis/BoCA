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
template <typename Multiplet_1>
class EventMultiplet : public boca::TwoBody<Multiplet_1, boca::GlobalObservables>
{

public:

    using TwoBody<Multiplet_1, boca::GlobalObservables>::TwoBody;

    Multiplet_1 const& Signature() const {
        return boca::TwoBody<Multiplet_1, boca::GlobalObservables>::Multiplet1();
    }

    boca::GlobalObservables const& GlobalObservables() const {
        return boca::TwoBody<Multiplet_1, boca::GlobalObservables>::Multiplet2();
    }
};

}


