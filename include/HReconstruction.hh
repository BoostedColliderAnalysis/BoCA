# ifndef HReconstruction_hh
# define HReconstruction_hh

# include "HObject.hh"

/**
 * @brief Higgs Top Discriminator
 *
 *
 */
class HReconstruction : public HObject
{
    
public:
    
    /**
     * @brief constructor
     *
     */
    HReconstruction();
    
    /**
     * @brief destructor
     *
     */
    ~HReconstruction();
    
protected:
    
    /**
     * @brief Get mass drop jet
     *
     * @param  FatJet
     * @return MassDropJet
     */
    PseudoJet GetMassDropJet(const PseudoJet&) const;
    
    /**
     * @brief Filter Jets
     *
     * @param  MassDropJet
     * @return FilteredJet
     */
    PseudoJet GetFilteredJet(const PseudoJet&) const;
        
    string ClassName() const {
        
        return ("HReconstruction");
        
    };
    
};

# endif
