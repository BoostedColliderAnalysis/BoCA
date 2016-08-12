#pragma once

#include "boca/MultipletSignature.hh"
#include "boca/standardmodel/tagger/Higgs.hh"
#include "boca/standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Octet.hh"

#include "include/tagger/TopLeptonicPair.hh"
#include "include/branch/SignatureLeptonT.hh"

namespace higgscpv
{

namespace tagger
{

/**
 *
 * @brief event BDT for
 *
 */
class SignatureLeptonT : public Tagger<MultipletSignature< Octet332 >, branch::SignatureLeptonT>
{

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector< MultipletSignature< Octet332 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

    std::vector< Particle > Leptons(const boca::Event& event) const;

private:

    MultipletSignature<Octet332> Signature(boca::Triplet const& triplet_1, boca::Triplet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

};

}

}
