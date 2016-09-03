#pragma once

#include "boca/tagger/Event.hh"

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
class EventPair : public boca::tagger::Event<TopPartnerPair, Decuplet55, boca::branch::Event>
{

public:

    std::string Name() const override;

    latex::String LatexName() const override;
};

}

}
