# ifndef HFileDelphes_hh
# define HFileDelphes_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "HClonesArray.hh"
# include "HFile.hh"

/**
 * @brief Delphes files
 *
 */
class hanalysis::hdelphes::HFile : public hanalysis::HFile
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
     * @brief Compose file path
     *
     * @return string file path
     */
    string GetFilePath() const;

//     string GetTreeName() const;

    hanalysis::HEvent *GetEvent();

    hanalysis::HClonesArray *GetClonesArrays();

protected:

    inline string NameSpaceName() const {
        return "HDelphes";
    }

    virtual inline string ClassName() const {
        return "HFile";
    };

private:

};


# endif
