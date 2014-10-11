# ifndef HJetTag_hh
# define HJetTag_hh

# include <set>

# include "HObject.hh"

using std::set;

/**
 * @brief small class loading the Branches into ClonesArrays
 *
 */
class HJetTag : public HObject
{

public:

    /**
     * @brief Constructor
     *
     */
    HJetTag();

    /**
     * @brief Destructor
     *
     */
    ~HJetTag();

    virtual int GetBranchId(int, int) const;

protected:

    const set<int> InitialState = {GluonId, UpId, DownId, StrangeId, CharmId, UpDown0Id, UpDown1Id, UpUp1Id, DownDown1Id};

    const set<int> MotherParticle = {BottomId, TopId, HeavyHiggsId};

private:

    virtual string ClassName() const {

        return ("HJetTag");

    };

};

# endif
