/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "standardmodel/tagger/Event.hh"

#include "toppartner/branch/Event.hh"
#include "toppartner/tagger/SignatureSubDom.hh"

namespace toppartner
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSubDom : public standardmodel::tagger::Event<SignatureSubDom, Duodecuplet552, boca::branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
