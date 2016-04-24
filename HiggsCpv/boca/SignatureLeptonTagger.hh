#pragma once

#include "boca/MultipletSignature.hh"
#include "boca/standardmodel/HiggsTagger.hh"
#include "boca/TopLeptonicPairTagger.hh"
#include "boca/multiplets/Octet.hh"

namespace boca
{

namespace higgscpv
{

/**
 *
 * @brief event BDT for
 *
 */
class SignatureLeptonTagger : public TaggerTemplate<MultipletSignature< Quartet211 >,SignatureLeptonTaggerBranch>
{

public:

    int Train(Event const& event, boca::PreCuts const&, Tag tag) override;

    std::vector< MultipletSignature< Quartet211 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) override;

    std::string Name() const override;

private:

    MultipletSignature<Quartet211> Signature(boca::Doublet const& doublet, boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

};

}

}
