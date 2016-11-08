/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "standardmodel/tagger/Event.hh"

#include "toppartner/tagger/SignatureEffective.hh"

namespace toppartner
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffective : public standardmodel::tagger::Event<SignatureEffective, Quattuordecuplet554, boca::branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
