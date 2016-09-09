#pragma once

#include "standardmodel/tagger/Event.hh"

#include "toppartner/tagger/TopPartnerPair.hh"

namespace toppartner
{

namespace tagger
{

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class EventPair : public standardmodel::tagger::Event<TopPartnerPair, Decuplet55, boca::branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;
};

}

}
