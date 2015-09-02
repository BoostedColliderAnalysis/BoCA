/**
 * Copyright (C) 2015 Jan Hajer
 */
#pragma once

#include "Identification.hh"
#include "exroot/ExRootAnalysis.hh"
#include "TMVA/Factory.h"

namespace TMVA {
class MethodBDT;
}

namespace boca {

class Tagger;

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
    Trainer(boca::Tagger& tagger, TMVA::Types::EMVA mva);

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

    long AddTree(std::string const& tree_name, boca::Tag tag);

    long Entries(exroot::TreeReader& tree_reader);

    float Weight(exroot::TreeReader& tree_reader);

    TTree &Tree(std::string const& tree_name, boca::Tag tag);

    exroot::TreeReader TreeReader(std::string const& tree_name, Tag tag);

    TFile* OutputFile() const;

    std::string FactoryOptions();

    std::string MethodOptions(TMVA::Types::EMVA mva);

    boca::Tagger& Tagger() const
    {
        return tagger_;
    }

    TMVA::Factory& Factory()
    {
        return factory_;
    }

    boca::Tagger& tagger_;

    TMVA::Factory factory_;

};

}
