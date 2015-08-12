#pragma once

#include "BottomTagger.hh"
#include "Doublet.hh"
#include "Reader.hh"

namespace analysis
{

/**
 * @brief W BDT tagger
 *
 */
class WHadronicTagger : public BranchTagger<WHadronicBranch>
{

public:

    WHadronicTagger();

    int Train(Event const& event, PreCuts const& pre_cuts,
              const Tag Tag) const override;

    virtual int GetBdt(Event const& event, PreCuts const& pre_cuts,
                       TMVA::Reader const& reader) const override;

    std::vector<Doublet> Multiplets(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Doublet Multiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const;

    Doublet Multiplet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2, TMVA::Reader const& reader) const;

    Doublet SubMultiplet(fastjet::PseudoJet const& jet, TMVA::Reader const& reader) const;

    /**
     * @brief signed id of the hadronic W, the event contains two hadronic W with opposite sign 0 is returned
     *
     */

    int WHadronicId(Event const& event) const;

    std::string Name() const final {
        return "WHadronic";
    }

private:

  std::vector<Doublet> Doublets(Jets const& jets, PreCuts const& pre_cuts, Tag tag) const;

  Doublet Doublett(Doublet doublet, PreCuts const& pre_cuts, Tag tag) const;

    std::vector<Doublet> Multiplets(Event const& event, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::vector<Doublet> Multiplets3(Jets const& jets, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Doublet Multiplet(fastjet::PseudoJet const& jet, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Doublet Multiplet(fastjet::PseudoJet const& jet_1, fastjet::PseudoJet const& jet_2, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Doublet SubMultiplet(fastjet::PseudoJet const& jet, PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    bool Problematic(analysis::Doublet const& doublet, analysis::PreCuts const& pre_cuts, Tag tag) const;

    bool Problematic(analysis::Doublet const& doublet, analysis::PreCuts const& pre_cuts) const;

    Doublet Multiplet(analysis::Doublet& doublet, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    std::vector<Doublet> SubMultiplets(analysis::Jets const& jets, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader, size_t sub_jet_number) const;

    std::vector<Doublet> SubMultiplets2(analysis::Jets const& jets, analysis::PreCuts const& pre_cuts, TMVA::Reader const& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Jets WDaughters(Event const& event) const;

    int WHadronicId(analysis::Jets const& daughters) const;

    float w_mass_window_ = 40;
};

}
