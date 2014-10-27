# ifndef HFactory_hh
# define HFactory_hh

# include "TFile.h"
# include "TSystem.h"
# include "TClonesArray.h"
# include "TTree.h"
# include "TROOT.h"


# include "ExRootAnalysis/ExRootTreeReader.h"

# include "TMVA/Factory.h"
# include "TMVA/Types.h"
# include "TMVA/Config.h"

# include "HMva.hh"

# include "HObject.hh"

using TMVA::Types;


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
    HFactory(HMva*);

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

    TFile *OutputFile;

    TMVA::Factory *Factory;

    string Verbose;

    string Silent;

    string VerboseLevel;

    string VerbosityLevel;

    string Color;

    string DefaultOptions;

    void AddTree(const TFile * const, const string, const bool);

    HMva *Mva;

    inline string ClassName() const {

        return ("HFactory");

    };


};

# endif
