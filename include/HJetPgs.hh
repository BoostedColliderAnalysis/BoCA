# ifndef HJetPgs_hh
# define HJetPgs_hh

# include "HJet.hh"

/**
 * @brief Pgs Jets
 *
 */
class hanalysis::hpgs::HJet : public hanalysis::HJet
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
    bool GetJets(const HJetDetails JetDetails);

private:

  inline string NameSpaceName() const {
    return "HPgs";
  }

    inline string ClassName() const {

        return "HJet";

    };

};

#endif
