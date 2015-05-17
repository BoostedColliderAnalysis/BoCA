# pragma once

# include "Tagger.hh"
# include "TMVA/Factory.h"
# include "TSystem.h"

/**
 * @brief Prepares multivariant analysis
 *
 */
class analysis::HFactory : public Object
{

public:

    /**
     * @brief Constructor
     *
     */
    HFactory(analysis::Tagger &tagger);

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

    Tagger &tagger() const {
        return tagger_;
    }

    TMVA::Factory &factory() {
        return factory_;
    }

    Tagger &tagger_;

    TMVA::Factory factory_;

};
