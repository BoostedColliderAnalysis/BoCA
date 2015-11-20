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

    int Train(const Event &event, const PreCuts &pre_cuts,
              const Tag Tag) const override;

    virtual int GetBdt(const Event &event, const PreCuts &pre_cuts,
                       const TMVA::Reader &reader) const override;

    std::vector<Doublet> Multiplets(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, const TMVA::Reader& reader) const;

    Doublet SubMultiplet(const fastjet::PseudoJet& jet, const TMVA::Reader& reader) const;

    /**
     * @brief signed id of the hadronic W, the event contains two hadronic W with opposite sign 0 is returned
     *
     */

    int WHadronicId(const Event& event) const;

    std::string Name() const final { return "WHadronic"; }

private:

    std::vector<Doublet> Multiplets(const Event& event, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::vector<Doublet> Multiplets3(const Jets& jets, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet Multiplet(const fastjet::PseudoJet& jet_1, const fastjet::PseudoJet& jet_2, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Doublet SubMultiplet(const fastjet::PseudoJet& jet, const PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    bool Problematic(const analysis::Doublet& doublet, const analysis::PreCuts& pre_cuts, Tag tag) const;

    bool Problematic(const analysis::Doublet& doublet, const analysis::PreCuts& pre_cuts) const;

    Doublet Multiplet(analysis::Doublet& doublet, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    std::vector<Doublet> SubMultiplets(const analysis::Jets& jets, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader, size_t sub_jet_number) const;

    std::vector<Doublet> SubMultiplets2(const analysis::Jets& jets, const analysis::PreCuts& pre_cuts, const TMVA::Reader& reader) const;

    Reader<BottomTagger> bottom_reader_;

    Jets WDaughters(const Event& event) const;

    int WHadronicId(const Jets& jets) const;
    
    Jets Particles(Event const& event) const;

    float w_mass_window_ = 40;
};

}
