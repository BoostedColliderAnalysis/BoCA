#pragma once

#include "standardmodel/tagger/Higgs.hh"
#include "standardmodel/tagger/TopLeptonic.hh"
#include "boca/multiplets/Octet.hh"

#include "include/MultipletSignature.hh"
#include "include/branch/SignatureT.hh"

namespace higgscpv
{

namespace tagger
{

/**
 *
 * @brief event BDT for
 *
 */
class SignatureT : public Tagger<MultipletSignature< Octet332 >, branch::SignatureT>
{

public:

    int Train(boca::Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector< MultipletSignature< Octet332 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override {
        return "TChannel";
    }

private:

    MultipletSignature<Octet332> Signature(boca::Triplet const& triplet_1, boca::Triplet const& triplet_2, boca::Doublet const& doublet) const;

    Reader<standardmodel::tagger::Higgs> higgs_reader_;

    Reader<standardmodel::tagger::TopLeptonic> top_reader_;

};

}

}
