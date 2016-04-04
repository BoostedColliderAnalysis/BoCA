/**
 * Copyright (C) 2015-2016 Jan Hajer
 */
#pragma once

#include "TMVA/Factory.h"

#include "multiplets/Identification.hh"

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
    Trainer(boca::Tagger& tagger);

private:

    /**
     * @brief Book MVA methods
     *
     */
    std::vector<double> BookMethod();

    /**
     * @brief Add Variables
     */
    void AddObservables();

    /**
     * @brief Get Trees
     *
     */
    long AddAllTrees();

    long AddTrees(Tag tag);

    /**
     * @brief Prepare Trainig and Test Trees
     *
     */
    void PrepareTrainingAndTestTree(long event_number);

    long AddTree(std::string const& tree_name, Tag tag);

    long Entries(std::string const& tree_name, Tag tag);

    double Weight(std::string const& tree_name, Tag tag);

    TTree &Tree(std::string const& tree_name, Tag tag);

    TFile& OutputFile() const;

    std::string FactoryOptions();

    std::string MethodOptions() const;

    boca::Tagger const& Tagger() const;

    boca::Tagger & Tagger();

    TMVA::Factory const& Factory() const;

    TMVA::Factory& Factory();

    boca::Tagger& tagger_;

    TMVA::Factory factory_;

};

}
