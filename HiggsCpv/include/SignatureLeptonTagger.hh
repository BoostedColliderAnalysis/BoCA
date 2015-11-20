#pragma once

#include "MultipletSignature.hh"
#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "Octet.hh"

namespace analysis
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

    SignatureLeptonTagger();

    int Train(const Event& event, const analysis::PreCuts&, Tag tag) const override;

    std::vector< MultipletSignature< Quartet211 > > Multiplets(const analysis::Event& event, const analysis::PreCuts&, const TMVA::Reader& reader) const;

    int GetBdt(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const final {
      return SaveEntries(Multiplets(event, pre_cuts, reader), 1);
    }

    auto Multiplets(const Event& event, const TMVA::Reader& reader) {
        PreCuts pre_cuts;
        return Multiplets(event, pre_cuts, reader);
    }

    std::string Name() const final {
        return "Leptons";
    }

private:

    MultipletSignature<Quartet211> Signature(const analysis::Doublet& doublet, const analysis::Singlet& singlet_1, const analysis::Singlet& singlet_2) const;

    Reader<HiggsTagger> higgs_reader_;

};

}

}
