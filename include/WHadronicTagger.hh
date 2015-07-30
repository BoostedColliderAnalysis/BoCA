#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis {

/**
 * @brief W BDT tagger
 *
 */
class WHadronicTagger : public BranchTagger<WHadronicBranch> {

public:

    WHadronicTagger();

    int Train(const Event& event, PreCuts& pre_cuts, const Tag Tag) const;

    virtual int GetBdt(const Event& event, PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::vector<Doublet> Multiplets(const Jets& jets, PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, const TMVA::Reader& reader) const;

    Doublet SubMultiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const;

    int WHadronicId(const Event& event) const;

    std::string Name() const final
    {
        return "WHadronic";
    }

private:

    std::vector<Doublet> Multiplets(const Event& event, PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::vector<Doublet> Multiplets3(const Jets& jets, PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet SubMultiplet(const fastjet::PseudoJet& jet, PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    bool Problematic(const analysis::Doublet& doublet, analysis::PreCuts& pre_cuts, const analysis::Tag tag) const;

    bool Problematic(const analysis::Doublet& doublet, analysis::PreCuts& pre_cuts) const;

    Doublet Multiplet(analysis::Doublet& doublet, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::vector<Doublet> SubMultiplets(const analysis::Jets& jets, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader, const std::size_t sub_jet_number) const;

    std::vector<Doublet> SubMultiplets2(const analysis::Jets& jets, analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Jets WDaughters(const Event& event) const;

    int WHadronicId(const Jets& jets) const;

    float w_mass_window_ = 20;
};

}
