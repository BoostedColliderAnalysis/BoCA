#pragma once

#include "boca/Signature.hh"

namespace higgscpv {

/**
* @brief %Tagger
*
*/
namespace tagger {

/**
 *
 * @brief Prepares multivariant analysis
 *
 */
class Global : public Tagger<EventMultiplet<Octet62>, Event> {

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector<EventMultiplet<Octet62>> Multiplets(boca::Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    Reader<Signature> signature_reader_;

    Reader<standardmodel::tagger::Bottom> bottom_reader_;

};

}

}
