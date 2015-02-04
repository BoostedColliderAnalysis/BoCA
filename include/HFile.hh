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
     * @brief constructor defining default path
     *
     */
    HFile();

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const std::string &Process);

    HFile(const std::string &Process, float NewCrosssection);

    HFile(const std::string &Process, float NewCrosssection, float NewMass);

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const std::string &Process, const std::string &Run);

    /**
     * @brief destructor
     *
     */
    virtual ~HFile();

    std::shared_ptr< ExRootTreeReader > GetTreeReader();

    virtual std::shared_ptr<hanalysis::HClonesArray> GetClonesArrays();

    virtual std::shared_ptr<hanalysis::HEvent> GetEvent();

    void SetBasePath(const std::string &NewBasePath) {
        BasePath = NewBasePath;
    }

    /**
     * @brief Name of Process
     *
     */
    std::string GetTitle() const;

    float GetCrosssection() const {
        return Crosssection;
    }

    void SetCrosssection(const float NewCrosssection) {
        Crosssection = NewCrosssection;
    }

    void SetError(const float NewError) {
        Error = NewError;
    }

    void SetMass(const float NewMass) {
        Mass = NewMass;
    }

    void SetFileSuffix(const std::string &NewFileSuffix) {
        FileSuffix = NewFileSuffix;
    }

    float GetError() const {
        return Error;
    }

    float GetMass() const {
        return Mass;
    }


    void SetSnowMass(const bool NewSnowMass) {
        SnowMass = NewSnowMass;
    }

    void SetTreeName(const std::string &NewTreeName) {
        TreeName = NewTreeName;
    }

    /**
     * @brief Compose file path
     *
     * @return std::string file path
     */
    virtual std::string GetFilePath() const;

    virtual std::string GetTreeName() const;

protected:

//     ExRootTreeReader *TreeReader;

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
    std::string ProcessFolder;

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
    static std::string TreeName;

    /**
     * @brief Crosssection of the event
     *
     */
    float Crosssection;

    /**
     * @brief Error of the Crosssection
     *
     */
    float Error;

    float Mass;

    static std::string FileSuffix;

    static bool SnowMass;

//     HEvent * Event = NULL;

//     HClonesArray *ClonesArrays = NULL;

//     std::shared_ptr<HEvent> Event;

//     std::shared_ptr<HClonesArray> ClonesArrays;

private:

    TFile *ImportFile = NULL;
};

# endif
