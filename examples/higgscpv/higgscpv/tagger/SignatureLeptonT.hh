#pragma once

#include "standardmodel/tagger/Higgs.hh"
#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Octet.hh"

#include "higgscpv/MultipletSignature.hh"
#include "higgscpv/tagger/TopLeptonicPair.hh"
#include "higgscpv/branch/SignatureLeptonT.hh"

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

    MultipletSignature<Octet332> Signature(boca::Jet const& triplet_1, boca::Jet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

};

}

}
