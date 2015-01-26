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
    HFactory(hanalysis::HMva &NewMva);

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

    int AddTree(const TFile *const File, const std::string &TreeName, const bool Signal);

    HMva *Mva;

    TMVA::Factory *Factory;

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
