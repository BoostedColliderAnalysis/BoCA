# ifndef HFactory_hh
# define HFactory_hh

# include "TFile.h"
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
class hmva::HFactory : public hanalysis::HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HFactory(hmva::HMva *const NewMva);

    /**
     * @brief Destructor
     *
     */
    ~HFactory();

private:

    /**
     * @brief Book MVA methods
     *
     * @return void
     *
     */
    void BookMethods();

    /**
     * @brief ...
     *
     * @return void
     */
    void NewFactory();

    /**
     * @brief ...
     *
     * @return void
     */
    void AddVariables();

    /**
     * @brief ...
     *
     * @return void
     */
    void GetTrees();

    /**
     * @brief ...
     *
     * @return void
     */
    void PrepareTrainingAndTestTree();

    void AddTree(const TFile *const File, const std::string &TreeName, const bool Signal);

    HMva *Mva;

    TMVA::Factory *Factory;

    TFile *OutputFile;

    std::string Verbose;

    std::string Silent;

    std::string VerboseLevel;

    std::string VerbosityLevel;

    std::string Color;

    std::string DefaultOptions;

    inline std::string NameSpaceName() const {
      return "hmva";
    };

    inline std::string ClassName() const {
        return "HFactory";
    };


};

# endif
