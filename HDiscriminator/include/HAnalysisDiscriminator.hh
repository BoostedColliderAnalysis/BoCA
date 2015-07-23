#pragma once

#include "Analysis.hh"
#include "File.hh"
// #include "HEventDelphes.hh"
#include "HBranchDiscriminator.hh"
#include "SubStructure.hh"


namespace hcpvhiggs {

/**
 *
 * @brief JetTag subclass for Discriminator
 *
 */
class JetTag : public analysis::JetTag {

public:

    int GetBranchId(int id, int BranchId);

    const std::set<analysis::Id> HeavyParticles {analysis::Id::top, analysis::Id::CP_violating_higgs, analysis::Id::higgs};

};

/**
 *
 * @brief HAnalysis subclass defining the HiggsCPV Analysis
 *
 * \author Jan Hajer
 *
 */
class HAnalysis { //: public analysis::Analysis

public:

    /**
     * @brief Constructor
     *
     */
    HAnalysis();

    /**
     * @brief Constructor
     *
     */
    ~HAnalysis();

    /**
     * @brief Branch to write Higgs info into
     *
     */
    exroot::TreeBranch* CandidateBranch;

    /**
     * @brief Branch to write Lepton info into
     *
     */
    exroot::TreeBranch* LeptonBranch;

    /**
     * @brief Branch to write constituent info into
     *
     */
    exroot::TreeBranch* constituentBranch;

private:

    long EventNumberMax() const
    {
        return 10000;
    };

    std::string ProjectName() const
    {
        return "Discriminator";
    };

    analysis::JetTag  jet_tag;

    analysis::SubStructure* sub_structure;

    /**
     * @brief Lepton calculations
     *
     * @param event ...
     * @return std::vector< fastjet::PseudoJet, std::allocator< void > >
     */
    analysis::Jets GetLeptonJets(analysis::Event& event);

    /**
     * @brief Lepton event counter
     *
     */
    int LeptoneventCounter;

    /**
     * @brief Main Analysis function
     *
     * @return void
     */
    int RunAnalysis(analysis::Event& event, const std::string& Study);

    /**
     * @brief prepares the std::vector describing the input root files
     *
     * @return void
     */
    std::vector<analysis::File*> GetFiles(const std::string& Name);

    /**
     * @brief New Analysis
     *
     * @return void
     */
    void NewBranches(exroot::TreeWriter* NewTreeWriter);

    analysis::Strings GetStudyNames() const;

};

}
