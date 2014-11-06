# ifndef HFilePgs_hh
# define HFilePgs_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "HClonesArray.hh"
# include "HFile.hh"

/**
 * @brief PGS files
 *
 */
class hanalysis::hpgs::HFile : public hanalysis::HFile
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

    string GetTreeName() const;

    hanalysis::HEvent *GetEvent() const;

protected:

    inline string NameSpaceName() const {
        return "HPgs";
    }

    virtual inline string ClassName() const {

        return "HFile";

    };

private:

};


# endif
