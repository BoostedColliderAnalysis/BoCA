# ifndef HBranch_hh
# define HBranch_hh

# include "TObject.h"

/**
 * @brief Class for saving leptons to root
 *
 */
class HInfoBranch : public TObject
{

public:

    float Crosssection;
    float Error;
    float EventNumber;

    HInfoBranch();

    virtual ~HInfoBranch();

private:

    void reset();

    ClassDef(HInfoBranch, 1)

};

# endif
