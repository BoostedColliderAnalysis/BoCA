/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "standardmodel/tagger/Event.hh"

#include "toppartner/tagger/SignatureSingleLeptonic.hh"
#include "toppartner/branch/Event.hh"


namespace toppartner
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleLeptonic : public standardmodel::tagger::Event<SignatureSingleLeptonic, Decuplet532, branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
