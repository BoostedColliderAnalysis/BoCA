#pragma once

#include "MultipletSignature.hh"
#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "multiplets/Octet.hh"

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

    int Train(Event const& event, boca::PreCuts const&, Tag tag) const final;

    std::vector< MultipletSignature< Quartet211 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const final;

    std::string Name() const final;

private:

    MultipletSignature<Quartet211> Signature(boca::Doublet const& doublet, boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const;

    Reader<standardmodel::HiggsTagger> higgs_reader_;

};

}

}
