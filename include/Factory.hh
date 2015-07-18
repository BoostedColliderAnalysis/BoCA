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
class Factory {

public:

    /**
     * @brief Constructor
     *
     */
    Factory(Tagger& tagger);

private:

    /**
     * @brief Book MVA methods
     *
     */
    TMVA::MethodBDT& BookMethods();

    /**
     * @brief Add Variables
     */
    void AddVariables();

    /**
     * @brief Get Trees
     *
     */
    long GetTrees();

    /**
     * @brief Prepare Trainig and Test Trees
     *
     */
    void PrepareTrainingAndTestTree(const long event_number);

    long AddTree(TFile& file, const std::string& tree_name, const analysis::Tag tag);

    TFile* output_file() const;

    std::string factory_options();

    Tagger& tagger() const
    {
        return tagger_;
    }

    TMVA::Factory& factory()
    {
        return factory_;
    }

    Tagger& tagger_;

    TMVA::Factory factory_;

};

}
