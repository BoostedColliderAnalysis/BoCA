# ifndef HBranch_hh
# define HBranch_hh

# include "TObject.h"

/**
 * @brief Basic tree branches
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

/**
 * @brief Class for saving Event informations to root
 *
 */
class HEventBranch : public TObject
{

public:

    float ScalarPtSum;

    HEventBranch();

    virtual ~HEventBranch();

private:

    void reset();

    ClassDef(HEventBranch, 1)

};

/**
 * @brief Class for saving Event informations to root
 *
 */
class HParticleBranch : public TObject
{

public:

    float Pt;
    float Eta;
    float Phi;

    HParticleBranch();

    virtual ~HParticleBranch();

private:

    void reset();

    ClassDef(HParticleBranch, 1)

};

# endif
