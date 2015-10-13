#pragma once

#include "MultipletSignature.hh"
#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "Octet.hh"

namespace boca
{

namespace higgscpv
{

/**
 *
 * @brief event BDT for
 *
 */
class SignatureLeptonTagger : public BranchTagger<SignatureLeptonTaggerBranch>
{

public:
  
    int Train(Event const& event, boca::PreCuts const&, Tag tag) const override;

    std::vector< MultipletSignature< Quartet211 > > Multiplets(boca::Event const& event, boca::PreCuts const&, TMVA::Reader const& reader) const;

    int SaveBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(Event const& event, TMVA::Reader const& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "Leptons";
    }

private:

    MultipletSignature<Quartet211> Signature(boca::Doublet const& doublet, boca::Singlet const& singlet_1, boca::Singlet const& singlet_2) const;

    Reader<HiggsTagger> higgs_reader_;

};

}

}
