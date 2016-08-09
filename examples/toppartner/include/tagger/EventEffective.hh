/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/tagger/Event.hh"
#include "include/tagger/SignatureEffective.hh"

namespace toppartner
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventEffective : public boca::tagger::Event<SignatureEffective, Quattuordecuplet554>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
