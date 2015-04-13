# ifndef HFactory_hh
# define HFactory_hh

# include "TFile.h"
# include "TNamed.h"
# include "TSystem.h"
# include "TClonesArray.h"
# include "TTree.h"
# include "TROOT.h"
# include "TObjArray.h"
// # include "TSystem.h"
# include "TDirectoryFile.h"


# include "ExRootAnalysis/ExRootTreeReader.h"

# include "TMVA/Factory.h"
# include "TMVA/Types.h"
# include "TMVA/Config.h"

# include "HMva.hh"

# include "HObject.hh"

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

    /**
     * @brief Destructor
     *
     */
    ~HFactory();

private:

    /**
     * @brief Book MVA methods
     *
     */
    void BookMethods();

    /**
     * @brief New Factory
     */
    void NewFactory();

    TMVA::Factory & CreateFactory();

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
    void PrepareTrainingAndTestTree(const int EventNumber);

    int AddTree(const TFile &File, const std::string &TreeName, const bool Signal);

    HMva &tagger_;

    TMVA::Factory *Factory;

//     TMVA::Factory factory_;

    TFile *output_file();

    std::string factory_options();

    TFile *OutputFile;

    std::string Verbose;

    std::string Silent;

    std::string VerboseLevel;

    std::string VerbosityLevel;

    std::string Color;

    std::string DefaultOptions;

    inline std::string ClassName() const {
        return "HFactory";
    };


};

# endif
