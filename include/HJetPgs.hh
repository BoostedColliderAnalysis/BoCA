# ifndef HJetPgs_hh
# define HJetPgs_hh

# include "HJet.hh"

/**
 * @brief Pgs Jets
 *
 */
class Analysis::HPgs::HJet : public Analysis::HJet
{

public:

    /**
     * @brief constructor
     *
     */
    HJet();

    /**
     * @brief Destructor
     *
     */
    ~HJet();

    /**
     * @brief AnalyseJet calls AnalyseEFlow
     *
     * @return void
     */
    bool GetJets();

private:

    inline string ClassName() const {

        return ("HPgs: HJet");

    };

};

#endif
