/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "standardmodel/tagger/Event.hh"

#include "toppartner/tagger/SignatureSingleHadronic.hh"
#include "toppartner/branch/Event.hh"

namespace toppartner
{

/**
* @brief %Tagger
*
*/
namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventSingleHadronic : public standardmodel::tagger::Event<SignatureSingleHadronic, Decuplet532, branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
