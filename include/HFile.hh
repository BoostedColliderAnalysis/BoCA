# ifndef HFile_hh
# define HFile_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "HClonesArray.hh"

# include "HEventParton.hh"
# include "HEventPgs.hh"
# include "HEventDelphes.hh"

/**
 * @brief Input file infos
 *
 * ProcessFolder has to be set
 *
 */
class hanalysis::HFile : public HObject
{

public:

    /**
     * @brief constructor
     *
     */
    HFile();

    HFile(const std::string &NewProcess);

    HFile(const std::string &NewProcess, const float NewCrosssection);

    HFile(const std::string &NewProcess, const float NewCrosssection, const float NewMass);
    HFile(const std::string &NewProcess, const std::string &Run);

    HFile(const HStrings &NewProcesses);

    HFile(const HStrings &NewProcesses, const float NewCrosssection);

    HFile(const HStrings &NewProcesses, const float NewCrosssection, const float NewMass);

    /**
     * @brief destructor
     *
     */
    virtual ~HFile();

    std::shared_ptr< ExRootTreeReader > TreeReader();

    virtual std::shared_ptr<hanalysis::HClonesArray> ClonesArrays();

    virtual std::shared_ptr<hanalysis::HEvent> Event();

    void SetBasePath(const std::string &NewBasePath) {
        BasePath = NewBasePath;
    }

    /**
     * @brief Name of Process
     *
     */
    std::string GetTitle() const;

    float Crosssection() const {
        return CrosssectionM;
    }

    void SetCrosssection(const float NewCrosssection) {
        CrosssectionM = NewCrosssection;
    }

    void SetError(const float NewError) {
        ErrorM = NewError;
    }

    void SetMass(const float NewMass) {
        MassM = NewMass;
    }

    void SetFileSuffix(const std::string &NewFileSuffix) {
        FileSuffix = NewFileSuffix;
    }

    float CrosssectionError() const {
        return ErrorM;
    }

    float Mass() const {
        return MassM;
    }


    void SetSnowMass(const bool NewSnowMass) {
        SnowMass = NewSnowMass;
    }

    void SetTreeName(const std::string &NewTreeName) {
        TreeNameM = NewTreeName;
    }

    /**
     * @brief Compose file path
     *
     * @return std::string file path
     */

    virtual std::string TreeName() const;

    virtual HStrings Paths() const;

protected:

    void  SetVariables();

    std::string GetMadGraphFilePath() const;

    virtual inline std::string ClassName() const {
        return "HFile";
    };

    /**
     * @brief Path path to the MadGraph installation
     *
     */
    static std::string BasePath;

    /**
     * @brief Process name used in the file path
     *
     */
    HStrings ProcessFolders;

    /**
     * @brief Run name use in the file path
     *
     */
    std::string RunFolder;

    /**
     * @brief Tag std::string used in the file name
     *
     */
    std::string TagName;

    /**
     * @brief String containing the name of the root tree
     *
     */
    static std::string TreeNameM;

    /**
     * @brief Crosssection of the event
     *
     */
    float CrosssectionM;

    /**
     * @brief Error of the Crosssection
     *
     */
    float ErrorM;

    float MassM;

    static std::string FileSuffix;

    static bool SnowMass;

private:

    TFile *File = NULL;
    TChain * Chain = NULL;
};

# endif
