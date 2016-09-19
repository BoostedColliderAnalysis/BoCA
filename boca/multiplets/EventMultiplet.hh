/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/multiplets/Global.hh"
#include "boca/multiplets/TwoBody.hh"

namespace boca
{

/**
 * @brief An event composed of a multiplet an a singlet made up from the remaining jets
 *
 */
template <typename Multiplet_>
class EventMultiplet : public boca::TwoBody<Multiplet_, boca::Global>
{

public:

    using TwoBody<Multiplet_, boca::Global>::TwoBody;

    EventMultiplet(Multiplet_ const& multiplet_, Event const& event) :
        TwoBody<Multiplet_, boca::Global>::TwoBody(multiplet_, boca::Global(event)) {};


    EventMultiplet(Multiplet_ const& multiplet_, Event const& event, std::vector<Jet> const& jets) :
        TwoBody<Multiplet_, boca::Global>::TwoBody(multiplet_, boca::Global(event, jets)) {};

    Multiplet_ const& Signature() const {
        return boca::TwoBody<Multiplet_, boca::Global>::Multiplet1();
    }

    boca::Global const& Global() const {
        return boca::TwoBody<Multiplet_, boca::Global>::Multiplet2();
    }
};

}


