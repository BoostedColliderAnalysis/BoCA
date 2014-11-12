# ifndef HFileParton_hh
# define HFileParton_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "HClonesArray.hh"
# include "HFile.hh"

/**
 * @brief unweighted MadGraph files
 *
 */
class hparton::HFile : public hanalysis::HFile
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

    /**
     * @brief constructor defining default path
     *
     */
    HFile(const std::string &Process, const std::string &Run);

    /**
     * @brief Compose file path
     *
     * @return std::string file path
     */
    std::string GetFilePath() const;

    std::string GetTreeName() const;

    hanalysis::HEvent *GetEvent();

protected:

    inline std::string NameSpaceName() const {
        return "HParton";
    }

    virtual inline std::string ClassName() const {

        return "HFile";

    };

private:

};

# endif
