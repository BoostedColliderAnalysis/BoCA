/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "boca/tagger/Event.hh"

#include "include/tagger/SignatureSingleHadronic.hh"
#include "include/branch/Event.hh"

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
class EventSingleHadronic : public boca::tagger::Event<SignatureSingleHadronic, Decuplet532, branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;

};

}

}
