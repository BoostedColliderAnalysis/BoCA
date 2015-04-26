# pragma once

# include "HMva.hh"
# include "TMVA/Factory.h"
# include "TSystem.h"

/**
 * @brief Prepares multivariant analysis
 *
 */
class hanalysis::HFactory : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HFactory(hanalysis::HMva &tagger);

private:

    /**
     * @brief Book MVA methods
     *
     */
    void BookMethods();

    /**
     * @brief Add Variables
     */
    void AddVariables();

    /**
     * @brief Get Trees
     *
     */
    int GetTrees();

    /**
     * @brief Prepare Trainig and Test Trees
     *
     */
    void PrepareTrainingAndTestTree(const int event_number);

    int AddTree(TFile &file, const std::string &tree_name, const bool signal);

    TFile *output_file() const;

    std::string factory_options();

    inline std::string ClassName() const {
        return "HFactory";
    };

    HMva &tagger() const {
        return tagger_;
    }

    TMVA::Factory &factory() {
        return factory_;
    }

    HMva &tagger_;

    TMVA::Factory factory_;

};
