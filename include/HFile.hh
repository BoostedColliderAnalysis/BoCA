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
    HFile(const string &Process);

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const string &Process, const string &Run);

    /**
     * @brief destructor
     *
     */
    virtual ~HFile();

    ExRootTreeReader *GetTreeReader();

    virtual HClonesArray *GetClonesArrays();

    virtual HEvent *GetEvent();

    void SetBasePath(const string &NewBasePath) {
        BasePath = NewBasePath;
    }

    /**
     * @brief Name of Process
     *
     */
    string GetTitle() const;

    float GetCrosssection() const {
        return Crosssection;
    }

    void SetCrosssection(const float NewCrosssection) {
        Crosssection = NewCrosssection;
    }

    void SetError(const float NewError) {
        Crosssection = NewError;
    }

    void SetFileSuffix(const string &NewFileSuffix) {
        FileSuffix = NewFileSuffix;
    }

    float GetError() const {
        return Error;
    }

    void SetSnowMass(const bool NewSnowMass) {
        SnowMass = NewSnowMass;
    }

    void SetTreeName(const string &NewTreeName) {
        TreeName = NewTreeName;
    }

    /**
     * @brief Compose file path
     *
     * @return string file path
     */
    virtual string GetFilePath() const;

    virtual string GetTreeName() const;

protected:

    ExRootTreeReader *TreeReader;

    void  SetVariables();

    string GetMadGraphFilePath() const;

    virtual inline string ClassName() const {
        return "HFile";
    };

    /**
     * @brief Path path to the MadGraph installation
     *
     */
    static string BasePath;

    /**
     * @brief Process name used in the file path
     *
     */
    string ProcessFolder;

    /**
     * @brief Run name use in the file path
     *
     */
    string RunFolder;

    /**
     * @brief Tag string used in the file name
     *
     */
    string TagString;

    /**
     * @brief String containing the name of the root tree
     *
     */
    static string TreeName;

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

    static string FileSuffix;

    static bool SnowMass;

    HEvent * Event;

    HClonesArray *ClonesArrays;

private:

    TFile *ImportFile;

    TTree *ImportTree;

};

# endif
