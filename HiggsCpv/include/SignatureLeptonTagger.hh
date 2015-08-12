#pragma once

#include "HiggsTagger.hh"
#include "TopLeptonicPairTagger.hh"
#include "MultipletSignature.hh"
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

    int Train(Event const& event, analysis::PreCuts const&, Tag tag) const override;

    std::vector< MultipletSignature< Quartet211 > > Multiplets(analysis::Event const& event, analysis::PreCuts const&, TMVA::Reader const& reader) const;

    int GetBdt(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const final {
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

    MultipletSignature<Quartet211> Signature(analysis::Doublet const& doublet, analysis::Singlet const& singlet_1, analysis::Singlet const& singlet_2) const;

    Reader<HiggsTagger> higgs_reader_;

};

}

}
