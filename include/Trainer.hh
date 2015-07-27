#pragma once

#include "Tagger.hh"
#include "TMVA/Factory.h"

namespace TMVA {
class MethodBDT;
}


namespace analysis {

/**
 * @brief Prepares multivariant analysis
 *
 */
class Trainer {

public:

    /**
     * @brief Constructor
     *
     */
    Trainer(analysis::Tagger& tagger);

private:

    /**
     * @brief Book MVA methods
     *
     */
    TMVA::MethodBDT& BookMethod(TMVA::Types::EMVA mva);

    /**
     * @brief Add Variables
     */
    void AddVariables();

    /**
     * @brief Get Trees
     *
     */
    long GetTrees();

    long GetTree(Tag tag);

    /**
     * @brief Prepare Trainig and Test Trees
     *
     */
    void PrepareTrainingAndTestTree(long event_number);

    long AddTree(const std::string& tree_name, analysis::Tag tag);

    long Entries(const std::string& tree_name, Tag tag);

    float Weight(const std::string& tree_name, analysis::Tag tag);

    TTree &Tree(const std::string& tree_name, analysis::Tag tag);

    TFile* OutputFile() const;

    std::string FactoryOptions();

    std::string MethodOptions(TMVA::Types::EMVA mva);

    analysis::Tagger& Tagger() const
    {
        return tagger_;
    }

    TMVA::Factory& Factory()
    {
        return factory_;
    }

    analysis::Tagger& tagger_;

    TMVA::Factory factory_;

};

}
