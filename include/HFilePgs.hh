# ifndef HFilePgs_hh
# define HFilePgs_hh

# include "TFile.h"
# include "TTree.h"
# include "ExRootAnalysis/ExRootTreeReader.h"

# include "HObject.hh"
# include "ClonesArrays.hh"
# include "RootFile.hh"

/**
 * @brief PGS files
 *
 */
class hanalysis::hpgs::HFile : public hanalysis::RootFile
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
    Strings Paths() const;

    std::string tree_name() const;

//     std::shared_ptr<hanalysis::Event> event();

protected:

    inline std::string NameSpaceName() const {
        return "HPgs";
    }

    virtual inline std::string ClassName() const {
        return "HFile";
    }

private:

};


# endif
