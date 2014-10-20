# ifndef HJetPgs_hh
# define HJetPgs_hh

# include "HJet.hh"

/**
 * @brief Pgs Jets
 *
 */
class HJetPgs : public HJet
{

public:

    /**
     * @brief constructor
     *
     */
    HJetPgs();

    /**
     * @brief Destructor
     *
     */
    ~HJetPgs();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets();

private:

    string ClassName() const {

        return ("HJetPgs");

    };

};

#endif
