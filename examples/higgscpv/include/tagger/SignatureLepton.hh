#pragma once

#include "boca/MultipletSignature.hh"
#include "boca/standardmodel/tagger/Higgs.hh"
#include "boca/multiplets/Octet.hh"

#include "include/tagger/TopLeptonicPair.hh"
#include "include/branch/SignatureLepton.hh"

namespace higgscpv
{

namespace tagger
{

/**
 *
 * @brief event BDT for
 *
 */
class SignatureLepton : public Tagger<MultipletSignature< Quartet211 >, branch::SignatureLepton>
{

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector< MultipletSignature< Quartet211 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    MultipletSignature<Quartet211> Signature(boca::Doublet const& doublet, boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

};

}

}
