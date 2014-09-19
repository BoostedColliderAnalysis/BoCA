# ifndef HConstants_hh
# define HConstants_hh

# include "HObject.hh"

class HConstants : public HObject
{

public:

    HConstants();

    virtual ~HConstants();

protected:

    virtual TString ClassName() {
        return ("HConstants");
    };

    const float HiggsMass;

    const float TopMass;
    
    const float WMass;
    
    /**
     * @brief Physical Muon Mass
     *
     */
    const float MuonMass;
    
    /**
     * @brief Physical Electron Mass
     *
     */
    const float ElectronMass;
    
    const int HiggsUserIndex;
    
    const int TopUserIndex;

private:

};

#endif
