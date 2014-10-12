# ifndef HJetPropertiesBranch_hh
# define HJetPropertiesBranch_hh

# include "TObject.h"

/**
 * @brief Class for saving leptons to root
 *
 */
class HJetPropertiesBranch : public TObject
{

public:

    float Mass;
    float Pt;
    float Eta;
    float Phi;
    float Radius;
    float JetPtSum;
    float PtSum;

    HJetPropertiesBranch();

    virtual ~HJetPropertiesBranch();

private:

    void reset();

    ClassDef(HJetPropertiesBranch, 1)

};


/**
 * @brief Class for saving leptons to root
 *
 */
class HConstituentBranch : public TObject
{

public:

  float Eta;
  float Phi;
  float Pt;
  int Id;

  HConstituentBranch();

  virtual ~HConstituentBranch();

private:

  void reset();

  ClassDef(HConstituentBranch, 1)

};

# endif
