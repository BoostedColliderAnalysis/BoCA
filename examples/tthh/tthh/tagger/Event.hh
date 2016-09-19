/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "standardmodel/tagger/Event.hh"

#include "boca/branch/Event.hh"
#include "tthh/tagger/Signature.hh"

namespace tthh
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class Event : public standardmodel::tagger::Event<Signature, Duodecuplet633, boca::branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
